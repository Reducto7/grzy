#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SceneID scene;
ObjectID kid, ball, end;
ObjectID brick[106];
ObjectID up[26];
ObjectID down[18];
ObjectID left[17];
ObjectID right[12];


int x = 105, y = 350;
int dx = 0, dy = 0;


#define ANIMATION_TIME		0.01f
#define ANIMATION_STEP		6


int brickX[106] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 240, 290, 340, 390, 440, 490, 540, 590, 640, 690, 740, 790, 840, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1230, 1230, 1230, 1230, 1230, 1230, 1230, 1230, 1230, 1230, 1230, 1230, 1230, 1230 };
int brickY[106] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700 };

int leftX[17] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 1050, 1080, 1110, 1050, 1080, 1110};
int leftY[17] = {50, 120, 190, 260, 330, 400, 470, 540, 610, 680, 750, 150, 150, 150, 500, 500, 500};

int rightX[12] = { 121, 121, 121, 121, 121, 121, 121, 121, 121, 1161, 1131, 1101};
int rightY[12] = { 50, 120, 190, 260, 330, 400, 470, 540, 587, 330, 330, 330};

int upX[26] = {240, 310, 380, 450, 520, 590, 660, 730, 800, 823, 600, 600, 600, 600, 860, 930, 240, 310, 380, 450, 520, 590, 660, 730, 800, 823 };
int upY[26] = {538, 538, 538, 538, 538, 538, 538, 538, 538, 538, 231, 200, 170, 140, 231, 231, 508, 508, 508, 508, 508, 508, 508, 508, 508, 508 };

int downX[18] = {350, 420, 490, 560, 630, 700, 770, 840, 910, 933, 240, 310, 380, 600, 860, 860, 860, 860};
int downY[18] = {350, 350, 350, 350, 350, 350, 350, 350, 350, 350, 50, 50, 50, 50, 50, 80, 110, 140};

void keyboardCallback(KeyCode code, KeyState state)
{
	if (code == KeyCode::KEY_SPACE) {
		dy += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_RIGHT_ARROW) {
		dx += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		setObjectImage(kid, "Images/kid.png");
	}
	else if (code == KeyCode::KEY_LEFT_ARROW) {
		dx -= (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		setObjectImage(kid, "Images/kid2.tga");
	}
} 

void timerCallback(TimerID timer)
{
	x += dx; y += dy;
	locateObject(kid, scene, x, y);

	setTimer(timer, ANIMATION_TIME);
	startTimer(timer);
    if (x >= 1115 && x <= 1200 && y >= 600 && y <= 652) {
		stopTimer(timer);
		showMessage("CONGRATULATION!");
		playSound(sound1);
		showObject(end);
	}
    else if (x < 80 || x > 120 && x < 160 && y < 656) { // 区域1死亡
		stopTimer(timer);
		x = 105, y = 350;
		startTimer(timer);
		showMessage("dead!");
	}
	else if (x > 240 && x < 890 && y > 508 && y < 538 || x > 350 && x < 1000 && y > 350 && y < 380 || x > 190 && x < 440 && y > 40 && y < 80) { // 区域2死亡
		stopTimer(timer);
		x = 840, y = 660;
		startTimer(timer);
		showMessage("dead!");
	}
	else if (x > 565 && x < 655 && y > 40 && y < 80 || x > 565 && x < 655 && y > 150 && y < 310) { // 区域3中死亡
		stopTimer(timer);
		x = 500, y = 60;
		startTimer(timer);
		showMessage("dead!");
	}
	else if (x > 825 && x < 915 && y > 40 && y < 170 || x > 825 && x < 1010 && y > 240 && y < 310) { // 区域3右死亡
		stopTimer(timer);
		x = 500, y = 60;
		startTimer(timer);
		showMessage("dead!");
	}
	else if (x > 1050 && x < 1130 && y > 115 && y < 220 || x > 1050 && x < 1130 && y > 465 && y < 570 || x > 1105 && x < 1230 && y > 295 && y < 400) { //右侧区域死亡
		stopTimer(timer);
		x = 1000, y = 60;
		startTimer(timer);
		showMessage("dead!");
	}
	else if (y > 680 || y < 270 && y > 260 && x > 350 && x < 980) { // 最上方上墙+中下方上墙
		y -= 6;
	}
	else if (y < 603 && x > 230 && x < 240 || x > 1040  &&x < 1050 && y >= 100) { //中间区域左墙+右侧区域左墙
		x += 6;
	}
	else if (y > 70 && x > 960 && x < 970 || x > 1185) { //中间区域右墙+右侧区域右墙
		x -= 6;
	}
	else if (x > 880 && x < 890 && y > 607 && y < 657) { //右上方左墙
		x += 6;
	}
	else if (x > 310 && x < 320 && y > 300 && y < 350 ) { //左下方右墙
		x -= 6;
	}
	else if (x >= 970 && x <= 1040 && y > 60 && y < 70) { //右下区域上墙
		y -= 6;
	}
	else if (x >= 240 && x <= 1000 && y >= 50 && y <= 607 ) { //中间区域
		y -= 3;
	}
	else if (x >= 190 && x <= 890 && y >= 653 || x > 890 && x < 1010 &&y > 607) { //上方区域+右上空白
		y -= 3;
	}
	else if (x <= 160 && y >= 50 || x > 1000 && y >= 50) { //左侧区域+右侧区域
		y -= 3;
	}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == end) {
		endGame();
	}
}

int main()
{
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, true);

	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);
	setMouseCallback(mouseCallback);

	scene = createScene("scene", "Images/sea.png");

	kid = createObject("Images/kid.png");
	locateObject(kid, scene, x, y);
	showObject(kid);
	scaleObject(kid, 0.05f);

	ball = createObject("Images/ball.png");
	locateObject(ball, scene, 1150, 630);
	showObject(ball);

	end = createObject("Images/end.png");
	locateObject(end, scene, 570, 400);
	scaleObject(end, 1.5f);

	for (int i = 0; i < 106; i++) {
		brick[i] = createObject("Images/brick.png");
		locateObject(brick[i], scene, brickX[i], brickY[i]);
		showObject(brick[i]);
	}

	for (int i = 0; i < 17; i++) {
		left[i] = createObject("Images/left.tga");
		locateObject(left[i], scene, leftX[i], leftY[i]);
		showObject(left[i]);
	}

	for (int i = 0; i < 12; i++) {
		right[i] = createObject("Images/right.tga");
		locateObject(right[i], scene, rightX[i], rightY[i]);
		showObject(right[i]);
	}

	for (int i = 0; i < 26; i++) {
		up[i] = createObject("Images/up.tga");
		locateObject(up[i], scene, upX[i], upY[i]);
		showObject(up[i]);
	}

	for (int i = 0; i < 18; i++) {
		down[i] = createObject("Images/down.png");
		locateObject(down[i], scene, downX[i], downY[i]);
		showObject(down[i]);
	}

	TimerID timer = createTimer(ANIMATION_TIME);
	startTimer(timer);

	SoundID sound = createSound("Audios/snowy.mp3");
	playSound(sound);

	startGame(scene);
}
