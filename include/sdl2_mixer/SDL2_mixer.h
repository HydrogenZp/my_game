#ifndef SDL_MIXER_H_
#define SDL_MIXER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* SDL mixer audio format definitions */
#define MIX_DEFAULT_FORMAT 0x8010  /* AUDIO_S16LSB */

/* Error handling */
const char* Mix_GetError(void);

/* Initialize audio */
int Mix_OpenAudio(int frequency, unsigned short format, int channels, int chunksize);
void Mix_CloseAudio(void);

/* Sound chunk structure */
typedef struct Mix_Chunk {
    int allocated;
    unsigned char *abuf;
    unsigned int alen;
    unsigned char volume;
} Mix_Chunk;

/* Music structure */
typedef struct Mix_Music Mix_Music;

/* Load audio files */
Mix_Chunk* Mix_LoadWAV(const char *file);
Mix_Music* Mix_LoadMUS(const char *file);

/* Free audio resources */
void Mix_FreeChunk(Mix_Chunk *chunk);
void Mix_FreeMusic(Mix_Music *music);

/* Play audio */
int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops);
int Mix_PlayMusic(Mix_Music *music, int loops);

/* Control playback */
void Mix_HaltMusic(void);
void Mix_PauseMusic(void);
void Mix_ResumeMusic(void);
int Mix_PlayingMusic(void);

/* Volume control */
int Mix_Volume(int channel, int volume);
int Mix_VolumeMusic(int volume);

#ifdef __cplusplus
}
#endif

#endif /* SDL_MIXER_H_ */
