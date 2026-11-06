#include <iostream>
#include <string>
#include <stdexcept>
#include "stack.h"

void checkBrackets(const std::string& str) {
	Stack<char> stack;
	bool hasError = false;
	size_t errorIndex = 0;
	std::string errorReason = "";

	for (size_t i = 0; i < str.length(); ++i) {
		char ch = str[i];
		if (ch == ';') {
			break;

		}
		if (ch == '(' || ch == '{' || ch == '[') {
			try {
				stack.push(ch);
			}
			catch (const std::exception& ex) {
				hasError = true;
				errorIndex = i;
				errorReason = ex.what();
				break;
			}
		}
		else if (ch == ')' || ch == '}' || ch == ']') {
			if (stack.isEmpty()) {
				hasError = true;
				errorIndex = i;
				errorReason = "Знайдено закриваючу дужку без пари: '" + std::string(1, ch) + "'";
				break;
			}

			try {
				char top = stack.pop();
				if ((ch == ')' && top != '(') ||
					(ch == '}' && top != '{') ||
					(ch == ']' && top != '[')) {
					hasError = true;
					errorIndex = i;
					errorReason = "Невідповідність типів дужок";
					break;
				}
			}
			catch (const std::exception& ex) {
				hasError = true;
				errorIndex = i;
				errorReason = ex.what();
				break;
			}
		}
	}

	if (!hasError && !stack.isEmpty()) {
		hasError = true;
		errorIndex = str.length() > 0 ? str.length() - 1 : 0;
		errorReason = "Залишилися незакриті відкриті дужки";
	}

	if (hasError) {
		std::cout << "Помилка! Рядок є НЕКОРЕКТНИМ." << std::endl;
		std::cout << "Рядок до місця виникнення першої помилки:\n"
			<< str.substr(0, errorIndex + 1) << std::endl;
		std::cout << "Причина: " << errorReason << std::endl;
	}
	else {
		std::cout << "Успіх! Рядок є КОРЕКТНИМ." << std::endl;
	}
	std::cout << "--------------------------------------------------" << std::endl;
}

int main() {

	setlocale(0, "");
	std::cout << "===  Перевірка дужок за допомогою стека ===" << std::endl;

	std::string correctStr = "({x-y-z} * [x + 2y] - (z + 4x));";
	std::string incorrectStr = "([x-y-z} * [x + 2y) - {z + 4x)];";

	std::cout << "Перевірка правильного рядка:\n" << correctStr << "\n";
	checkBrackets(correctStr);

	std::cout << "Перевірка неправильного рядка:\n" << incorrectStr << "\n";
	checkBrackets(incorrectStr);

	return 0;
}