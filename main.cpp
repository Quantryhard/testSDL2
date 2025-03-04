#include <iostream>
#include <SDL.h>
using namespace std;
enum keyPressed{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_TOTAL
};

const int WEIGHT_SCREEN = 680 ;
const int HEIGHT_SCRENN = 480 ;
const char* NAME_SCREEN = "Mario" ;
bool init();
bool loadMedia();
void close();

SDL_Window* swindow = NULL;
SDL_Surface* gSurface = NULL;
SDL_Surface* pSurface = NULL;
SDL_Surface* loadSurface(char* p);
SDL_Surface* gKeypressed[KEY_PRESS_SURFACE_DEFAULT];

bool init(){
    bool sucess = true ;
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        cout<<"Couldn't create init!"<<SDL_GetError()<<endl;
        sucess = false;
    }
    else{
        swindow = SDL_CreateWindow(NAME_SCREEN,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WEIGHT_SCREEN,HEIGHT_SCRENN,SDL_WINDOW_SHOWN);
        if(swindow == NULL){
            cout<<"Couldn't create window!"<<SDL_GetError()<<endl;
            sucess = false;
        }
        else{
            gSurface = SDL_GetWindowSurface(swindow);
        }
    }
    return sucess;
}

SDL_Surface* loadSurface(char* p){
    SDL_Surface* optimized = NULL;
    SDL_Surface* loadsurface = SDL_LoadBMP(p);
    if(loadsurface == NULL){
        cout<<"Couldn't load imagine!"<<SDL_GetError()<<endl;
    }
    else{
        optimized = SDL_ConvertSurface(loadsurface,gSurface->format,0);
        if(optimized == NULL){
            cout<<"Couldn't convert!"<<SDL_GetError()<<endl;
        }
        SDL_FreeSurface(loadsurface);
    }
    return optimized;
}

bool loadMedia(){
    bool sucess = true ;
    gKeypressed[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.BMP");
    if(gKeypressed[KEY_PRESS_SURFACE_DEFAULT] == NULL){
        cout<<"Error press"<<SDL_GetError()<<endl;
        sucess = false;
    }
    gKeypressed[KEY_PRESS_SURFACE_UP] = loadSurface("up.BMP");
    if(gKeypressed[KEY_PRESS_SURFACE_UP] == NULL){
        cout<<"Error up"<<SDL_GetError()<<endl;
        sucess = false;
    }
    gKeypressed[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.BMP");
    if(gKeypressed[KEY_PRESS_SURFACE_DOWN] == NULL){
        cout<<"Error down"<<SDL_GetError()<<endl;
        sucess = false;
    }
    gKeypressed[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.BMP");
    if(gKeypressed[KEY_PRESS_SURFACE_RIGHT] == NULL){
        cout<<"Error right"<<SDL_GetError()<<endl;
        sucess = false;
    }
    gKeypressed[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.BMP");
    if(gKeypressed[KEY_PRESS_SURFACE_LEFT] == NULL){
        cout<<"Error left"<<SDL_GetError()<<endl;
        sucess = false;
    }
    return sucess;
}
void close(){
    for(int i = 0 ; i < KEY_PRESS_SURFACE_TOTAL ; i++){
        SDL_FreeSurface(gKeypressed[i]);
        gKeypressed[i] = NULL;
    }
    SDL_DestroyWindow(swindow);
    swindow = NULL;

    SDL_Quit();
}
int main(int argc ,char* arcv[])
{
    if(!init()){
        cout<<"Error init"<<endl;
    }
    else{
        if(!loadMedia()){
            cout<<"Error media"<<endl;
        }
        else{
            SDL_Event e;
            bool quit = false;
            pSurface = gKeypressed[KEY_PRESS_SURFACE_DEFAULT];
            while(!quit){
                while(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                        case SDLK_UP:
                            pSurface = gKeypressed[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_DOWN:
                            pSurface = gKeypressed[KEY_PRESS_SURFACE_DOWN];
                            break;
                        case SDLK_RIGHT:
                            pSurface = gKeypressed[KEY_PRESS_SURFACE_RIGHT];
                            break;
                        case SDLK_LEFT:
                            pSurface = gKeypressed[KEY_PRESS_SURFACE_LEFT];
                            break;
                        default:
                            pSurface = gKeypressed[KEY_PRESS_SURFACE_TOTAL];
                            break;
                    }
                }
            }
                SDL_Rect dest ;
                dest.x = 0;
                dest.y = 0;
                dest.w = WEIGHT_SCREEN;
                dest.h = HEIGHT_SCRENN;
                SDL_BlitSurface(pSurface,NULL,gSurface,&dest);
                SDL_UpdateWindowSurface(swindow);
        }
    }
    }
    close();
    return 0;
}
