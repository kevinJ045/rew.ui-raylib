void InitAudioDeviceWrapper() {
	InitAudioDevice();
}

void CloseAudioDeviceWrapper() {
	CloseAudioDevice();
}

bool IsAudioDeviceReadyWrapper() {
	return IsAudioDeviceReady();
}

void SetMasterVolumeWrapper(float volume) {
	SetMasterVolume(volume);
}

float GetMasterVolumeWrapper() {
	return GetMasterVolume();
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

void WaveCropWrapper(Wave *wave, int initFrame, int finalFrame) {
	WaveCrop(wave, initFrame, finalFrame);
}

void WaveFormatWrapper(Wave *wave, int sampleRate, int sampleSize, int channels) {
	WaveFormat(wave, sampleRate, sampleSize, channels);
}

void UnloadWaveSamplesWrapper(float *samples) {
	UnloadWaveSamples(samples);
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

void SetAudioStreamBufferSizeDefaultWrapper(int size) {
	SetAudioStreamBufferSizeDefault(size);
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

void AttachAudioMixedProcessorWrapper(AudioCallback processor) {
	AttachAudioMixedProcessor(processor);
}

void DetachAudioMixedProcessorWrapper(AudioCallback processor) {
	DetachAudioMixedProcessor(processor);
}
