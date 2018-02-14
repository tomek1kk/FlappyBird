#include "bird.h"
#include<time.h>

class wall
{
    public:
        wall(SDL_Texture* texta, SDL_Texture* texta2, SDL_Renderer* rendi, int xpos, int x, int y);
        void update();
        void render();
        SDL_Rect getRect1();
        SDL_Rect getRect2();

    protected:

    private:
        int xpos;
        int ypos_up;
        int ypos_down;
        SDL_Rect r1;
        SDL_Rect r2;
        SDL_Texture* texta;
        SDL_Texture* texta2;
        SDL_Renderer* rendi;
};

