#ifndef FOODVIEW_H
#define FOODVIEW_H

#include "FoodViewModel.h"
#include <iostream>
#include "Utils.h"
#include "View.h"

/**
 * @class FoodView
 * @brief Handles the user interface for displaying and managing food items.
 *
 * This class provides methods to display the food items menu and handle user interactions.
 */
class FoodView : public View
{
public:
    /**
     * @brief Constructs a FoodView object.
     *
     * @param viewModel A reference to the FoodViewModel object.
     */
    FoodView(FoodViewModel& viewModel);

    /**
     * @brief Displays the food items menu and handles user interactions.
     */
    void display();

private:
    FoodViewModel& viewModel; ///< Reference to the FoodViewModel object.
    std::vector<MenuOption> menuOptions; ///< List of menu options for the food view.

    /**
     * @brief Imports food items from a file.
     *
     * This method is used to import food items from a specified file.
     */
    void importFromFile();
};

#endif // FOODVIEW_H
