#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Misc_functions.h"

class character_matrix {
private:
    std::vector<std::vector<char>> height_vec;
    std::vector<char> width_vec;
    char default_char = '0';
    std::string char_buffer = " ";
public:
    character_matrix(int height, int width, char default_char = '0', std::string char_buffer = " ") {
        matrix_height = height;
        matrix_width = width;
        default_char = default_char;
		char_buffer = char_buffer;
        height_vec.reserve(height);
        for (int i = 0; i < matrix_width; i++) {
            width_vec.push_back(default_char);
        }
        for (int i = 0; i < matrix_height; i++) {
            height_vec.push_back(width_vec);
        }
        std::reverse(height_vec.begin(), height_vec.end());
    }

    int matrix_height = 0;
    int matrix_width = 0;

    void to_matrix(int x, int y, char z, bool shifting = true) {
        std::vector<char> buffer;
        if (shifting == true) {
            if (x <= 0 || x > matrix_width || y <= 0 || y > matrix_height) {
                return;
            }
            y = matrix_height - y;
            x--;
        }
        else
            if (x < 0 || x >= matrix_width || y < 0 || y >= matrix_height) {
                return;
            }
        buffer = height_vec[y];
        buffer[x] = z;
        height_vec[y] = buffer;
    }

    char get_matrix(int x, int y, bool shifting = true) {
        std::vector<char> buffer;
        if (shifting == true) {
			if (x <= 0 || x > matrix_width || y <= 0 || y > matrix_height) {
				return '0';
			}
            y = matrix_height - y;
            x--;
        }
        else
            if (x < 0 || x >= matrix_width || y < 0 || y >= matrix_height) {
                return '0';
            }
        
        buffer = height_vec[y];
        return buffer[x];
    }

    std::string to_save_string() {
        std::string save = "";
        save += std::to_string(matrix_height) + '|' + std::to_string(matrix_width) + '|';
        save += default_char + char_buffer + '|';

        for (int i = 0; i < matrix_height; i++) {
            std::vector<char> buffer = height_vec[i];
            for (int j = 0; j < matrix_width; j++) {
                save += buffer[j];
            }
        }
        return save;
    }

    void from_save_string(std::string save) {
        std::vector<std::string> parts = split(save, '|');
        resize(stoi(parts[0]), stoi(parts[1]));
        default_char = parts[2][0];
        char_buffer = parts[2].substr(1);

        int iterator = 0;
        for (int i = 0; i < matrix_height; i++) {
            std::vector<char> buffer = height_vec[i];
            for (int j = 0; j < matrix_width; j++) {
                buffer[j] = parts[3][iterator];
                iterator++;
            }
            height_vec[i] = buffer;
        }
        return;
    }

    void print_matrix() {
        for (int i = 0; i < matrix_height; i++) {
            std::vector<char> buffer = height_vec[i];
            for (int j = 0; j < matrix_width; j++) {
                std::cout << buffer[j] << char_buffer << std::flush;
            }
            std::cout << "\n" << std::flush;
        }
        std::cout << "\n" << std::flush;
    }

    void custom_print_matrix() {
        for (int i = 0; i < matrix_height; i++) {
            std::vector<char> buffer = height_vec[i];
            for (int j = 0; j < matrix_width; j++) {
                char board_char = buffer[j];
                if (board_char == 'G') {
                    color(2);
                }
                else if (board_char == 'R') {
                    color(8);
                }
                else if (board_char == 'S') {
                    color(8);
                }
                else if (board_char == 'T') {
                    color(2 | 4);
                }
                else if (board_char == 'W') {
                    color(2 | 4);
                }
                else
                    color(7);
                std::cout << buffer[j] << char_buffer << std::flush;
            }
            std::cout << "\n" << std::flush;
        }
        std::cout << "\n" << std::flush;
        color(7);
    }

    void clear_matrix() {
        width_vec.clear();
        for (int i = 0; i < matrix_width; i++) {
            width_vec.push_back(default_char);
        }
        for (int i = 0; i < matrix_height; i++) {
            height_vec.push_back(width_vec);
        }
        std::reverse(height_vec.begin(), height_vec.end());
    }

    void resize(int height, int width) {
        matrix_height = height;
        matrix_width = width;
        clear_matrix();
    }

    void set_height(int height) {
        matrix_height = height;
        clear_matrix();
    }

    void set_width(int width) {
        matrix_width = width;
        clear_matrix();
    }
};