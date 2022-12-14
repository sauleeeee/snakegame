#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>
using namespace std;


bool gameOver;
const int w = 20;
const int h = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
void Setup() {
	gameOver = false;
	dir = STOP;
	x = w / 2 - 1;
	y = h / 2 - 1;
	fruitX = rand() % w;
	fruitY = rand() % h;
	score = 0;
}
void Draw() {
	system("cls");
	for (int i = 0;i < w+1;i++)
		cout << "#";
	cout << endl;
	for (int i = 0;i < h;i++) {
		for (int j = 0;j < w;j++) {
			if (j == 0 || j==w-1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0;k < nTail;k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0;i < w+1;i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
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
		case 's' :
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1;i < nTail;i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	//if (x > w || x < 0 || y>h || y<0)
	//	gameOver = true;
	if (x >= w-1)
		x = 0;
	else if (x < 0)
		x = w - 2;
	if (y >= h-1)
		y = 0;
	else if (y < 0)
		y = h - 2;
	for (int i = 0;i < nTail;i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % w;
		fruitY = rand() % h;
		nTail++;
	}
}
int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}
	if(gameOver){
		cout<<"Game over!";
	}
	return 0;
}
