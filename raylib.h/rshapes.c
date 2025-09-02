void SetShapesTextureWrapper(Texture2D texture, Rectangle* source) {
	SetShapesTexture(texture, *source);
}

Texture2D GetShapesTextureWrapper() {
	return GetShapesTexture();
}

Rectangle* GetShapesTextureRectangleWrapper() {
	Rectangle* result = malloc(sizeof(Rectangle));
	*result = GetShapesTextureRectangle();
	return result;
}

void DrawPixelWrapper(int posX, int posY, Color* color) {
	DrawPixel(posX, posY, *color);
}

void DrawPixelVWrapper(Vector2* position, Color* color) {
	DrawPixelV(*position, *color);
}

void DrawLineWrapper(int startPosX, int startPosY, int endPosX, int endPosY, Color* color) {
	DrawLine(startPosX, startPosY, endPosX, endPosY, *color);
}

void DrawLineVWrapper(Vector2* startPos, Vector2* endPos, Color* color) {
	DrawLineV(*startPos, *endPos, *color);
}

void DrawLineExWrapper(Vector2* startPos, Vector2* endPos, float thick, Color* color) {
	DrawLineEx(*startPos, *endPos, thick, *color);
}

void DrawLineStripWrapper(const Vector2 *points, int pointCount, Color* color) {
	DrawLineStrip(points, pointCount, *color);
}

void DrawLineBezierWrapper(Vector2* startPos, Vector2* endPos, float thick, Color* color) {
	DrawLineBezier(*startPos, *endPos, thick, *color);
}

void DrawCircleWrapper(int centerX, int centerY, float radius, Color* color) {
	DrawCircle(centerX, centerY, radius, *color);
}

void DrawCircleSectorWrapper(Vector2* center, float radius, float startAngle, float endAngle, int segments, Color* color) {
	DrawCircleSector(*center, radius, startAngle, endAngle, segments, *color);
}

void DrawCircleSectorLinesWrapper(Vector2* center, float radius, float startAngle, float endAngle, int segments, Color* color) {
	DrawCircleSectorLines(*center, radius, startAngle, endAngle, segments, *color);
}

void DrawCircleGradientWrapper(int centerX, int centerY, float radius, Color* inner, Color* outer) {
	DrawCircleGradient(centerX, centerY, radius, *inner, *outer);
}

void DrawCircleVWrapper(Vector2* center, float radius, Color* color) {
	DrawCircleV(*center, radius, *color);
}

void DrawCircleLinesWrapper(int centerX, int centerY, float radius, Color* color) {
	DrawCircleLines(centerX, centerY, radius, *color);
}

void DrawCircleLinesVWrapper(Vector2* center, float radius, Color* color) {
	DrawCircleLinesV(*center, radius, *color);
}

void DrawEllipseWrapper(int centerX, int centerY, float radiusH, float radiusV, Color* color) {
	DrawEllipse(centerX, centerY, radiusH, radiusV, *color);
}

void DrawEllipseLinesWrapper(int centerX, int centerY, float radiusH, float radiusV, Color* color) {
	DrawEllipseLines(centerX, centerY, radiusH, radiusV, *color);
}

void DrawRingWrapper(Vector2* center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color* color) {
	DrawRing(*center, innerRadius, outerRadius, startAngle, endAngle, segments, *color);
}

void DrawRingLinesWrapper(Vector2* center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color* color) {
	DrawRingLines(*center, innerRadius, outerRadius, startAngle, endAngle, segments, *color);
}

void DrawRectangleWrapper(int posX, int posY, int width, int height, Color* color) {
	DrawRectangle(posX, posY, width, height, *color);
}

void DrawRectangleVWrapper(Vector2* position, Vector2* size, Color* color) {
	DrawRectangleV(*position, *size, *color);
}

void DrawRectangleRecWrapper(Rectangle* rec, Color* color) {
	DrawRectangleRec(*rec, *color);
}

void DrawRectangleProWrapper(Rectangle* rec, Vector2* origin, float rotation, Color* color) {
	DrawRectanglePro(*rec, *origin, rotation, *color);
}

void DrawRectangleGradientVWrapper(int posX, int posY, int width, int height, Color* top, Color* bottom) {
	DrawRectangleGradientV(posX, posY, width, height, *top, *bottom);
}

void DrawRectangleGradientHWrapper(int posX, int posY, int width, int height, Color* left, Color* right) {
	DrawRectangleGradientH(posX, posY, width, height, *left, *right);
}

void DrawRectangleGradientExWrapper(Rectangle* rec, Color* topLeft, Color* bottomLeft, Color* topRight, Color* bottomRight) {
	DrawRectangleGradientEx(*rec, *topLeft, *bottomLeft, *topRight, *bottomRight);
}

void DrawRectangleLinesWrapper(int posX, int posY, int width, int height, Color* color) {
	DrawRectangleLines(posX, posY, width, height, *color);
}

void DrawRectangleLinesExWrapper(Rectangle* rec, float lineThick, Color* color) {
	DrawRectangleLinesEx(*rec, lineThick, *color);
}

void DrawRectangleRoundedWrapper(Rectangle* rec, float roundness, int segments, Color* color) {
	DrawRectangleRounded(*rec, roundness, segments, *color);
}

void DrawRectangleRoundedLinesWrapper(Rectangle* rec, float roundness, int segments, Color* color) {
	DrawRectangleRoundedLines(*rec, roundness, segments, *color);
}

void DrawRectangleRoundedLinesExWrapper(Rectangle* rec, float roundness, int segments, float lineThick, Color* color) {
	DrawRectangleRoundedLinesEx(*rec, roundness, segments, lineThick, *color);
}

void DrawTriangleWrapper(Vector2* v1, Vector2* v2, Vector2* v3, Color* color) {
	DrawTriangle(*v1, *v2, *v3, *color);
}

void DrawTriangleLinesWrapper(Vector2* v1, Vector2* v2, Vector2* v3, Color* color) {
	DrawTriangleLines(*v1, *v2, *v3, *color);
}

void DrawTriangleFanWrapper(const Vector2 *points, int pointCount, Color* color) {
	DrawTriangleFan(points, pointCount, *color);
}

void DrawTriangleStripWrapper(const Vector2 *points, int pointCount, Color* color) {
	DrawTriangleStrip(points, pointCount, *color);
}

void DrawPolyWrapper(Vector2* center, int sides, float radius, float rotation, Color* color) {
	DrawPoly(*center, sides, radius, rotation, *color);
}

void DrawPolyLinesWrapper(Vector2* center, int sides, float radius, float rotation, Color* color) {
	DrawPolyLines(*center, sides, radius, rotation, *color);
}

void DrawPolyLinesExWrapper(Vector2* center, int sides, float radius, float rotation, float lineThick, Color* color) {
	DrawPolyLinesEx(*center, sides, radius, rotation, lineThick, *color);
}

void DrawSplineLinearWrapper(const Vector2 *points, int pointCount, float thick, Color* color) {
	DrawSplineLinear(points, pointCount, thick, *color);
}

void DrawSplineBasisWrapper(const Vector2 *points, int pointCount, float thick, Color* color) {
	DrawSplineBasis(points, pointCount, thick, *color);
}

void DrawSplineCatmullRomWrapper(const Vector2 *points, int pointCount, float thick, Color* color) {
	DrawSplineCatmullRom(points, pointCount, thick, *color);
}

void DrawSplineBezierQuadraticWrapper(const Vector2 *points, int pointCount, float thick, Color* color) {
	DrawSplineBezierQuadratic(points, pointCount, thick, *color);
}

void DrawSplineBezierCubicWrapper(const Vector2 *points, int pointCount, float thick, Color* color) {
	DrawSplineBezierCubic(points, pointCount, thick, *color);
}

void DrawSplineSegmentLinearWrapper(Vector2* p1, Vector2* p2, float thick, Color* color) {
	DrawSplineSegmentLinear(*p1, *p2, thick, *color);
}

void DrawSplineSegmentBasisWrapper(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, float thick, Color* color) {
	DrawSplineSegmentBasis(*p1, *p2, *p3, *p4, thick, *color);
}

void DrawSplineSegmentCatmullRomWrapper(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, float thick, Color* color) {
	DrawSplineSegmentCatmullRom(*p1, *p2, *p3, *p4, thick, *color);
}

void DrawSplineSegmentBezierQuadraticWrapper(Vector2* p1, Vector2* c2, Vector2* p3, float thick, Color* color) {
	DrawSplineSegmentBezierQuadratic(*p1, *c2, *p3, thick, *color);
}

void DrawSplineSegmentBezierCubicWrapper(Vector2* p1, Vector2* c2, Vector2* c3, Vector2* p4, float thick, Color* color) {
	DrawSplineSegmentBezierCubic(*p1, *c2, *c3, *p4, thick, *color);
}

Vector2* GetSplinePointLinearWrapper(Vector2* startPos, Vector2* endPos, float t) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetSplinePointLinear(*startPos, *endPos, t);
	return result;
}

Vector2* GetSplinePointBasisWrapper(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, float t) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetSplinePointBasis(*p1, *p2, *p3, *p4, t);
	return result;
}

Vector2* GetSplinePointCatmullRomWrapper(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, float t) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetSplinePointCatmullRom(*p1, *p2, *p3, *p4, t);
	return result;
}

Vector2* GetSplinePointBezierQuadWrapper(Vector2* p1, Vector2* c2, Vector2* p3, float t) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetSplinePointBezierQuad(*p1, *c2, *p3, t);
	return result;
}

Vector2* GetSplinePointBezierCubicWrapper(Vector2* p1, Vector2* c2, Vector2* c3, Vector2* p4, float t) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetSplinePointBezierCubic(*p1, *c2, *c3, *p4, t);
	return result;
}

bool CheckCollisionRecsWrapper(Rectangle* rec1, Rectangle* rec2) {
	return CheckCollisionRecs(*rec1, *rec2);
}

bool CheckCollisionCirclesWrapper(Vector2* center1, float radius1, Vector2* center2, float radius2) {
	return CheckCollisionCircles(*center1, radius1, *center2, radius2);
}

bool CheckCollisionCircleRecWrapper(Vector2* center, float radius, Rectangle* rec) {
	return CheckCollisionCircleRec(*center, radius, *rec);
}

bool CheckCollisionCircleLineWrapper(Vector2* center, float radius, Vector2* p1, Vector2* p2) {
	return CheckCollisionCircleLine(*center, radius, *p1, *p2);
}

bool CheckCollisionPointRecWrapper(Vector2* point, Rectangle* rec) {
	return CheckCollisionPointRec(*point, *rec);
}

bool CheckCollisionPointCircleWrapper(Vector2* point, Vector2* center, float radius) {
	return CheckCollisionPointCircle(*point, *center, radius);
}

bool CheckCollisionPointTriangleWrapper(Vector2* point, Vector2* p1, Vector2* p2, Vector2* p3) {
	return CheckCollisionPointTriangle(*point, *p1, *p2, *p3);
}

bool CheckCollisionPointLineWrapper(Vector2* point, Vector2* p1, Vector2* p2, int threshold) {
	return CheckCollisionPointLine(*point, *p1, *p2, threshold);
}

bool CheckCollisionPointPolyWrapper(Vector2* point, const Vector2 *points, int pointCount) {
	return CheckCollisionPointPoly(*point, points, pointCount);
}

bool CheckCollisionLinesWrapper(Vector2* startPos1, Vector2* endPos1, Vector2* startPos2, Vector2* endPos2, Vector2 *collisionPoint) {
	return CheckCollisionLines(*startPos1, *endPos1, *startPos2, *endPos2, collisionPoint);
}

Rectangle* GetCollisionRecWrapper(Rectangle* rec1, Rectangle* rec2) {
	Rectangle* result = malloc(sizeof(Rectangle));
	*result = GetCollisionRec(*rec1, *rec2);
	return result;
}
