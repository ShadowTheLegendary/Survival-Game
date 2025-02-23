#pragma once
#include <iostream>

class Hotbar {
private:
	static const int hotbarsize = 7;

	char topHotbar[hotbarsize];
	int bottomHotbar[hotbarsize];

	std::string interval = " ";
public:
	void hotbarSettup() {
		for (int i = 0; i < hotbarsize; i++) {
			topHotbar[i] = '0';
			bottomHotbar[i] = 0;
		}
	}
	void toHotbar(char type, int amount) {
		for (int i = 0; i < hotbarsize; i++) {
			if (topHotbar[i] == type) {
				topHotbar[i] = type;
				bottomHotbar[i] += amount;
				return;
			}
			else if (topHotbar[i] == '0') {
				topHotbar[i] = type;
				bottomHotbar[i] = amount;
				return;
			}
		}
	}
	void writeHotbar() {
		for (int i = 0; i < hotbarsize; i++) {
			std::cout << topHotbar[i] << interval;
		}
		std::cout << "\n";
		for (int i = 0; i < hotbarsize; i++) {
			std::cout << bottomHotbar[i] << interval;
		}
		std::cout << "\n";
	}
};
