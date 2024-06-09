#include "game.h"

int main() {
	InitWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "ZamozdraLand");
	InitAudioDevice();
	SetTargetFPS(60);

	Player pl = { 0, };
	Ball ball = { 0, };
	Mus = LoadMusicStream("Music.mp3");

	Main_Menu(&ball, &pl);

	CloseAudioDevice();
	CloseWindow();
	return 0;
}