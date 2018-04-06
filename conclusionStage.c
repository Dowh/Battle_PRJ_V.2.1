#include "conclusionStage.h"

int startConclusion()
{
    int now=0;
    int ex=0;
    int boucle=33;

    char buffer[50];
    char yo[50];
    FILE* pseudo=NULL;
    concluVar concluvar;

    //
    concluvar.concluScreen=NULL;
    concluvar.concluMusic=NULL;
    concluvar.sortir=0;
    concluvar.concluScores=NULL;
    concluvar.labelActionExit=NULL;
    concluvar.labelPoints=NULL;
    concluvar.labelBestOne=NULL;
    concluvar.labelBestTwo=NULL;
    concluvar.labelBestThree=NULL;
    concluvar.labelpseudo=NULL;
    concluvar.labelrejouer=NULL;
    //

    concluvar.concluScreen=Stage_create(WIDTH,HEIGHT,"Conclusion Battle",0);
    
    concluvar.bkg=ImageScrollingV_create(concluvar.concluScreen->screen,"./assets/images/background2.png",-SPEED_SCROLLING/10);

    //scores
    concluvar.concluScores=scores_create(concluvar.concluScreen->screen,"./assets/files/scores.txt");
    scores_readScores(concluvar.concluScores);

    int points=scores_getLastPoint(concluvar.concluScores);
    int bestOne=scores_getBestOne(concluvar.concluScores);
    int bestTwo=scores_getBestTwo(concluvar.concluScores);
    int bestThree=scores_getBestThree(concluvar.concluScores);

    //label exit
    concluvar.labelActionExit=Label_create(concluvar.concluScreen->screen,"./assets/fonts/free.ttf",35);

    Label_setColor(concluvar.labelActionExit,0,200,255);
    Label_setText(concluvar.labelActionExit,"Appuyez sur Echap pour quitter",30,50);
    
    //label pseudo
    concluvar.labelpseudo=Label_create(concluvar.concluScreen->screen,"./assets/fonts/free.ttf",40);
    Label_setColor(concluvar.labelpseudo,255,255,255);

    pseudo=fopen("./assets/files/pseudo.txt","r");
    fgets(yo,50,pseudo);
    sprintf(buffer,"Felicitations %s !", yo);
    Label_setText(concluvar.labelpseudo,buffer,20,150);
    fclose(pseudo);
    
   //label points
    concluvar.labelPoints=Label_create(concluvar.concluScreen->screen,"./assets/fonts/free.ttf",30);
    Label_setColor(concluvar.labelPoints,255,105,0);
    sprintf(buffer,"Ton score = %d", points);
    Label_setText(concluvar.labelPoints,buffer,10,250);
    
    //label BestOne
    concluvar.labelBestOne=Label_create(concluvar.concluScreen->screen,"./assets/fonts/free.ttf",30);
    Label_setColor(concluvar.labelBestOne,255,155,50);
    //
    sprintf(buffer,"Meilleur score = %d",bestOne);
    Label_setText(concluvar.labelBestOne,buffer,10,300);

    //label BestTwo
    concluvar.labelBestTwo=Label_create(concluvar.concluScreen->screen,"./assets/fonts/free.ttf",30);
    Label_setColor(concluvar.labelBestTwo,255,205,100);
    sprintf(buffer,"Deuxieme meilleur = %d",bestTwo);
    Label_setText(concluvar.labelBestTwo,buffer,10,350);

    //label BestThree
    concluvar.labelBestThree=Label_create(concluvar.concluScreen->screen,"./assets/fonts/free.ttf",30);
    Label_setColor(concluvar.labelBestThree,255,255,150);
    sprintf(buffer,"Troiseme meilleur = %d",bestThree);
    Label_setText(concluvar.labelBestThree,buffer,10,400);
    
    //label rejouer
    concluvar.labelrejouer=Label_create(concluvar.concluScreen->screen,"./assets/fonts/free.ttf",35);
    Label_setColor(concluvar.labelrejouer,0,128,255);
    Label_setText(concluvar.labelrejouer,"Rejouer = Espace",160,500);

    //music
    concluvar.concluMusic=Music_create("./assets/musics/lucgame.ogg");
    Music_setVolume(concluvar.concluMusic,MOYEN);
    //Music_play(concluvar.concluMusic);

    Stage_start(concluvar.concluScreen);

    //
    while(Stage_isRunning(concluvar.concluScreen))
    {
        now=SDL_GetTicks();

        if((now-ex) > boucle)
        {
            concluvar.event=Stage_processEvent(concluvar.concluScreen);

            eventConclusion(& concluvar);

            updateConclusion(&concluvar);

            renderConclusion(&concluvar);

            ex=now;
        }
        else
        {
            SDL_Delay(boucle-(now-ex));
        }
        //
    }
    //
    disposeConclusion(&concluvar);

    return concluvar.sortir;
}
//******************************************
void disposeConclusion(concluVar* concluvar)
{
    scores_dispose(concluvar->concluScores);
    //
    ImageScrollingV_dispose(concluvar->bkg);
    //
    Label_dispose(concluvar->labelActionExit);
    //

    //
    Label_dispose(concluvar->labelPoints);
    //
    Label_dispose(concluvar->labelBestOne);
    //
    Label_dispose(concluvar->labelBestTwo);
    //
    Label_dispose(concluvar->labelBestThree);
    //
    Label_dispose(concluvar->labelpseudo);
    //
    Label_dispose(concluvar->labelrejouer);
    //
    Music_dispose(concluvar->concluMusic);
    //
    Stage_dispose(concluvar->concluScreen);
}
//*****************************************
void renderConclusion(concluVar* concluvar)
{
    Stage_render(concluvar->concluScreen);
    //
    ImageScrollingV_render(concluvar->bkg);
    //
    Label_render(concluvar->labelActionExit);
    //
    Label_render(concluvar->labelPoints);
    //
    Label_render(concluvar->labelBestOne);
    //
    Label_render(concluvar->labelBestTwo);
    //
    Label_render(concluvar->labelBestThree);
	//
    Label_render(concluvar->labelpseudo);
    //
    Label_render(concluvar->labelrejouer);
	//
    Stage_flip(concluvar->concluScreen);
}
//*****************************************
void updateConclusion(concluVar* concluvar)
{
    ImageScrollingV_update(concluvar->bkg);
}
//****************************************
void eventConclusion(concluVar* concluvar)
{
    switch(concluvar->event.type)
    {
    //
    case SDL_KEYDOWN:

        switch(concluvar->event.key.keysym.sym)
        {
        //
        case SDLK_ESCAPE:
            Stage_stop(concluvar->concluScreen);
            concluvar->sortir=1;
            break;
            
		case SDLK_SPACE:
            startGame();
           
            break;

        //
        default:
            break;

        }
        break;
    //
    default:
        break;
    }
}
//**************************************
int exitConclusion(concluVar* concluvar)
{
    return concluvar->sortir;
}
