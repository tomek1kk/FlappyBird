#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
using namespace std;

class bird
{
    public:
        bird(SDL_Texture* textura, SDL_Renderer* rendi);
        void update();
        void jump();
        void render();
        void wypisz();
        bool spadl();
        SDL_Rect getRect();
    protected:

    private:
        float xpos, ypos;
        float speed;
        SDL_Rect r;
        bool fall;
        int x;
        SDL_Texture* textura;
        SDL_Renderer* rendi;
};


