#include "wall.h"
#include <sstream>
#include <SDL_ttf.h>
#include <fstream>
using namespace std;

// functions
void intTexture(std::string path, SDL_Color color, SDL_Renderer* rendi,int font_size,int text,int x,int y);
SDL_Texture* loadTexture(string path);
void gaps(int *x, int *y);
bool checkColision(SDL_Rect r1, SDL_Rect r2);
string inttostring(int x)
{
    stringstream xx;
    string napis;
    xx << x;
    xx >> napis;
    return napis;

}
int stringtoint(string x)
{
    stringstream xx;
    int liczba;
    xx << x;
    xx >> liczba;
    return liczba;

}


// consts

SDL_Window* okno = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, NULL);
SDL_Renderer* rendi = SDL_CreateRenderer(okno, NULL, SDL_RENDERER_ACCELERATED);
SDL_Texture* birdt = loadTexture("test1.png");
SDL_Texture* mur = loadTexture("pipe.png");
SDL_Texture* mur2 = loadTexture("pipe2.png");
SDL_Texture* bg = loadTexture("background.jpg");
SDL_Texture* frame1 = loadTexture("frame1.png");
SDL_Texture* main_menu = loadTexture("main_menu.jpg");

const int min_gap = 180;
const int max_gap = 270;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    fstream odczyt;
    fstream zapis;
    odczyt.open("best_score.txt", ios::in | ios::out);

    int best;
    odczyt >> best;
    cout << best << endl;
    SDL_Event e;
    SDL_PollEvent(&e);
    bool run_game = true;
    int frame = 3;
    while (run_game == true)
    {
    vector <wall> tab;
    bool running = true;
    int licznik = 0;
    bool again = false;

    int score = 1;
    bird *bird1 = new bird(birdt, rendi);
    int x, y, z, x1, y1, z1;
    while (frame == 2)
    {

        while (SDL_PollEvent(&e))
        {
        if (e.type == SDL_QUIT)
        {
            frame = 1;
            run_game = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_SPACE:
                    bird1->jump();
                    break;
                case SDLK_ESCAPE:
                    {
                        frame = 1;
                        run_game = false;
                    }
                break;
            }
        }

        }
        bird1->update();

        if (licznik % 50  == 0)
        {
            if (tab.size() == 0)
            {
                x = rand() % 300 + 50;
                y = rand() % 300 + 300;
                gaps(&x, &y);
                wall w(mur, mur2, rendi, 500, x, y);
                tab.push_back(w);
                x = rand() % 300 + 50;
                y = rand() % 300 + 300;
                gaps(&x, &y);
                wall w1(mur, mur2, rendi, 800, x, y);
                tab.push_back(w1);
            }
            else
            {
                x = rand() % 400 + 50;
                y = rand() % 250 + 300;
                gaps(&x, &y);
                wall w(mur, mur2, rendi, 800, x, y);
                tab.push_back(w);
                score++;
            }
        }
        if (checkColision(bird1->getRect(), tab[1].getRect1()) == true || checkColision(bird1->getRect(), tab[1].getRect2()) == true
            || checkColision(bird1->getRect(), tab[0].getRect1()) == true || checkColision(bird1->getRect(), tab[0].getRect2()) == true)
        {
            frame = 1;
        }
        if (tab.size() > 4)
            tab.erase(tab.begin(), tab.begin() + 1);
        if (bird1->spadl() == true)
        {
            frame = 1;
        }

        for (int i = 0; i < tab.size(); i++)
            tab[i].update();


        SDL_RenderClear(rendi);

        SDL_RenderCopy(rendi, bg, NULL, NULL);
        for (int i = 0; i < tab.size(); i++)
            tab[i].render();
        bird1->render();
        if (frame == 1)
        {
            SDL_RenderCopy(rendi, frame1, NULL, NULL);
        }

        intTexture("font.ttf", {0, 0, 0, 255}, rendi, 80, score - 1, 280, 50);

        SDL_RenderPresent(rendi);

       // cout << best << endl;


        licznik++;
        SDL_Delay(16);
    }
    tab.clear();
    delete bird1;
    cout << best << endl;
    cout << score - 1 << endl;
    if (score - 1 > best)
        {
            cout << "w ifie" << endl;
            best = score - 1;
            odczyt << inttostring(best);
        }

    while (frame == 1)
    {
        while (SDL_PollEvent(&e))
        {
        if (e.type == SDL_QUIT)
        {
            run_game = false;
            frame = 0;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_SPACE:
                    frame = 2;
                    break;
                case SDLK_ESCAPE:
                    {
                        run_game = false;
                        frame = 0;
                    }
                break;
            }
        }

        }

    }

    while (frame == 3)
    {
        if (frame == 3)
        {
        SDL_RenderClear(rendi);
        SDL_RenderCopy(rendi, main_menu, NULL, NULL);
        SDL_RenderPresent(rendi);

        }

          while (SDL_PollEvent(&e))
        {
        if (e.type == SDL_QUIT)
        {
            run_game = false;
            frame = 0;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_SPACE:
                    frame = 2;
                    break;
                case SDLK_ESCAPE:
                    {
                        run_game = false;
                        frame = 0;
                    }
                break;
            }
        }

        }


    }

    }
    odczyt.close();
    SDL_Quit();
    return 0;
}

SDL_Texture* loadTexture(string path)
{
    SDL_Surface* surf = IMG_Load(path.c_str());
    SDL_Texture* texta = SDL_CreateTextureFromSurface(rendi, surf);
    if (texta == NULL)
        cout << "Blad ladowania textury!" << endl;
    return texta;
}

void gaps(int *x, int *y)
{
    int p;
    if (*y - *x > min_gap && *y - *x < max_gap)
        return;
    else if (*y - *x < min_gap)
    {
        p = rand() % (max_gap - min_gap) + min_gap;
        while (*y - *x < p)
        {
            if (*y < 550 && *x > 50)
            {
                *y = *y + 1;
                *x = *x - 1;
            }
            else if (*y > 550)
                *x = *x - 1;
            else
                *y = *y + 1;

        }
        return;
    }
    else
    {
        p = rand() % (max_gap - min_gap) + min_gap;
        while (*y - *x > p)
        {
             if (*y < 550 && *x > 50)
            {
                *y = *y - 1;
                *x = *x + 1;
            }
            else if (*y > 550)
                *x = *x + 1;
            else
                *y = *y - 1;
        }
        return;
    }
}

bool checkColision(SDL_Rect r1, SDL_Rect r2)
{
    if ((r1.x < r2.x && r1.x + r1.w > r2.x) && (r2.y > r1.y && r1.y + r1.h > r2.y))
        return true;
    if ((r2.x > r1.x && r1.x + r1.w > r2.x) && (r1.y > r2.y && r2.y + r2.h > r1.y))
        return true;
    if ((r1.x > r2.x && r2.x + r2.w > r1.x) && (r2.y > r1.y && r1.y + r1.h > r2.y))
        return true;
    if ((r1.x > r2.x && r2.x + r2.w > r1.x) && (r1.y > r2.y && r2.y + r2.h > r1.y))
        return true;
    return false;
}

void intTexture(std::string path, SDL_Color color, SDL_Renderer* rendi,int font_size,int text,int x,int y)
{
    std::stringstream convert;
    convert << text;
    TTF_Init();
    TTF_Font* font = TTF_OpenFont(path.c_str(),font_size);
    if(font == NULL)
        std::cout<<"czcionka nie zaladowala sie!"<<std::endl;
    SDL_Surface* tempSur = TTF_RenderText_Solid(font,convert.str().c_str(),color);
    int width = tempSur->w;
    int height = tempSur->h;
    SDL_Rect r = {x,y,width,height};
    SDL_Texture* textura = SDL_CreateTextureFromSurface(rendi,tempSur);
    SDL_FreeSurface(tempSur);
    SDL_RenderCopy(rendi,textura,NULL,&r);

}
