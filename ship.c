#include "ship.h"
int i=0;
int incr=0;
//****************************************************
Ship* ship_create(SDL_Surface* screen,int xp,int yp)
{
    Ship* ship=NULL;

    ship=(Ship*)malloc(sizeof(Ship));

    if(ship==NULL)
        return NULL;

    else
    {
        ship->sprite=NULL;

        ship->sprite=Sprite_create(screen,"./assets/images/Terre1.png");

        Sprite_setCollidRectInflate(ship->sprite,1,10);
        //Sprite_setDebugRect(ship->sprite,1);//DEBUG RECT
        
        Sprite_setCenter(ship->sprite,xp,yp);

        Sprite_setSpeedModule(ship->sprite,SHIP_SPEED);

        Sprite_setState(ship->sprite,SHIP_STATE_ON);
        
        
         ship->explo=Animation_create(screen,"./assets/images/explosion.png",5,5);
		Animation_loadSound(ship->explo,"./assets/sounds/Ship Explod Ennemy.ogg");
		Sound_setVolume(ship->explo->sound,MOYEN);
 
	
    }
    return ship;
}
//******************************
void ship_dispose(Ship* ship)
{
	    //
    if(ship->sprite != NULL)
    {
        Sprite_dispose(ship->sprite);
        ship->sprite=NULL;
    }
    Animation_dispose(ship->explo);
    //
    free(ship);
}
//*****************************************
void ship_update(Ship* ship,float delta)
{
	if(ship->hit = 1)
	incr++;
	
	if(incr > 5){	
	incr=0; 
	ship->hit=0;
	
	}
	
    Sprite_update(ship->sprite);
    Animation_update(ship->explo);
    //limite haute
    if(Sprite_getTop(ship->sprite) <=HEIGHT-HEIGHT/3)
    {
        Sprite_setTop(ship->sprite,HEIGHT-HEIGHT/3);
    }

    //limite basse
    if(Sprite_getBottom(ship->sprite) >=HEIGHT)
    {
        Sprite_setBottom(ship->sprite,HEIGHT);

    }
    
    //limite gauche
    if(Sprite_getLeft(ship->sprite) <=0)
    {
        Sprite_setLeft(ship->sprite,0);
    }
    
    //limite droite
    if(Sprite_getRight(ship->sprite) >=WIDTH)
    {
        Sprite_setRight(ship->sprite,WIDTH);
    }
}
//*****************************
void ship_render(Ship* ship)
{
    int st=Sprite_getState(ship->sprite);

    if(st==SHIP_STATE_ON)
    {
         Sprite_render(ship->sprite);
    }
    else{
		i++;
		if( i > 8){
		Sprite_setState(ship->sprite,SHIP_STATE_ON);
		i=0;
		}
	}
    Animation_render(ship->explo);
    //
}
//************************************************
void ship_setDirection(Ship* ship,int direction)
{

    switch(direction)
    {
    //
    case DIRECTION_DOWN:
        ship->direction=DIRECTION_DOWN;
        Sprite_setDirectionDeg(ship->sprite,270);
        break;

    //
    case DIRECTION_UP:
        ship->direction=DIRECTION_UP;
        Sprite_setDirectionDeg(ship->sprite,90);
        break;

    //
    case DIRECTION_RIGHT:
        ship->direction=DIRECTION_RIGHT;
        Sprite_setDirectionDeg(ship->sprite,0);
        break;

    //
    case DIRECTION_LEFT:
        ship->direction=DIRECTION_LEFT;
        Sprite_setDirectionDeg(ship->sprite,180);
        break;

    //
    default:
        break;

    }

}
//**************************************************
void ship_setSpeedModule(Ship* ship,float module)
{
    Sprite_setSpeedModule(ship->sprite,module);
}
//**************************************
void ship_changeDirection(Ship* ship)
{
    int direction=ship->direction;

    switch(direction)
    {
    //
    case DIRECTION_DOWN:
        ship->direction=DIRECTION_UP;
        Sprite_setDirectionDeg(ship->sprite,90);
        break;

    //
    case DIRECTION_UP:
        ship->direction=DIRECTION_DOWN;
        Sprite_setDirectionDeg(ship->sprite,270);
        break;

    //
    case DIRECTION_LEFT:
        ship->direction=DIRECTION_RIGHT;
        Sprite_setDirectionDeg(ship->sprite,0);
        break;

    //
    case DIRECTION_RIGHT:
        ship->direction=DIRECTION_LEFT;
        Sprite_setDirectionDeg(ship->sprite,180);
        break;

    //
    default:
        break;
    }

}
//*******************************
void ship_touched(Ship* ship)
{
    Sprite_setState(ship->sprite,SHIP_STATE_TOUCHED);
    int xp=Sprite_getX(ship->sprite);
    int yp=Sprite_getY(ship->sprite);
    
	ship->hit=1;
	//Add anim
	Animation_setPosition(ship->explo,Sprite_getLeft(ship->sprite)-30,Sprite_getTop(ship->sprite)-30);
	Animation_play(ship->explo);
	Animation_playSound(ship->explo);

}
//
