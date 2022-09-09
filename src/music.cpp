#include <music.hpp>

void MusicPlayer::playFromMem(void *buf, int sz)
{
    freeBuf();
    musicBuf = new char[sz];
    SDL_memcpy(musicBuf, buf, sz);

    freeOps();
    rw = SDL_RWFromMem(musicBuf, sz);

    freeMusic();
    // Setting freesrc will free rw upon return
    mus = Mix_LoadMUS_RW(rw, 0);
    // mus = Mix_LoadMUSType_RW(rw, MUS_NONE, 1);

    playMusic();

    printf("rw: %p\n", rw);
    printf("mus: %p\n", mus);
    printf("musicBuf: %p\n", musicBuf);
}

void MusicPlayer::playFromFile(char *fpath)
{
    freeMusic();

    mus = Mix_LoadMUS(fpath);
    playMusic();
}

void MusicPlayer::freeMusic()
{
    if (mus != NULL)
    {
        printf("Mix_FreeMusic %p\n", mus);
        Mix_HaltMusic();
        Mix_FreeMusic(mus);
    }
}
void MusicPlayer::freeOps()
{
    if (rw != NULL)
    {
        printf("SDL_RWclose %p\n", rw);
        // Will break if next SDL_RWops allocation is at 0xa1;
        if (SDL_RWclose(rw) < 0)
        {
            printf("Error SDL_RWclose\n");
        }
    }
}

void MusicPlayer::freeBuf()
{
    if (musicBuf != NULL)
    {
        printf("freeBuf %p\n", musicBuf);
        delete[] musicBuf;
    }
}

void MusicPlayer::playMusic()
{
    Mix_PlayMusic(mus, -1);
}

void MusicPlayer::init()
{
    mus = NULL;
    rw = NULL;
    musicBuf = NULL;
}