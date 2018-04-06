#ifndef SCORES_H_INCLUDED
#define SCORES_H_INCLUDED

#include "GameEngine.h"
#include <stdio.h>
#include <stdlib.h>

//
typedef struct Scores Scores;

struct Scores{
int points;
int lives;
int incremente;

int bestOne;
int bestTwo;
int bestThree;

Label* labelPoints;
Sprite* tabHeart[3];
char* filetxt;

};
//
Scores* scores_create(SDL_Surface* screen, char* filetext);
//
int scores_getLastPoint(const Scores* scores);
//
int scores_getBestOne(const Scores* scores);
//
int scores_getBestTwo(const Scores* scores);
//
int scores_getBestThree(const Scores* scores);
//
int scores_getLives(const Scores* scores);
//
void scores_readScores(Scores* scores);
//
void scores_writeScore(Scores* scores);
//
void scores_changeBestScores(Scores* scores);
//
void scores_reset(Scores* scores);
//
void scores_incrementPoints(Scores* scores,int amt);
//
void scores_decrementLives(Scores* scores);
//
void scores_incrementLives(Scores* scores);
//
void scores_update(Scores* scores);
//
void scores_render(Scores* scores);
//
void scores_dispose(Scores* scores);


#endif // SCORES_H_INCLUDED
