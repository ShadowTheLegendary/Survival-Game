#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
#include <cctype>

std::string up_str(std::string& str) {
	for (int i = 0; i < str.size(); i++)
		str[i] = std::toupper(str[i]);
	return str;
}

std::string low_str(std::string& str) {
	for (int i = 0; i < str.size(); i++)
		str[i] = std::tolower(str[i]);
	return str;
}

class menu_view {
private:
	std::vector<std::string> buttons;
	std::string text;
	int current_button = 1;
public:
	menu_view(std::string text_in, std::vector<std::string> buttons_in) {
		text = text_in;
		buttons = buttons_in;
	}

	void highlight_button(int index) {
		if (index <= 0 || index > buttons.size())
			return;
		low_str(buttons[current_button - 1]);
		current_button = index;
		up_str(buttons[index - 1]);
	}

	int get_button() {
		return current_button;
	}

	std::string get_button_str(int index) {
		return buttons[index - 1];
	}

	void print_menu() {
		std::cout << text << "\n";
		for (int i = 0; i < buttons.size(); i++)
			std::cout << buttons[i] << "\n";
	}
};

class menu_manager {
private:
	menu_view main_menu;
	menu_view pause_menu;
	int current_state = 1;
	int current_button = 1;
	std::string states[4] = { "main", "settings", "game", "quit" };
public:
	menu_manager() : main_menu("Survival Game", { "play", "settings", "quit" }),
		pause_menu("Game Paused", { "continue", "quit to menu", "settings", "save", "load" }) {
	}

	int update_state(int state = -1, int button = -1) {
		if (state == -1)
			state = current_state;
		if (button == -1)
			button = current_button;

		if (state == 1) {
			main_menu.highlight_button(button);
			main_menu.print_menu();
			current_state = state;
			current_button = button;
			return 0;
		}
		else if (state == 2) {
			std::cout << "Sorry, settings arent ready yet";
			current_state = 1;
			current_button = 1;
			main_menu.highlight_button(current_button);
			main_menu.print_menu();
			return 0;
		}
		else if (state == 3) {
			pause_menu.highlight_button(button);
			pause_menu.print_menu();
			current_state = state;
			current_button = button;
			return 0;
		}
		else if (state == 4) {
			current_state = state;
			current_button = button;
		}
	}

	int get_button() {
		return current_button;
	}

	std::string get_str_button(std::string menu = "main") {
		if (menu == "main")
			return main_menu.get_button_str(current_button);
	}

	int get_state() {
		return current_state;
	}
};