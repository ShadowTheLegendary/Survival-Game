#pragma once
#include <iostream>
#include <windows.h>

static const int boardHeight = 10;
static const int boardWidth = 20;

char Board[boardHeight][boardWidth];
int collBoard[boardHeight][boardWidth];
int generate[boardHeight][boardWidth];

void toBoard(int xPos, int yPos, char z) {
	Board[boardHeight - xPos][yPos - 1] = z;
}

void toCollBoard(int xPos, int yPos, int z) {
	collBoard[boardHeight - xPos][yPos - 1] = z;
}

char getBoard(int xPos, int yPos) {
	return Board[boardHeight - xPos][yPos - 1];
}

int getCollBoard(int xPos, int yPos) {
	return collBoard[boardHeight - xPos][yPos - 1];
}

class TileBoard {
private:
	std::string interval = " ";

	void Color(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

public:
	void terrainGen() {
		srand(time(0));
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				generate[i][j] = rand() % 10;
			}
		}
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				if (generate[i][j] == 0 || generate[i][j] == 1) {
					Board[i][j] = 'R';
					collBoard[i][j] = 1;
				}
				else if (generate[i][j] == 2) {
					Board[i][j] = 'T';
					collBoard[i][j] = 1;
				}
				else if (generate[i][j] > 2)
					Board[i][j] = 'G';
			}
		}
	}

	void writeBoard() {
		system("cls");
		for (int i = 0; i < boardHeight; i++) {
			for (int j = 0; j < boardWidth; j++) {
				if (Board[i][j] == 'G') {
					Color(2);
					std::cout << Board[i][j] << interval;
					Color(7);

				}
				else if (Board[i][j] == 'R') {
					Color(8);
					std::cout << Board[i][j] << interval;
					Color(7);
				}
				else if (Board[i][j] == 'S') {
					Color(8);
					std::cout << Board[i][j] << interval;
					Color(7);
				}
				else if (Board[i][j] == 'T') {
					Color(2 | 4);
					std::cout << Board[i][j] << interval;
					Color(7);
				}
				else if (Board[i][j] == 'W') {
					Color(2 | 4);
					std::cout << Board[i][j] << interval;
					Color(7);
				}
				else
					std::cout << Board[i][j] << interval;
			}
			std::cout << "\n";
		}
	}
};