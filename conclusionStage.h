#ifndef CONCLUSIONSTAGE_H_INCLUDED
#define CONCLUSIONSTAGE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#include "GameEngine.h"
#include "gameStage.h"
#include "Scores.h"
#include "Constantes.h"

//
typedef struct concluVar concluVar;

struct concluVar{

Stage* concluScreen;
SDL_Event event;

Music* concluMusic;

int sortir;

Scores* concluScores;
ImageScrollingV* bkg;

Label* labelActionExit;
Label* labelPoints;
Label* labelBestOne;
Label* labelBestTwo;
Label* labelBestThree;
Label* labelpseudo;
Label* labelrejouer;
};

//
int startConclusion();
//
void disposeConclusion(concluVar* concluvar);
//
void renderConclusion(concluVar* concluvar);
//
void updateConclusion(concluVar* concluvar);
//
void eventConclusion(concluVar* concluvar);
//
int exitConclusion(concluVar* concluvar);

#endif // CONCLUSIONSTAGE_H_INCLUDED
