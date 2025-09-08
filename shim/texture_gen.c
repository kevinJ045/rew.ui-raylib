#include "texture_gen.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// ---------- helpers ----------
static inline unsigned char _clampU8(int v){ if(v<0) return 0; if(v>255) return 255; return (unsigned char)v; }
static inline float _saturate(float x){ return (x<0)?0.0f:((x>1)?1.0f:x); }

// Get grayscale 0..1 from Color
static inline float _gray01(Color c){ return (c.r + c.g + c.b) / (255.0f*3.0f); }

// Lerp Color (premult independent channels)
static Color _lerpColor(Color a, Color b, float t){
    Color o;
    o.r = (unsigned char)((1.0f-t)*a.r + t*b.r);
    o.g = (unsigned char)((1.0f-t)*a.g + t*b.g);
    o.b = (unsigned char)((1.0f-t)*a.b + t*b.b);
    o.a = (unsigned char)((1.0f-t)*a.a + t*b.a);
    return o;
}

// Sample a color ramp (stops must be sorted by t ascending)
static Color _sampleRamp(const ColorStop* stops, int count, float t){
    if (count <= 0) return (Color){255,255,255,255};
    if (t <= stops[0].t) return stops[0].color;
    if (t >= stops[count-1].t) return stops[count-1].color;
    for (int i=0; i<count-1; ++i){
        if (t >= stops[i].t && t <= stops[i+1].t){
            float span = stops[i+1].t - stops[i].t;
            float u = (span <= 1e-6f)? 0.0f : (t - stops[i].t)/span;
            return _lerpColor(stops[i].color, stops[i+1].color, _saturate(u));
        }
    }
    return stops[count-1].color;
}

// ---------- Generators (grayscale Images) ----------

Image* TG_Checker(int w, int h, int cellsX, int cellsY){
  if (cellsX < 1) cellsX = 1; if (cellsY < 1) cellsY = 1;
  Image img = GenImageChecked(w, h, w/cellsX, h/cellsY, WHITE, BLACK); // already 2 colors
  // Convert to pure grayscale (in case of filtering later)
  ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
  Color *px = LoadImageColors(img);
  for (int i=0; i<w*h; ++i){
      unsigned char g = (px[i].r > 127)? 255 : 0;
      px[i] = (Color){ g, g, g, 255 };
  }
  Image* i = malloc(sizeof(Image));
  Image newImg = { .data = px, .width=w, .height=h, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
  UnloadImage(img);
  *i = newImg;
  return i; // note: px belongs to newImg now
}

Image* TG_Gradient(int w, int h, bool vertical){
    Image img = GenImageColor(w, h, BLACK);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Color *px = LoadImageColors(img);
    for (int y=0; y<h; ++y){
        for (int x=0; x<w; ++x){
            float t = vertical ? (float)y/(float)(h-1) : (float)x/(float)(w-1);
            unsigned char g = (unsigned char)(t*255.0f + 0.5f);
            px[y*w + x] = (Color){ g, g, g, 255 };
        }
    }
    Image out = { .data = px, .width=w, .height=h, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    UnloadImage(img);
    Image* i = malloc(sizeof(Image));
    *i = out;
    return i;
}

Image* TG_Wave(int w, int h, float freqX, float freqY, float amp, float phase){
    const float TAU = 6.28318530718f;
    Image img = GenImageColor(w, h, BLACK);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Color *px = LoadImageColors(img);
    for (int y=0; y<h; ++y){
        for (int x=0; x<w; ++x){
            float u = (float)x/(float)w;
            float v = (float)y/(float)h;
            float s = sinf(TAU*(u*freqX + v*freqY) + phase);
            float g01 = _saturate(0.5f + 0.5f*s*amp);
            unsigned char g = (unsigned char)(g01*255.0f + 0.5f);
            px[y*w + x] = (Color){ g, g, g, 255 };
        }
    }
    Image out = { .data = px, .width=w, .height=h, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    UnloadImage(img);
    Image* i = malloc(sizeof(Image));
    *i = out;
    return i;
}

Image* TG_Voronoi(int w, int h, int seed, int tileSize){
    if (tileSize < 1) tileSize = 1;
    Image img = GenImageCellular(w, h, tileSize);
    // GenImageCellular returns colored cells; convert to grayscale by luminance
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Color *px = LoadImageColors(img);
    for (int i=0; i<w*h; ++i){
        unsigned char g = (unsigned char)(_gray01(px[i]) * 255.0f + 0.5f);
        px[i] = (Color){ g, g, g, 255 };
    }
    Image out = { .data = px, .width=w, .height=h, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    UnloadImage(img);
    Image* i = malloc(sizeof(Image));
    *i = out;
    return i;
}

// ---------- Modifiers ----------

Image* TG_ColorRamp(Image* grayp, const ColorStop* stops, int count){
    ImageFormat(grayp, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Image gray = *grayp;
    Color *px = LoadImageColors(gray);
    for (int i=0, n=gray.width*gray.height; i<n; ++i){
        float t = px[i].r/255.0f; // grayscale (R=G=B)
        px[i] = _sampleRamp(stops, count, t);
        px[i].a = 255;
    }
    Image out = { .data = px, .width=gray.width, .height=gray.height, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    UnloadImage(gray);
    Image* i = malloc(sizeof(Image));
    *i = out;
    return i;
}

Image* TG_Clamp01(Image* img){
    ImageFormat(img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    return img;
}

// ---------- Packing / Conversions ----------

Image* TG_PackMRA(Image* metallicGray_ptr, Image* roughnessGray_ptr, Image* aoGray_ptr){
    Image metallicGray = *metallicGray_ptr;
    Image roughnessGray = *roughnessGray_ptr;
    Image aoGray = *aoGray_ptr;
    int w = metallicGray.width, h = metallicGray.height;
    // Ensure same size
    if (roughnessGray.width != w || roughnessGray.height != h ||
        aoGray.width != w || aoGray.height != h){
        // Simple nearest resize to match metallic
        ImageResizeNN(&roughnessGray, w, h);
        ImageResizeNN(&aoGray, w, h);
    }
    ImageFormat(&metallicGray, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    ImageFormat(&roughnessGray, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    ImageFormat(&aoGray,        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    Color *pm = LoadImageColors(metallicGray);
    Color *pr = LoadImageColors(roughnessGray);
    Color *pa = LoadImageColors(aoGray);

    Color *out = (Color*)RL_CALLOC(w*h, sizeof(Color));
    for (int i=0; i<w*h; ++i){
        out[i].r = pm[i].r;          // Metallic
        out[i].g = pr[i].r;          // Roughness
        out[i].b = pa[i].r;          // AO
        out[i].a = 255;
    }

    UnloadImage(metallicGray);
    UnloadImage(roughnessGray);
    UnloadImage(aoGray);

    Image img = { .data=out, .width=w, .height=h, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    
    Image* i = malloc(sizeof(Image));
    *i = img;
    return i;
}

Image* TG_HeightToNormal(Image* height, float strength){
    int w = height->width, h = height->height;
    ImageFormat(height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Color *src = LoadImageColors(*height);
    Color *dst = (Color*)RL_CALLOC(w*h, sizeof(Color));

    // Sobel kernels
    int kx[9] = {-1,0,1, -2,0,2, -1,0,1};
    int ky[9] = {-1,-2,-1, 0,0,0, 1,2,1};
    const float inv255 = 1.0f/255.0f;

    for (int y=0; y<h; ++y){
        for (int x=0; x<w; ++x){
            float gx = 0, gy = 0;
            int idx = 0;
            for (int j=-1; j<=1; ++j){
                int yy = (y+j + h) % h;        // wrap for tiling
                for (int i=-1; i<=1; ++i){
                    int xx = (x+i + w) % w;    // wrap
                    float g = src[yy*w + xx].r * inv255; // grayscale
                    gx += g * (float)kx[idx];
                    gy += g * (float)ky[idx];
                    idx++;
                }
            }
            // Derive normal
            float nx = -gx * strength;
            float ny = -gy * strength;
            float nz = 1.0f;
            float len = sqrtf(nx*nx + ny*ny + nz*nz);
            nx /= len; ny /= len; nz /= len;
            unsigned char r = (unsigned char)((nx*0.5f + 0.5f)*255.0f + 0.5f);
            unsigned char g = (unsigned char)((ny*0.5f + 0.5f)*255.0f + 0.5f);
            unsigned char b = (unsigned char)((nz*0.5f + 0.5f)*255.0f + 0.5f);
            dst[y*w + x] = (Color){ r, g, b, 255 };
        }
    }

    UnloadImage(*height);
    RL_FREE(src);

    Image img = { .data=dst, .width=w, .height=h, .mipmaps=1, .format=PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    
    Image* i = malloc(sizeof(Image));
    *i = img;
    return i;
}

// ---------- Convenience (Textures) ----------

Texture2D* TG_TextureFromImageAndFree(Image* img){
    Texture2D* tex = malloc(sizeof(Texture2D));
    *tex = LoadTextureFromImage(*img);
    UnloadImage(*img);
    return tex;
}

Texture2D* TG_AlbedoFromField(Image* gray, const ColorStop* stops, int count){
    Image* img = TG_ColorRamp(gray, stops, count);
    return TG_TextureFromImageAndFree(img);
}

Texture2D* TG_MRAFromFields(Image* m, Image* r, Image* a){
    Image* packed = TG_PackMRA(m, r, a);
    return TG_TextureFromImageAndFree(packed);
}

Texture2D* TG_NormalFromHeight(Image* height, float strength){
    Image* n = TG_HeightToNormal(height, strength);
    return TG_TextureFromImageAndFree(n);
}

// ---------- Quick recipes ----------

Texture2D* TG_MakeCheckerAlbedo(int w,int h,int cellsX,int cellsY, Color c0, Color c1){
    Image* g = TG_Checker(w,h,cellsX,cellsY);
    ColorStop ramp[2] = {
        {0.0f, c0},
        {1.0f, c1}
    };
    return TG_AlbedoFromField(g, ramp, 2);
}

Texture2D* TG_MakeVoronoiAlbedo(int w,int h,int seed,int tile, const ColorStop* stops, int count){
    Image* g = TG_Voronoi(w,h,seed,tile);
    return TG_AlbedoFromField(g, stops, count);
}

Texture2D* TG_MakeWaveGray(int w,int h,float fx,float fy,float amp,float phase){
    Image* g = TG_Wave(w,h,fx,fy,amp,phase);
    // Keep as grayscale RGB (no ramp): just copy channels
    return TG_TextureFromImageAndFree(g);
}

Texture2D* TG_MakeGradientGray(int w,int h,bool vertical){
    Image* g = TG_Gradient(w,h,vertical);
    return TG_TextureFromImageAndFree(g);
}

ColorStop* CreateColorStopsFromArrays(int count, float* many_t, unsigned char* colors) {
    if (!many_t || !colors) return NULL;

    ColorStop* stops = (ColorStop*)malloc(sizeof(ColorStop) * count);
    if (!stops) return NULL;

    for (int i = 0; i < count; i++) {
        stops[i].t = many_t[i];
        stops[i].color.r = colors[i*4 + 0];
        stops[i].color.g = colors[i*4 + 1];
        stops[i].color.b = colors[i*4 + 2];
        stops[i].color.a = colors[i*4 + 3];
    }

    return stops;
}

