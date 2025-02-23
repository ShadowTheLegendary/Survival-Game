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
        if (_kbhit()) {  
            char ch = _getch(); 

            if (ch == 27) {
                break;
            }

            switch (ch) {
            case 'W':
				player.mine("up");
            case 'w':
                player.moveSprite("up");
                tile.writeBoard();
				hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'A':
                player.mine("left");
            case 'a':
                player.moveSprite("left");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'S':
                player.mine("down");
            case 's':
                player.moveSprite("down");
                tile.writeBoard();
                hotbar.writeHotbar();
                std::cout << player.getCoords();
                break;
            case 'D':
                player.mine("right");
            case 'd':
                player.moveSprite("right");
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