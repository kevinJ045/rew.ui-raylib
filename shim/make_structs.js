

module.exports = function makeStruct(){
  return `Vector2* CreateVector2(float x, float y) {
  Vector2* v = malloc(sizeof(Vector2));
  *v = (Vector2){ x, y };
  return v;
}

Vector3* CreateVector3(float x, float y, float z) {
  Vector3* v = malloc(sizeof(Vector3));
  *v = (Vector3){ x, y, z };
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

void SetCamera3DVal(Camera3D* c, Vector3 *position, Vector3 *target, float fovy) {
  c->position = *position;
  c->target = *target;
  c->up = (Vector3){0.0f, 1.0f, 0.0f};
  c->fovy = fovy;
  c->projection = CAMERA_PERSPECTIVE;
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

void SetMaterialTextures(Model *model, Texture2D* diffuse, Texture2D* specular, Texture2D* normal, Texture2D* emission) {
  if (!model) return;

  for (int i = 0; i < model->materialCount; i++) {
    model->materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = *diffuse;
    model->materials[i].maps[MATERIAL_MAP_SPECULAR].texture = *specular;
    model->materials[i].maps[MATERIAL_MAP_NORMAL].texture = *normal;
    model->materials[i].maps[MATERIAL_MAP_EMISSION].texture = *emission;
  }
}


Camera3D* CreateCamera3DDefault(Vector3 *position, Vector3 *target, Vector3* up, float fovy, int projection) {
  Camera3D* c = malloc(sizeof(Camera3D));
  *c = (Camera3D){ *position, *target, *up, fovy, projection };
  return c;
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
`
}