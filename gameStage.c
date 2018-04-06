#include "gameStage.h"
int nxtlvl=150;
int nxtWave=200;
int canAddEag=1;

//*************
void createGame(gameVar* gamevar)
{
	printf("yo");
    gamevar->gameStage=NULL;
    gamevar->music=NULL;
    gamevar->bkg=NULL;
    gamevar->pause2=NULL;
    gamevar->scores=NULL;
	gamevar->heart=NULL;
	gamevar->ship=NULL;
	gamevar->bullets=NULL;
	gamevar->eaglesp=NULL;
	gamevar->boss=NULL;

    
    //stage
    gamevar->gameStage=Stage_create(WIDTH,HEIGHT,"Battle",0);
    
    //pause
    gamevar->pause2_rect={0,0,0,0};
    gamevar->pause2=IMG_Load("./assets/images/pause.png");
    SDL_GetClipRect(gamevar->pause2,&gamevar->pause2_rect);
    SDL_SetAlpha(gamevar->pause2,SDL_SRCALPHA,64);
    
    //background
    gamevar->bkg=ImageScrollingV_create(gamevar->gameStage->screen,"./assets/images/background2.png",-SPEED_SCROLLING/10);
    
    //label pause
    gamevar->pauselabel=Label_create(gamevar->gameStage->screen,"./assets/fonts/free.ttf",15);
    Label_setColor(gamevar->pauselabel,255,255,255);
    Label_setText(gamevar->pauselabel,"Touche p pour pause",250,23);



    //ship
    gamevar->ship=ship_create(gamevar->gameStage->screen,WIDTH/2,HEIGHT-HEIGHT/5);
    ship_setSpeedModule(gamevar->ship,0);

    //eaglesp
    gamevar->eaglesp=eaglesp_create(gamevar->gameStage->screen);
    //Heart
    gamevar->heart=heart_create(gamevar->gameStage->screen);
    //BULLET
    gamevar->bullets=bullets_create(gamevar->gameStage->screen);
    //boss
	gamevar->boss=boss_create(gamevar->gameStage->screen);
    
    //scores
    gamevar->scores=scores_create(gamevar->gameStage->screen,"./assets/files/scores.txt");
    scores_readScores(gamevar->scores);
    scores_reset(gamevar->scores);
    


    
    //music
    gamevar->music=Music_create("./assets/musics/lucgame.ogg");
    Music_setVolume(gamevar->music,FORT);
    Music_play(gamevar->music);
    
    

}

int startGame()
{
	printf("yo2");
    int now=0;
    int ex=0;
    int boucle=33;
    
    float delta_s=0.0;
    //
    gameVar gamevar;
	
	
    createGame(&gamevar);
    //
    Stage_start(gamevar.gameStage);
    gamevar.pause=(-1);
	gamevar.canpause=1;


    while(Stage_isRunning(gamevar.gameStage))
    {
        now=SDL_GetTicks();

         if((now-ex) > boucle)
        {
            delta_s=(now-ex)/1000.0;
            
            gamevar.gameevent=Stage_processEvent(gamevar.gameStage);
			eventGame(&gamevar);
			
			if (gamevar.pause !=1)	//Pause
			{
            updateGame(delta_s,& gamevar);
            renderGame(&gamevar);
            checkCollide(&gamevar);
               //Difficulty incr
				if(gamevar.scores->points > nxtlvl && canAddEag == 1){
				gamevar.eaglesp->nbr_eagles_now += 1;
				nxtlvl += 250;
				}
				//BossSpawn
				if(gamevar.scores->points > nxtWave ){
					canAddEag=0;
					for(int y=0 ; y < gamevar.eaglesp->nbr_eagles_now ; y++) {
					eagle_standby(gamevar.eaglesp->tabeagle[y]);
					}

				boss_setPosition(gamevar.boss,WIDTH/2-75, 150 );
				nxtWave += 250;
				}
			}
			
			if(gamevar.scores->lives == -1)	//GameOver
			{	
				    
					scores_changeBestScores(gamevar.scores);
					scores_writeScore(gamevar.scores);					
					Stage_stop(gamevar.gameStage);
				
					printf("close game\n");
			}
            ex=now;
        }
        else
        {
            SDL_Delay(boucle-(now-ex));
        }

    }
    //
	disposeGame(&gamevar);
    return 1;
}

//*******************************************************
void disposeGame(gameVar* gamevar)
{
	
	
    Music_dispose(gamevar->music);
    //
    ImageScrollingV_dispose(gamevar->bkg);
    //
    Label_dispose(gamevar->pauselabel);
	//
	boss_dispose(gamevar->boss);
	//
	scores_dispose(gamevar->scores);
	
    ship_dispose(gamevar->ship);
    //
    eaglesp_dispose(gamevar->eaglesp);
    //
    heart_dispose(gamevar->heart);
    //
    bullets_dispose(gamevar->bullets);
    //
    Stage_dispose(gamevar->gameStage);
}
//*******************************************************
void renderGame(gameVar* gamevar)
{
	
    Stage_render(gamevar->gameStage);
    //
    ImageScrollingV_render(gamevar->bkg);
    //
    Label_render(gamevar->pauselabel);
	//
	boss_render(gamevar->boss);
	//
	scores_render(gamevar->scores);
	
	eaglesp_render(gamevar->eaglesp);
    //
    heart_render(gamevar->heart);
    //
    bullets_render(gamevar->bullets);
    //
    ship_render(gamevar->ship);
    //
    Stage_flip(gamevar->gameStage);
     
}
//*******************************************************
void updateGame(float delta_s,gameVar* gamevar)
{

 
    scores_update(gamevar->scores);
    //
   boss_update(gamevar->boss);
    //
    bullets_update(NULL,gamevar->bullets,delta_s);
    //
    eaglesp_update(NULL,gamevar->eaglesp,delta_s);
    //
    heart_update(gamevar->heart);
    //
    ship_update(gamevar->ship,delta_s);
    //
    ImageScrollingV_update(gamevar->bkg);
   
}
//*******************************************************
void eventGame(gameVar* gamevar)
{
    switch(gamevar->gameevent.type)
	{
    //*************************KEYDOWN**********************************
    case SDL_KEYDOWN:
        
        switch(gamevar->gameevent.key.keysym.sym)

        {
        //
        case SDLK_ESCAPE:
           // Stage_stop(gamevar->gameStage);
           // printf("close game\n");
            break;

         //   
        //SHOOT
        
        case SDLK_SPACE:
                    
				if(gamevar->bullets->canshoot==1)
				{
				bullets_setPosSpeed(gamevar->bullets,Sprite_getCenterX(gamevar->ship->sprite)-3,Sprite_getCenterY(gamevar->ship->sprite)-10);
			    gamevar->bullets->shoot_i++;
			    gamevar->bullets->canshoot=0;
			    }
            break;

		//******************MOUVEMENT***********************************
        //
        case SDLK_UP:
			 ship_setSpeedModule(gamevar->ship,SHIP_SPEED);
             ship_setDirection(gamevar->ship,DIRECTION_UP);
            break;
        //
        case SDLK_DOWN:
			 ship_setSpeedModule(gamevar->ship,SHIP_SPEED);
             ship_setDirection(gamevar->ship,DIRECTION_DOWN);
            break;
        //
        case SDLK_RIGHT:
        	ship_setSpeedModule(gamevar->ship,SHIP_SPEED);
             ship_setDirection(gamevar->ship,DIRECTION_RIGHT);
            break;
        //
        case SDLK_LEFT:
			ship_setSpeedModule(gamevar->ship,SHIP_SPEED);
             ship_setDirection(gamevar->ship,DIRECTION_LEFT);
            break;
         //*************************************************************   
            
          case SDLK_p:
			if(gamevar->pause == -1 && gamevar->canpause ==1)
			{
				
				SDL_BlitSurface(gamevar->pause2, NULL, gamevar->gameStage->screen, &gamevar->pause2_rect);
				SDL_Flip(gamevar->gameStage->screen);
				gamevar->canpause=0;
				gamevar->pause = 1;
				Music_setVolume(gamevar->music,FAIBLE);
			}
			if(gamevar->pause == 1 && gamevar->canpause ==1)
			{
			    SDL_UpdateRect(gamevar->gameStage->screen,0,0,620,620);
				SDL_Flip(gamevar->gameStage->screen);
				gamevar->canpause=0;
				gamevar->pause = -1;
				Music_setVolume(gamevar->music,FORT);
			}
            break;
        default:
            break;

        }
        break;

    //******************KEYUP*******************************************
    case SDL_KEYUP:
        switch(gamevar->gameevent.key.keysym.sym)

        {
		//

        case SDLK_UP:
			if(gamevar->ship->direction == DIRECTION_UP)
			{ship_setSpeedModule(gamevar->ship,0);}
			 
            break;
        //
        case SDLK_DOWN:
				if(gamevar->ship->direction == DIRECTION_DOWN)	
				{ship_setSpeedModule(gamevar->ship,0);}
            break;
        //
        case SDLK_RIGHT:        			
			if(gamevar->ship->direction == DIRECTION_RIGHT)	
			{ship_setSpeedModule(gamevar->ship,0);}
			
            break;
        //
        case SDLK_LEFT:
			if(gamevar->ship->direction == DIRECTION_LEFT)	
			{ship_setSpeedModule(gamevar->ship,0);}
            break;

		//
          case SDLK_p:
				gamevar->canpause=1;
			break;
			 
        default: 
            break;

        }
    break;

    default:
        break;
    }
}
//*******************************************************
void checkCollide(gameVar* gamevar)
{ 
	
	//Ship & Eagles
	for(int i=0 ; i < gamevar->eaglesp->nbr_eagles_now ; i++) {
		if(Sprite_collidRect(gamevar->ship->sprite,gamevar->eaglesp->tabeagle[i]->sprite))
		{				
			
			//anim&sound
			eagle_hit(gamevar->eaglesp->tabeagle[i]);
			ship_touched(gamevar->ship);
			eaglesp_newWave(gamevar->eaglesp,i);
			scores_decrementLives(gamevar->scores);
		}
	}
	
	//Ship & Heart
	if(Sprite_collidRect(gamevar->ship->sprite,gamevar->heart->sprite))
	{
			
			scores_incrementLives(gamevar->scores);
			heart_Hit(gamevar->heart);
			//playsound
			Sound_play(gamevar->heart->sound);
	}
	
	//Bullet&Eagles
	for(int y=0 ; y < gamevar->eaglesp->nbr_eagles_now ; y++) {
		for(int i=0 ; i < gamevar->bullets->nbr_mun_now ; i++) {
			if(Sprite_collidRect(gamevar->bullets->tabbullet[i]->sprite,gamevar->eaglesp->tabeagle[y]->sprite))
			{	
				if(gamevar->bullets->tabbullet[i]->type == BULLET_TYPE_2){
				eagle_hit(gamevar->eaglesp->tabeagle[y]);
				scores_incrementPoints(gamevar->scores,10);
				eaglesp_newWave(gamevar->eaglesp,y);
				bullet_reset(gamevar->bullets->tabbullet[i]);//à enlever pour bonus ?
				bullet_hit(gamevar->bullets->tabbullet[i]);
				gamevar->bullets->tab_n[i]=1;
				gamevar->eagleskilled++;
				}
						
			}
		}
	}
	//SHIP&BULLET
	for(int i=0 ; i < gamevar->eaglesp->nbr_eagles_now ; i++) {
			if(Sprite_collidRect(gamevar->eaglesp->tabeagle[i]->bullet->sprite,gamevar->ship->sprite))
			{	
				
				ship_touched(gamevar->ship);
				scores_decrementLives(gamevar->scores);
				bullet_reset(gamevar->eaglesp->tabeagle[i]->bullet);//à enlever pour bonus ?
				bullet_hit(gamevar->eaglesp->tabeagle[i]->bullet);			
						
			}
		}
		
	//BOSS_bullet&SHIP
		
	for(int i=0; i< gamevar->boss->nbr_bullets; i++){
		if( gamevar->ship->hit != 1){
		if(Sprite_collidRect(gamevar->boss->tabbullet2[i]->sprite,gamevar->ship->sprite)){
		scores_decrementLives(gamevar->scores);
		bullet_reset(gamevar->boss->tabbullet2[i]);//à enlever pour bonus ?
		bullet_hit(gamevar->boss->tabbullet2[i]);
		ship_touched(gamevar->ship);
		}
		}	
	}
	
	//BOSS&Ship_Bullet
		for(int i=0 ; i < gamevar->bullets->nbr_mun_now ; i++) {
			if(Sprite_collidRect(gamevar->bullets->tabbullet[i]->sprite,gamevar->boss->sprite))
			{	
				int x = Sprite_getCenterX(gamevar->bullets->tabbullet[i]->sprite)-20;
				int y = Sprite_getCenterY(gamevar->bullets->tabbullet[i]->sprite)-50;
								
				bullet_reset(gamevar->bullets->tabbullet[i]);//à enlever pour bonus ?
				bullet_hit(gamevar->bullets->tabbullet[i]);
				gamevar->bullets->tab_n[i]=1;
				int isdead=boss_hit(gamevar->boss,x,y);
				if(isdead && canAddEag != 1){
				canAddEag=1;
				scores_incrementPoints(gamevar->scores,50);
					for(int y=0 ; y < gamevar->eaglesp->nbr_eagles_now ; y++){ 
					eaglesp_newWave(gamevar->eaglesp,y);
					gamevar->eaglesp->tabeagle[y]->canupdate=1;
					}
				//mort
				}
				
						
			}
		}
	 
}

