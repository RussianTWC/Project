#pragma once
#include "raylib.h"
#include <stdio.h>

#define WIDTH_SCREEN	1080
#define HEIGHT_SCREEN	720

_Bool isQuit;
int SpeedRot;

Texture2D BackGround;
Texture2D Ast;
Texture2D Zam;
size_t Player_Score;
Music Mus;
Sound ClickBnt;
Sound FX;

Rectangle sourse;
Rectangle dest;

typedef struct Player {
	Vector2 pos;
	int Width, Height;
	int Speed;
}Player;

typedef struct Ball {
	Vector2 pos;
	int speed_x, speed_y;
	float radius;
}Ball;

typedef struct Block {
	Vector2 pos;
	int Width, Height;
}Block;

typedef struct Button {
	Rectangle Form;
	const char* Message;
	_Bool Action;
	Color color;
}Button;

Block InstanceBlock;

Block Array_of_blocks[5][18];

void InitArr();
void Draw(Player* pl, Ball* bl);
void UpdatePl(Player* pl);
void UpdateBall(Ball* bl);
void CheckMousePosition(Button* button);

void Start_Game(Ball* ball, Player* pl);

void Main_Menu(Ball* ball, Player* pl);