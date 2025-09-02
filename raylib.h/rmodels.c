void DrawLine3DWrapper(Vector3* startPos, Vector3* endPos, Color* color) {
	DrawLine3D(*startPos, *endPos, *color);
}

void DrawPoint3DWrapper(Vector3* position, Color* color) {
	DrawPoint3D(*position, *color);
}

void DrawCircle3DWrapper(Vector3* center, float radius, Vector3* rotationAxis, float rotationAngle, Color* color) {
	DrawCircle3D(*center, radius, *rotationAxis, rotationAngle, *color);
}

void DrawTriangle3DWrapper(Vector3* v1, Vector3* v2, Vector3* v3, Color* color) {
	DrawTriangle3D(*v1, *v2, *v3, *color);
}

void DrawTriangleStrip3DWrapper(const Vector3 *points, int pointCount, Color* color) {
	DrawTriangleStrip3D(points, pointCount, *color);
}

void DrawCubeWrapper(Vector3* position, float width, float height, float length, Color* color) {
	DrawCube(*position, width, height, length, *color);
}

void DrawCubeVWrapper(Vector3* position, Vector3* size, Color* color) {
	DrawCubeV(*position, *size, *color);
}

void DrawCubeWiresWrapper(Vector3* position, float width, float height, float length, Color* color) {
	DrawCubeWires(*position, width, height, length, *color);
}

void DrawCubeWiresVWrapper(Vector3* position, Vector3* size, Color* color) {
	DrawCubeWiresV(*position, *size, *color);
}

void DrawSphereWrapper(Vector3* centerPos, float radius, Color* color) {
	DrawSphere(*centerPos, radius, *color);
}

void DrawSphereExWrapper(Vector3* centerPos, float radius, int rings, int slices, Color* color) {
	DrawSphereEx(*centerPos, radius, rings, slices, *color);
}

void DrawSphereWiresWrapper(Vector3* centerPos, float radius, int rings, int slices, Color* color) {
	DrawSphereWires(*centerPos, radius, rings, slices, *color);
}

void DrawCylinderWrapper(Vector3* position, float radiusTop, float radiusBottom, float height, int slices, Color* color) {
	DrawCylinder(*position, radiusTop, radiusBottom, height, slices, *color);
}

void DrawCylinderExWrapper(Vector3* startPos, Vector3* endPos, float startRadius, float endRadius, int sides, Color* color) {
	DrawCylinderEx(*startPos, *endPos, startRadius, endRadius, sides, *color);
}

void DrawCylinderWiresWrapper(Vector3* position, float radiusTop, float radiusBottom, float height, int slices, Color* color) {
	DrawCylinderWires(*position, radiusTop, radiusBottom, height, slices, *color);
}

void DrawCylinderWiresExWrapper(Vector3* startPos, Vector3* endPos, float startRadius, float endRadius, int sides, Color* color) {
	DrawCylinderWiresEx(*startPos, *endPos, startRadius, endRadius, sides, *color);
}

void DrawCapsuleWrapper(Vector3* startPos, Vector3* endPos, float radius, int slices, int rings, Color* color) {
	DrawCapsule(*startPos, *endPos, radius, slices, rings, *color);
}

void DrawCapsuleWiresWrapper(Vector3* startPos, Vector3* endPos, float radius, int slices, int rings, Color* color) {
	DrawCapsuleWires(*startPos, *endPos, radius, slices, rings, *color);
}

void DrawPlaneWrapper(Vector3* centerPos, Vector2* size, Color* color) {
	DrawPlane(*centerPos, *size, *color);
}

void DrawRayWrapper(Ray* ray, Color* color) {
	DrawRay(*ray, *color);
}

void DrawGridWrapper(int slices, float spacing) {
	DrawGrid(slices, spacing);
}

Model* LoadModelWrapper(const char *fileName) {
	Model* result = malloc(sizeof(Model));
	*result = LoadModel(fileName);
	return result;
}

Model* LoadModelFromMeshWrapper(Mesh* mesh) {
	Model* result = malloc(sizeof(Model));
	*result = LoadModelFromMesh(*mesh);
	return result;
}

bool IsModelValidWrapper(Model* model) {
	return IsModelValid(*model);
}

void UnloadModelWrapper(Model* model) {
	UnloadModel(*model);
}

BoundingBox* GetModelBoundingBoxWrapper(Model* model) {
	BoundingBox* result = malloc(sizeof(BoundingBox));
	*result = GetModelBoundingBox(*model);
	return result;
}

void DrawModelWrapper(Model* model, Vector3* position, float scale, Color* tint) {
	DrawModel(*model, *position, scale, *tint);
}

void DrawModelExWrapper(Model* model, Vector3* position, Vector3* rotationAxis, float rotationAngle, Vector3* scale, Color* tint) {
	DrawModelEx(*model, *position, *rotationAxis, rotationAngle, *scale, *tint);
}

void DrawModelWiresWrapper(Model* model, Vector3* position, float scale, Color* tint) {
	DrawModelWires(*model, *position, scale, *tint);
}

void DrawModelWiresExWrapper(Model* model, Vector3* position, Vector3* rotationAxis, float rotationAngle, Vector3* scale, Color* tint) {
	DrawModelWiresEx(*model, *position, *rotationAxis, rotationAngle, *scale, *tint);
}

void DrawModelPointsWrapper(Model* model, Vector3* position, float scale, Color* tint) {
	DrawModelPoints(*model, *position, scale, *tint);
}

void DrawModelPointsExWrapper(Model* model, Vector3* position, Vector3* rotationAxis, float rotationAngle, Vector3* scale, Color* tint) {
	DrawModelPointsEx(*model, *position, *rotationAxis, rotationAngle, *scale, *tint);
}

void DrawBoundingBoxWrapper(BoundingBox* box, Color* color) {
	DrawBoundingBox(*box, *color);
}

void DrawBillboardWrapper(Camera* camera, Texture2D texture, Vector3* position, float scale, Color* tint) {
	DrawBillboard(*camera, texture, *position, scale, *tint);
}

void DrawBillboardRecWrapper(Camera* camera, Texture2D texture, Rectangle* source, Vector3* position, Vector2* size, Color* tint) {
	DrawBillboardRec(*camera, texture, *source, *position, *size, *tint);
}

void DrawBillboardProWrapper(Camera* camera, Texture2D texture, Rectangle* source, Vector3* position, Vector3* up, Vector2* size, Vector2* origin, float rotation, Color* tint) {
	DrawBillboardPro(*camera, texture, *source, *position, *up, *size, *origin, rotation, *tint);
}

void UploadMeshWrapper(Mesh *mesh, bool dynamic) {
	UploadMesh(mesh, dynamic);
}

void UpdateMeshBufferWrapper(Mesh* mesh, int index, const void *data, int dataSize, int offset) {
	UpdateMeshBuffer(*mesh, index, data, dataSize, offset);
}

void UnloadMeshWrapper(Mesh* mesh) {
	UnloadMesh(*mesh);
}

void DrawMeshWrapper(Mesh* mesh, Material* material, Matrix* transform) {
	DrawMesh(*mesh, *material, *transform);
}

void DrawMeshInstancedWrapper(Mesh* mesh, Material* material, const Matrix *transforms, int instances) {
	DrawMeshInstanced(*mesh, *material, transforms, instances);
}

BoundingBox* GetMeshBoundingBoxWrapper(Mesh* mesh) {
	BoundingBox* result = malloc(sizeof(BoundingBox));
	*result = GetMeshBoundingBox(*mesh);
	return result;
}

void GenMeshTangentsWrapper(Mesh *mesh) {
	GenMeshTangents(mesh);
}

bool ExportMeshWrapper(Mesh* mesh, const char *fileName) {
	return ExportMesh(*mesh, fileName);
}

bool ExportMeshAsCodeWrapper(Mesh* mesh, const char *fileName) {
	return ExportMeshAsCode(*mesh, fileName);
}

Mesh* GenMeshPolyWrapper(int sides, float radius) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshPoly(sides, radius);
	return result;
}

Mesh* GenMeshPlaneWrapper(float width, float length, int resX, int resZ) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshPlane(width, length, resX, resZ);
	return result;
}

Mesh* GenMeshCubeWrapper(float width, float height, float length) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshCube(width, height, length);
	return result;
}

Mesh* GenMeshSphereWrapper(float radius, int rings, int slices) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshSphere(radius, rings, slices);
	return result;
}

Mesh* GenMeshHemiSphereWrapper(float radius, int rings, int slices) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshHemiSphere(radius, rings, slices);
	return result;
}

Mesh* GenMeshCylinderWrapper(float radius, float height, int slices) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshCylinder(radius, height, slices);
	return result;
}

Mesh* GenMeshConeWrapper(float radius, float height, int slices) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshCone(radius, height, slices);
	return result;
}

Mesh* GenMeshTorusWrapper(float radius, float size, int radSeg, int sides) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshTorus(radius, size, radSeg, sides);
	return result;
}

Mesh* GenMeshKnotWrapper(float radius, float size, int radSeg, int sides) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshKnot(radius, size, radSeg, sides);
	return result;
}

Mesh* GenMeshHeightmapWrapper(Image* heightmap, Vector3* size) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshHeightmap(*heightmap, *size);
	return result;
}

Mesh* GenMeshCubicmapWrapper(Image* cubicmap, Vector3* cubeSize) {
	Mesh* result = malloc(sizeof(Mesh));
	*result = GenMeshCubicmap(*cubicmap, *cubeSize);
	return result;
}

Material* LoadMaterialDefaultWrapper() {
	Material* result = malloc(sizeof(Material));
	*result = LoadMaterialDefault();
	return result;
}

bool IsMaterialValidWrapper(Material* material) {
	return IsMaterialValid(*material);
}

void UnloadMaterialWrapper(Material* material) {
	UnloadMaterial(*material);
}

void SetMaterialTextureWrapper(Material *material, int mapType, Texture2D texture) {
	SetMaterialTexture(material, mapType, texture);
}

void SetModelMeshMaterialWrapper(Model *model, int meshId, int materialId) {
	SetModelMeshMaterial(model, meshId, materialId);
}

void UpdateModelAnimationWrapper(Model* model, ModelAnimation* anim, int frame) {
	UpdateModelAnimation(*model, *anim, frame);
}

void UpdateModelAnimationBonesWrapper(Model* model, ModelAnimation* anim, int frame) {
	UpdateModelAnimationBones(*model, *anim, frame);
}

void UnloadModelAnimationWrapper(ModelAnimation* anim) {
	UnloadModelAnimation(*anim);
}

void UnloadModelAnimationsWrapper(ModelAnimation *animations, int animCount) {
	UnloadModelAnimations(animations, animCount);
}

bool IsModelAnimationValidWrapper(Model* model, ModelAnimation* anim) {
	return IsModelAnimationValid(*model, *anim);
}

bool CheckCollisionSpheresWrapper(Vector3* center1, float radius1, Vector3* center2, float radius2) {
	return CheckCollisionSpheres(*center1, radius1, *center2, radius2);
}

bool CheckCollisionBoxesWrapper(BoundingBox* box1, BoundingBox* box2) {
	return CheckCollisionBoxes(*box1, *box2);
}

bool CheckCollisionBoxSphereWrapper(BoundingBox* box, Vector3* center, float radius) {
	return CheckCollisionBoxSphere(*box, *center, radius);
}

RayCollision* GetRayCollisionSphereWrapper(Ray* ray, Vector3* center, float radius) {
	RayCollision* result = malloc(sizeof(RayCollision));
	*result = GetRayCollisionSphere(*ray, *center, radius);
	return result;
}

RayCollision* GetRayCollisionBoxWrapper(Ray* ray, BoundingBox* box) {
	RayCollision* result = malloc(sizeof(RayCollision));
	*result = GetRayCollisionBox(*ray, *box);
	return result;
}

RayCollision* GetRayCollisionMeshWrapper(Ray* ray, Mesh* mesh, Matrix* transform) {
	RayCollision* result = malloc(sizeof(RayCollision));
	*result = GetRayCollisionMesh(*ray, *mesh, *transform);
	return result;
}

RayCollision* GetRayCollisionTriangleWrapper(Ray* ray, Vector3* p1, Vector3* p2, Vector3* p3) {
	RayCollision* result = malloc(sizeof(RayCollision));
	*result = GetRayCollisionTriangle(*ray, *p1, *p2, *p3);
	return result;
}

RayCollision* GetRayCollisionQuadWrapper(Ray* ray, Vector3* p1, Vector3* p2, Vector3* p3, Vector3* p4) {
	RayCollision* result = malloc(sizeof(RayCollision));
	*result = GetRayCollisionQuad(*ray, *p1, *p2, *p3, *p4);
	return result;
}
