#pragma once
#include <string>
#include "Tileset.h"
#include "Globals.h"

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
		else 
			hotbar.toHotbar(getBoard(breakXPos, breakYPos), 1);

		toBoard(breakXPos, breakYPos, 'G');
		toCollBoard(breakXPos, breakYPos, 0);
	}

	void spawnSprite() {
		toBoard(xPosition, yPosition, sprite);
	}
};