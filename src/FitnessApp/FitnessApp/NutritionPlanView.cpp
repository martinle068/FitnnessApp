#include "NutritionPlanView.h"
#include <iostream>

/**
 * @brief Constructs a NutritionPlanView with the given ViewModel.
 *
 * @param vm The ViewModel to be used by this view.
 */
NutritionPlanView::NutritionPlanView(NutritionPlanViewModel& vm) : viewModel(vm)
{
    menuOptions = {
        {"View Nutrition Plans", [this]() { printLabel("Viewing Nutrition Plans"); viewModel.view(); }},
        {"Add Nutrition Plan", [this]() { printLabel("Adding Nutrition Plan"); viewModel.add(); }},
        {"Modify Nutrition Plan", [this]() { printLabel("Modifying Nutrition Plan"); viewModel.modify(); }},
        {"Delete Nutrition Plan", [this]() { printLabel("Deleting Nutrition Plan"); viewModel.remove(); }},
        {"Import from file", [this]() { importFromFile(); }},
        {"Back", [this]() { return; }}
    };
}

/**
 * @brief Displays the Nutrition Plan menu and handles user interaction.
 */
void NutritionPlanView::display()
{
    viewModel.reload();
    displayAndHandleSubMenu("Nutrition Plans", menuOptions, true);
}

/**
 * @brief Prompts the user for a filename and imports nutrition plans from the specified file.
 */
void NutritionPlanView::importFromFile()
{
    std::string filename;
    std::cout << "Enter the filename to import nutrition plans from: ";
    std::getline(std::cin >> std::ws, filename);
    viewModel.importFromFile(filename);
    std::cout << "Nutrition plans imported from file: " << filename << std::endl;
}
