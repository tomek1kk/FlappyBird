#include "bird.h"

bird::bird(SDL_Texture* textura, SDL_Renderer* rendi)
{
    xpos = 200.0;
    ypos = 200.0;
    speed = 4.0;
    fall = true;
    x = 0;
    this->textura = textura;
    this->rendi = rendi;
}

void bird::update()
{
    speed += 0.6;
    if (fall == true)
        ypos = ypos + speed;
    else
    {
        ypos = ypos - (speed * 2);
        x++;
    }
    if (x > 6)
    {
        fall = true;
        x = 0;
        speed = 3.0;
    }
    if (ypos < 0)
        fall = true;

}

void bird::jump()
{
    if (fall == true)
        fall = false;
    else
        x = 0;

    speed = 6.0;
}


void bird::render()
{
    r.w = 60;
    r.h = 44;
    r.x = xpos;
    r.y = ypos;

    SDL_RenderCopy(rendi, textura, NULL, &r);

}

bool bird::spadl()
{
    if (ypos > 570)
        return true;
    else
        return false;

}

SDL_Rect bird::getRect()
{
    return r;
}
