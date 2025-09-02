void InitWindowWrapper(int width, int height, const char *title) {
	InitWindow(width, height, title);
}

void CloseWindowWrapper() {
	CloseWindow();
}

bool WindowShouldCloseWrapper() {
	return WindowShouldClose();
}

bool IsWindowReadyWrapper() {
	return IsWindowReady();
}

bool IsWindowFullscreenWrapper() {
	return IsWindowFullscreen();
}

bool IsWindowHiddenWrapper() {
	return IsWindowHidden();
}

bool IsWindowMinimizedWrapper() {
	return IsWindowMinimized();
}

bool IsWindowMaximizedWrapper() {
	return IsWindowMaximized();
}

bool IsWindowFocusedWrapper() {
	return IsWindowFocused();
}

bool IsWindowResizedWrapper() {
	return IsWindowResized();
}

bool IsWindowStateWrapper(unsigned int flag) {
	return IsWindowState(flag);
}

void SetWindowStateWrapper(unsigned int flags) {
	SetWindowState(flags);
}

void ClearWindowStateWrapper(unsigned int flags) {
	ClearWindowState(flags);
}

void ToggleFullscreenWrapper() {
	ToggleFullscreen();
}

void ToggleBorderlessWindowedWrapper() {
	ToggleBorderlessWindowed();
}

void MaximizeWindowWrapper() {
	MaximizeWindow();
}

void MinimizeWindowWrapper() {
	MinimizeWindow();
}

void RestoreWindowWrapper() {
	RestoreWindow();
}

void SetWindowIconWrapper(Image* image) {
	SetWindowIcon(*image);
}

void SetWindowIconsWrapper(Image *images, int count) {
	SetWindowIcons(images, count);
}

void SetWindowTitleWrapper(const char *title) {
	SetWindowTitle(title);
}

void SetWindowPositionWrapper(int x, int y) {
	SetWindowPosition(x, y);
}

void SetWindowMonitorWrapper(int monitor) {
	SetWindowMonitor(monitor);
}

void SetWindowMinSizeWrapper(int width, int height) {
	SetWindowMinSize(width, height);
}

void SetWindowMaxSizeWrapper(int width, int height) {
	SetWindowMaxSize(width, height);
}

void SetWindowSizeWrapper(int width, int height) {
	SetWindowSize(width, height);
}

void SetWindowOpacityWrapper(float opacity) {
	SetWindowOpacity(opacity);
}

void SetWindowFocusedWrapper() {
	SetWindowFocused();
}

int GetScreenWidthWrapper() {
	return GetScreenWidth();
}

int GetScreenHeightWrapper() {
	return GetScreenHeight();
}

int GetRenderWidthWrapper() {
	return GetRenderWidth();
}

int GetRenderHeightWrapper() {
	return GetRenderHeight();
}

int GetMonitorCountWrapper() {
	return GetMonitorCount();
}

int GetCurrentMonitorWrapper() {
	return GetCurrentMonitor();
}

Vector2* GetMonitorPositionWrapper(int monitor) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetMonitorPosition(monitor);
	return result;
}

int GetMonitorWidthWrapper(int monitor) {
	return GetMonitorWidth(monitor);
}

int GetMonitorHeightWrapper(int monitor) {
	return GetMonitorHeight(monitor);
}

int GetMonitorPhysicalWidthWrapper(int monitor) {
	return GetMonitorPhysicalWidth(monitor);
}

int GetMonitorPhysicalHeightWrapper(int monitor) {
	return GetMonitorPhysicalHeight(monitor);
}

int GetMonitorRefreshRateWrapper(int monitor) {
	return GetMonitorRefreshRate(monitor);
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

void SetClipboardTextWrapper(const char *text) {
	SetClipboardText(text);
}

Image* GetClipboardImageWrapper() {
	Image* result = malloc(sizeof(Image));
	*result = GetClipboardImage();
	return result;
}

void EnableEventWaitingWrapper() {
	EnableEventWaiting();
}

void DisableEventWaitingWrapper() {
	DisableEventWaiting();
}

void ShowCursorWrapper() {
	ShowCursor();
}

void HideCursorWrapper() {
	HideCursor();
}

bool IsCursorHiddenWrapper() {
	return IsCursorHidden();
}

void EnableCursorWrapper() {
	EnableCursor();
}

void DisableCursorWrapper() {
	DisableCursor();
}

bool IsCursorOnScreenWrapper() {
	return IsCursorOnScreen();
}

void ClearBackgroundWrapper(Color* color) {
	ClearBackground(*color);
}

void BeginDrawingWrapper() {
	BeginDrawing();
}

void EndDrawingWrapper() {
	EndDrawing();
}

void BeginMode2DWrapper(Camera2D* camera) {
	BeginMode2D(*camera);
}

void EndMode2DWrapper() {
	EndMode2D();
}

void BeginMode3DWrapper(Camera3D* camera) {
	BeginMode3D(*camera);
}

void EndMode3DWrapper() {
	EndMode3D();
}

void BeginTextureModeWrapper(RenderTexture2D target) {
	BeginTextureMode(target);
}

void EndTextureModeWrapper() {
	EndTextureMode();
}

void BeginShaderModeWrapper(Shader* shader) {
	BeginShaderMode(*shader);
}

void EndShaderModeWrapper() {
	EndShaderMode();
}

void BeginBlendModeWrapper(int mode) {
	BeginBlendMode(mode);
}

void EndBlendModeWrapper() {
	EndBlendMode();
}

void BeginScissorModeWrapper(int x, int y, int width, int height) {
	BeginScissorMode(x, y, width, height);
}

void EndScissorModeWrapper() {
	EndScissorMode();
}

void BeginVrStereoModeWrapper(VrStereoConfig* config) {
	BeginVrStereoMode(*config);
}

void EndVrStereoModeWrapper() {
	EndVrStereoMode();
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

void SetShaderValueTextureWrapper(Shader* shader, int locIndex, Texture2D texture) {
	SetShaderValueTexture(*shader, locIndex, texture);
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

void SetTargetFPSWrapper(int fps) {
	SetTargetFPS(fps);
}

float GetFrameTimeWrapper() {
	return GetFrameTime();
}

double GetTimeWrapper() {
	return GetTime();
}

int GetFPSWrapper() {
	return GetFPS();
}

void SwapScreenBufferWrapper() {
	SwapScreenBuffer();
}

void PollInputEventsWrapper() {
	PollInputEvents();
}

void WaitTimeWrapper(double seconds) {
	WaitTime(seconds);
}

void SetRandomSeedWrapper(unsigned int seed) {
	SetRandomSeed(seed);
}

int GetRandomValueWrapper(int min, int max) {
	return GetRandomValue(min, max);
}

void UnloadRandomSequenceWrapper(int *sequence) {
	UnloadRandomSequence(sequence);
}

void TakeScreenshotWrapper(const char *fileName) {
	TakeScreenshot(fileName);
}

void SetConfigFlagsWrapper(unsigned int flags) {
	SetConfigFlags(flags);
}

void OpenURLWrapper(const char *url) {
	OpenURL(url);
}

void TraceLogWrapper(int logLevel, const char *text,  ...) {
	TraceLog(logLevel, text, ...);
}

void SetTraceLogLevelWrapper(int logLevel) {
	SetTraceLogLevel(logLevel);
}

void MemFreeWrapper(void *ptr) {
	MemFree(ptr);
}

void SetTraceLogCallbackWrapper(TraceLogCallback callback) {
	SetTraceLogCallback(callback);
}

void SetLoadFileDataCallbackWrapper(LoadFileDataCallback callback) {
	SetLoadFileDataCallback(callback);
}

void SetSaveFileDataCallbackWrapper(SaveFileDataCallback callback) {
	SetSaveFileDataCallback(callback);
}

void SetLoadFileTextCallbackWrapper(LoadFileTextCallback callback) {
	SetLoadFileTextCallback(callback);
}

void SetSaveFileTextCallbackWrapper(SaveFileTextCallback callback) {
	SetSaveFileTextCallback(callback);
}

void UnloadFileDataWrapper(unsigned char *data) {
	UnloadFileData(data);
}

bool SaveFileDataWrapper(const char *fileName, void *data, int dataSize) {
	return SaveFileData(fileName, data, dataSize);
}

bool ExportDataAsCodeWrapper(const unsigned char *data, int dataSize, const char *fileName) {
	return ExportDataAsCode(data, dataSize, fileName);
}

void UnloadFileTextWrapper(char *text) {
	UnloadFileText(text);
}

bool SaveFileTextWrapper(const char *fileName, char *text) {
	return SaveFileText(fileName, text);
}

bool FileExistsWrapper(const char *fileName) {
	return FileExists(fileName);
}

bool DirectoryExistsWrapper(const char *dirPath) {
	return DirectoryExists(dirPath);
}

bool IsFileExtensionWrapper(const char *fileName, const char *ext) {
	return IsFileExtension(fileName, ext);
}

int GetFileLengthWrapper(const char *fileName) {
	return GetFileLength(fileName);
}

int MakeDirectoryWrapper(const char *dirPath) {
	return MakeDirectory(dirPath);
}

bool ChangeDirectoryWrapper(const char *dir) {
	return ChangeDirectory(dir);
}

bool IsPathFileWrapper(const char *path) {
	return IsPathFile(path);
}

bool IsFileNameValidWrapper(const char *fileName) {
	return IsFileNameValid(fileName);
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

bool IsFileDroppedWrapper() {
	return IsFileDropped();
}

FilePathList* LoadDroppedFilesWrapper() {
	FilePathList* result = malloc(sizeof(FilePathList));
	*result = LoadDroppedFiles();
	return result;
}

void UnloadDroppedFilesWrapper(FilePathList* files) {
	UnloadDroppedFiles(*files);
}

long GetFileModTimeWrapper(const char *fileName) {
	return GetFileModTime(fileName);
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

void SetAutomationEventListWrapper(AutomationEventList *list) {
	SetAutomationEventList(list);
}

void SetAutomationEventBaseFrameWrapper(int frame) {
	SetAutomationEventBaseFrame(frame);
}

void StartAutomationEventRecordingWrapper() {
	StartAutomationEventRecording();
}

void StopAutomationEventRecordingWrapper() {
	StopAutomationEventRecording();
}

void PlayAutomationEventWrapper(AutomationEvent* event) {
	PlayAutomationEvent(*event);
}

bool IsKeyPressedWrapper(int key) {
	return IsKeyPressed(key);
}

bool IsKeyPressedRepeatWrapper(int key) {
	return IsKeyPressedRepeat(key);
}

bool IsKeyDownWrapper(int key) {
	return IsKeyDown(key);
}

bool IsKeyReleasedWrapper(int key) {
	return IsKeyReleased(key);
}

bool IsKeyUpWrapper(int key) {
	return IsKeyUp(key);
}

int GetKeyPressedWrapper() {
	return GetKeyPressed();
}

int GetCharPressedWrapper() {
	return GetCharPressed();
}

void SetExitKeyWrapper(int key) {
	SetExitKey(key);
}

bool IsGamepadAvailableWrapper(int gamepad) {
	return IsGamepadAvailable(gamepad);
}

bool IsGamepadButtonPressedWrapper(int gamepad, int button) {
	return IsGamepadButtonPressed(gamepad, button);
}

bool IsGamepadButtonDownWrapper(int gamepad, int button) {
	return IsGamepadButtonDown(gamepad, button);
}

bool IsGamepadButtonReleasedWrapper(int gamepad, int button) {
	return IsGamepadButtonReleased(gamepad, button);
}

bool IsGamepadButtonUpWrapper(int gamepad, int button) {
	return IsGamepadButtonUp(gamepad, button);
}

int GetGamepadButtonPressedWrapper() {
	return GetGamepadButtonPressed();
}

int GetGamepadAxisCountWrapper(int gamepad) {
	return GetGamepadAxisCount(gamepad);
}

float GetGamepadAxisMovementWrapper(int gamepad, int axis) {
	return GetGamepadAxisMovement(gamepad, axis);
}

int SetGamepadMappingsWrapper(const char *mappings) {
	return SetGamepadMappings(mappings);
}

void SetGamepadVibrationWrapper(int gamepad, float leftMotor, float rightMotor, float duration) {
	SetGamepadVibration(gamepad, leftMotor, rightMotor, duration);
}

bool IsMouseButtonPressedWrapper(int button) {
	return IsMouseButtonPressed(button);
}

bool IsMouseButtonDownWrapper(int button) {
	return IsMouseButtonDown(button);
}

bool IsMouseButtonReleasedWrapper(int button) {
	return IsMouseButtonReleased(button);
}

bool IsMouseButtonUpWrapper(int button) {
	return IsMouseButtonUp(button);
}

int GetMouseXWrapper() {
	return GetMouseX();
}

int GetMouseYWrapper() {
	return GetMouseY();
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

void SetMousePositionWrapper(int x, int y) {
	SetMousePosition(x, y);
}

void SetMouseOffsetWrapper(int offsetX, int offsetY) {
	SetMouseOffset(offsetX, offsetY);
}

void SetMouseScaleWrapper(float scaleX, float scaleY) {
	SetMouseScale(scaleX, scaleY);
}

float GetMouseWheelMoveWrapper() {
	return GetMouseWheelMove();
}

Vector2* GetMouseWheelMoveVWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetMouseWheelMoveV();
	return result;
}

void SetMouseCursorWrapper(int cursor) {
	SetMouseCursor(cursor);
}

int GetTouchXWrapper() {
	return GetTouchX();
}

int GetTouchYWrapper() {
	return GetTouchY();
}

Vector2* GetTouchPositionWrapper(int index) {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetTouchPosition(index);
	return result;
}

int GetTouchPointIdWrapper(int index) {
	return GetTouchPointId(index);
}

int GetTouchPointCountWrapper() {
	return GetTouchPointCount();
}

void SetGesturesEnabledWrapper(unsigned int flags) {
	SetGesturesEnabled(flags);
}

bool IsGestureDetectedWrapper(unsigned int gesture) {
	return IsGestureDetected(gesture);
}

int GetGestureDetectedWrapper() {
	return GetGestureDetected();
}

float GetGestureHoldDurationWrapper() {
	return GetGestureHoldDuration();
}

Vector2* GetGestureDragVectorWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetGestureDragVector();
	return result;
}

float GetGestureDragAngleWrapper() {
	return GetGestureDragAngle();
}

Vector2* GetGesturePinchVectorWrapper() {
	Vector2* result = malloc(sizeof(Vector2));
	*result = GetGesturePinchVector();
	return result;
}

float GetGesturePinchAngleWrapper() {
	return GetGesturePinchAngle();
}

void UpdateCameraWrapper(Camera *camera, int mode) {
	UpdateCamera(camera, mode);
}

void UpdateCameraProWrapper(Camera *camera, Vector3* movement, Vector3* rotation, float zoom) {
	UpdateCameraPro(camera, *movement, *rotation, zoom);
}
