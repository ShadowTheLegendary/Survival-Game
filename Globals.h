#pragma once
#include <string>
#include <vector>
#include <algorithm>
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
Menu menu;

void writeAll() {
    tile.write_board();
    hotbar.writeHotbar();
    std::cout << player.getCoords();
}

void save_file() {
    std::string save = tile.save();
    std::ofstream board_file("board_save.txt");
    board_file << save;
    board_file.close();
    save = hotbar.save();
    std::ofstream file("hotbar_save.txt");
    file << save;
    file.close();
    save = player.getCoords();
    std::ofstream player_file("player_save.txt");
    player_file << save;
    player_file.close();
}

void load_file() {
    system("cls");
    std::string save = "";
    std::ifstream board_file("board_save.txt");
    if (!board_file.is_open()) {
        std::cerr << "ERROR: 'board_save.txt' does not exist";
        return;
    }
    std::string line;
    while (std::getline(board_file, line)) {
        save += line;
    }
    board_file.close();
    tile.load(save);
    save = "";
    std::ifstream file("hotbar_save.txt");
    if (!file.is_open()) {
        std::cerr << "ERROR: 'hotbar_save.txt' does not exist";
        return;
    }
    file >> save;
    file.close();
    save = "";
    std::ifstream player_file("player_save.txt");
    if (!player_file.is_open()) {
        std::cerr << "ERROR: 'player_save.txt' does not exist";
        return;
    }
    while (std::getline(player_file, line)) {
        save += line;
    }
    player_file.close();
    std::replace(save.begin(), save.end(), '(', ' ');
    std::replace(save.begin(), save.end(), ')', ' ');
    save.erase(std::remove_if(save.begin(), save.end(), ::isspace), save.end());
    std::vector<std::string> coords = split(save, ',');
    player.setCoords(stoi(coords[0]), stoi(coords[1]));
    writeAll();
}

void run_game() {
    writeAll();

    while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // Escape key (pausing)
            system("cls");
            menu.select_menu();
			menu.print_menu();
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
            save_file();
            Sleep(500);
        }

        if (GetAsyncKeyState(VK_RSHIFT) & 0x8000) { // Right shift for loading file
            load_file();
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
    menu.add_menu("Survival Game", { "play", "settings", "quit" }, { 2, 4, 5 }, 1);
    menu.add_menu("", { "pause" }, { 3 }, 2);
    menu.add_menu("Game Paused", { "continue", "quit to menu", "settings", "save", "load" }, { 2, 1, 4, 6, 7 }, 3);
    menu.add_id(5);
	menu.add_id(6);
	menu.add_id(7);
    hotbar.hotbarSettup();
    tile.terrain_gen();
    player.spawnSprite();
	menu.print_menu();
    while (true) {
        while (menu.current_id == 1 || menu.current_id == 3) {
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                menu.select_button(menu.current_button + 1);
                system("cls");
                menu.print_menu();
                Sleep(50);
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                menu.select_button(menu.current_button - 1);
                system("cls");
                menu.print_menu();
                Sleep(50);
            }
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                system("cls");
                menu.select_menu();
                if (menu.current_id == 1) {
                    menu.print_menu();
                }
            }
        }

		while (menu.current_id == 2) {
			system("cls");
			run_game();
		}

        while (menu.current_id == 5) {
			system("cls");
            std::cout << "Goodbye!";
            return;
        }
    }
}