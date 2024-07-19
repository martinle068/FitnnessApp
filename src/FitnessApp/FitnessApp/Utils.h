#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <algorithm>

/**
 * @brief Generic function to write data to a CSV file.
 *
 * @tparam T Type of the item to write.
 * @param filename Name of the file.
 * @param item Item to write to the file.
 */
template<typename T>
void writeToCSV(const std::string& filename, const T& item)
{
	std::ofstream file(filename, std::ios::app); // Append mode
	if (file.is_open())
	{
		item.toCSV(file);
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file for writing: " << filename << std::endl;
	}
}

/**
 * @brief Generic function to overwrite data in a CSV file.
 *
 * @tparam T Type of the items to write.
 * @param filename Name of the file.
 * @param items Map of items to overwrite the file with.
 */
template<typename T>
void overwriteCSV(const std::string& filename, const std::map<std::string, T>& items)
{
	std::ofstream file(filename, std::ios::trunc); // Truncate mode to clear the file
	if (file.is_open())
	{
		for (const auto& pair : items)
		{
			writeToCSV(filename, pair.second);
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file for writing: " << filename << std::endl;
	}
}

/**
 * @brief Generic function to read data from a CSV file into a map.
 *
 * @tparam T Type of the items to read.
 * @tparam U Type of the items source map.
 * @param filename Name of the file.
 * @param itemsSource Source map of items.
 * @return Map of items read from the file.
 */
template<typename T, typename U>
std::map<std::string, T> readFromCSV(const std::string& filename, const std::map<std::string, U>& itemsSource)
{
	std::map<std::string, T> items;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			T item;
			if (item.fromCSV(ss, itemsSource))
			{
				items[item.name] = item;
			}
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file for reading: " << filename << std::endl;
	}
	return items;
}

/**
 * @brief Generic function to read data from a CSV file into a map.
 *
 * @tparam T Type of the items to read.
 * @param filename Name of the file.
 * @return Map of items read from the file.
 */
template<typename T>
std::map<std::string, T> readFromCSV(const std::string& filename)
{
	std::map<std::string, T> items;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			T item;
			if (item.fromCSV(ss))
			{
				items[item.name] = item;
			}
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file for reading: " << filename << std::endl;
	}
	return items;
}

/**
 * @brief Generic helper function to get valid numeric input.
 *
 * @tparam T Type of the variable.
 * @param variable Variable to store the input.
 * @param prompt Prompt message for the input.
 */
template<typename T>
void getValidInput(T& variable, const std::string& prompt)
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);

		std::istringstream iss(input);
		T temp;
		char extra;

		if (!(iss >> temp) || (iss >> extra))
		{
			std::cout << "Invalid input. Please enter a valid number.\n";
		}
		else
		{
			variable = temp;
			break; // Valid input
		}
	}
}

/**
 * @brief Helper function to get valid numeric input within a specified range.
 *
 * @param variable Variable to store the input.
 * @param prompt Prompt message for the input.
 * @param min Minimum value for the input.
 * @param max Maximum value for the input.
 */
inline void getValidInput(int& variable, const std::string& prompt, int min, int max)
{
	std::string input;
	while (true)
	{
		getValidInput(variable, prompt);
		if (variable >= min && variable <= max)
		{
			break;
		}
		std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
	}
}

/**
 * @brief Template function to get optional input.
 *
 * @tparam T Type of the variable.
 * @param variable Variable to store the input.
 * @param prompt Prompt message for the input.
 */
template<typename T>
void getOptionalInput(T& variable, const std::string& prompt)
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		if (input.empty())
		{
			break; // Keep current value if input is empty
		}
		std::stringstream ss(input);
		T temp;
		if (ss >> temp && ss.eof())
		{ // Check if the input is valid for type T
			variable = temp;
			break;
		}
		else
		{
			std::cout << "Invalid input. ";
		}
	}
}

/**
 * @brief Function to check if a string can be converted to an integer.
 *
 * @param value String to check.
 * @param intValue Integer value to store the result.
 * @return True if the string can be converted, false otherwise.
 */

bool inline stringToInt(const std::string& value, int& intValue)
{
	size_t p;

	try
	{
		intValue = std::stoi(value, &p);
		if (p != value.size())
		{
			return false;
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}

/**
 * @brief Function to check if a string can be converted to a float.
 *
 * @param value String to check.
 * @param floatValue Float value to store the result.
 * @return True if the string can be converted, false otherwise.
 */

bool inline stringToFloat(const std::string& value, float& floatValue)
{
	size_t p;

	try
	{
		floatValue = std::stof(value, &p);
		if (p != value.size())
		{
			return false;
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}

/**
* @brief vector of days of the week.
*/
const std::vector<std::string> DAYS_OF_WEEK = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

/**
* @brief vector of meal names of a mealplan 
*/
const std::vector<std::string> MEAL_NAMES = { "Breakfast", "Snack1", "Lunch", "Snack2", "Dinner" };

/**
 * @brief Alias for a menu option, consisting of a display name and an action function.
 */
using MenuOption = std::pair<std::string, std::function<void()>>;

/**
 * @brief Clears the screen.
 */
inline void clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
	// Windows system call
	system("cls");
#else
	// Unix-like system call
	std::system("clear");
#endif
}

/**
 * @brief Enum for basic colors.
 */
enum class Color
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	RESET
};

/**
 * @brief Function to get the color code from the Color enum.
 *
 * @param color Desired color.
 * @return Color code as a string.
 */
inline std::string getColorCode(Color color)
{
	switch (color)
	{
	case Color::RED:
		return "\033[1;31m";
	case Color::GREEN:
		return "\033[1;32m";
	case Color::YELLOW:
		return "\033[1;33m";
	case Color::BLUE:
		return "\033[1;34m";
	case Color::MAGENTA:
		return "\033[1;35m";
	case Color::CYAN:
		return "\033[1;36m";
	case Color::WHITE:
		return "\033[1;37m";
	case Color::RESET:
	default:
		return "\033[0m";
	}
}

/**
 * @brief Function to color a text string with the desired color.
 *
 * @param text Text to color.
 * @param color Desired color.
 * @return Colored text as a string.
 */
inline std::string colorText(const std::string& text, Color color)
{
	return getColorCode(color) + text + getColorCode(Color::RESET);
}

/**
 * @brief Prints a separator line of the given length.
 *
 * @param length Length of the separator line.
 */
inline void printSeparator(const char symbol, Color color, size_t length)
{
	std::cout << getColorCode(color); // Change the color here
	for (int i = 0; i < length; ++i) std::cout << symbol;
	std::cout << std::endl << getColorCode(Color::RESET);
}

/**
 * @brief Prints a label with a separator line around it.
 *
 * @param label Label to print.
 */
inline void printLabel(const std::string& label, Color color = Color::BLUE)
{
	size_t length = label.length() + 6;
	printSeparator('=', color, length);
	std::cout << colorText("|| ", color) << label << colorText(" ||", color) << std::endl;
	printSeparator('=', color, length);
}

/**
 * @brief Converts a string to lowercase.
 *
 * @param str String to convert.
 * @return Lowercase version of the string.
 */
inline std::string toLower(const std::string& str)
{
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

#ifdef _WIN32
#include <windows.h>

/**
 * @brief Prints a window-sized separator line for Windows.
 */
inline void printWindowSizedSeparator()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;

	// Get the number of columns in the console window
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	printSeparator('-', Color::BLUE, columns);
}
#else
#include <unistd.h>
#include <sys/ioctl.h>

/**
 * @brief Prints a window-sized separator line for Unix-like systems.
 */
void printWindowSizedSeparator()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	int columns = w.ws_col;

	printSeparator('-', Color::BLUE, columns);
}
#endif

/**
 * @brief Displays a menu with the given title and options.
 *
 * @param title Title of the menu.
 * @param menuOptions Vector of menu options.
 */
inline void displayMenu(const std::string& title, const std::vector<MenuOption>& menuOptions)
{
	clearScreen(); // Clear the screen before displaying the menu
	printLabel(title, Color::BLUE);
	for (size_t i = 0; i < menuOptions.size(); ++i)
	{
		std::cout << i + 1 << ". " << menuOptions[i].first << "\n";
	}
	printWindowSizedSeparator();
}

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <cstdlib>
#endif

#endif // UTILS_H
