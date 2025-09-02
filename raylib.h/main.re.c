
typedef Vector3* Vec3Ptr;

Rectangle* CreateRectangle(float x, float y, float w, float h) {
  Rectangle* r = malloc(sizeof(Rectangle));
  *r = (Rectangle){ x, y, w, h };
  return r;
}

Vec3Ptr Vec3_Create(float x, float y, float z) {
  Vec3Ptr v = malloc(sizeof(Vector3));
  *v = (Vector3){x, y, z};
  return v;
}

void Vec3_Free(Vec3Ptr v) {
  free(v);
}

Camera3D* Camera3D_Create(Vec3Ptr position, Vec3Ptr target) {
  Camera3D* cam = malloc(sizeof(Camera3D));
  cam->position = *position;
  cam->target = *target;
  cam->up = (Vector3){0.0f, 1.0f, 0.0f};
  cam->fovy = 45.0f;
  cam->projection = CAMERA_PERSPECTIVE;
  return cam;
}

void Camera3D_Free(Camera3D* cam) {
  free(cam);
}

void BeginMode3DWrapper(Camera3D* cam) {
  BeginMode3D(*cam);
}

void DrawCubeWrapper(Vector3* pos, float width, float height, float length, Color color) {
  DrawCube(*pos, width, height, length, color);
}

void DrawModelWrapper(Model* model, Vector3* pos, float scale, Color color) {
  DrawModel(*model, *pos, scale, color);
}
