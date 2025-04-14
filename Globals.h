#pragma once
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "Tileset.h"
#include "Sprite.h"
#include "Hotbar.h"
#include "Menu.h"

Tileboard tile;
Hotbar hotbar;
Sprite player;
menu_manager menu;

void writeAll() {
    tile.write_board();
    hotbar.writeHotbar();
    std::cout << player.getCoords();
}

/*void saveFile() {
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
	if (!file.is_open()) {
		std::cerr << "Error: Valid save file not found\n";
		return;
	}
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

    if (std::stoi(BoardHeightRead) != boardHeight || std::stoi(BoardWidthRead) != boardWidth) {
        std::cerr << "Error: Board size does not match the current board size: (" << BoardHeightRead << ", " << BoardWidthRead << ") (" << boardHeight << ", " << boardWidth << ")\n";
        return;
    }

	int k = 0;
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++) {
            if (BoardRead[k] == '@')
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

    if (std::stoi(HotbarSizeRead) != hotbarsize) {
        std::cerr << "Error: Hotbar size does not match the current hotbar size: " << HotbarSizeRead << " != " << hotbarsize << "\n";
		return;
    }

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

    writeAll();
}*/

void run_game() {
    writeAll();

    while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // Escape key (pausing)
            system("cls");
            menu.update_state(3, 0);
            return;
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Arrow keys (Moving)
            player.moveSprite("left");
            writeAll();
            Sleep(50);
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            player.moveSprite("right");
            writeAll();
            Sleep(50);
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            player.moveSprite("up");
            writeAll();
            Sleep(50);
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            player.moveSprite("down");
            writeAll();
            Sleep(50);
        }


        while (GetAsyncKeyState(VK_LSHIFT) & 0x8000) { // Shift plus arrow keys (Mining)
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                player.mine("left");
                writeAll();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                player.mine("right");
                writeAll();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000) {
                player.mine("up");
                writeAll();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                player.mine("down");
                writeAll();
                Sleep(50);
            }
        }

        while (GetAsyncKeyState(VK_LCONTROL) & 0x8000) { // Control plus arrow keys (Building)
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                player.place("left");
                writeAll();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                player.place("right");
                writeAll();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000) {
                player.place("up");
                writeAll();
                Sleep(50);
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                player.place("down");
                writeAll();
                Sleep(50);
            }
        }

        if (GetAsyncKeyState(VK_RCONTROL) & 0x8000) { // Right control for saving
            //saveFile();
            Sleep(500);
        }

        if (GetAsyncKeyState(VK_RSHIFT) & 0x8000) { // Right shift for loading file
            //loadFile();
            Sleep(500);
        }

        if (_kbhit()) {
            char input = _getch();

            if (input >= '0' && input <= '9') {
                hotbar.selectSlot(input - '0');
                writeAll();
            }
        }
    }
}

void start_program() {
    hotbar.hotbarSettup();
    tile.terrain_gen();
    player.spawnSprite();
    int button = 1;
    std::string menu_options[4] = {"", "Play", "Settings", "Quit"};
    std::string pause_options[6] = { "", "Continue", "Quit", "Settings", "Save", "Load"};
    menu.update_state(1, 1);
    while (true) {
        while (menu.get_state() == 1) {
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                if (!(button + 1 > 3))
                    button++;
                system("cls");
                menu.update_state(1, button);
                Sleep(50);
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                if (!(button - 1 < 1))
                    button--;
                system("cls");
                menu.update_state(1, button);
                Sleep(50);
            }
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                if (menu_options[button] == "Play") {
                    menu.update_state(4, 1);
                    system("cls");
                    run_game();
                    Sleep(50);
                }
                if (menu_options[button] == "Quit") {
                    system("cls");
                    std::cout << "Goodbye!";
                    return;
                }
            }
        }

        while (menu.get_state() == 3) {
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                if (!(button + 1 > 5))
                    button++;
                system("cls");
                menu.update_state(3, button);
                Sleep(50);
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                if (!(button - 1 < 1))
                    button--;
                system("cls");
                menu.update_state(3, button);
                Sleep(50);
            }
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                if (pause_options[button] == "Continue") {
                    menu.update_state(4, 1);
                    system("cls");
                    run_game();
                    Sleep(50);
                }
                if (pause_options[button] == "Quit") {
                    system("cls");
                    menu.update_state(1, 1);
                }
                //if (pause_options[button] == "Save") {
                    //saveFile();
                //}
                //if (pause_options[button] == "Load") {
                //    loadFile();
                //}
            }
        }
    }
}