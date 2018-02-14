#include "wall.h"

wall::wall(SDL_Texture* texta, SDL_Texture* texta2, SDL_Renderer* rendi, int xpos, int x, int y)
{
    this->texta = texta;
    this->texta2 = texta2;
    this->rendi = rendi;
    this->xpos = xpos;
    ypos_up = x;
    ypos_down =  y; // 300 - 550


    r1.y = x - 402;
    r1.w = 70;
    r1.h = 402;

    r2.y = ypos_down;
    r2.w = 70;
    r2.h = 402;
}

void wall::update()
{
    xpos = xpos - 6;
}

void wall::render()
{
    r1.x = xpos;
    r2.x = xpos;

    SDL_RenderCopy(rendi, texta2, NULL, &r1);
    SDL_RenderCopy(rendi, texta, NULL, &r2);

}

SDL_Rect wall::getRect1()
{
    return r1;
}

SDL_Rect wall::getRect2()
{
    return r2;
}
