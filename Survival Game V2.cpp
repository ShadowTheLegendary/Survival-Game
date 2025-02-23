#include <iostream>
#include <conio.h>
#include "Tileset.h"
#include "Sprite.h"
#include "Hotbar.h"
#include "Globals.h"

int main()
{
    Sprite player;
	hotbar.hotbarSettup();
	tile.terrainGen();
	player.spawnSprite();
	tile.writeBoard();
    hotbar.writeHotbar();
    std::cout << player.getCoords();

    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            player.moveSprite("left");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            player.moveSprite("right");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            player.moveSprite("up");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            player.moveSprite("down");
            tile.writeBoard();
            hotbar.writeHotbar();
            std::cout << player.getCoords();
        }

        if (_kbhit()) {
            char ch = _getch(); 

            if (ch == 27) {
                break;
            }

            if (ch >= '0' && ch <= '9') {
                int num = ch - '0';
				hotbar.selectSlot(num);
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
            }

            switch (ch) {
            case 'W':
                player.place("up");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'w':
                player.mine("up");
                tile.writeBoard();
				hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'A':
                player.place("left");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'a':
                player.mine("left");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'S':
                player.place("down");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 's':
                player.mine("down");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'D':
                player.place("right");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'd':
                player.mine("right");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            default:
                break;
            }
        }
    }
}