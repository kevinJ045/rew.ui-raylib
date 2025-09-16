#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdlib.h>
#include <string.h>

#include "r3d.h"
#include "texture_gen.h"




typedef struct {
    int type;
    int enabled;
    Vector3 position;
    Vector3 target;
    float color[4];
    float intensity;

    int typeLoc;
    int enabledLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int intensityLoc;
} LightPBR;

Matrix* GetMatrixIdentity(){
  Matrix* v = malloc(sizeof(Matrix));
  *v = MatrixIdentity();
  return v;
}

Vector2* CreateVector2(float x, float y) {
  Vector2* v = malloc(sizeof(Vector2));
  *v = (Vector2){ x, y };
  return v;
}

Vector3* CreateVector3(float x, float y, float z) {
  Vector3* v = malloc(sizeof(Vector3));
  *v = (Vector3){ x, y, z };
  return v;
}

Vector3* Vector3ScaleW(Vector3 *v1, float scale){
  Vector3* v = malloc(sizeof(Vector3));
  *v = Vector3Scale(*v1, scale);
  return v;
}

Vector3* Vector3NormalizeW(Vector3 *v1){
  Vector3* v = malloc(sizeof(Vector3));
  *v = Vector3Normalize(*v1);
  return v;
}

Vector4* ColorNormalizeW(Color color){
  Vector4* v = malloc(sizeof(Vector4));
  *v = ColorNormalize(color);
  return v;
}

void SetVector3Vals(Vector3 *vec3, float x, float y, float z) {
  vec3->x = x;
  vec3->y = y;
  vec3->z = z;
}

Vector4* CreateVector4(float x, float y, float z, float w) {
  Vector4* v = malloc(sizeof(Vector4));
  *v = (Vector4){ x, y, z, w };
  return v;
}

void FreePTRVal(void *v){
  free(v);
}

Matrix* CreateMatrix(
  float m0, float m4, float m8,  float m12,
  float m1, float m5, float m9,  float m13,
  float m2, float m6, float m10, float m14,
  float m3, float m7, float m11, float m15
) {
  Matrix* m = malloc(sizeof(Matrix));
  *m = (Matrix){ m0,m4,m8,m12, m1,m5,m9,m13, m2,m6,m10,m14, m3,m7,m11,m15 };
  return m;
}

Matrix* CreateMatrixWrapper() {
  Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
  if (mat) {
    *mat = (Matrix){0};
  }
  return mat;
}

Rectangle* CreateRectangle(float x, float y, float width, float height) {
  Rectangle* r = malloc(sizeof(Rectangle));
  *r = (Rectangle){ x, y, width, height };
  return r;
}

Color* CreateColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  Color* c = malloc(sizeof(Color));
  *c = (Color){ r, g, b, a };
  return c;
}

Camera2D* CreateCamera2D(Vector2 *offset, Vector2 *target, float rotation, float zoom) {
  Camera2D* c = malloc(sizeof(Camera2D));
  *c = (Camera2D){ *offset, *target, rotation, zoom };
  return c;
}


Camera3D* CreateCamera3D(Vector3 *position, Vector3 *target, float fovy) {
  Camera3D* c = malloc(sizeof(Camera3D));

  c->position = *position;
  c->target = *target;
  c->up = (Vector3){0.0f, 1.0f, 0.0f};
  c->fovy = fovy;
  c->projection = CAMERA_PERSPECTIVE;

  return c;
}

Camera3D* CreateCamera3DOrtho(Vector3 *position, Vector3 *target, float fovy) {
  Camera3D* c = malloc(sizeof(Camera3D));

  c->position = *position;
  c->target = *target;
  c->up = (Vector3){0.0f, 1.0f, 0.0f};
  c->fovy = fovy;
  c->projection = CAMERA_ORTHOGRAPHIC;

  return c;
}


Camera3D* CreateCamera3DDefault(Vector3 *position, Vector3 *target, Vector3* up, float fovy, int projection) {
  Camera3D* c = malloc(sizeof(Camera3D));
  
  c->position = *position;
  c->target = *target;
  c->up = *up;
  c->fovy = fovy;
  c->projection = projection;

  return c;
}


void SetCamera3DPos(Camera3D* c, Vector3 *position) {
  c->position = *position;
}

void SetCamera3DVal(Camera3D* c, Vector3 *position, Vector3 *target, float fovy) {
  c->position = *position;
  c->target = *target;
  c->up = (Vector3){0.0f, 1.0f, 0.0f};
  c->fovy = fovy;
}

void SetMaterialColors(Model *model, Color diffuse, Color specular, Color ambient, Color emission, Color normal) {
  if (!model) return;

  for (int i = 0; i < model->materialCount; i++) {
    Material *mat = &model->materials[i];

    mat->maps[MATERIAL_MAP_DIFFUSE].color = diffuse;

    mat->maps[MATERIAL_MAP_SPECULAR].color = specular;

    mat->maps[MATERIAL_MAP_OCCLUSION].color = ambient;

    mat->maps[MATERIAL_MAP_EMISSION].color = emission;

    mat->maps[MATERIAL_MAP_NORMAL].color = normal;
  }
}
  

void SetMaterialShaderByIndex(Model *model, Shader *shader, int index) {
  if (!model || !shader) return;

  model->materials[index].shader = *shader;
}

void SetMaterialShader(Model *model, Shader *shader) {
  if (!model || !shader) return;

  for (int i = 0; i < model->materialCount; i++) {
    SetMaterialShaderByIndex(model, shader, i);
  }

  // Optional: initialize all material maps to default textures/colors
  // for (int i = 0; i < MATERIAL_MAP_COUNT; i++) {
  //   model->materials[0].maps[i].texture = GetTextureDefault();
  //   model->materials[0].maps[i].color = WHITE;
  //   model->materials[0].maps[i].value = 1.0f;
  // }
}

void SetMaterialTextures(Model *model, Texture2D* diffuse, Texture2D* specular, Texture2D* normal, Texture2D* emission) {
  if (!model) return;

  for (int i = 0; i < model->materialCount; i++) {
    model->materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = *diffuse;
    model->materials[i].maps[MATERIAL_MAP_SPECULAR].texture = *specular;
    model->materials[i].maps[MATERIAL_MAP_NORMAL].texture = *normal;
    model->materials[i].maps[MATERIAL_MAP_EMISSION].texture = *emission;
  }
}

void SetMaterialMapValueByIndex(Model *model, int index, int id, const char* type, void* value) {
  if (!model) return;

  MaterialMap *map = &model->materials[index].maps[id];

  if (strcmp(type, "texture") == 0) {
    map->texture = *(Texture2D *)value;
  }
  else if (strcmp(type, "color") == 0) {
    map->color = *(Color *)value;
  }
  else if (strcmp(type, "value") == 0) {
    map->value = *(float *)value;
  }
}

void SetMaterialMapValue(Model *model, int id, const char* type, void* value) {
  if (!model) return;

  for (int i = 0; i < model->materialCount; i++) {
    SetMaterialMapValueByIndex(model, i, id, type, value);
  }
}

void GetLightViewProj(Camera3D *lightCam, Matrix *outMatrix) {
  if (!lightCam || !outMatrix) return;

  Matrix view = MatrixLookAt(lightCam->position, lightCam->target, lightCam->up);
  Matrix proj = MatrixPerspective(lightCam->fovy * DEG2RAD, 1.0f, 0.1f, 100.0f);
  
  *outMatrix = MatrixMultiply(proj, view);
}

Transform* CreateTransform(Vector3 *translation, float rotation, float scale) {
  Transform* t = malloc(sizeof(Transform));
  *t = (Transform){ *translation, rotation, scale };
  return t;
}

Ray* CreateRay(Vector3* position, Vector3* direction) {
  Ray* r = malloc(sizeof(Ray));
  *r = (Ray){ *position, *direction };
  return r;
}

RayCollision* CreateRayCollision(bool hit, float point, Vector3* normal, float distance) {
  RayCollision* rc = malloc(sizeof(RayCollision));
  *rc = (RayCollision){ hit, point, *normal, distance };
  return rc;
}

BoundingBox* CreateBoundingBox(Vector3* min, Vector3* max) {
  BoundingBox* bb = malloc(sizeof(BoundingBox));
  *bb = (BoundingBox){ *min, *max };
  return bb;
}
  
void UpdateModelAnimationWrapper2(Model *model, ModelAnimation *anim, int index, int frame){
  UpdateModelAnimation(*model, anim[index], frame);
}


void SetShaderLoc(Shader *shader, int id, const char *name){
  shader->locs[id] = GetShaderLocation(*shader, name);
}

RenderTexture2D* LoadShadowmapRenderTexture(int width, int height)
{
  RenderTexture2D* tex = malloc(sizeof(RenderTexture2D));
  RenderTexture2D target = { 0 };

  target.id = rlLoadFramebuffer();
  target.texture.width = width;
  target.texture.height = height;

  if (target.id > 0)
  {
    rlEnableFramebuffer(target.id);

    target.depth.id = rlLoadTextureDepth(width, height, false);
    target.depth.width = width;
    target.depth.height = height;
    target.depth.format = 19; 
    target.depth.mipmaps = 1;

    rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

    rlDisableFramebuffer();
  }
  else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

  *tex = target;
  return tex;
}

Vector3* GetCameraPosition(Camera3D* cam){
  Vector3* v = malloc(sizeof(Vector3));
  *v = cam->position;
  return v;
}

Matrix* GetMatrixModelviewWrapper(){
  Matrix* v = malloc(sizeof(Matrix));
  *v = rlGetMatrixModelview();
  return v;
}

Matrix* GetMatrixProjectionWrapper(){
  Matrix* v = malloc(sizeof(Matrix));
  *v = rlGetMatrixProjection();
  return v;
}

Matrix* MatrixMultiplyW(Matrix *mat1, Matrix *mat2){
  Matrix* v = malloc(sizeof(Matrix));
  *v = MatrixMultiply(*mat1, *mat2);
  return v;
}

Matrix* MatrixTranslateW(int x, int y, int z){
  Matrix* v = malloc(sizeof(Matrix));
  *v = MatrixTranslate(x, y, z);
  return v;
}

Matrix* MatrixScaleW(int x, int y, int z){
  Matrix* v = malloc(sizeof(Matrix));
  *v = MatrixScale(x, y, z);
  return v;
}

Matrix* MatrixRotateZYXW(Vector3 *vec){
  Matrix* v = malloc(sizeof(Matrix));
  *v = MatrixRotateZYX(*vec);
  return v;
}


void DoStuffPls(Shader *shadowShader, RenderTexture2D *shadowMap, int shadowMapLoc){
  rlEnableShader(shadowShader->id);
  int slot = 10;
  rlActiveTextureSlot(10);
  rlEnableTexture(shadowMap->depth.id);
  rlSetUniform(shadowMapLoc, &slot, SHADER_UNIFORM_INT, 1);
}

static int lightCount = 0;

void UpdateLightPBR(Shader *shader_ptr, LightPBR *light_ptr)
{
  LightPBR light = *light_ptr;
  Shader shader = *shader_ptr;

  SetShaderValue(shader, light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
  SetShaderValue(shader, light.typeLoc, &light.type, SHADER_UNIFORM_INT);

  float position[3] = { light.position.x, light.position.y, light.position.z };
  SetShaderValue(shader, light.positionLoc, position, SHADER_UNIFORM_VEC3);

  float target[3] = { light.target.x, light.target.y, light.target.z };
  SetShaderValue(shader, light.targetLoc, target, SHADER_UNIFORM_VEC3);
  SetShaderValue(shader, light.colorLoc, light.color, SHADER_UNIFORM_VEC4);
  SetShaderValue(shader, light.intensityLoc, &light.intensity, SHADER_UNIFORM_FLOAT);
}

LightPBR* CreateLightPBR(int maxl, int type, Vector3 *position, Vector3 *target, Color color, float intensity, Shader *shader)
{
  LightPBR* light = malloc(sizeof(LightPBR));

  if (lightCount < maxl)
  {
    light->enabled = 1;
    light->type = type;
    light->position = *position;
    light->target = *target;
    light->color[0] = (float)color.r/255.0f;
    light->color[1] = (float)color.g/255.0f;
    light->color[2] = (float)color.b/255.0f;
    light->color[3] = (float)color.a/255.0f;
    light->intensity = intensity;

    light->enabledLoc = GetShaderLocation(*shader, TextFormat("lights[%i].enabled", lightCount));
    light->typeLoc = GetShaderLocation(*shader, TextFormat("lights[%i].type", lightCount));
    light->positionLoc = GetShaderLocation(*shader, TextFormat("lights[%i].position", lightCount));
    light->targetLoc = GetShaderLocation(*shader, TextFormat("lights[%i].target", lightCount));
    light->colorLoc = GetShaderLocation(*shader, TextFormat("lights[%i].color", lightCount));
    light->intensityLoc = GetShaderLocation(*shader, TextFormat("lights[%i].intensity", lightCount));

    UpdateLightPBR(shader, light);

    lightCount++;
  }

  return light;
}

void SetLightPBRPos(LightPBR *light, Vector3 *position){
  light->position = *position;
}


R3D_Material* R3D_Model_GetMaterial(R3D_Model* model, int material_index) {
    if (!model || material_index < 0 || material_index >= model->materialCount) {
      model->materials[material_index] = R3D_GetDefaultMaterial();
    }
    return &model->materials[material_index];
}

void R3D_Material_SetAlbedoColor(R3D_Material* material, Color color) {
    if (material) material->albedo.color = color;
}

void R3D_Material_SetAlbedoTexture(R3D_Material* material, Texture2D* texture) {
    if (material) material->albedo.texture = *texture;
}

void R3D_Material_SetEmissionColor(R3D_Material* material, Color color) {
    if (material) material->emission.color = color;
}

void R3D_Material_SetEmissionEnergy(R3D_Material* material, float energy) {
    if (material) material->emission.energy = energy;
}

void R3D_Material_SetNormalTexture(R3D_Material* material, Texture2D* texture) {
    if (material) material->normal.texture = *texture;
}

void R3D_Material_SetNormalScale(R3D_Material* material, float scale) {
    if (material) material->normal.scale = scale;
}

void R3D_Material_SetORMTexture(R3D_Material* material, Texture2D* texture) {
    if (material) material->orm.texture = *texture;
}

void R3D_Material_SetORMOcclusion(R3D_Material* material, float occlusion) {
    if (material) material->orm.occlusion = occlusion;
}

void R3D_Material_SetORMRoughness(R3D_Material* material, float roughness) {
    if (material) material->orm.roughness = roughness;
}

void R3D_Material_SetORMMetalness(R3D_Material* material, float metalness) {
    if (material) material->orm.metalness = metalness;
}

void R3D_Material_SetBlendMode(R3D_Material* material, int blendMode) {
    if (material) material->blendMode = (R3D_BlendMode)blendMode;
}

void R3D_Material_SetCullMode(R3D_Material* material, int cullMode) {
    if (material) material->cullMode = (R3D_CullMode)cullMode;
}

void R3D_Material_SetUVOffset(R3D_Material* material, Vector2* offset) {
    if (material) material->uvOffset = *offset;
}

void R3D_Material_SetUVScale(R3D_Material* material, Vector2* scale) {
    if (material) material->uvScale = *scale;
}

void R3D_Material_SetAlphaCutoff(R3D_Material* material, float cutoff) {
    if (material) material->alphaCutoff = cutoff;
}



void R3D_InitWrapper(int resWidth, int resHeight, unsigned int flags) {
	R3D_Init(resWidth, resHeight, flags);
}

void R3D_CloseWrapper() {
	R3D_Close();
}

bool R3D_HasStateWrapper(unsigned int flag) {
	return R3D_HasState(flag);
}

void R3D_SetStateWrapper(unsigned int flags) {
	R3D_SetState(flags);
}

void R3D_ClearStateWrapper(unsigned int flags) {
	R3D_ClearState(flags);
}

void R3D_GetResolutionWrapper(int* width, int* height) {
	R3D_GetResolution(width, height);
}

void R3D_UpdateResolutionWrapper(int width, int height) {
	R3D_UpdateResolution(width, height);
}

void R3D_SetSceneBoundsWrapper(BoundingBox* sceneBounds) {
	R3D_SetSceneBounds(*sceneBounds);
}

void R3D_SetTextureFilterWrapper(TextureFilter filter) {
	R3D_SetTextureFilter(filter);
}

R3D_Layer R3D_GetActiveLayersWrapper() {
	return R3D_GetActiveLayers();
}

void R3D_SetActiveLayersWrapper(R3D_Layer layers) {
	R3D_SetActiveLayers(layers);
}

void R3D_EnableLayersWrapper(R3D_Layer bitfield) {
	R3D_EnableLayers(bitfield);
}

void R3D_DisableLayersWrapper(R3D_Layer bitfield) {
	R3D_DisableLayers(bitfield);
}

void R3D_BeginWrapper(Camera3D* camera) {
	R3D_Begin(*camera);
}

void R3D_BeginExWrapper(Camera3D* camera, const RenderTexture* target) {
	R3D_BeginEx(*camera, target);
}

void R3D_EndWrapper() {
	R3D_End();
}

void R3D_DrawMeshWrapper(const R3D_Mesh* mesh, const R3D_Material* material, Matrix* transform) {
	R3D_DrawMesh(mesh, material, *transform);
}

void R3D_DrawMeshInstancedWrapper(const R3D_Mesh* mesh, const R3D_Material* material, const Matrix* instanceTransforms, int instanceCount) {
	R3D_DrawMeshInstanced(mesh, material, instanceTransforms, instanceCount);
}

void R3D_DrawMeshInstancedExWrapper(const R3D_Mesh* mesh, const R3D_Material* material, const Matrix* instanceTransforms, const Color* instanceColors, int instanceCount) {
	R3D_DrawMeshInstancedEx(mesh, material, instanceTransforms, instanceColors, instanceCount);
}

void R3D_DrawModelWrapper(const R3D_Model* model, Vector3* position, float scale) {
	R3D_DrawModel(model, *position, scale);
}

void R3D_DrawModelExWrapper(const R3D_Model* model, Vector3* position, Vector3* rotationAxis, float rotationAngle, Vector3* scale) {
	R3D_DrawModelEx(model, *position, *rotationAxis, rotationAngle, *scale);
}

void R3D_DrawModelProWrapper(const R3D_Model* model, Matrix* transform) {
	R3D_DrawModelPro(model, *transform);
}

void R3D_DrawModelInstancedWrapper(const R3D_Model* model, const Matrix* instanceTransforms, int instanceCount) {
	R3D_DrawModelInstanced(model, instanceTransforms, instanceCount);
}

void R3D_DrawModelInstancedExWrapper(const R3D_Model* model, const Matrix* instanceTransforms, const Color* instanceColors, int instanceCount) {
	R3D_DrawModelInstancedEx(model, instanceTransforms, instanceColors, instanceCount);
}

void R3D_DrawSpriteWrapper(const R3D_Sprite* sprite, Vector3* position) {
	R3D_DrawSprite(sprite, *position);
}

void R3D_DrawSpriteExWrapper(const R3D_Sprite* sprite, Vector3* position, Vector2* size, float rotation) {
	R3D_DrawSpriteEx(sprite, *position, *size, rotation);
}

void R3D_DrawSpriteProWrapper(const R3D_Sprite* sprite, Vector3* position, Vector2* size, Vector3* rotationAxis, float rotationAngle) {
	R3D_DrawSpritePro(sprite, *position, *size, *rotationAxis, rotationAngle);
}

void R3D_DrawSpriteInstancedWrapper(const R3D_Sprite* sprite, const Matrix* instanceTransforms, int instanceCount) {
	R3D_DrawSpriteInstanced(sprite, instanceTransforms, instanceCount);
}

void R3D_DrawSpriteInstancedExWrapper(const R3D_Sprite* sprite, const Matrix* instanceTransforms, const Color* instanceColors, int instanceCount) {
	R3D_DrawSpriteInstancedEx(sprite, instanceTransforms, instanceColors, instanceCount);
}

void R3D_DrawParticleSystemWrapper(const R3D_ParticleSystem* system, const R3D_Mesh* mesh, const R3D_Material* material) {
	R3D_DrawParticleSystem(system, mesh, material);
}

void R3D_DrawParticleSystemExWrapper(const R3D_ParticleSystem* system, const R3D_Mesh* mesh, const R3D_Material* material, Matrix* transform) {
	R3D_DrawParticleSystemEx(system, mesh, material, *transform);
}

R3D_Mesh* R3D_GenMeshPolyWrapper(int sides, float radius, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshPoly(sides, radius, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshPlaneWrapper(float width, float length, int resX, int resZ, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshPlane(width, length, resX, resZ, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshCubeWrapper(float width, float height, float length, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshCube(width, height, length, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshSphereWrapper(float radius, int rings, int slices, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshSphere(radius, rings, slices, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshHemiSphereWrapper(float radius, int rings, int slices, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshHemiSphere(radius, rings, slices, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshCylinderWrapper(float radius, float height, int slices, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshCylinder(radius, height, slices, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshConeWrapper(float radius, float height, int slices, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshCone(radius, height, slices, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshTorusWrapper(float radius, float size, int radSeg, int sides, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshTorus(radius, size, radSeg, sides, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshKnotWrapper(float radius, float size, int radSeg, int sides, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshKnot(radius, size, radSeg, sides, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshHeightmapWrapper(Image* heightmap, Vector3* size, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshHeightmap(*heightmap, *size, upload);
	return result;
}

R3D_Mesh* R3D_GenMeshCubicmapWrapper(Image* cubicmap, Vector3* cubeSize, bool upload) {
	R3D_Mesh* result = malloc(sizeof(R3D_Mesh));
	*result = R3D_GenMeshCubicmap(*cubicmap, *cubeSize, upload);
	return result;
}

void R3D_UnloadMeshWrapper(const R3D_Mesh* mesh) {
	R3D_UnloadMesh(mesh);
}

bool R3D_UploadMeshWrapper(R3D_Mesh* mesh, bool dynamic) {
	return R3D_UploadMesh(mesh, dynamic);
}

bool R3D_UpdateMeshWrapper(R3D_Mesh* mesh) {
	return R3D_UpdateMesh(mesh);
}

void R3D_UpdateMeshBoundingBoxWrapper(R3D_Mesh* mesh) {
	R3D_UpdateMeshBoundingBox(mesh);
}

R3D_Material* R3D_GetDefaultMaterialWrapper() {
	R3D_Material* result = malloc(sizeof(R3D_Material));
	*result = R3D_GetDefaultMaterial();
	return result;
}

void R3D_UnloadMaterialWrapper(const R3D_Material* material) {
	R3D_UnloadMaterial(material);
}

R3D_Model* R3D_LoadModelWrapper(const char* filePath) {
	R3D_Model* result = malloc(sizeof(R3D_Model));
	*result = R3D_LoadModel(filePath);
	return result;
}

R3D_Model* R3D_LoadModelFromMemoryWrapper(const char* fileType, const void* data, unsigned int size) {
	R3D_Model* result = malloc(sizeof(R3D_Model));
	*result = R3D_LoadModelFromMemory(fileType, data, size);
	return result;
}

R3D_Model* R3D_LoadModelFromMeshWrapper(const R3D_Mesh* mesh) {
	R3D_Model* result = malloc(sizeof(R3D_Model));
	*result = R3D_LoadModelFromMesh(mesh);
	return result;
}

void R3D_UnloadModelWrapper(const R3D_Model* model, bool unloadMaterials) {
	R3D_UnloadModel(model, unloadMaterials);
}

void R3D_UpdateModelBoundingBoxWrapper(R3D_Model* model, bool updateMeshBoundingBoxes) {
	R3D_UpdateModelBoundingBox(model, updateMeshBoundingBoxes);
}

R3D_ModelAnimation* R3D_LoadModelAnimationsWrapper(const char* fileName, int* animCount, int targetFrameRate) {
	return R3D_LoadModelAnimations(fileName, animCount, targetFrameRate);
}

R3D_ModelAnimation* R3D_LoadModelAnimationsFromMemoryWrapper(const char* fileType, const void* data, unsigned int size, int* animCount, int targetFrameRate) {
	return R3D_LoadModelAnimationsFromMemory(fileType, data, size, animCount, targetFrameRate);
}

void R3D_UnloadModelAnimationsWrapper(R3D_ModelAnimation* animations, int animCount) {
	R3D_UnloadModelAnimations(animations, animCount);
}

R3D_ModelAnimation* R3D_GetModelAnimationWrapper(R3D_ModelAnimation* animations, int animCount, const char* name) {
	return R3D_GetModelAnimation(animations, animCount, name);
}

void R3D_ListModelAnimationsWrapper(R3D_ModelAnimation* animations, int animCount) {
	R3D_ListModelAnimations(animations, animCount);
}

void R3D_SetModelImportScaleWrapper(float value) {
	R3D_SetModelImportScale(value);
}

R3D_Light* R3D_CreateLightWrapper(R3D_LightType type) {
	R3D_Light* result = malloc(sizeof(R3D_Light));
	*result = R3D_CreateLight(type);
	return result;
}

void R3D_DestroyLightWrapper(R3D_Light* id) {
	R3D_DestroyLight(*id);
}

bool R3D_IsLightExistWrapper(R3D_Light* id) {
	return R3D_IsLightExist(*id);
}

R3D_LightType R3D_GetLightTypeWrapper(R3D_Light* id) {
	return R3D_GetLightType(*id);
}

bool R3D_IsLightActiveWrapper(R3D_Light* id) {
	return R3D_IsLightActive(*id);
}

void R3D_ToggleLightWrapper(R3D_Light* id) {
	R3D_ToggleLight(*id);
}

void R3D_SetLightActiveWrapper(R3D_Light* id, bool active) {
	R3D_SetLightActive(*id, active);
}

Color R3D_GetLightColorWrapper(R3D_Light* id) {
	return R3D_GetLightColor(*id);
}

Vector3* R3D_GetLightColorVWrapper(R3D_Light* id) {
	Vector3* result = malloc(sizeof(Vector3));
	*result = R3D_GetLightColorV(*id);
	return result;
}

void R3D_SetLightColorWrapper(R3D_Light* id, Color color) {
	R3D_SetLightColor(*id, color);
}

void R3D_SetLightColorVWrapper(R3D_Light* id, Vector3* color) {
	R3D_SetLightColorV(*id, *color);
}

Vector3* R3D_GetLightPositionWrapper(R3D_Light* id) {
	Vector3* result = malloc(sizeof(Vector3));
	*result = R3D_GetLightPosition(*id);
	return result;
}

void R3D_SetLightPositionWrapper(R3D_Light* id, Vector3* position) {
	R3D_SetLightPosition(*id, *position);
}

Vector3* R3D_GetLightDirectionWrapper(R3D_Light* id) {
	Vector3* result = malloc(sizeof(Vector3));
	*result = R3D_GetLightDirection(*id);
	return result;
}

void R3D_SetLightDirectionWrapper(R3D_Light* id, Vector3* direction) {
	R3D_SetLightDirection(*id, *direction);
}

void R3D_LightLookAtWrapper(R3D_Light* id, Vector3* position, Vector3* target) {
	R3D_LightLookAt(*id, *position, *target);
}

float R3D_GetLightEnergyWrapper(R3D_Light* id) {
	return R3D_GetLightEnergy(*id);
}

void R3D_SetLightEnergyWrapper(R3D_Light* id, float energy) {
	R3D_SetLightEnergy(*id, energy);
}

float R3D_GetLightSpecularWrapper(R3D_Light* id) {
	return R3D_GetLightSpecular(*id);
}

void R3D_SetLightSpecularWrapper(R3D_Light* id, float specular) {
	R3D_SetLightSpecular(*id, specular);
}

float R3D_GetLightRangeWrapper(R3D_Light* id) {
	return R3D_GetLightRange(*id);
}

void R3D_SetLightRangeWrapper(R3D_Light* id, float range) {
	R3D_SetLightRange(*id, range);
}

float R3D_GetLightAttenuationWrapper(R3D_Light* id) {
	return R3D_GetLightAttenuation(*id);
}

void R3D_SetLightAttenuationWrapper(R3D_Light* id, float attenuation) {
	R3D_SetLightAttenuation(*id, attenuation);
}

float R3D_GetLightInnerCutOffWrapper(R3D_Light* id) {
	return R3D_GetLightInnerCutOff(*id);
}

void R3D_SetLightInnerCutOffWrapper(R3D_Light* id, float degrees) {
	R3D_SetLightInnerCutOff(*id, degrees);
}

float R3D_GetLightOuterCutOffWrapper(R3D_Light* id) {
	return R3D_GetLightOuterCutOff(*id);
}

void R3D_SetLightOuterCutOffWrapper(R3D_Light* id, float degrees) {
	R3D_SetLightOuterCutOff(*id, degrees);
}

void R3D_EnableShadowWrapper(R3D_Light* id, int resolution) {
	R3D_EnableShadow(*id, resolution);
}

void R3D_DisableShadowWrapper(R3D_Light* id, bool destroyMap) {
	R3D_DisableShadow(*id, destroyMap);
}

bool R3D_IsShadowEnabledWrapper(R3D_Light* id) {
	return R3D_IsShadowEnabled(*id);
}

bool R3D_HasShadowMapWrapper(R3D_Light* id) {
	return R3D_HasShadowMap(*id);
}

R3D_ShadowUpdateMode R3D_GetShadowUpdateModeWrapper(R3D_Light* id) {
	return R3D_GetShadowUpdateMode(*id);
}

void R3D_SetShadowUpdateModeWrapper(R3D_Light* id, R3D_ShadowUpdateMode mode) {
	R3D_SetShadowUpdateMode(*id, mode);
}

int R3D_GetShadowUpdateFrequencyWrapper(R3D_Light* id) {
	return R3D_GetShadowUpdateFrequency(*id);
}

void R3D_SetShadowUpdateFrequencyWrapper(R3D_Light* id, int msec) {
	R3D_SetShadowUpdateFrequency(*id, msec);
}

void R3D_UpdateShadowMapWrapper(R3D_Light* id) {
	R3D_UpdateShadowMap(*id);
}

float R3D_GetShadowSoftnessWrapper(R3D_Light* id) {
	return R3D_GetShadowSoftness(*id);
}

void R3D_SetShadowSoftnessWrapper(R3D_Light* id, float softness) {
	R3D_SetShadowSoftness(*id, softness);
}

float R3D_GetShadowDepthBiasWrapper(R3D_Light* id) {
	return R3D_GetShadowDepthBias(*id);
}

void R3D_SetShadowDepthBiasWrapper(R3D_Light* id, float value) {
	R3D_SetShadowDepthBias(*id, value);
}

float R3D_GetShadowSlopeBiasWrapper(R3D_Light* id) {
	return R3D_GetShadowSlopeBias(*id);
}

void R3D_SetShadowSlopeBiasWrapper(R3D_Light* id, float value) {
	R3D_SetShadowSlopeBias(*id, value);
}

BoundingBox* R3D_GetLightBoundingBoxWrapper(R3D_Light* light) {
	BoundingBox* result = malloc(sizeof(BoundingBox));
	*result = R3D_GetLightBoundingBox(*light);
	return result;
}

void R3D_DrawLightShapeWrapper(R3D_Light* id) {
	R3D_DrawLightShape(*id);
}

R3D_ParticleSystem* R3D_LoadParticleSystemWrapper(int maxParticles) {
	R3D_ParticleSystem* result = malloc(sizeof(R3D_ParticleSystem));
	*result = R3D_LoadParticleSystem(maxParticles);
	return result;
}

void R3D_UnloadParticleSystemWrapper(R3D_ParticleSystem* system) {
	R3D_UnloadParticleSystem(system);
}

bool R3D_EmitParticleWrapper(R3D_ParticleSystem* system) {
	return R3D_EmitParticle(system);
}

void R3D_UpdateParticleSystemWrapper(R3D_ParticleSystem* system, float deltaTime) {
	R3D_UpdateParticleSystem(system, deltaTime);
}

void R3D_CalculateParticleSystemBoundingBoxWrapper(R3D_ParticleSystem* system) {
	R3D_CalculateParticleSystemBoundingBox(system);
}

R3D_Sprite* R3D_LoadSpriteWrapper(Texture2D* texture, int xFrameCount, int yFrameCount) {
	R3D_Sprite* result = malloc(sizeof(R3D_Sprite));
	*result = R3D_LoadSprite(*texture, xFrameCount, yFrameCount);
	return result;
}

void R3D_UnloadSpriteWrapper(const R3D_Sprite* sprite) {
	R3D_UnloadSprite(sprite);
}

void R3D_UpdateSpriteWrapper(R3D_Sprite* sprite, float speed) {
	R3D_UpdateSprite(sprite, speed);
}

void R3D_UpdateSpriteExWrapper(R3D_Sprite* sprite, int firstFrame, int lastFrame, float speed) {
	R3D_UpdateSpriteEx(sprite, firstFrame, lastFrame, speed);
}

R3D_InterpolationCurve* R3D_LoadInterpolationCurveWrapper(int capacity) {
	R3D_InterpolationCurve* result = malloc(sizeof(R3D_InterpolationCurve));
	*result = R3D_LoadInterpolationCurve(capacity);
	return result;
}

void R3D_UnloadInterpolationCurveWrapper(R3D_InterpolationCurve* curve) {
	R3D_UnloadInterpolationCurve(*curve);
}

bool R3D_AddKeyframeWrapper(R3D_InterpolationCurve* curve, float time, float value) {
	return R3D_AddKeyframe(curve, time, value);
}

float R3D_EvaluateCurveWrapper(R3D_InterpolationCurve* curve, float time) {
	return R3D_EvaluateCurve(*curve, time);
}

void R3D_SetBackgroundColorWrapper(Color color) {
	R3D_SetBackgroundColor(color);
}

void R3D_SetAmbientColorWrapper(Color color) {
	R3D_SetAmbientColor(color);
}

void R3D_EnableSkyboxWrapper(R3D_Skybox* skybox) {
	R3D_EnableSkybox(*skybox);
}

void R3D_DisableSkyboxWrapper() {
	R3D_DisableSkybox();
}

void R3D_SetSkyboxRotationWrapper(float pitch, float yaw, float roll) {
	R3D_SetSkyboxRotation(pitch, yaw, roll);
}

Vector3* R3D_GetSkyboxRotationWrapper() {
	Vector3* result = malloc(sizeof(Vector3));
	*result = R3D_GetSkyboxRotation();
	return result;
}

void R3D_SetSkyboxIntensityWrapper(float background, float ambient, float reflection) {
	R3D_SetSkyboxIntensity(background, ambient, reflection);
}

void R3D_GetSkyboxIntensityWrapper(float* background, float* ambient, float* reflection) {
	R3D_GetSkyboxIntensity(background, ambient, reflection);
}

void R3D_SetSSAOWrapper(bool enabled) {
	R3D_SetSSAO(enabled);
}

bool R3D_GetSSAOWrapper() {
	return R3D_GetSSAO();
}

void R3D_SetSSAORadiusWrapper(float value) {
	R3D_SetSSAORadius(value);
}

float R3D_GetSSAORadiusWrapper() {
	return R3D_GetSSAORadius();
}

void R3D_SetSSAOBiasWrapper(float value) {
	R3D_SetSSAOBias(value);
}

float R3D_GetSSAOBiasWrapper() {
	return R3D_GetSSAOBias();
}

void R3D_SetSSAOIterationsWrapper(int value) {
	R3D_SetSSAOIterations(value);
}

int R3D_GetSSAOIterationsWrapper() {
	return R3D_GetSSAOIterations();
}

void R3D_SetSSAOIntensityWrapper(float value) {
	R3D_SetSSAOIntensity(value);
}

float R3D_GetSSAOIntensityWrapper() {
	return R3D_GetSSAOIntensity();
}

void R3D_SetSSAOPowerWrapper(float value) {
	R3D_SetSSAOPower(value);
}

float R3D_GetSSAOPowerWrapper() {
	return R3D_GetSSAOPower();
}

void R3D_SetSSAOLightAffectWrapper(float value) {
	R3D_SetSSAOLightAffect(value);
}

float R3D_GetSSAOLightAffectWrapper() {
	return R3D_GetSSAOLightAffect();
}

void R3D_SetBloomModeWrapper(R3D_Bloom mode) {
	R3D_SetBloomMode(mode);
}

R3D_Bloom R3D_GetBloomModeWrapper() {
	return R3D_GetBloomMode();
}

void R3D_SetBloomLevelsWrapper(int value) {
	R3D_SetBloomLevels(value);
}

int R3D_GetBloomLevelsWrapper() {
	return R3D_GetBloomLevels();
}

void R3D_SetBloomIntensityWrapper(float value) {
	R3D_SetBloomIntensity(value);
}

float R3D_GetBloomIntensityWrapper() {
	return R3D_GetBloomIntensity();
}

void R3D_SetBloomFilterRadiusWrapper(int value) {
	R3D_SetBloomFilterRadius(value);
}

int R3D_GetBloomFilterRadiusWrapper() {
	return R3D_GetBloomFilterRadius();
}

void R3D_SetBloomThresholdWrapper(float value) {
	R3D_SetBloomThreshold(value);
}

float R3D_GetBloomThresholdWrapper() {
	return R3D_GetBloomThreshold();
}

void R3D_SetBloomSoftThresholdWrapper(float value) {
	R3D_SetBloomSoftThreshold(value);
}

float R3D_GetBloomSoftThresholdWrapper() {
	return R3D_GetBloomSoftThreshold();
}

void R3D_SetSSRWrapper(bool enabled) {
	R3D_SetSSR(enabled);
}

bool R3D_GetSSRWrapper() {
	return R3D_GetSSR();
}

void R3D_SetSSRMaxRayStepsWrapper(int maxRaySteps) {
	R3D_SetSSRMaxRaySteps(maxRaySteps);
}

int R3D_GetSSRMaxRayStepsWrapper() {
	return R3D_GetSSRMaxRaySteps();
}

void R3D_SetSSRBinarySearchStepsWrapper(int binarySearchSteps) {
	R3D_SetSSRBinarySearchSteps(binarySearchSteps);
}

int R3D_GetSSRBinarySearchStepsWrapper() {
	return R3D_GetSSRBinarySearchSteps();
}

void R3D_SetSSRRayMarchLengthWrapper(float rayMarchLength) {
	R3D_SetSSRRayMarchLength(rayMarchLength);
}

float R3D_GetSSRRayMarchLengthWrapper() {
	return R3D_GetSSRRayMarchLength();
}

void R3D_SetSSRDepthThicknessWrapper(float depthThickness) {
	R3D_SetSSRDepthThickness(depthThickness);
}

float R3D_GetSSRDepthThicknessWrapper() {
	return R3D_GetSSRDepthThickness();
}

void R3D_SetSSRDepthToleranceWrapper(float depthTolerance) {
	R3D_SetSSRDepthTolerance(depthTolerance);
}

float R3D_GetSSRDepthToleranceWrapper() {
	return R3D_GetSSRDepthTolerance();
}

void R3D_SetSSRScreenEdgeFadeWrapper(float start, float end) {
	R3D_SetSSRScreenEdgeFade(start, end);
}

void R3D_GetSSRScreenEdgeFadeWrapper(float* start, float* end) {
	R3D_GetSSRScreenEdgeFade(start, end);
}

void R3D_SetFogModeWrapper(R3D_Fog mode) {
	R3D_SetFogMode(mode);
}

R3D_Fog R3D_GetFogModeWrapper() {
	return R3D_GetFogMode();
}

void R3D_SetFogColorWrapper(Color color) {
	R3D_SetFogColor(color);
}

Color R3D_GetFogColorWrapper() {
	return R3D_GetFogColor();
}

void R3D_SetFogStartWrapper(float value) {
	R3D_SetFogStart(value);
}

float R3D_GetFogStartWrapper() {
	return R3D_GetFogStart();
}

void R3D_SetFogEndWrapper(float value) {
	R3D_SetFogEnd(value);
}

float R3D_GetFogEndWrapper() {
	return R3D_GetFogEnd();
}

void R3D_SetFogDensityWrapper(float value) {
	R3D_SetFogDensity(value);
}

float R3D_GetFogDensityWrapper() {
	return R3D_GetFogDensity();
}

void R3D_SetFogSkyAffectWrapper(float value) {
	R3D_SetFogSkyAffect(value);
}

float R3D_GetFogSkyAffectWrapper() {
	return R3D_GetFogSkyAffect();
}

void R3D_SetDofModeWrapper(R3D_Dof mode) {
	R3D_SetDofMode(mode);
}

R3D_Dof R3D_GetDofModeWrapper() {
	return R3D_GetDofMode();
}

void R3D_SetDofFocusPointWrapper(float value) {
	R3D_SetDofFocusPoint(value);
}

float R3D_GetDofFocusPointWrapper() {
	return R3D_GetDofFocusPoint();
}

void R3D_SetDofFocusScaleWrapper(float value) {
	R3D_SetDofFocusScale(value);
}

float R3D_GetDofFocusScaleWrapper() {
	return R3D_GetDofFocusScale();
}

void R3D_SetDofMaxBlurSizeWrapper(float value) {
	R3D_SetDofMaxBlurSize(value);
}

float R3D_GetDofMaxBlurSizeWrapper() {
	return R3D_GetDofMaxBlurSize();
}

void R3D_SetDofDebugModeWrapper(bool enabled) {
	R3D_SetDofDebugMode(enabled);
}

bool R3D_GetDofDebugModeWrapper() {
	return R3D_GetDofDebugMode();
}

void R3D_SetTonemapModeWrapper(R3D_Tonemap mode) {
	R3D_SetTonemapMode(mode);
}

R3D_Tonemap R3D_GetTonemapModeWrapper() {
	return R3D_GetTonemapMode();
}

void R3D_SetTonemapExposureWrapper(float value) {
	R3D_SetTonemapExposure(value);
}

float R3D_GetTonemapExposureWrapper() {
	return R3D_GetTonemapExposure();
}

void R3D_SetTonemapWhiteWrapper(float value) {
	R3D_SetTonemapWhite(value);
}

float R3D_GetTonemapWhiteWrapper() {
	return R3D_GetTonemapWhite();
}

void R3D_SetBrightnessWrapper(float value) {
	R3D_SetBrightness(value);
}

float R3D_GetBrightnessWrapper() {
	return R3D_GetBrightness();
}

void R3D_SetContrastWrapper(float value) {
	R3D_SetContrast(value);
}

float R3D_GetContrastWrapper() {
	return R3D_GetContrast();
}

void R3D_SetSaturationWrapper(float value) {
	R3D_SetSaturation(value);
}

float R3D_GetSaturationWrapper() {
	return R3D_GetSaturation();
}

R3D_Skybox* R3D_LoadSkyboxWrapper(const char* fileName, CubemapLayout layout) {
	R3D_Skybox* result = malloc(sizeof(R3D_Skybox));
	*result = R3D_LoadSkybox(fileName, layout);
	return result;
}

R3D_Skybox* R3D_LoadSkyboxFromMemoryWrapper(Image* image, CubemapLayout layout) {
	R3D_Skybox* result = malloc(sizeof(R3D_Skybox));
	*result = R3D_LoadSkyboxFromMemory(*image, layout);
	return result;
}

R3D_Skybox* R3D_LoadSkyboxPanoramaWrapper(const char* fileName, int size) {
	R3D_Skybox* result = malloc(sizeof(R3D_Skybox));
	*result = R3D_LoadSkyboxPanorama(fileName, size);
	return result;
}

R3D_Skybox* R3D_LoadSkyboxPanoramaFromMemoryWrapper(Image* image, int size) {
	R3D_Skybox* result = malloc(sizeof(R3D_Skybox));
	*result = R3D_LoadSkyboxPanoramaFromMemory(*image, size);
	return result;
}

void R3D_UnloadSkyboxWrapper(R3D_Skybox* sky) {
	R3D_UnloadSkybox(*sky);
}

bool R3D_IsPointInFrustumWrapper(Vector3* position) {
	return R3D_IsPointInFrustum(*position);
}

bool R3D_IsSphereInFrustumWrapper(Vector3* position, float radius) {
	return R3D_IsSphereInFrustum(*position, radius);
}

bool R3D_IsAABBInFrustumWrapper(BoundingBox* aabb) {
	return R3D_IsAABBInFrustum(*aabb);
}

bool R3D_IsOBBInFrustumWrapper(BoundingBox* aabb, Matrix* transform) {
	return R3D_IsOBBInFrustum(*aabb, *transform);
}

bool R3D_IsPointInFrustumBoundingBoxWrapper(Vector3* position) {
	return R3D_IsPointInFrustumBoundingBox(*position);
}

bool R3D_IsSphereInFrustumBoundingBoxWrapper(Vector3* position, float radius) {
	return R3D_IsSphereInFrustumBoundingBox(*position, radius);
}

bool R3D_IsAABBInFrustumBoundingBoxWrapper(BoundingBox* aabb) {
	return R3D_IsAABBInFrustumBoundingBox(*aabb);
}

Texture2D* R3D_GetWhiteTextureWrapper() {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = R3D_GetWhiteTexture();
	return result;
}

Texture2D* R3D_GetBlackTextureWrapper() {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = R3D_GetBlackTexture();
	return result;
}

Texture2D* R3D_GetNormalTextureWrapper() {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = R3D_GetNormalTexture();
	return result;
}

Texture2D* R3D_GetBufferColorWrapper() {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = R3D_GetBufferColor();
	return result;
}

Texture2D* R3D_GetBufferNormalWrapper() {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = R3D_GetBufferNormal();
	return result;
}

Texture2D* R3D_GetBufferDepthWrapper() {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = R3D_GetBufferDepth();
	return result;
}

Matrix* R3D_GetMatrixViewWrapper() {
	Matrix* result = malloc(sizeof(Matrix));
	*result = R3D_GetMatrixView();
	return result;
}

Matrix* R3D_GetMatrixInvViewWrapper() {
	Matrix* result = malloc(sizeof(Matrix));
	*result = R3D_GetMatrixInvView();
	return result;
}

Matrix* R3D_GetMatrixProjectionWrapper() {
	Matrix* result = malloc(sizeof(Matrix));
	*result = R3D_GetMatrixProjection();
	return result;
}

Matrix* R3D_GetMatrixInvProjectionWrapper() {
	Matrix* result = malloc(sizeof(Matrix));
	*result = R3D_GetMatrixInvProjection();
	return result;
}

void R3D_DrawBufferAlbedoWrapper(float x, float y, float w, float h) {
	R3D_DrawBufferAlbedo(x, y, w, h);
}

void R3D_DrawBufferEmissionWrapper(float x, float y, float w, float h) {
	R3D_DrawBufferEmission(x, y, w, h);
}

void R3D_DrawBufferNormalWrapper(float x, float y, float w, float h) {
	R3D_DrawBufferNormal(x, y, w, h);
}

void R3D_DrawBufferORMWrapper(float x, float y, float w, float h) {
	R3D_DrawBufferORM(x, y, w, h);
}

void R3D_DrawBufferSSAOWrapper(float x, float y, float w, float h) {
	R3D_DrawBufferSSAO(x, y, w, h);
}

void R3D_DrawBufferBloomWrapper(float x, float y, float w, float h) {
	R3D_DrawBufferBloom(x, y, w, h);
}


Wave* LoadWaveWrapper(const char *fileName) {
	Wave* result = malloc(sizeof(Wave));
	*result = LoadWave(fileName);
	return result;
}

Wave* LoadWaveFromMemoryWrapper(const char *fileType, const unsigned char *fileData, int dataSize) {
	Wave* result = malloc(sizeof(Wave));
	*result = LoadWaveFromMemory(fileType, fileData, dataSize);
	return result;
}

bool IsWaveValidWrapper(Wave* wave) {
	return IsWaveValid(*wave);
}

Sound* LoadSoundWrapper(const char *fileName) {
	Sound* result = malloc(sizeof(Sound));
	*result = LoadSound(fileName);
	return result;
}

Sound* LoadSoundFromWaveWrapper(Wave* wave) {
	Sound* result = malloc(sizeof(Sound));
	*result = LoadSoundFromWave(*wave);
	return result;
}

Sound* LoadSoundAliasWrapper(Sound* source) {
	Sound* result = malloc(sizeof(Sound));
	*result = LoadSoundAlias(*source);
	return result;
}

bool IsSoundValidWrapper(Sound* sound) {
	return IsSoundValid(*sound);
}

void UpdateSoundWrapper(Sound* sound, const void *data, int sampleCount) {
	UpdateSound(*sound, data, sampleCount);
}

void UnloadWaveWrapper(Wave* wave) {
	UnloadWave(*wave);
}

void UnloadSoundWrapper(Sound* sound) {
	UnloadSound(*sound);
}

void UnloadSoundAliasWrapper(Sound* alias) {
	UnloadSoundAlias(*alias);
}

bool ExportWaveWrapper(Wave* wave, const char *fileName) {
	return ExportWave(*wave, fileName);
}

bool ExportWaveAsCodeWrapper(Wave* wave, const char *fileName) {
	return ExportWaveAsCode(*wave, fileName);
}

void PlaySoundWrapper(Sound* sound) {
	PlaySound(*sound);
}

void StopSoundWrapper(Sound* sound) {
	StopSound(*sound);
}

void PauseSoundWrapper(Sound* sound) {
	PauseSound(*sound);
}

void ResumeSoundWrapper(Sound* sound) {
	ResumeSound(*sound);
}

bool IsSoundPlayingWrapper(Sound* sound) {
	return IsSoundPlaying(*sound);
}

void SetSoundVolumeWrapper(Sound* sound, float volume) {
	SetSoundVolume(*sound, volume);
}

void SetSoundPitchWrapper(Sound* sound, float pitch) {
	SetSoundPitch(*sound, pitch);
}

void SetSoundPanWrapper(Sound* sound, float pan) {
	SetSoundPan(*sound, pan);
}

Wave* WaveCopyWrapper(Wave* wave) {
	Wave* result = malloc(sizeof(Wave));
	*result = WaveCopy(*wave);
	return result;
}

Music* LoadMusicStreamWrapper(const char *fileName) {
	Music* result = malloc(sizeof(Music));
	*result = LoadMusicStream(fileName);
	return result;
}

Music* LoadMusicStreamFromMemoryWrapper(const char *fileType, const unsigned char *data, int dataSize) {
	Music* result = malloc(sizeof(Music));
	*result = LoadMusicStreamFromMemory(fileType, data, dataSize);
	return result;
}

bool IsMusicValidWrapper(Music* music) {
	return IsMusicValid(*music);
}

void UnloadMusicStreamWrapper(Music* music) {
	UnloadMusicStream(*music);
}

void PlayMusicStreamWrapper(Music* music) {
	PlayMusicStream(*music);
}

bool IsMusicStreamPlayingWrapper(Music* music) {
	return IsMusicStreamPlaying(*music);
}

void UpdateMusicStreamWrapper(Music* music) {
	UpdateMusicStream(*music);
}

void StopMusicStreamWrapper(Music* music) {
	StopMusicStream(*music);
}

void PauseMusicStreamWrapper(Music* music) {
	PauseMusicStream(*music);
}

void ResumeMusicStreamWrapper(Music* music) {
	ResumeMusicStream(*music);
}

void SeekMusicStreamWrapper(Music* music, float position) {
	SeekMusicStream(*music, position);
}

void SetMusicVolumeWrapper(Music* music, float volume) {
	SetMusicVolume(*music, volume);
}

void SetMusicPitchWrapper(Music* music, float pitch) {
	SetMusicPitch(*music, pitch);
}

void SetMusicPanWrapper(Music* music, float pan) {
	SetMusicPan(*music, pan);
}

float GetMusicTimeLengthWrapper(Music* music) {
	return GetMusicTimeLength(*music);
}

float GetMusicTimePlayedWrapper(Music* music) {
	return GetMusicTimePlayed(*music);
}

AudioStream* LoadAudioStreamWrapper(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels) {
	AudioStream* result = malloc(sizeof(AudioStream));
	*result = LoadAudioStream(sampleRate, sampleSize, channels);
	return result;
}

bool IsAudioStreamValidWrapper(AudioStream* stream) {
	return IsAudioStreamValid(*stream);
}

void UnloadAudioStreamWrapper(AudioStream* stream) {
	UnloadAudioStream(*stream);
}

void UpdateAudioStreamWrapper(AudioStream* stream, const void *data, int frameCount) {
	UpdateAudioStream(*stream, data, frameCount);
}

bool IsAudioStreamProcessedWrapper(AudioStream* stream) {
	return IsAudioStreamProcessed(*stream);
}

void PlayAudioStreamWrapper(AudioStream* stream) {
	PlayAudioStream(*stream);
}

void PauseAudioStreamWrapper(AudioStream* stream) {
	PauseAudioStream(*stream);
}

void ResumeAudioStreamWrapper(AudioStream* stream) {
	ResumeAudioStream(*stream);
}

bool IsAudioStreamPlayingWrapper(AudioStream* stream) {
	return IsAudioStreamPlaying(*stream);
}

void StopAudioStreamWrapper(AudioStream* stream) {
	StopAudioStream(*stream);
}

void SetAudioStreamVolumeWrapper(AudioStream* stream, float volume) {
	SetAudioStreamVolume(*stream, volume);
}

void SetAudioStreamPitchWrapper(AudioStream* stream, float pitch) {
	SetAudioStreamPitch(*stream, pitch);
}

void SetAudioStreamPanWrapper(AudioStream* stream, float pan) {
	SetAudioStreamPan(*stream, pan);
}

void SetAudioStreamCallbackWrapper(AudioStream* stream, AudioCallback callback) {
	SetAudioStreamCallback(*stream, callback);
}

void AttachAudioStreamProcessorWrapper(AudioStream* stream, AudioCallback processor) {
	AttachAudioStreamProcessor(*stream, processor);
}

void DetachAudioStreamProcessorWrapper(AudioStream* stream, AudioCallback processor) {
	DetachAudioStreamProcessor(*stream, processor);
}


void SetWindowIconWrapper(Image* image) {
	SetWindowIcon(*image);
}

Vector2* GetMonitorPositionWrapper(int monitor) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetMonitorPosition(monitor);
	return result;
}

Vector2* GetWindowPositionWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetWindowPosition();
	return result;
}

Vector2* GetWindowScaleDPIWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetWindowScaleDPI();
	return result;
}

Image* GetClipboardImageWrapper() {
	Image* result = malloc(sizeof(Image));
	*result = GetClipboardImage();
	return result;
}

void BeginMode2DWrapper(Camera2D* camera) {
	BeginMode2D(*camera);
}

void BeginMode3DWrapper(Camera3D* camera) {
	BeginMode3D(*camera);
}

void BeginTextureModeWrapper(RenderTexture2D* target) {
	BeginTextureMode(*target);
}

void BeginShaderModeWrapper(Shader* shader) {
	BeginShaderMode(*shader);
}

void BeginVrStereoModeWrapper(VrStereoConfig* config) {
	BeginVrStereoMode(*config);
}

VrStereoConfig* LoadVrStereoConfigWrapper(VrDeviceInfo* device) {
	VrStereoConfig* result = malloc(sizeof(VrStereoConfig));
	*result = LoadVrStereoConfig(*device);
	return result;
}

void UnloadVrStereoConfigWrapper(VrStereoConfig* config) {
	UnloadVrStereoConfig(*config);
}

Shader* LoadShaderWrapper(const char *vsFileName, const char *fsFileName) {
	Shader* result = malloc(sizeof(Shader));
	*result = LoadShader(vsFileName, fsFileName);
	return result;
}

Shader* LoadShaderFromMemoryWrapper(const char *vsCode, const char *fsCode) {
	Shader* result = malloc(sizeof(Shader));
	*result = LoadShaderFromMemory(vsCode, fsCode);
	return result;
}

bool IsShaderValidWrapper(Shader* shader) {
	return IsShaderValid(*shader);
}

int GetShaderLocationWrapper(Shader* shader, const char *uniformName) {
	return GetShaderLocation(*shader, uniformName);
}

int GetShaderLocationAttribWrapper(Shader* shader, const char *attribName) {
	return GetShaderLocationAttrib(*shader, attribName);
}

void SetShaderValueWrapper(Shader* shader, int locIndex, const void *value, int uniformType) {
	SetShaderValue(*shader, locIndex, value, uniformType);
}

void SetShaderValueVWrapper(Shader* shader, int locIndex, const void *value, int uniformType, int count) {
	SetShaderValueV(*shader, locIndex, value, uniformType, count);
}

void SetShaderValueMatrixWrapper(Shader* shader, int locIndex, Matrix* mat) {
	SetShaderValueMatrix(*shader, locIndex, *mat);
}

void SetShaderValueTextureWrapper(Shader* shader, int locIndex, Texture2D* texture) {
	SetShaderValueTexture(*shader, locIndex, *texture);
}

void UnloadShaderWrapper(Shader* shader) {
	UnloadShader(*shader);
}

Ray* GetScreenToWorldRayWrapper(Vector2* position, Camera* camera) {
	Ray* result = malloc(sizeof(Ray));
	*result = GetScreenToWorldRay(*position, *camera);
	return result;
}

Ray* GetScreenToWorldRayExWrapper(Vector2* position, Camera* camera, int width, int height) {
	Ray* result = malloc(sizeof(Ray));
	*result = GetScreenToWorldRayEx(*position, *camera, width, height);
	return result;
}

Vector2* GetWorldToScreenWrapper(Vector3* position, Camera* camera) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetWorldToScreen(*position, *camera);
	return result;
}

Vector2* GetWorldToScreenExWrapper(Vector3* position, Camera* camera, int width, int height) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetWorldToScreenEx(*position, *camera, width, height);
	return result;
}

Vector2* GetWorldToScreen2DWrapper(Vector2* position, Camera2D* camera) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetWorldToScreen2D(*position, *camera);
	return result;
}

Vector2* GetScreenToWorld2DWrapper(Vector2* position, Camera2D* camera) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetScreenToWorld2D(*position, *camera);
	return result;
}

Matrix* GetCameraMatrixWrapper(Camera* camera) {
	Matrix* result = malloc(sizeof(Matrix));
	*result = GetCameraMatrix(*camera);
	return result;
}

Matrix* GetCameraMatrix2DWrapper(Camera2D* camera) {
	Matrix* result = malloc(sizeof(Matrix));
	*result = GetCameraMatrix2D(*camera);
	return result;
}

FilePathList* LoadDirectoryFilesWrapper(const char *dirPath) {
	FilePathList* result = malloc(sizeof(FilePathList));
	*result = LoadDirectoryFiles(dirPath);
	return result;
}

FilePathList* LoadDirectoryFilesExWrapper(const char *basePath, const char *filter, bool scanSubdirs) {
	FilePathList* result = malloc(sizeof(FilePathList));
	*result = LoadDirectoryFilesEx(basePath, filter, scanSubdirs);
	return result;
}

void UnloadDirectoryFilesWrapper(FilePathList* files) {
	UnloadDirectoryFiles(*files);
}

FilePathList* LoadDroppedFilesWrapper() {
	FilePathList* result = malloc(sizeof(FilePathList));
	*result = LoadDroppedFiles();
	return result;
}

void UnloadDroppedFilesWrapper(FilePathList* files) {
	UnloadDroppedFiles(*files);
}

AutomationEventList* LoadAutomationEventListWrapper(const char *fileName) {
	AutomationEventList* result = malloc(sizeof(AutomationEventList));
	*result = LoadAutomationEventList(fileName);
	return result;
}

void UnloadAutomationEventListWrapper(AutomationEventList* list) {
	UnloadAutomationEventList(*list);
}

bool ExportAutomationEventListWrapper(AutomationEventList* list, const char *fileName) {
	return ExportAutomationEventList(*list, fileName);
}

void PlayAutomationEventWrapper(AutomationEvent* event) {
	PlayAutomationEvent(*event);
}

Vector2* GetMousePositionWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetMousePosition();
	return result;
}

Vector2* GetMouseDeltaWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetMouseDelta();
	return result;
}

Vector2* GetMouseWheelMoveVWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetMouseWheelMoveV();
	return result;
}

Vector2* GetTouchPositionWrapper(int index) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetTouchPosition(index);
	return result;
}

Vector2* GetGestureDragVectorWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetGestureDragVector();
	return result;
}

Vector2* GetGesturePinchVectorWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetGesturePinchVector();
	return result;
}

void UpdateCameraProWrapper(Camera *camera, Vector3* movement, Vector3* rotation, float zoom) {
	UpdateCameraPro(camera, *movement, *rotation, zoom);
}


void GuiSetFontWrapper(Font* font) {
	GuiSetFont(*font);
}

Font* GuiGetFontWrapper() {
	Font* result = malloc(sizeof(Font));
	*result = GuiGetFont();
	return result;
}

int GuiWindowBoxWrapper(Rectangle* bounds, const char *title) {
	return GuiWindowBox(*bounds, title);
}

int GuiGroupBoxWrapper(Rectangle* bounds, const char *text) {
	return GuiGroupBox(*bounds, text);
}

int GuiLineWrapper(Rectangle* bounds, const char *text) {
	return GuiLine(*bounds, text);
}

int GuiPanelWrapper(Rectangle* bounds, const char *text) {
	return GuiPanel(*bounds, text);
}

int GuiTabBarWrapper(Rectangle* bounds, const char **text, int count, int *active) {
	return GuiTabBar(*bounds, text, count, active);
}

int GuiScrollPanelWrapper(Rectangle* bounds, const char *text, Rectangle* content, Vector2 *scroll, Rectangle *view) {
	return GuiScrollPanel(*bounds, text, *content, scroll, view);
}

int GuiLabelWrapper(Rectangle* bounds, const char *text) {
	return GuiLabel(*bounds, text);
}

int GuiButtonWrapper(Rectangle* bounds, const char *text) {
	return GuiButton(*bounds, text);
}

int GuiLabelButtonWrapper(Rectangle* bounds, const char *text) {
	return GuiLabelButton(*bounds, text);
}

int GuiToggleWrapper(Rectangle* bounds, const char *text, bool *active) {
	return GuiToggle(*bounds, text, active);
}

int GuiToggleGroupWrapper(Rectangle* bounds, const char *text, int *active) {
	return GuiToggleGroup(*bounds, text, active);
}

int GuiToggleSliderWrapper(Rectangle* bounds, const char *text, int *active) {
	return GuiToggleSlider(*bounds, text, active);
}

int GuiCheckBoxWrapper(Rectangle* bounds, const char *text, bool *checked) {
	return GuiCheckBox(*bounds, text, checked);
}

int GuiComboBoxWrapper(Rectangle* bounds, const char *text, int *active) {
	return GuiComboBox(*bounds, text, active);
}

int GuiDropdownBoxWrapper(Rectangle* bounds, const char *text, int *active, bool editMode) {
	return GuiDropdownBox(*bounds, text, active, editMode);
}

int GuiSpinnerWrapper(Rectangle* bounds, const char *text, int *value, int minValue, int maxValue, bool editMode) {
	return GuiSpinner(*bounds, text, value, minValue, maxValue, editMode);
}

int GuiValueBoxWrapper(Rectangle* bounds, const char *text, int *value, int minValue, int maxValue, bool editMode) {
	return GuiValueBox(*bounds, text, value, minValue, maxValue, editMode);
}

int GuiTextBoxWrapper(Rectangle* bounds, char *text, int textSize, bool editMode) {
	return GuiTextBox(*bounds, text, textSize, editMode);
}

int GuiSliderWrapper(Rectangle* bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue) {
	return GuiSlider(*bounds, textLeft, textRight, value, minValue, maxValue);
}

int GuiSliderBarWrapper(Rectangle* bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue) {
	return GuiSliderBar(*bounds, textLeft, textRight, value, minValue, maxValue);
}

int GuiProgressBarWrapper(Rectangle* bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue) {
	return GuiProgressBar(*bounds, textLeft, textRight, value, minValue, maxValue);
}

int GuiStatusBarWrapper(Rectangle* bounds, const char *text) {
	return GuiStatusBar(*bounds, text);
}

int GuiDummyRecWrapper(Rectangle* bounds, const char *text) {
	return GuiDummyRec(*bounds, text);
}

int GuiGridWrapper(Rectangle* bounds, const char *text, float spacing, int subdivs, Vector2 *mouseCell) {
	return GuiGrid(*bounds, text, spacing, subdivs, mouseCell);
}

int GuiListViewWrapper(Rectangle* bounds, const char *text, int *scrollIndex, int *active) {
	return GuiListView(*bounds, text, scrollIndex, active);
}

int GuiListViewExWrapper(Rectangle* bounds, const char **text, int count, int *scrollIndex, int *active, int *focus) {
	return GuiListViewEx(*bounds, text, count, scrollIndex, active, focus);
}

int GuiMessageBoxWrapper(Rectangle* bounds, const char *title, const char *message, const char *buttons) {
	return GuiMessageBox(*bounds, title, message, buttons);
}

int GuiTextInputBoxWrapper(Rectangle* bounds, const char *title, const char *message, const char *buttons, char *text, int textMaxSize, bool *secretViewActive) {
	return GuiTextInputBox(*bounds, title, message, buttons, text, textMaxSize, secretViewActive);
}

int GuiColorPickerWrapper(Rectangle* bounds, const char *text, Color *color) {
	return GuiColorPicker(*bounds, text, color);
}

int GuiColorPanelWrapper(Rectangle* bounds, const char *text, Color *color) {
	return GuiColorPanel(*bounds, text, color);
}

int GuiColorBarAlphaWrapper(Rectangle* bounds, const char *text, float *alpha) {
	return GuiColorBarAlpha(*bounds, text, alpha);
}

int GuiColorBarHueWrapper(Rectangle* bounds, const char *text, float *value) {
	return GuiColorBarHue(*bounds, text, value);
}

int GuiColorPickerHSVWrapper(Rectangle* bounds, const char *text, Vector3 *colorHsv) {
	return GuiColorPickerHSV(*bounds, text, colorHsv);
}

int GuiColorPanelHSVWrapper(Rectangle* bounds, const char *text, Vector3 *colorHsv) {
	return GuiColorPanelHSV(*bounds, text, colorHsv);
}


void DrawLine3DWrapper(Vector3* startPos, Vector3* endPos, Color color) {
	DrawLine3D(*startPos, *endPos, color);
}

void DrawPoint3DWrapper(Vector3* position, Color color) {
	DrawPoint3D(*position, color);
}

void DrawCircle3DWrapper(Vector3* center, float radius, Vector3* rotationAxis, float rotationAngle, Color color) {
	DrawCircle3D(*center, radius, *rotationAxis, rotationAngle, color);
}

void DrawTriangle3DWrapper(Vector3* v1, Vector3* v2, Vector3* v3, Color color) {
	DrawTriangle3D(*v1, *v2, *v3, color);
}

void DrawCubeWrapper(Vector3* position, float width, float height, float length, Color color) {
	DrawCube(*position, width, height, length, color);
}

void DrawCubeVWrapper(Vector3* position, Vector3* size, Color color) {
	DrawCubeV(*position, *size, color);
}

void DrawCubeWiresWrapper(Vector3* position, float width, float height, float length, Color color) {
	DrawCubeWires(*position, width, height, length, color);
}

void DrawCubeWiresVWrapper(Vector3* position, Vector3* size, Color color) {
	DrawCubeWiresV(*position, *size, color);
}

void DrawSphereWrapper(Vector3* centerPos, float radius, Color color) {
	DrawSphere(*centerPos, radius, color);
}

void DrawSphereExWrapper(Vector3* centerPos, float radius, int rings, int slices, Color color) {
	DrawSphereEx(*centerPos, radius, rings, slices, color);
}

void DrawSphereWiresWrapper(Vector3* centerPos, float radius, int rings, int slices, Color color) {
	DrawSphereWires(*centerPos, radius, rings, slices, color);
}

void DrawCylinderWrapper(Vector3* position, float radiusTop, float radiusBottom, float height, int slices, Color color) {
	DrawCylinder(*position, radiusTop, radiusBottom, height, slices, color);
}

void DrawCylinderExWrapper(Vector3* startPos, Vector3* endPos, float startRadius, float endRadius, int sides, Color color) {
	DrawCylinderEx(*startPos, *endPos, startRadius, endRadius, sides, color);
}

void DrawCylinderWiresWrapper(Vector3* position, float radiusTop, float radiusBottom, float height, int slices, Color color) {
	DrawCylinderWires(*position, radiusTop, radiusBottom, height, slices, color);
}

void DrawCylinderWiresExWrapper(Vector3* startPos, Vector3* endPos, float startRadius, float endRadius, int sides, Color color) {
	DrawCylinderWiresEx(*startPos, *endPos, startRadius, endRadius, sides, color);
}

void DrawCapsuleWrapper(Vector3* startPos, Vector3* endPos, float radius, int slices, int rings, Color color) {
	DrawCapsule(*startPos, *endPos, radius, slices, rings, color);
}

void DrawCapsuleWiresWrapper(Vector3* startPos, Vector3* endPos, float radius, int slices, int rings, Color color) {
	DrawCapsuleWires(*startPos, *endPos, radius, slices, rings, color);
}

void DrawPlaneWrapper(Vector3* centerPos, Vector2* size, Color color) {
	DrawPlane(*centerPos, *size, color);
}

void DrawRayWrapper(Ray* ray, Color color) {
	DrawRay(*ray, color);
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

void DrawModelWrapper(Model* model, Vector3* position, float scale, Color tint) {
	DrawModel(*model, *position, scale, tint);
}

void DrawModelExWrapper(Model* model, Vector3* position, Vector3* rotationAxis, float rotationAngle, Vector3* scale, Color tint) {
	DrawModelEx(*model, *position, *rotationAxis, rotationAngle, *scale, tint);
}

void DrawModelWiresWrapper(Model* model, Vector3* position, float scale, Color tint) {
	DrawModelWires(*model, *position, scale, tint);
}

void DrawModelWiresExWrapper(Model* model, Vector3* position, Vector3* rotationAxis, float rotationAngle, Vector3* scale, Color tint) {
	DrawModelWiresEx(*model, *position, *rotationAxis, rotationAngle, *scale, tint);
}

void DrawModelPointsWrapper(Model* model, Vector3* position, float scale, Color tint) {
	DrawModelPoints(*model, *position, scale, tint);
}

void DrawModelPointsExWrapper(Model* model, Vector3* position, Vector3* rotationAxis, float rotationAngle, Vector3* scale, Color tint) {
	DrawModelPointsEx(*model, *position, *rotationAxis, rotationAngle, *scale, tint);
}

void DrawBoundingBoxWrapper(BoundingBox* box, Color color) {
	DrawBoundingBox(*box, color);
}

void DrawBillboardWrapper(Camera* camera, Texture2D* texture, Vector3* position, float scale, Color tint) {
	DrawBillboard(*camera, *texture, *position, scale, tint);
}

void DrawBillboardRecWrapper(Camera* camera, Texture2D* texture, Rectangle* source, Vector3* position, Vector2* size, Color tint) {
	DrawBillboardRec(*camera, *texture, *source, *position, *size, tint);
}

void DrawBillboardProWrapper(Camera* camera, Texture2D* texture, Rectangle* source, Vector3* position, Vector3* up, Vector2* size, Vector2* origin, float rotation, Color tint) {
	DrawBillboardPro(*camera, *texture, *source, *position, *up, *size, *origin, rotation, tint);
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

void SetMaterialTextureWrapper(Material *material, int mapType, Texture2D* texture) {
	SetMaterialTexture(material, mapType, *texture);
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


void SetShapesTextureWrapper(Texture2D* texture, Rectangle* source) {
	SetShapesTexture(*texture, *source);
}

Texture2D* GetShapesTextureWrapper() {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = GetShapesTexture();
	return result;
}

Rectangle* GetShapesTextureRectangleWrapper() {
	Rectangle* result = malloc(sizeof(Rectangle));
	*result = GetShapesTextureRectangle();
	return result;
}

void DrawPixelVWrapper(Vector2* position, Color color) {
	DrawPixelV(*position, color);
}

void DrawLineVWrapper(Vector2* startPos, Vector2* endPos, Color color) {
	DrawLineV(*startPos, *endPos, color);
}

void DrawLineExWrapper(Vector2* startPos, Vector2* endPos, float thick, Color color) {
	DrawLineEx(*startPos, *endPos, thick, color);
}

void DrawLineBezierWrapper(Vector2* startPos, Vector2* endPos, float thick, Color color) {
	DrawLineBezier(*startPos, *endPos, thick, color);
}

void DrawCircleSectorWrapper(Vector2* center, float radius, float startAngle, float endAngle, int segments, Color color) {
	DrawCircleSector(*center, radius, startAngle, endAngle, segments, color);
}

void DrawCircleSectorLinesWrapper(Vector2* center, float radius, float startAngle, float endAngle, int segments, Color color) {
	DrawCircleSectorLines(*center, radius, startAngle, endAngle, segments, color);
}

void DrawCircleVWrapper(Vector2* center, float radius, Color color) {
	DrawCircleV(*center, radius, color);
}

void DrawCircleLinesVWrapper(Vector2* center, float radius, Color color) {
	DrawCircleLinesV(*center, radius, color);
}

void DrawRingWrapper(Vector2* center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) {
	DrawRing(*center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
}

void DrawRingLinesWrapper(Vector2* center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) {
	DrawRingLines(*center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
}

void DrawRectangleVWrapper(Vector2* position, Vector2* size, Color color) {
	DrawRectangleV(*position, *size, color);
}

void DrawRectangleRecWrapper(Rectangle* rec, Color color) {
	DrawRectangleRec(*rec, color);
}

void DrawRectangleProWrapper(Rectangle* rec, Vector2* origin, float rotation, Color color) {
	DrawRectanglePro(*rec, *origin, rotation, color);
}

void DrawRectangleGradientExWrapper(Rectangle* rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight) {
	DrawRectangleGradientEx(*rec, topLeft, bottomLeft, topRight, bottomRight);
}

void DrawRectangleLinesExWrapper(Rectangle* rec, float lineThick, Color color) {
	DrawRectangleLinesEx(*rec, lineThick, color);
}

void DrawRectangleRoundedWrapper(Rectangle* rec, float roundness, int segments, Color color) {
	DrawRectangleRounded(*rec, roundness, segments, color);
}

void DrawRectangleRoundedLinesWrapper(Rectangle* rec, float roundness, int segments, Color color) {
	DrawRectangleRoundedLines(*rec, roundness, segments, color);
}

void DrawRectangleRoundedLinesExWrapper(Rectangle* rec, float roundness, int segments, float lineThick, Color color) {
	DrawRectangleRoundedLinesEx(*rec, roundness, segments, lineThick, color);
}

void DrawTriangleWrapper(Vector2* v1, Vector2* v2, Vector2* v3, Color color) {
	DrawTriangle(*v1, *v2, *v3, color);
}

void DrawTriangleLinesWrapper(Vector2* v1, Vector2* v2, Vector2* v3, Color color) {
	DrawTriangleLines(*v1, *v2, *v3, color);
}

void DrawPolyWrapper(Vector2* center, int sides, float radius, float rotation, Color color) {
	DrawPoly(*center, sides, radius, rotation, color);
}

void DrawPolyLinesWrapper(Vector2* center, int sides, float radius, float rotation, Color color) {
	DrawPolyLines(*center, sides, radius, rotation, color);
}

void DrawPolyLinesExWrapper(Vector2* center, int sides, float radius, float rotation, float lineThick, Color color) {
	DrawPolyLinesEx(*center, sides, radius, rotation, lineThick, color);
}

void DrawSplineSegmentLinearWrapper(Vector2* p1, Vector2* p2, float thick, Color color) {
	DrawSplineSegmentLinear(*p1, *p2, thick, color);
}

void DrawSplineSegmentBasisWrapper(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, float thick, Color color) {
	DrawSplineSegmentBasis(*p1, *p2, *p3, *p4, thick, color);
}

void DrawSplineSegmentCatmullRomWrapper(Vector2* p1, Vector2* p2, Vector2* p3, Vector2* p4, float thick, Color color) {
	DrawSplineSegmentCatmullRom(*p1, *p2, *p3, *p4, thick, color);
}

void DrawSplineSegmentBezierQuadraticWrapper(Vector2* p1, Vector2* c2, Vector2* p3, float thick, Color color) {
	DrawSplineSegmentBezierQuadratic(*p1, *c2, *p3, thick, color);
}

void DrawSplineSegmentBezierCubicWrapper(Vector2* p1, Vector2* c2, Vector2* c3, Vector2* p4, float thick, Color color) {
	DrawSplineSegmentBezierCubic(*p1, *c2, *c3, *p4, thick, color);
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

Font* LoadFontFromImageWrapper(Image* image, Color key, int firstChar) {
	Font* result = malloc(sizeof(Font));
	*result = LoadFontFromImage(*image, key, firstChar);
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
	*result = GenImageFontAtlas(glyphs, glyphRecs, glyphCount, fontSize, padding, packMethod);
	return result;
}

void UnloadFontWrapper(Font* font) {
	UnloadFont(*font);
}

bool ExportFontAsCodeWrapper(Font* font, const char *fileName) {
	return ExportFontAsCode(*font, fileName);
}

void DrawTextExWrapper(Font* font, const char *text, Vector2* position, float fontSize, float spacing, Color tint) {
	DrawTextEx(*font, text, *position, fontSize, spacing, tint);
}

void DrawTextProWrapper(Font* font, const char *text, Vector2* position, Vector2* origin, float rotation, float fontSize, float spacing, Color tint) {
	DrawTextPro(*font, text, *position, *origin, rotation, fontSize, spacing, tint);
}

void DrawTextCodepointWrapper(Font* font, int codepoint, Vector2* position, float fontSize, Color tint) {
	DrawTextCodepoint(*font, codepoint, *position, fontSize, tint);
}

void DrawTextCodepointsWrapper(Font* font, const int *codepoints, int codepointCount, Vector2* position, float fontSize, float spacing, Color tint) {
	DrawTextCodepoints(*font, codepoints, codepointCount, *position, fontSize, spacing, tint);
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

Image* LoadImageFromTextureWrapper(Texture2D* texture) {
	Image* result = malloc(sizeof(Image));
	*result = LoadImageFromTexture(*texture);
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

Image* GenImageColorWrapper(int width, int height, Color color) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageColor(width, height, color);
	return result;
}

Image* GenImageGradientLinearWrapper(int width, int height, int direction, Color start, Color end) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageGradientLinear(width, height, direction, start, end);
	return result;
}

Image* GenImageGradientRadialWrapper(int width, int height, float density, Color inner, Color outer) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageGradientRadial(width, height, density, inner, outer);
	return result;
}

Image* GenImageGradientSquareWrapper(int width, int height, float density, Color inner, Color outer) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageGradientSquare(width, height, density, inner, outer);
	return result;
}

Image* GenImageCheckedWrapper(int width, int height, int checksX, int checksY, Color col1, Color col2) {
	Image* result = malloc(sizeof(Image));
	*result = GenImageChecked(width, height, checksX, checksY, col1, col2);
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

Image* ImageTextWrapper(const char *text, int fontSize, Color color) {
	Image* result = malloc(sizeof(Image));
	*result = ImageText(text, fontSize, color);
	return result;
}

Image* ImageTextExWrapper(Font* font, const char *text, float fontSize, float spacing, Color tint) {
	Image* result = malloc(sizeof(Image));
	*result = ImageTextEx(*font, text, fontSize, spacing, tint);
	return result;
}

void ImageCropWrapper(Image *image, Rectangle* crop) {
	ImageCrop(image, *crop);
}

void ImageAlphaMaskWrapper(Image *image, Image* alphaMask) {
	ImageAlphaMask(image, *alphaMask);
}

Rectangle* GetImageAlphaBorderWrapper(Image* image, float threshold) {
	Rectangle* result = malloc(sizeof(Rectangle));
	*result = GetImageAlphaBorder(*image, threshold);
	return result;
}

Color GetImageColorWrapper(Image* image, int x, int y) {
	return GetImageColor(*image, x, y);
}

void ImageDrawPixelVWrapper(Image *dst, Vector2* position, Color color) {
	ImageDrawPixelV(dst, *position, color);
}

void ImageDrawLineVWrapper(Image *dst, Vector2* start, Vector2* end, Color color) {
	ImageDrawLineV(dst, *start, *end, color);
}

void ImageDrawLineExWrapper(Image *dst, Vector2* start, Vector2* end, int thick, Color color) {
	ImageDrawLineEx(dst, *start, *end, thick, color);
}

void ImageDrawCircleVWrapper(Image *dst, Vector2* center, int radius, Color color) {
	ImageDrawCircleV(dst, *center, radius, color);
}

void ImageDrawCircleLinesVWrapper(Image *dst, Vector2* center, int radius, Color color) {
	ImageDrawCircleLinesV(dst, *center, radius, color);
}

void ImageDrawRectangleVWrapper(Image *dst, Vector2* position, Vector2* size, Color color) {
	ImageDrawRectangleV(dst, *position, *size, color);
}

void ImageDrawRectangleRecWrapper(Image *dst, Rectangle* rec, Color color) {
	ImageDrawRectangleRec(dst, *rec, color);
}

void ImageDrawRectangleLinesWrapper(Image *dst, Rectangle* rec, int thick, Color color) {
	ImageDrawRectangleLines(dst, *rec, thick, color);
}

void ImageDrawTriangleWrapper(Image *dst, Vector2* v1, Vector2* v2, Vector2* v3, Color color) {
	ImageDrawTriangle(dst, *v1, *v2, *v3, color);
}

void ImageDrawTriangleExWrapper(Image *dst, Vector2* v1, Vector2* v2, Vector2* v3, Color c1, Color c2, Color c3) {
	ImageDrawTriangleEx(dst, *v1, *v2, *v3, c1, c2, c3);
}

void ImageDrawTriangleLinesWrapper(Image *dst, Vector2* v1, Vector2* v2, Vector2* v3, Color color) {
	ImageDrawTriangleLines(dst, *v1, *v2, *v3, color);
}

void ImageDrawWrapper(Image *dst, Image* src, Rectangle* srcRec, Rectangle* dstRec, Color tint) {
	ImageDraw(dst, *src, *srcRec, *dstRec, tint);
}

void ImageDrawTextExWrapper(Image *dst, Font* font, const char *text, Vector2* position, float fontSize, float spacing, Color tint) {
	ImageDrawTextEx(dst, *font, text, *position, fontSize, spacing, tint);
}

Texture2D* LoadTextureWrapper(const char *fileName) {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = LoadTexture(fileName);
	return result;
}

Texture2D* LoadTextureFromImageWrapper(Image* image) {
	Texture2D* result = malloc(sizeof(Texture2D));
	*result = LoadTextureFromImage(*image);
	return result;
}

TextureCubemap* LoadTextureCubemapWrapper(Image* image, int layout) {
	TextureCubemap* result = malloc(sizeof(TextureCubemap));
	*result = LoadTextureCubemap(*image, layout);
	return result;
}

RenderTexture2D* LoadRenderTextureWrapper(int width, int height) {
	RenderTexture2D* result = malloc(sizeof(RenderTexture2D));
	*result = LoadRenderTexture(width, height);
	return result;
}

bool IsTextureValidWrapper(Texture2D* texture) {
	return IsTextureValid(*texture);
}

void UnloadTextureWrapper(Texture2D* texture) {
	UnloadTexture(*texture);
}

bool IsRenderTextureValidWrapper(RenderTexture2D* target) {
	return IsRenderTextureValid(*target);
}

void UnloadRenderTextureWrapper(RenderTexture2D* target) {
	UnloadRenderTexture(*target);
}

void UpdateTextureWrapper(Texture2D* texture, const void *pixels) {
	UpdateTexture(*texture, pixels);
}

void UpdateTextureRecWrapper(Texture2D* texture, Rectangle* rec, const void *pixels) {
	UpdateTextureRec(*texture, *rec, pixels);
}

void SetTextureFilterWrapper(Texture2D* texture, int filter) {
	SetTextureFilter(*texture, filter);
}

void SetTextureWrapWrapper(Texture2D* texture, int wrap) {
	SetTextureWrap(*texture, wrap);
}

void DrawTextureWrapper(Texture2D* texture, int posX, int posY, Color tint) {
	DrawTexture(*texture, posX, posY, tint);
}

void DrawTextureVWrapper(Texture2D* texture, Vector2* position, Color tint) {
	DrawTextureV(*texture, *position, tint);
}

void DrawTextureExWrapper(Texture2D* texture, Vector2* position, float rotation, float scale, Color tint) {
	DrawTextureEx(*texture, *position, rotation, scale, tint);
}

void DrawTextureRecWrapper(Texture2D* texture, Rectangle* source, Vector2* position, Color tint) {
	DrawTextureRec(*texture, *source, *position, tint);
}

void DrawTextureProWrapper(Texture2D* texture, Rectangle* source, Rectangle* dest, Vector2* origin, float rotation, Color tint) {
	DrawTexturePro(*texture, *source, *dest, *origin, rotation, tint);
}

void DrawTextureNPatchWrapper(Texture2D* texture, NPatchInfo* nPatchInfo, Rectangle* dest, Vector2* origin, float rotation, Color tint) {
	DrawTextureNPatch(*texture, *nPatchInfo, *dest, *origin, rotation, tint);
}

Vector4* ColorNormalizeWrapper(Color color) {
	Vector4* result = malloc(sizeof(Vector4));
	*result = ColorNormalize(color);
	return result;
}

Color ColorFromNormalizedWrapper(Vector4* normalized) {
	return ColorFromNormalized(*normalized);
}

Vector3* ColorToHSVWrapper(Color color) {
	Vector3* result = malloc(sizeof(Vector3));
	*result = ColorToHSV(color);
	return result;
}
