#pragma once
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "Tileset.h"
#include "Sprite.h"
#include "Hotbar.h"

TileBoard tile;
Hotbar hotbar;
Sprite player;

void saveFile() {
	std::string fileData = "";
	fileData += std::to_string(boardHeight) + "|" + std::to_string(boardWidth) + "|";
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++) {
			fileData += Board[i][j];
		}
	fileData += "|";
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
			fileData += std::to_string(collBoard[i][j]);
	fileData += "|" + std::to_string(hotbarsize) + "|";
	for (int i = 0; i < hotbarsize; i++)
		fileData += topHotbar[i];
	fileData += "|";
	for (int i = 0; i < hotbarsize; i++)
		fileData += std::to_string(bottomHotbar[i]) + ',';
	fileData += "|" + player.getCoords();
	std::ofstream file("save.txt");
	file.clear();
	file << fileData;
}

enum currentReadingMode {
	BOARDHEIGHT = 1,
	BOARDWIDTH = 2,
	BOARD = 3,
	COLLBOARD = 4,
	HOTBARSIZE = 5,
	HOTBAR = 6,
	BOTTOMHOTBAR = 7,
	COORDS1 = 8,
	COORDS2 = 9
};

currentReadingMode mode = BOARDHEIGHT;

void loadFile() {
	std::ifstream file("save.txt");
	std::string fileData;
	file >> fileData;
	std::string BoardHeightRead = "";
	std::string BoardWidthRead = "";
	std::string BoardRead = "";
	std::string CollBoardRead = "";
	std::string HotbarSizeRead = "";
	std::string TopHotbarRead = "";
	std::string BottomHotbarRead = "";
    int xCoordRead = 0;
	int yCoordRead = 0;

	for (int i = 0; i < fileData.size(); i++) {
		if (fileData[i] == '|')
			mode = static_cast<currentReadingMode>(mode + 1);
		//else if (fileData[i] == ',')
			//continue;
		else if (mode == BOARDHEIGHT)
			BoardHeightRead += fileData[i];
		else if (mode == BOARDWIDTH)
			BoardWidthRead += fileData[i];
		else if (mode == BOARD)
			BoardRead += fileData[i];
		else if (mode == COLLBOARD)
			CollBoardRead += fileData[i];
		else if (mode == HOTBARSIZE)
			HotbarSizeRead += fileData[i];
		else if (mode == HOTBAR)
			TopHotbarRead += fileData[i];
		else if (mode == BOTTOMHOTBAR)
			BottomHotbarRead += fileData[i];
        else if (mode == COORDS1) {
            if (fileData[i] == ',')
                mode = COORDS2;
            else if (fileData[i] == '(')
                continue;
            else
                xCoordRead = fileData[i] - '0';
        }
        else if (mode == COORDS2) {
            if (fileData[i] == ',')
                continue;
            else if (fileData[i] == ' ')
                continue;
            else
                yCoordRead = fileData[i] - '0';
        }
	}

	if (std::stoi(BoardHeightRead) != boardHeight || std::stoi(BoardWidthRead) != boardWidth)
		std::cerr << "Error: Board size does not match the current board size: (" << BoardHeightRead << ", " << BoardWidthRead << ") (" << boardHeight << ", " << boardWidth << ")\n";

	int k = 0;
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++) {
            if (Board[i][j] == '@')
				Board[i][j] = 'G';
            else
			    Board[i][j] = BoardRead[k];
			k++;
		}

	k = 0;
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++) {
            collBoard[i][j] = CollBoardRead[k] - '0';
			k++;
		}

	if (std::stoi(HotbarSizeRead) != hotbarsize)
		std::cerr << "Error: Hotbar size does not match the current hotbar size: " << HotbarSizeRead << " != " << hotbarsize << "\n";

	std::string hotbarBuffer = "";
	int hotbarSlot = 0;

    for (int i = 0; i < TopHotbarRead.size(); i++) {
		topHotbar[i] = TopHotbarRead[i];
    }

	hotbarSlot = 0;

    for (int i = 0; i < BottomHotbarRead.size(); i++) {
        if (BottomHotbarRead[i] == ',') {
			bottomHotbar[hotbarSlot] = std::stoi(hotbarBuffer);
			hotbarBuffer = "";
            hotbarSlot++;
        }
		else
			hotbarBuffer += BottomHotbarRead[i];
    }

	player.setCoords(xCoordRead, yCoordRead);
	player.spawnSprite();
}

void gameStart() {
    hotbar.hotbarSettup();
    tile.terrainGen();
    player.spawnSprite();
    tile.writeBoard();
    hotbar.writeHotbar();
    std::cout << player.getCoords();

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // Escape key (exit)
            break;

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            player.moveSprite("left");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
            Sleep(50);
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            player.moveSprite("right");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
            Sleep(50);
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            player.moveSprite("up");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
            Sleep(50);
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            player.moveSprite("down");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
            Sleep(50);
        }


        while (GetAsyncKeyState(VK_LSHIFT) & 0x8000) { // Shift plus arrow keys (Mining)
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                player.mine("left");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                player.mine("right");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000) {
                player.mine("up");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                player.mine("down");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
        }

        while (GetAsyncKeyState(VK_LCONTROL) & 0x8000) { // Control plus arrow keys (Building)
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                player.place("left");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                player.place("right");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000) {
                player.place("up");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                player.place("down");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                Sleep(50);
            }
        }

        if (GetAsyncKeyState(VK_RCONTROL) & 0x8000) {
            saveFile();
            Sleep(500);
        }

        if (GetAsyncKeyState(VK_RSHIFT) & 0x8000) {
            loadFile();
            Sleep(500);
        }

        if (_kbhit()) {
            char input = _getch();

            if (input >= '0' && input <= '9') {
                hotbar.selectSlot(input - '0');
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
            }
        }
    }
}