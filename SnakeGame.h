#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

// Function Declarations
void Setup();
void Draw();
void Input();
void Logic();

// Constants
const int width = 20;
const int height = 20;

// Enumerations
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

// Global Variables
extern bool gameover;
extern int x, y, fruitX, fruitY, score;
extern int tailX[100], tailY[100];
extern int nTail;
extern eDirection dir;
extern int delayTime;
extern bool paused;
extern time_t startTime;
extern time_t pauseStartTime;
extern int elapsedPauseTime;

#endif
