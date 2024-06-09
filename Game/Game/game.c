#include "game.h"

void InitArr() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 18; j++) {
			Array_of_blocks[i][j] = InstanceBlock;
			InstanceBlock.pos.x += InstanceBlock.Width + 5;
		}
		InstanceBlock.pos.x = 50;
		InstanceBlock.pos.y += InstanceBlock.Height + 5;
	}
}

void Draw(Player* pl, Ball* bl) {
	DrawTexture(BackGround, 0, 0, WHITE);

	DrawRectangle(pl->pos.x, pl->pos.y, pl->Width, pl->Height, GRAY);
	/*DrawCircle(bl->pos.x, bl->pos.y, bl->radius, WHITE);*/
	/*DrawTexture(Ast, bl->pos.x, bl->pos.y, WHITE);*/
	DrawTexturePro(Ast, sourse, dest, (Vector2) { bl->radius, bl->radius }, SpeedRot * 45 * (float)GetTime(), WHITE);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 18; j++) {
			//DrawRectangle(Array_of_blocks[i][j].pos.x, Array_of_blocks[i][j].pos.y, Array_of_blocks[i][j].Width, Array_of_blocks[i][j].Height, DARKGRAY);
			DrawTexture(Zam, Array_of_blocks[i][j].pos.x, Array_of_blocks[i][j].pos.y, WHITE);
		}
	}
	DrawText(TextFormat("Score: %zd", Player_Score), 5, 5, 20, WHITE);
}

void UpdatePl(Player* pl) {
	if (IsKeyDown(KEY_A)) {
		pl->pos.x -= pl->Speed;
	}
	if (IsKeyDown(KEY_D)) {
		pl->pos.x += pl->Speed;
	}
	if (pl->pos.x < 0) {
		pl->pos.x = 0;
	}
	if (pl->pos.x + pl->Width > WIDTH_SCREEN) {
		pl->pos.x = WIDTH_SCREEN - pl->Width;
	}
}

void UpdateBall(Ball* bl) {
	bl->pos.x += bl->speed_x;
	bl->pos.y += bl->speed_y;

	if (bl->pos.x + bl->radius >= WIDTH_SCREEN || bl->pos.x - bl->radius <= 0) {
		PlaySound(FX);
		bl->speed_x *= -1;
		SpeedRot *= -1;
	}
	if (bl->pos.y - bl->radius <= 0) {
		PlaySound(FX);
		bl->speed_y *= -1;
		SpeedRot *= -1;
	}
	if (bl->pos.y + bl->radius >= HEIGHT_SCREEN) {
		bl->speed_x = 0;
		bl->speed_y = 0;
		bl->pos = (Vector2){ WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2 - 10 };
		SpeedRot = 0;
	}
}

void CheckMousePosition(Button* button) {
	if (CheckCollisionPointRec(GetMousePosition(), button->Form)) {
		button->color = LIGHTGRAY;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			PlaySound(ClickBnt);
			button->Action = 1;
			button->color = RED;
		}
	}
	else {
		button->Action = 0;
		button->color = DARKBLUE;
	}
}

void Start_Game(Ball* ball, Player* pl) {
	isQuit = 0;
	SpeedRot = 5;
	
	Ast = LoadTexture("Ast.png");
	Zam = LoadTexture("Zamozdra.png");

	Player_Score = 0;
	FX = LoadSound("Kick.mp3");

	pl->Width = 150;
	pl->Height = 25;
	pl->pos.x = WIDTH_SCREEN / 2 - pl->Width;
	pl->pos.y = HEIGHT_SCREEN - pl->Height - 25;
	pl->Speed = 10;

	ball->pos.x = WIDTH_SCREEN / 2;
	ball->pos.y = HEIGHT_SCREEN / 2;
	ball->radius = 15;
	ball->speed_x = 5;
	ball->speed_y = 7;

	InstanceBlock.pos.x = 50;
	InstanceBlock.pos.y = 40;

	InstanceBlock.Width = 50;
	InstanceBlock.Height = 50;
	InitArr();

	while (WindowShouldClose() == 0)
	{
		sourse = (Rectangle){ 0, 0, ball->radius * 2, ball->radius * 2 };
		dest = (Rectangle){ (float)ball->pos.x, (float)ball->pos.y, sourse.width, sourse.height };
		UpdateMusicStream(Mus);
		if (isQuit == 0) {
			UpdatePl(pl);
			UpdateBall(ball);
		}
		if (CheckCollisionCircleRec(ball->pos, ball->radius, (Rectangle) { pl->pos.x, pl->pos.y, pl->Width, pl->Height })) {
			ball->speed_y *= -1;
			PlaySound(FX);
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 18; j++) {
				if (CheckCollisionCircleRec(ball->pos, ball->radius, (Rectangle) {
					Array_of_blocks[i][j].pos.x, Array_of_blocks[i][j].pos.y,
						Array_of_blocks[i][j].Width, Array_of_blocks[i][j].Height
				})) {
					PlaySound(FX);
					Array_of_blocks[i][j] = (Block){ -50, };
					ball->speed_y *= -1;
					Player_Score++;
				}
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		Draw(pl, ball);

		if (ball->speed_x == 0 && ball->speed_y == 0 && IsKeyDown(KEY_Q) == 0) {
			DrawText("You Lose. Press \"Q\" to exit", WIDTH_SCREEN / 2 - 350, HEIGHT_SCREEN / 2, 50, WHITE);
			isQuit = 1;
		}
		if (Player_Score == 90) {
			DrawText("You Win. Press \"Q\" to exit", WIDTH_SCREEN / 2 - 350, HEIGHT_SCREEN / 2, 50, WHITE);
			isQuit = 1;
		}

		if (isQuit && IsKeyDown(KEY_Q)) {
			return;
		}

		EndDrawing();
	}
}

void Main_Menu(Ball* ball, Player* pl) {
	Button Start = { 0, };

	Start.Form = (Rectangle){WIDTH_SCREEN/2 - 150, HEIGHT_SCREEN/2-100,  300, 150};
	Start.Message = "Start Game";
	Start.Action = 0;
	Start.color = DARKBLUE;

	Button Exit = { 0, };

	Exit.Form = (Rectangle){WIDTH_SCREEN/2 - 150, HEIGHT_SCREEN - 300, 300, 150};
	Exit.Message = "Exit";
	Exit.Action = 0;
	Exit.color = DARKBLUE;

	BackGround = LoadTexture("Space.png");
	ClickBnt = LoadSound("Bnt.mp3");

	PlayMusicStream(Mus);
	while (WindowShouldClose() == 0)
	{
		CheckMousePosition(&Start);
		CheckMousePosition(&Exit);

		UpdateMusicStream(Mus);

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(BackGround, 0, 0, WHITE);

		DrawText("Arkanoid", WIDTH_SCREEN/2 - 200, 100, 100, WHITE);

		DrawRectangle(Start.Form.x, Start.Form.y, Start.Form.width, Start.Form.height, Start.color);
		DrawRectangleLines(Start.Form.x, Start.Form.y, Start.Form.width, Start.Form.height, GRAY);
		DrawText(Start.Message, Start.Form.x+7, Start.Form.y+50, 50, WHITE);

		DrawRectangle(Exit.Form.x, Exit.Form.y, Exit.Form.width, Exit.Form.height, Exit.color);
		DrawRectangleLines(Exit.Form.x, Exit.Form.y, Exit.Form.width, Exit.Form.height, GRAY);
		DrawText(Exit.Message, Exit.Form.x+100, Exit.Form.y+50, 50, WHITE);

		EndDrawing();

		if (Start.Action) {
			Start_Game(ball, pl);
			Start.Action = 0;
		}
		if (Exit.Action) {
			return;
		}
	}
}