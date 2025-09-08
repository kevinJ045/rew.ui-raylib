#ifndef TEXTURE_GEN_H
#define TEXTURE_GEN_H

#include "raylib.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ColorStop {
    float t;     // 0..1
    Color color; // RGBA
} ColorStop;

// ---------- Generators (return grayscale Image) ----------
Image* TG_Checker(int w, int h, int cellsX, int cellsY);
Image* TG_Gradient(int w, int h, bool vertical);                      // vertical=true: top->bottom
Image* TG_Wave(int w, int h, float freqX, float freqY, float amp, float phase);
Image* TG_Voronoi(int w, int h, int seed, int tileSize);              // uses GenImageCellular

// ---------- Modifiers ----------
Image* TG_ColorRamp(Image* gray, const ColorStop* stops, int count);   // grayscale -> RGB by ramp
Image* TG_Clamp01(Image* img);                                         // ensure 0..255

// ---------- Packing / Conversions ----------
Image* TG_PackMRA(Image* metallicGray, Image* roughnessGray, Image* aoGray); // R=metal, G=rough, B=ao
Image* TG_HeightToNormal(Image* height, float strength);               // height (grayscale) -> tangent-space normal

// ---------- Convenience (Textures) ----------
Texture2D* TG_TextureFromImageAndFree(Image* img);
Texture2D* TG_AlbedoFromField(Image* gray, const ColorStop* stops, int count);
Texture2D* TG_MRAFromFields(Image* m, Image* r, Image* a);
Texture2D* TG_NormalFromHeight(Image* height, float strength);

// ---------- Quick recipes ----------
Texture2D* TG_MakeCheckerAlbedo(int w,int h,int cellsX,int cellsY, Color a, Color b);
Texture2D* TG_MakeVoronoiAlbedo(int w,int h,int seed,int tile, const ColorStop* stops, int count);
Texture2D* TG_MakeWaveGray(int w,int h,float fx,float fy,float amp,float phase); // returns grayscale as RGB
Texture2D* TG_MakeGradientGray(int w,int h,bool vertical);

ColorStop* CreateColorStopsFromArrays(int count, float* many_t, unsigned char* colors);

#ifdef __cplusplus
}
#endif

#endif // TEXTURE_GEN_H
