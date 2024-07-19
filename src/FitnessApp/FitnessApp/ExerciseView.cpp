#include "ExerciseView.h"

/**
 * @brief Constructs an ExerciseView object.
 *
 * Initializes the menu options for the exercise view.
 *
 * @param vm A reference to the ExerciseViewModel object.
 */
ExerciseView::ExerciseView(ExerciseViewModel& vm) : viewModel(vm)
{
    menuOptions = {
        {"View Exercises", [this]() { printLabel("Viewing Exercises"); viewModel.view(); }},
        {"Add Exercise", [this]() { printLabel("Adding Exercise"); viewModel.add(); }},
        {"Modify Exercise", [this]() { printLabel("Modifying Exercise"); viewModel.modify(); }},
        {"Delete Exercise", [this]() { printLabel("Deleting Exercise"); viewModel.remove(); }},
        {"Import from file", [this]() { importFromFile(); }},
        {"Back", [this]() { return; }}
    };
}

/**
 * @brief Displays the exercise menu and handles user interactions.
 *
 * This method reloads the view model data and displays the exercise menu.
 * It allows the user to select various actions related to exercises.
 */
void ExerciseView::display()
{
    viewModel.reload();
    displayAndHandleSubMenu("Exercises", menuOptions, true);
}

/**
 * @brief Imports exercises from a file.
 *
 * Prompts the user to enter a filename and imports exercises from the specified file.
 */
void ExerciseView::importFromFile()
{
    std::string filename;
    std::cout << "Enter the filename to import exercises from: ";
    std::getline(std::cin >> std::ws, filename);
    viewModel.importFromFile(filename);
    std::cout << "Exercises imported from file: " << filename << std::endl;
}
