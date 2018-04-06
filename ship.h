#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "GameEngine.h"
#include "Constantes.h"
#include "animFrame.h"

typedef struct Ship Ship;

struct Ship
{
Sprite* sprite;
int direction;
int hit;
AnimFrame* anim;

Animation* explo;
};

//
Ship* ship_create(SDL_Surface* screen,int xp,int yp);
//
void ship_dispose(Ship* ship);
//
void ship_update(Ship* ship,float delta);
//
void ship_render(Ship* ship);
//
void ship_setDirection(Ship* ship,int direction);
//
void ship_setSpeedModule(Ship* ship,float module);
//
void ship_changeDirection(Ship* ship);
//
void ship_touched(Ship* ship);
//
#endif // SHIP_H_INCLUDED
