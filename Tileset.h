#pragma once
#include <iostream>
#include <windows.h>
#include <array>
#include "character_matrix.h"

class Tileboard {  
/*TileBoard class that represents the game board*/  
private:
	int board_height = 10;
	int board_width = 10;

	character_matrix board;
	std::string interval = " ";  

	std::array<int, 4> get_neighbors(int x, int y) {
		std::array<int, 4> arr = { 0, 0, 0, 0 };
		switch (board.get_matrix(x - 1, y)) {
		case 'G':
			arr[0]++;
			break;
		case 'R':
			arr[1]++;
			break;
		case 'T':
			arr[2]++;
			break;
		}
		return arr;
	}

	bool random_percent(int percent) {
		int random_number = rand()%100 + 1;
		if (random_number <= percent)
			return true;
		else
			return false;
	}

public:
	Tileboard() : board(board_width, board_height, 'G', " ") {}

	void to_board(int x_pos, int y_pos, char z) {
		board.to_matrix(x_pos, y_pos, z);
	}

	char get_board(int x_pos, int y_pos) {
		return board.get_matrix(x_pos, y_pos);
	}

	std::string save() {
		return board.to_save_string();
	}

	void load(std::string save) {
		board.from_save_string(save);
		board_height = board.matrix_height;
		board_width = board.matrix_height;return;
	}

	void terrain_gen() {
		srand(time(0));
		for (int i = 1; i <= board_width; i++) {
			for (int j = 1; j <= board_height; j++) {
				std::array<int, 4> neighbors = get_neighbors(i, j);
				int chance = 20;
				chance += neighbors[1] * 35;
				if (chance >= 100) {
					board.to_matrix(i, j, 'R');
				}
				else if (chance <= 0) {
					continue;
				}
				else {
					if (random_percent(chance)) {
						board.to_matrix(i, j, 'R');
					}
					else {
						continue;
					}
				}
			}
		}

		for (int i = 1; i <= board_width; i++) {
			for (int j = 1; j <= board_height; j++) {
				std::array<int, 4> neighbors = get_neighbors(i, j);
				int chance = 15;
				chance -= neighbors[1] * 30;
				chance -= neighbors[2] * 10;
				if (chance >= 100) {
					board.to_matrix(i, j, 'T');
				}
				else if (chance <= 0) {
					continue;
				}
				else {
					if (random_percent(chance)) {
						board.to_matrix(i, j, 'T');
					}
					else {
						continue;
					}
				}
			}
		}
	}

	void write_board() {  
		system("cls");
		board.custom_print_matrix();
	}
};