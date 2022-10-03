#include <SDL.h>

#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>  
#else
#include <SDL_mixer.h>  
#endif

#include <string>

using namespace std;


#define BITS 8

class AudioManager {

public:

    AudioManager();
    static AudioManager* getInstance();

    void init();
    void play_audio(const char* path);
    void cleanup();

private:

    static AudioManager* audioManager;
    Mix_Chunk* wave = NULL;

};