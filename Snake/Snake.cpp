#include<iostream>
#include<conio.h>
#include<stdlib.h>

using namespace std;

const int length =  50;
const int width = 20;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int x, y, xFruit, yFruit, score = 0;
int tailSnakeX[100], tailSnakeY[100], numberTail;
bool isRight = true, isLeft = true, isUp = true, isDown = true;
bool gameOver;

void Setup() {
	gameOver = false;
	srand(time(NULL));
	dir = STOP;
	x = length / 4;
	y = width / 2;
	xFruit = rand() % length - 1;
	yFruit = rand() % width - 1;
}

void DrawBackGround() {
	system("cls");
	cout << "\t\t\t";
	for (int i = 0; i < length + 2; i++)
		cout << "\xDB";
	cout << endl;
	for (int i = 0; i < width; i++) {
		cout << "\t\t\t";
		for (int j = 0; j < length; j++) {
			if (j == 0)
				cout << "\xDB";
			if (j == x && i == y)
				cout << "\x99";
			else if (j == xFruit && i == yFruit)
				cout << "\xE8";
			else {
				bool isPrint = false;
				for (int k = 0; k < numberTail; k++)
				{
					if (tailSnakeX[k] == j && tailSnakeY[k] == i) {
						cout << "o";
						isPrint = true;
					}
				}
				if(!isPrint)
					cout << " ";
			}
			if (j == length - 1)
				cout << "\xDB";
		}
		cout << endl;
	}
	cout << "\t\t\t";
	for (int i = 0; i < length + 2; i++)
		cout << "\xDB";
	cout << endl;
	cout << "Score: " << score;
}

void Logic() {
	int preX = tailSnakeX[0];
	int preY = tailSnakeY[0];
	int pre2X, pre2Y;
	tailSnakeX[0] = x;
	tailSnakeY[0] = y;
	for (int i = 1; i < numberTail; i++) {
		pre2X = tailSnakeX[i];
		pre2Y = tailSnakeY[i];
		tailSnakeX[i] = preX;
		tailSnakeY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
	}
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		}
	}
}

void SnakeMove() {
	switch (dir)
	{
	case LEFT:
		if (isLeft) {
			isRight = false;
			isUp = true;
			isDown = true;
			x--;
		}
		else x++;
		break;
	case RIGHT:
		if (isRight) {
			isLeft = false;
			isUp = true;
			isDown = true;
			x++;
		}
		else x--;
		break;
	case UP:
		if (isUp) {
			isDown = false;
			isLeft = true;
			isRight = true;
			y--;
		}
		else y++;
		break;
	case DOWN:
		if (isDown) {
			isUp = false;
			isLeft = true;
			isRight = true;
			y++;
		}
		else y--;
		break;
	}
	if (x == xFruit && y == yFruit) {
		score += 10;
		xFruit = rand() % length;
		yFruit = rand() % width;
		numberTail++;
	}
	for (int i = 0; i < numberTail; i++)
		if (tailSnakeX[i] == x && tailSnakeY[i] == y)
			gameOver = true;
	if (x >= length) x = 0;
	else if (x < 0) x = length - 1;
	if (y >= width) y = 0;
	else if (y < 0) y = width - 1;
}

int main(){
	Setup();
	while (!gameOver)
	{
		DrawBackGround();
		Logic();
		SnakeMove();
	}
	return 0;
}