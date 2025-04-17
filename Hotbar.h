#pragma once
#include <iostream>
#include <vector>

static const int hotbarsize = 7;

char topHotbar[hotbarsize];
int bottomHotbar[hotbarsize];

class Hotbar {
	/*Hotbar class that represents the players inventory*/
private:
	std::string interval = " ";

	int selectedSlot = 1;
public:
	void hotbarSettup() {
		for (int i = 0; i < hotbarsize; i++) {
			topHotbar[i] = '0';
			bottomHotbar[i] = 0;
		}
	}

	void toHotbar(char type, int amount) {
		for (int i = 0; i < hotbarsize; i++) {
			if (topHotbar[i] == type || topHotbar[i] == std::tolower(type)) {
				bottomHotbar[i] += amount;
				if (bottomHotbar[i] <= 0) {
					topHotbar[i] = '0';
				}
				return;
			}
			else if (topHotbar[i] == '0') {
				topHotbar[i] = std::tolower(type);
				bottomHotbar[i] = amount;
				return;
			}
		}
	}

	void writeHotbar() {
		for (int i = 0; i < hotbarsize; i++) {
			std::cout << topHotbar[i] << interval << std::flush;
		}
		std::cout << "\n" << std::flush;
		for (int i = 0; i < hotbarsize; i++) {
			std::cout << bottomHotbar[i] << interval << std::flush;
		}
		std::cout << "\n" << std::flush;
	}

	void selectSlot(int slot) {
		topHotbar[selectedSlot - 1] = std::tolower(topHotbar[selectedSlot - 1]);
		topHotbar[slot - 1] = std::toupper(topHotbar[slot - 1]);
		selectedSlot = slot;
	}

	char getSelectedSlot() {
		return topHotbar[selectedSlot - 1];
	}

	std::string save() {
		std::string save = "";
		save += std::to_string(hotbarsize) + '|';
		for (int i = 0; i < hotbarsize; i++) {
			save += topHotbar[i];
		}
		save += '|';
		for (int i = 0; i < hotbarsize; i++) {
			save += std::to_string(bottomHotbar[i]) + ',';
		}
		return save;
	}

	void load(std::string save) {
		std::vector<std::string> save_vec = split(save, '|');
		for (int i = 0; i < hotbarsize; i++) {
			topHotbar[i] = save_vec[1][i];
		}
		save_vec = split(save_vec[2], ',');
		for (int i = 0; i < hotbarsize; i++) {
			bottomHotbar[i] = stoi(save_vec[i]);
		}
	}
};