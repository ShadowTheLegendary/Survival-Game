#pragma once
#include <string>
#include "Tileset.h"
#include "Globals.h"
#include "Hotbar.h"

extern Hotbar hotbar;
extern Tileboard tile;

class Sprite {
	/*Sprite class that represents the player, but can be used to represent a NPC (Non Player Charecter)*/
private:
	int xPosition = 1;
	int yPosition = 1;
	char sprite = '@';
public:
	std::string getCoords() {
		return "(" + std::to_string(xPosition) + ", " + std::to_string(yPosition) + ")";
	}

	void moveSprite(std::string direction) {
		tile.to_board(xPosition, yPosition, 'G');

		if (direction == "right" && tile.get_board(xPosition + 1, yPosition) == 'G') {
			xPosition++;
		}
		else if (direction == "left" && tile.get_board(xPosition - 1, yPosition) == 'G') {
			xPosition--;
		}
		else if (direction == "up" && tile.get_board(xPosition, yPosition + 1) == 'G') {
			yPosition++;
		}
		else if (direction == "down" && tile.get_board(xPosition, yPosition - 1) == 'G') {
			yPosition--;
		}
		else {
			tile.to_board(xPosition, yPosition, sprite);
			return;
		}
		tile.to_board(xPosition, yPosition, sprite);
	}

	void mine(std::string direction) {

		int breakXPos = xPosition;
		int breakYPos = yPosition;

		if (direction == "right" && tile.get_board(breakXPos + 1, breakYPos) != 'G') {
			breakXPos++;
		}
		else if (direction == "left" && tile.get_board(breakXPos - 1, breakYPos) != 'G') {
			breakXPos--;
		}
		else if (direction == "up" && tile.get_board(breakXPos, breakYPos + 1) != 'G') {
			breakYPos++;
		}
		else if (direction == "down" && tile.get_board(breakXPos, breakYPos - 1) != 'G') {
			breakYPos--;
		}
		else 
			return;

		if (tile.get_board(breakXPos, breakYPos) == 'T')
			hotbar.toHotbar('W', 4);
		else if (tile.get_board(breakXPos, breakYPos) == 'S')
			; // Janky 'pass' code
		else 
			hotbar.toHotbar(tile.get_board(breakXPos, breakYPos), 1);

		tile.to_board(breakXPos, breakYPos, 'G');
	}

	void place(std::string direction) {

		int placeXPos = xPosition;
		int placeYPos = yPosition;

		if (direction == "right" && tile.get_board(placeXPos + 1, placeYPos) == 'G') {
			placeXPos++;
		}
		else if (direction == "left" && tile.get_board(placeXPos - 1, placeYPos) == 'G') {
			placeXPos--;
		}
		else if (direction == "up" && tile.get_board(placeXPos, placeYPos + 1) == 'G') {
			placeYPos++;
		}
		else if (direction == "down" && tile.get_board(placeXPos, placeYPos - 1) == 'G') {
			placeYPos--;
		}
		else
			return;

		if (std::islower(hotbar.getSelectedSlot()) || hotbar.getSelectedSlot() == '0')
			return;
		else if (hotbar.getSelectedSlot() == 'R') {
			tile.to_board(placeXPos, placeYPos, 'S');
			hotbar.toHotbar('R', -1);
		}
		else {
			tile.to_board(placeXPos, placeYPos, hotbar.getSelectedSlot());
			hotbar.toHotbar(std::toupper(hotbar.getSelectedSlot()), -1);
		}
	}

	void spawnSprite() {
		tile.to_board(xPosition, yPosition, sprite);
	}

	void setCoords(int x, int y) {
		xPosition = x;
		yPosition = y;
	}
};