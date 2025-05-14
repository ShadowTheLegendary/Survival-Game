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

int find_index(std::vector<int> vec, int str) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == str)
			return i;
	}
	return -1;
}

class Menu {
private:
	std::vector<std::vector<std::string>> buttons;
	std::vector<std::string> prompts;
	std::vector<int> menu_ids;

public:
	std::vector<std::vector<int>> button_menu_ids;
	int current_button = 0;
	int current_id = 1;

	Menu(std::vector<std::string> Prompts = {},
		std::vector<std::vector<std::string>> Buttons = {},
		std::vector<std::vector<int>> Button_menu_ids = {},
		std::vector<int> Menu_ids = {}) {

		buttons = Buttons;
		prompts = Prompts;
		button_menu_ids = Button_menu_ids;
		menu_ids = Menu_ids;
	}

	void print_menu() {
		std::cout << prompts[find_index(menu_ids, current_id)] << "\n";
		for (int i = 0; i < buttons[find_index(menu_ids, current_id)].size(); i++) {
			std::cout << buttons[find_index(menu_ids, current_id)][i] << "\n";
		}
	}

	void select_button(int index) {
		if (index < 0 || index >= buttons[find_index(menu_ids, current_id)].size())
			return;
		low_str(buttons[find_index(menu_ids, current_id)][current_button]);
		current_button = index;
		up_str(buttons[find_index(menu_ids, current_id)][index]);
	}

	void select_menu() {
		int idx = find_index(menu_ids, current_id);
		if (idx == -1)
			return;
		if (current_button < 0 || current_button >= button_menu_ids[idx].size())
			return;
		int select_menu = button_menu_ids[idx][current_button];
		if (find_index(menu_ids, select_menu) == -1)
			return;
		current_button = 0;
		current_id = select_menu;
	}

	void add_menu(std::string Prompt, std::vector<std::string> Buttons = {},
		std::vector<int> Button_menu_ids = {}, int Id = -1) {
		prompts.push_back(Prompt);
		buttons.push_back(Buttons);
		button_menu_ids.push_back(Button_menu_ids);
		menu_ids.push_back(Id);
	}

	void add_id(int Id) {
		menu_ids.push_back(Id);
	}
};