

module.exports = function makeStruct(){
  return `
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

`
}