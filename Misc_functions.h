#pragma once
#include <string>
#include <vector>

std::string ascii_stream(std::string str) {
	std::string ascii_values;
	for (char c : str) {
		ascii_values += static_cast<int>(c) + ',';
	}
	return ascii_values;
}

std::string ascii_to_string(std::string input) {
	std::string str = "";
	std::string buffer = "";
	for (char c : input) {
		if (c == ',') {
			str += char(stoi(buffer));
			continue;
		}
		else {
			buffer += c;
		}
	}
	return str;
}

std::vector<std::string> ascii_split(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(ascii_to_string(token));
	}
	return tokens;
}

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}