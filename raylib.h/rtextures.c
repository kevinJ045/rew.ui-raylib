Image* LoadImageWrapper(const char *fileName) {
	Image* result = malloc(sizeof(Image));
	*result = LoadImage(fileName);
	return result;
}

Image* LoadImageRawWrapper(const char *fileName, int width, int height, int format, int headerSize) {
	Image* result = malloc(sizeof(Image));
	*result = LoadImageRaw(fileName, width, height, format, headerSize);
	return result;
}

Image* LoadImageAnimWrapper(const char *fileName, int *frames) {
	Image* result = malloc(sizeof(Image));
	*result = LoadImageAnim(fileName, frames);
	return result;
}

Image* LoadImageAnimFromMemoryWrapper(const char *fileType, const unsigned char *fileData, int dataSize, int *frames) {
	Image* result = malloc(sizeof(Image));
	*result = LoadImageAnimFromMemory(fileType, fileData, dataSize, frames);
	return result;
}

Image* LoadImageFromMemoryWrapper(const char *fileType, const unsigned char *fileData, int dataSize) {
	Image* result = malloc(sizeof(Image));
	*result = LoadImageFromMemory(fileType, fileData, dataSize);
	return result;
}

Image* LoadImageFromTextureWrapper(Texture2D texture) {
	Image* result = malloc(sizeof(Image));
	*result = LoadImageFromTexture(texture);
	return result;
}

Image* LoadImageFromScreenWrapper() {
	Image* result = malloc(sizeof(Image));
	*result = LoadImageFromScreen();
	return result;
}

bool IsImageValidWrapper(Image* image) {
	return IsImageValid(*image);
}

void UnloadImageWrapper(Image* image) {
	UnloadImage(*image);
}

bool ExportImageWrapper(Image* image, const char *fileName) {
	return ExportImage(*image, fileName);
}

bool ExportImageAsCodeWrapper(Image* image, const char *fileName) {
	return ExportImageAsCode(*image, fileName);
}

Image* GenImageColorWrapper(int width, int height, Color* color) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageColor(width, height, *color);
	return result;
}

Image* GenImageGradientLinearWrapper(int width, int height, int direction, Color* start, Color* end) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageGradientLinear(width, height, direction, *start, *end);
	return result;
}

Image* GenImageGradientRadialWrapper(int width, int height, float density, Color* inner, Color* outer) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageGradientRadial(width, height, density, *inner, *outer);
	return result;
}

Image* GenImageGradientSquareWrapper(int width, int height, float density, Color* inner, Color* outer) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageGradientSquare(width, height, density, *inner, *outer);
	return result;
}

Image* GenImageCheckedWrapper(int width, int height, int checksX, int checksY, Color* col1, Color* col2) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageChecked(width, height, checksX, checksY, *col1, *col2);
	return result;
}

Image* GenImageWhiteNoiseWrapper(int width, int height, float factor) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageWhiteNoise(width, height, factor);
	return result;
}

Image* GenImagePerlinNoiseWrapper(int width, int height, int offsetX, int offsetY, float scale) {
	Image* result = malloc(sizeof(Image));
	*result = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
	return result;
}

Image* GenImageCellularWrapper(int width, int height, int tileSize) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageCellular(width, height, tileSize);
	return result;
}

Image* GenImageTextWrapper(int width, int height, const char *text) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageText(width, height, text);
	return result;
}

Image* ImageCopyWrapper(Image* image) {
	Image* result = malloc(sizeof(Image));
	*result = ImageCopy(*image);
	return result;
}

Image* ImageFromImageWrapper(Image* image, Rectangle* rec) {
	Image* result = malloc(sizeof(Image));
	*result = ImageFromImage(*image, *rec);
	return result;
}

Image* ImageFromChannelWrapper(Image* image, int selectedChannel) {
	Image* result = malloc(sizeof(Image));
	*result = ImageFromChannel(*image, selectedChannel);
	return result;
}

Image* ImageTextWrapper(const char *text, int fontSize, Color* color) {
	Image* result = malloc(sizeof(Image));
	*result = ImageText(text, fontSize, *color);
	return result;
}

Image* ImageTextExWrapper(Font* font, const char *text, float fontSize, float spacing, Color* tint) {
	Image* result = malloc(sizeof(Image));
	*result = ImageTextEx(*font, text, fontSize, spacing, *tint);
	return result;
}

void ImageFormatWrapper(Image *image, int newFormat) {
	ImageFormat(image, newFormat);
}

void ImageToPOTWrapper(Image *image, Color* fill) {
	ImageToPOT(image, *fill);
}

void ImageCropWrapper(Image *image, Rectangle* crop) {
	ImageCrop(image, *crop);
}

void ImageAlphaCropWrapper(Image *image, float threshold) {
	ImageAlphaCrop(image, threshold);
}

void ImageAlphaClearWrapper(Image *image, Color* color, float threshold) {
	ImageAlphaClear(image, *color, threshold);
}

void ImageAlphaMaskWrapper(Image *image, Image* alphaMask) {
	ImageAlphaMask(image, *alphaMask);
}

void ImageAlphaPremultiplyWrapper(Image *image) {
	ImageAlphaPremultiply(image);
}

void ImageBlurGaussianWrapper(Image *image, int blurSize) {
	ImageBlurGaussian(image, blurSize);
}

void ImageKernelConvolutionWrapper(Image *image, const float *kernel, int kernelSize) {
	ImageKernelConvolution(image, kernel, kernelSize);
}

void ImageResizeWrapper(Image *image, int newWidth, int newHeight) {
	ImageResize(image, newWidth, newHeight);
}

void ImageResizeNNWrapper(Image *image, int newWidth, int newHeight) {
	ImageResizeNN(image, newWidth, newHeight);
}

void ImageResizeCanvasWrapper(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color* fill) {
	ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, *fill);
}

void ImageMipmapsWrapper(Image *image) {
	ImageMipmaps(image);
}

void ImageDitherWrapper(Image *image, int rBpp, int gBpp, int bBpp, int aBpp) {
	ImageDither(image, rBpp, gBpp, bBpp, aBpp);
}

void ImageFlipVerticalWrapper(Image *image) {
	ImageFlipVertical(image);
}

void ImageFlipHorizontalWrapper(Image *image) {
	ImageFlipHorizontal(image);
}

void ImageRotateWrapper(Image *image, int degrees) {
	ImageRotate(image, degrees);
}

void ImageRotateCWWrapper(Image *image) {
	ImageRotateCW(image);
}

void ImageRotateCCWWrapper(Image *image) {
	ImageRotateCCW(image);
}

void ImageColorTintWrapper(Image *image, Color* color) {
	ImageColorTint(image, *color);
}

void ImageColorInvertWrapper(Image *image) {
	ImageColorInvert(image);
}

void ImageColorGrayscaleWrapper(Image *image) {
	ImageColorGrayscale(image);
}

void ImageColorContrastWrapper(Image *image, float contrast) {
	ImageColorContrast(image, contrast);
}

void ImageColorBrightnessWrapper(Image *image, int brightness) {
	ImageColorBrightness(image, brightness);
}

void ImageColorReplaceWrapper(Image *image, Color* color, Color* replace) {
	ImageColorReplace(image, *color, *replace);
}

void UnloadImageColorsWrapper(Color *colors) {
	UnloadImageColors(colors);
}

void UnloadImagePaletteWrapper(Color *colors) {
	UnloadImagePalette(colors);
}

Rectangle* GetImageAlphaBorderWrapper(Image* image, float threshold) {
	Rectangle* result = malloc(sizeof(Rectangle));
	*result = GetImageAlphaBorder(*image, threshold);
	return result;
}

Color* GetImageColorWrapper(Image* image, int x, int y) {
	Color* result = malloc(sizeof(Color));
	*result = GetImageColor(*image, x, y);
	return result;
}

void ImageClearBackgroundWrapper(Image *dst, Color* color) {
	ImageClearBackground(dst, *color);
}

void ImageDrawPixelWrapper(Image *dst, int posX, int posY, Color* color) {
	ImageDrawPixel(dst, posX, posY, *color);
}

void ImageDrawPixelVWrapper(Image *dst, Vector2* position, Color* color) {
	ImageDrawPixelV(dst, *position, *color);
}

void ImageDrawLineWrapper(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color* color) {
	ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, *color);
}

void ImageDrawLineVWrapper(Image *dst, Vector2* start, Vector2* end, Color* color) {
	ImageDrawLineV(dst, *start, *end, *color);
}

void ImageDrawLineExWrapper(Image *dst, Vector2* start, Vector2* end, int thick, Color* color) {
	ImageDrawLineEx(dst, *start, *end, thick, *color);
}

void ImageDrawCircleWrapper(Image *dst, int centerX, int centerY, int radius, Color* color) {
	ImageDrawCircle(dst, centerX, centerY, radius, *color);
}

void ImageDrawCircleVWrapper(Image *dst, Vector2* center, int radius, Color* color) {
	ImageDrawCircleV(dst, *center, radius, *color);
}

void ImageDrawCircleLinesWrapper(Image *dst, int centerX, int centerY, int radius, Color* color) {
	ImageDrawCircleLines(dst, centerX, centerY, radius, *color);
}

void ImageDrawCircleLinesVWrapper(Image *dst, Vector2* center, int radius, Color* color) {
	ImageDrawCircleLinesV(dst, *center, radius, *color);
}

void ImageDrawRectangleWrapper(Image *dst, int posX, int posY, int width, int height, Color* color) {
	ImageDrawRectangle(dst, posX, posY, width, height, *color);
}

void ImageDrawRectangleVWrapper(Image *dst, Vector2* position, Vector2* size, Color* color) {
	ImageDrawRectangleV(dst, *position, *size, *color);
}

void ImageDrawRectangleRecWrapper(Image *dst, Rectangle* rec, Color* color) {
	ImageDrawRectangleRec(dst, *rec, *color);
}

void ImageDrawRectangleLinesWrapper(Image *dst, Rectangle* rec, int thick, Color* color) {
	ImageDrawRectangleLines(dst, *rec, thick, *color);
}

void ImageDrawTriangleWrapper(Image *dst, Vector2* v1, Vector2* v2, Vector2* v3, Color* color) {
	ImageDrawTriangle(dst, *v1, *v2, *v3, *color);
}

void ImageDrawTriangleExWrapper(Image *dst, Vector2* v1, Vector2* v2, Vector2* v3, Color* c1, Color* c2, Color* c3) {
	ImageDrawTriangleEx(dst, *v1, *v2, *v3, *c1, *c2, *c3);
}

void ImageDrawTriangleLinesWrapper(Image *dst, Vector2* v1, Vector2* v2, Vector2* v3, Color* color) {
	ImageDrawTriangleLines(dst, *v1, *v2, *v3, *color);
}

void ImageDrawTriangleFanWrapper(Image *dst, Vector2 *points, int pointCount, Color* color) {
	ImageDrawTriangleFan(dst, points, pointCount, *color);
}

void ImageDrawTriangleStripWrapper(Image *dst, Vector2 *points, int pointCount, Color* color) {
	ImageDrawTriangleStrip(dst, points, pointCount, *color);
}

void ImageDrawWrapper(Image *dst, Image* src, Rectangle* srcRec, Rectangle* dstRec, Color* tint) {
	ImageDraw(dst, *src, *srcRec, *dstRec, *tint);
}

void ImageDrawTextWrapper(Image *dst, const char *text, int posX, int posY, int fontSize, Color* color) {
	ImageDrawText(dst, text, posX, posY, fontSize, *color);
}

void ImageDrawTextExWrapper(Image *dst, Font* font, const char *text, Vector2* position, float fontSize, float spacing, Color* tint) {
	ImageDrawTextEx(dst, *font, text, *position, fontSize, spacing, *tint);
}

Texture2D LoadTextureWrapper(const char *fileName) {
	return LoadTexture(fileName);
}

Texture2D LoadTextureFromImageWrapper(Image* image) {
	return LoadTextureFromImage(*image);
}

TextureCubemap LoadTextureCubemapWrapper(Image* image, int layout) {
	return LoadTextureCubemap(*image, layout);
}

RenderTexture2D LoadRenderTextureWrapper(int width, int height) {
	return LoadRenderTexture(width, height);
}

bool IsTextureValidWrapper(Texture2D texture) {
	return IsTextureValid(texture);
}

void UnloadTextureWrapper(Texture2D texture) {
	UnloadTexture(texture);
}

bool IsRenderTextureValidWrapper(RenderTexture2D target) {
	return IsRenderTextureValid(target);
}

void UnloadRenderTextureWrapper(RenderTexture2D target) {
	UnloadRenderTexture(target);
}

void UpdateTextureWrapper(Texture2D texture, const void *pixels) {
	UpdateTexture(texture, pixels);
}

void UpdateTextureRecWrapper(Texture2D texture, Rectangle* rec, const void *pixels) {
	UpdateTextureRec(texture, *rec, pixels);
}

void GenTextureMipmapsWrapper(Texture2D *texture) {
	GenTextureMipmaps(texture);
}

void SetTextureFilterWrapper(Texture2D texture, int filter) {
	SetTextureFilter(texture, filter);
}

void SetTextureWrapWrapper(Texture2D texture, int wrap) {
	SetTextureWrap(texture, wrap);
}

void DrawTextureWrapper(Texture2D texture, int posX, int posY, Color* tint) {
	DrawTexture(texture, posX, posY, *tint);
}

void DrawTextureVWrapper(Texture2D texture, Vector2* position, Color* tint) {
	DrawTextureV(texture, *position, *tint);
}

void DrawTextureExWrapper(Texture2D texture, Vector2* position, float rotation, float scale, Color* tint) {
	DrawTextureEx(texture, *position, rotation, scale, *tint);
}

void DrawTextureRecWrapper(Texture2D texture, Rectangle* source, Vector2* position, Color* tint) {
	DrawTextureRec(texture, *source, *position, *tint);
}

void DrawTextureProWrapper(Texture2D texture, Rectangle* source, Rectangle* dest, Vector2* origin, float rotation, Color* tint) {
	DrawTexturePro(texture, *source, *dest, *origin, rotation, *tint);
}

void DrawTextureNPatchWrapper(Texture2D texture, NPatchInfo* nPatchInfo, Rectangle* dest, Vector2* origin, float rotation, Color* tint) {
	DrawTextureNPatch(texture, *nPatchInfo, *dest, *origin, rotation, *tint);
}

bool ColorIsEqualWrapper(Color* col1, Color* col2) {
	return ColorIsEqual(*col1, *col2);
}

Color* FadeWrapper(Color* color, float alpha) {
	Color* result = malloc(sizeof(Color));
	*result = Fade(*color, alpha);
	return result;
}

int ColorToIntWrapper(Color* color) {
	return ColorToInt(*color);
}

Vector4* ColorNormalizeWrapper(Color* color) {
	Vector4* result = malloc(sizeof(Vector4));
	*result = ColorNormalize(*color);
	return result;
}

Color* ColorFromNormalizedWrapper(Vector4* normalized) {
	Color* result = malloc(sizeof(Color));
	*result = ColorFromNormalized(*normalized);
	return result;
}

Vector3* ColorToHSVWrapper(Color* color) {
	Vector3* result = malloc(sizeof(Vector3));
	*result = ColorToHSV(*color);
	return result;
}

Color* ColorFromHSVWrapper(float hue, float saturation, float value) {
	Color* result = malloc(sizeof(Color));
	*result = ColorFromHSV(hue, saturation, value);
	return result;
}

Color* ColorTintWrapper(Color* color, Color* tint) {
	Color* result = malloc(sizeof(Color));
	*result = ColorTint(*color, *tint);
	return result;
}

Color* ColorBrightnessWrapper(Color* color, float factor) {
	Color* result = malloc(sizeof(Color));
	*result = ColorBrightness(*color, factor);
	return result;
}

Color* ColorContrastWrapper(Color* color, float contrast) {
	Color* result = malloc(sizeof(Color));
	*result = ColorContrast(*color, contrast);
	return result;
}

Color* ColorAlphaWrapper(Color* color, float alpha) {
	Color* result = malloc(sizeof(Color));
	*result = ColorAlpha(*color, alpha);
	return result;
}

Color* ColorAlphaBlendWrapper(Color* dst, Color* src, Color* tint) {
	Color* result = malloc(sizeof(Color));
	*result = ColorAlphaBlend(*dst, *src, *tint);
	return result;
}

Color* ColorLerpWrapper(Color* color1, Color* color2, float factor) {
	Color* result = malloc(sizeof(Color));
	*result = ColorLerp(*color1, *color2, factor);
	return result;
}

Color* GetColorWrapper(unsigned int hexValue) {
	Color* result = malloc(sizeof(Color));
	*result = GetColor(hexValue);
	return result;
}

Color* GetPixelColorWrapper(void *srcPtr, int format) {
	Color* result = malloc(sizeof(Color));
	*result = GetPixelColor(srcPtr, format);
	return result;
}

void SetPixelColorWrapper(void *dstPtr, Color* color, int format) {
	SetPixelColor(dstPtr, *color, format);
}

int GetPixelDataSizeWrapper(int width, int height, int format) {
	return GetPixelDataSize(width, height, format);
}
