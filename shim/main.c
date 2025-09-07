#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdlib.h>



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
