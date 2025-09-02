Font* GetFontDefaultWrapper() {
	Font* result = malloc(sizeof(Font));
	*result = GetFontDefault();
	return result;
}

Font* LoadFontWrapper(const char *fileName) {
	Font* result = malloc(sizeof(Font));
	*result = LoadFont(fileName);
	return result;
}

Font* LoadFontExWrapper(const char *fileName, int fontSize, int *codepoints, int codepointCount) {
	Font* result = malloc(sizeof(Font));
	*result = LoadFontEx(fileName, fontSize, codepoints, codepointCount);
	return result;
}

Font* LoadFontFromImageWrapper(Image* image, Color* key, int firstChar) {
	Font* result = malloc(sizeof(Font));
	*result = LoadFontFromImage(*image, *key, firstChar);
	return result;
}

Font* LoadFontFromMemoryWrapper(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, int *codepoints, int codepointCount) {
	Font* result = malloc(sizeof(Font));
	*result = LoadFontFromMemory(fileType, fileData, dataSize, fontSize, codepoints, codepointCount);
	return result;
}

bool IsFontValidWrapper(Font* font) {
	return IsFontValid(*font);
}

Image* GenImageFontAtlasWrapper(const GlyphInfo *glyphs, Rectangle **glyphRecs, int glyphCount, int fontSize, int padding, int packMethod) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageFontAtlas(glyphs, *glyphRecs, glyphCount, fontSize, padding, packMethod);
	return result;
}

void UnloadFontDataWrapper(GlyphInfo *glyphs, int glyphCount) {
	UnloadFontData(glyphs, glyphCount);
}

void UnloadFontWrapper(Font* font) {
	UnloadFont(*font);
}

bool ExportFontAsCodeWrapper(Font* font, const char *fileName) {
	return ExportFontAsCode(*font, fileName);
}

void DrawFPSWrapper(int posX, int posY) {
	DrawFPS(posX, posY);
}

void DrawTextWrapper(const char *text, int posX, int posY, int fontSize, Color* color) {
	DrawText(text, posX, posY, fontSize, *color);
}

void DrawTextExWrapper(Font* font, const char *text, Vector2* position, float fontSize, float spacing, Color* tint) {
	DrawTextEx(*font, text, *position, fontSize, spacing, *tint);
}

void DrawTextProWrapper(Font* font, const char *text, Vector2* position, Vector2* origin, float rotation, float fontSize, float spacing, Color* tint) {
	DrawTextPro(*font, text, *position, *origin, rotation, fontSize, spacing, *tint);
}

void DrawTextCodepointWrapper(Font* font, int codepoint, Vector2* position, float fontSize, Color* tint) {
	DrawTextCodepoint(*font, codepoint, *position, fontSize, *tint);
}

void DrawTextCodepointsWrapper(Font* font, const int *codepoints, int codepointCount, Vector2* position, float fontSize, float spacing, Color* tint) {
	DrawTextCodepoints(*font, codepoints, codepointCount, *position, fontSize, spacing, *tint);
}

void SetTextLineSpacingWrapper(int spacing) {
	SetTextLineSpacing(spacing);
}

int MeasureTextWrapper(const char *text, int fontSize) {
	return MeasureText(text, fontSize);
}

Vector2* MeasureTextExWrapper(Font* font, const char *text, float fontSize, float spacing) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = MeasureTextEx(*font, text, fontSize, spacing);
	return result;
}

int GetGlyphIndexWrapper(Font* font, int codepoint) {
	return GetGlyphIndex(*font, codepoint);
}

GlyphInfo* GetGlyphInfoWrapper(Font* font, int codepoint) {
	GlyphInfo* result = malloc(sizeof(GlyphInfo));
	*result = GetGlyphInfo(*font, codepoint);
	return result;
}

Rectangle* GetGlyphAtlasRecWrapper(Font* font, int codepoint) {
	Rectangle* result = malloc(sizeof(Rectangle));
	*result = GetGlyphAtlasRec(*font, codepoint);
	return result;
}

void UnloadUTF8Wrapper(char *text) {
	UnloadUTF8(text);
}

void UnloadCodepointsWrapper(int *codepoints) {
	UnloadCodepoints(codepoints);
}

int GetCodepointCountWrapper(const char *text) {
	return GetCodepointCount(text);
}

int GetCodepointWrapper(const char *text, int *codepointSize) {
	return GetCodepoint(text, codepointSize);
}

int GetCodepointNextWrapper(const char *text, int *codepointSize) {
	return GetCodepointNext(text, codepointSize);
}

int GetCodepointPreviousWrapper(const char *text, int *codepointSize) {
	return GetCodepointPrevious(text, codepointSize);
}

int TextCopyWrapper(char *dst, const char *src) {
	return TextCopy(dst, src);
}

bool TextIsEqualWrapper(const char *text1, const char *text2) {
	return TextIsEqual(text1, text2);
}

void TextAppendWrapper(char *text, const char *append, int *position) {
	TextAppend(text, append, position);
}

int TextFindIndexWrapper(const char *text, const char *find) {
	return TextFindIndex(text, find);
}

int TextToIntegerWrapper(const char *text) {
	return TextToInteger(text);
}

float TextToFloatWrapper(const char *text) {
	return TextToFloat(text);
}
