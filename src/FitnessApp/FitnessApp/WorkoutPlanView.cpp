#include "WorkoutPlanView.h"
#include "Utils.h"
#include <iostream>

/**
 * @brief Constructs a new WorkoutPlanView object.
 * @param vm The WorkoutPlanViewModel to be used by this view.
 */
WorkoutPlanView::WorkoutPlanView(WorkoutPlanViewModel& vm) : viewModel(vm)
{
    menuOptions = {
        {"View Workout Plans", [this]() { printLabel("Viewing Workout Plans"); viewModel.view(); }},
        {"Add Workout Plan", [this]() { printLabel("Adding Workout Plan"); viewModel.add(); }},
        {"Modify Workout Plan", [this]() { printLabel("Modifying Workout Plan"); viewModel.modify(); }},
        {"Delete Workout Plan", [this]() { printLabel("Deleting Workout Plan"); viewModel.remove(); }},
        {"Import Workout Plan from File", [this]() { importFromFile(); }},
        {"Back", [this]() { return; }}
    };
}

/**
 * @brief Displays the workout plan view menu and handles user interaction.
 */
void WorkoutPlanView::display()
{
    viewModel.reload();
    displayAndHandleSubMenu("Workout Plans", menuOptions, true);
}

/**
 * @brief Prompts the user to enter a filename and imports workout plans from the specified file.
 */
void WorkoutPlanView::importFromFile()
{
    std::string filename;
    std::cout << "Enter the filename to import workout plans from: ";
    std::getline(std::cin >> std::ws, filename);
    viewModel.importFromFile(filename);
    std::cout << "Workout plans imported from file: " << filename << std::endl;
}
