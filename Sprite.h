#pragma once
#include <string>
#include "Tileset.h"
#include "Globals.h"
#include "Hotbar.h"

extern Hotbar hotbar;

class Sprite {
private:
	int xPosition = 1;
	int yPosition = 1;
	char sprite = '@';
public:
	std::string getCoords() {
		return "(" + std::to_string(xPosition) + ", " + std::to_string(yPosition) + ")";
	}

	void moveSprite(std::string direction) {

		toBoard(xPosition, yPosition, 'G');
		toCollBoard(xPosition, yPosition, 0);

		if (direction == "right" && getCollBoard(xPosition, yPosition + 1) == 0) {
			yPosition++;
		}
		else if (direction == "left" && getCollBoard(xPosition, yPosition - 1) == 0) {
			yPosition--;
		}
		else if (direction == "up" && getCollBoard(xPosition + 1, yPosition) == 0) {
			xPosition++;
		}
		else if (direction == "down" && getCollBoard(xPosition - 1, yPosition) == 0) {
			xPosition--;
		}
		else {
			toBoard(xPosition, yPosition, sprite);
			return;
		}

		toBoard(xPosition, yPosition, sprite);
	}

	void mine(std::string direction) {

		int breakXPos = xPosition;
		int breakYPos = yPosition;

		if (direction == "right" && getCollBoard(breakXPos, breakYPos + 1) == 1) {
			breakYPos++;
		}
		else if (direction == "left" && getCollBoard(breakXPos, breakYPos - 1) == 1) {
			breakYPos--;
		}
		else if (direction == "up" && getCollBoard(breakXPos + 1, breakYPos) == 1) {
			breakXPos++;
		}
		else if (direction == "down" && getCollBoard(breakXPos - 1, breakYPos) == 1) {
			breakXPos--;
		}
		else 
			return;

		if (getBoard(breakXPos, breakYPos) == 'T')
			hotbar.toHotbar('W', 4);
		else if (getBoard(breakXPos, breakYPos) == 'S')
			;
		else 
			hotbar.toHotbar(getBoard(breakXPos, breakYPos), 1);

		toBoard(breakXPos, breakYPos, 'G');
		toCollBoard(breakXPos, breakYPos, 0);
	}

	void place(std::string direction) {

		int placeXPos = xPosition;
		int placeYPos = yPosition;

		if (direction == "right" && getCollBoard(placeXPos, placeYPos + 1) == 0) {
			placeYPos++;
		}
		else if (direction == "left" && getCollBoard(placeXPos, placeYPos - 1) == 0) {
			placeYPos--;
		}
		else if (direction == "up" && getCollBoard(placeXPos + 1, placeYPos) == 0) {
			placeXPos++;
		}
		else if (direction == "down" && getCollBoard(placeXPos - 1, placeYPos) == 0) {
			placeXPos--;
		}
		else
			return;

		if (std::islower(hotbar.getSelectedSlot()) || hotbar.getSelectedSlot() == '0')
			return;
		else if (hotbar.getSelectedSlot() == 'R') {
			toBoard(placeXPos, placeYPos, 'S');
			hotbar.toHotbar('R', -1);
		}
		else {
			toBoard(placeXPos, placeYPos, hotbar.getSelectedSlot());
			hotbar.toHotbar(std::toupper(hotbar.getSelectedSlot()), -1);
		}

		toCollBoard(placeXPos, placeYPos, 1);
	}

	void spawnSprite() {
		toBoard(xPosition, yPosition, sprite);
	}

	void setCoords(int x, int y) {
		xPosition = x;
		yPosition = y;
	}
};