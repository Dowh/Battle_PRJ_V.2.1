#include "Scores.h"
#include "Constantes.h"
//
Scores* scores_create(SDL_Surface* screen, char* filetext)
{
    int x=0;

    Scores* pscore=NULL;

    pscore=(Scores*)malloc(sizeof(Scores));

    if(pscore==NULL)
        return NULL;
    //
    else
    {
        pscore->points=0;
        pscore->lives=3;
        pscore->bestOne=3;
        pscore->bestTwo=2;
        pscore->bestThree=1;

        //label
        pscore->labelPoints=Label_create(screen,"./assets/fonts/free.ttf",30);
        Label_setColor(pscore->labelPoints,55,0,55);
        Label_setText(pscore->labelPoints,"Points",0,0);

        //
        pscore->tabHeart[0]=NULL;
        pscore->tabHeart[0]=Sprite_create(screen,"./assets/images/heart.png");
        x=WIDTH-32;
        Sprite_setPosition(pscore->tabHeart[0],x,16);

        pscore->tabHeart[1]=NULL;
        pscore->tabHeart[1]=Sprite_create(screen,"./assets/images/heart.png");
        x-=32;
        Sprite_setPosition(pscore->tabHeart[1],x,16);

        pscore->tabHeart[2]=NULL;
        pscore->tabHeart[2]=Sprite_create(screen,"./assets/images/heart.png");
        x-=32;
        Sprite_setPosition(pscore->tabHeart[2],x,16);

        //file txt
        pscore->filetxt=filetext;

    }
    return pscore;
}
//
int scores_getLastPoint(const Scores* scores)
{
    return scores->points;
}
//
int scores_getBestOne(const Scores* scores)
{
    return scores->bestOne;
}
//
int scores_getBestTwo(const Scores* scores)
{
    return scores->bestTwo;
}
//
int scores_getBestThree(const Scores* scores)
{
    return scores->bestThree;
}
//
void scores_readScores(Scores* scores)
{
    FILE* fiche=NULL;

    char buffer[10]={0};

    fiche=fopen(scores->filetxt,"r");
    //
    if(fiche==NULL)
    {
        printf("Error fichier score \n");
    }
    else
    {
        //fscanf(fiche,"%d %d %d %d",&scores->points, &scores->bestOne, &scores->bestTwo, &scores->bestThree);
        fgets(buffer,10,fiche);
        scores->points=atoi(buffer);
        //
        fgets(buffer,10,fiche);
        scores->bestOne=atoi(buffer);

        //
        fgets(buffer,10,fiche);
        scores->bestTwo=atoi(buffer);
        //
        fgets(buffer,10,fiche);
        scores->bestThree=atoi(buffer);
        //
        //
        fclose(fiche);
    }
}
//
int scores_getLives(const Scores* scores)
{
    return scores->lives;
}
//
void scores_writeScore(Scores* scores)
{
    FILE* fiche=NULL;

    fiche=fopen(scores->filetxt,"w");
    //
    if(fiche==NULL)
    {
        printf("Error fichier score \n");
    }
    else
    {
        fprintf(fiche,"%d \n",scores->points);
        //
        fprintf(fiche,"%d \n",scores->bestOne);
        //
        fprintf(fiche,"%d \n",scores->bestTwo);
        //
        fprintf(fiche,"%d \n",scores->bestThree);

        fclose(fiche);
    }
}
//
void scores_changeBestScores(Scores* scores)
{
    if(scores->points >=scores->bestOne)
    {	
		printf("bestone");
        scores->bestThree=scores->bestTwo;
        scores->bestTwo=scores->bestOne;
        scores->bestOne=scores->points;
        return;
    }
    //
	if(scores->points >= scores->bestTwo)
    {
		printf("besttwo");
        scores->bestThree=scores->bestTwo;
        scores->bestTwo=scores->points;
        return;
    }
    //
    if(scores->points >= scores->bestThree)
    {
		printf("bestthree");
         scores->bestThree=scores->points;
         return;
    }
}
//
void scores_reset(Scores* scores)
{
    scores->points=0;
    scores->lives=3;
}
//
void scores_incrementPoints(Scores* scores,int amt)
{
    scores->points += amt;
}
//
void scores_decrementLives(Scores* scores)
{
    scores->lives--;

    if(scores->lives <=-1)
        scores->lives =-1;  //gameOver
}
//
void scores_incrementLives(Scores* scores)
{
    scores->lives++;

    if(scores->lives >3)
        scores->lives=3;
}
//
void scores_update(Scores* scores)
{
    static char buffer[20]= {"\0"};
    
    if(scores->incremente++>30)
    {
    scores->points++;
    scores->incremente=0;
    }

    sprintf(buffer,"Points = %d",scores->points);

    Label_setText(scores->labelPoints,buffer,16,16);
}
//
void scores_render(Scores* scores)
{
    int i=0;

    //label point
    Label_render(scores->labelPoints);

    if(scores->lives <=0)
        return;

    //heart
    for(i=0; i<scores->lives; i++)
    {
        Sprite_render(scores->tabHeart[i]);
    }
}
//
void scores_dispose(Scores* scores)
{
    int i=0;

    //label point
    Label_dispose(scores->labelPoints);

    //heart
    for(i=0; i<3; i++)
    {
        Sprite_dispose(scores->tabHeart[i]);
        scores->tabHeart[i]=NULL;
    }
    //
    free(scores);
    scores=NULL;
}
//
