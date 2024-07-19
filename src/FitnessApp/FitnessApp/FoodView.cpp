#include "FoodView.h"

/**
 * @brief Constructs a FoodView object.
 *
 * Initializes the menu options for food-related actions.
 *
 * @param vm A reference to the FoodViewModel object.
 */
FoodView::FoodView(FoodViewModel& vm) : viewModel(vm)
{
    menuOptions = {
        {"View Food Items", [this]() { printLabel("Viewing Food Items"); viewModel.view(); }},
        {"Add Food Item", [this]() { printLabel("Adding a Food Item"); viewModel.add(); }},
        {"Modify Food Item", [this]() { printLabel("Modifying Food Item"); viewModel.modify(); }},
        {"Delete Food Item", [this]() { printLabel("Deleting Food Item"); viewModel.remove(); }},
        {"Import from file", [this]() { importFromFile(); }},
        {"Back", [this]() { return; }}
    };
}

/**
 * @brief Displays the food items menu and handles user interactions.
 *
 * Reloads the food items from the view model and displays the menu options.
 */
void FoodView::display()
{
    viewModel.reload();
    displayAndHandleSubMenu("Food", menuOptions, true);
}

/**
 * @brief Imports food items from a specified file.
 *
 * Prompts the user to enter a filename and imports food items from that file.
 */
void FoodView::importFromFile()
{
    std::string filename;
    std::cout << "Enter the filename to import food items from: ";
    std::getline(std::cin >> std::ws, filename);
    viewModel.importFromFile(filename);
    std::cout << "Food items imported from file: " << filename << std::endl;
}
