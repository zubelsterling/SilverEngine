#include <iostream>
#include <conio.h>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


using namespace std;

//Globals
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fX, fY, score;
enum eDirection{STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int nTail = 0;
vector<int> tailX;
vector<int> tailY;


void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fX = rand() % width;
	fY = rand() % height;
}

//Draws Map
void Draw() {
	system("cls");
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;

	bool emptySpace = true;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			emptySpace = true;
			if (j == 0) {
				cout << "#";
				emptySpace = false;
			}
			if (i == y && j == x) {
				cout << "O";
				emptySpace = false;
			}
			if (j == width - 1) {
				cout << "#";
				emptySpace = false;
			}
			if (i == fY && j == fX) {
				cout << "F";
				emptySpace = false;
			}
			for (int k = 1; k < nTail; k++) {
				if (tailX[k] == j && tailY[k] == i) {
					cout << "o";
					k = nTail;//can only be 1 
					emptySpace = false;
				}
			}

			if (emptySpace) cout << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "SCORE: " << score << endl;
	cout << endl;
}

//Handles Keyboard input
//WASD movement 
//X to terminate
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;;
		}
	}
	if (x < 0 || x > width) {
		gameOver = true;
	}
	if (y < 0 || y > width) {
		gameOver = true;
	}
	if (x == fX && y == fY) {
		score += 100;
		fX = rand() % width;
		fY = rand() % height;
		nTail++;
	}
}

void Logic() {
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y++;
		break;
	case DOWN:
		y--;
		break;
	default:
		break;
	}

	tailX.push_back(x);
	tailY.push_back(y);

	while (tailY.size() > nTail) {
		tailY.erase(tailY.begin(), tailY.begin()+1);
		tailX.erase(tailX.begin(), tailX.begin()+1);
	}
	for (int i = 0; i < tailX.size(); i++) {
		cout << tailX[i];
	}
}

int main() {
	Setup();

	while (!gameOver) {
		Draw();
		Logic();
		Input();
		Sleep(10);
	}

	return 0;
}