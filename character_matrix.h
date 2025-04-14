#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class character_matrix {
private:
    void color(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    std::vector<std::vector<char>> height_vec;
    std::vector<char> width_vec;
    int matrix_height = 0;
    int matrix_width = 0;
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