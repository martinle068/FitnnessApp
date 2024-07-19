#ifndef VIEW_H
#define VIEW_H

#include "Utils.h"
#include <iostream>
#include <vector>
#include <functional>

/**
 * @brief Abstract base class for all views in the application.
 */
class View
{
public:
    /**
     * @brief Virtual destructor for the View class.
     */
    virtual ~View() = default;

    /**
     * @brief Pure virtual function to display the view.
     */
    virtual void display() = 0;

    /**
     * @brief Displays a submenu and handles user input to navigate the options.
     *
     * @param title The title of the submenu.
     * @param menuOptions A vector of menu options to display.
     * @param askForEnterAtTheEnd A boolean indicating whether to ask for Enter key press at the end.
     */
    inline void displayAndHandleSubMenu(const std::string& title, const std::vector<MenuOption>& menuOptions, bool askForEnterAtTheEnd)
    {
        std::string input;
        int choice;
        while (true)
        {
            clearScreen(); // Clear the screen before displaying the menu
            displayMenu(title, menuOptions);
            std::cout << "Select an action: ";

            std::getline(std::cin >> std::ws, input);

            try
            {
                size_t pos;
                choice = std::stoi(input, &pos);
                // If pos is not at the end of the string, then not all characters were valid numbers
                if (pos != input.length())
                {
                    choice = 0; // Invalid choice
                }
            }
            catch (const std::exception&)
            {
                choice = 0; // Invalid choice
            }

            if (choice < 1 || choice > static_cast<int>(menuOptions.size()))
            {
                std::cout << "Invalid input, please enter a number between 1 and " << menuOptions.size() << ".\n";
                std::cout << "Press Enter to continue...";
                std::cin.get();
                clearScreen(); // Clear the screen for the next iteration
                continue;
            }

            clearScreen();

            if (choice == static_cast<int>(menuOptions.size()))
            {
                return; // Exit the loop and return to the previous menu
            }

            menuOptions[choice - 1].second();

            if (askForEnterAtTheEnd)
            {
                // After performing the action, display a message and show options again
                std::cout << "Press Enter to continue...";
                std::cin.get(); // Actually get the Enter key
                clearScreen(); // Clear the screen for the next iteration
            }
        }
    }
};

#endif // VIEW_H
