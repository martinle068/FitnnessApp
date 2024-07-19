#ifndef EXERCISEVIEW_H
#define EXERCISEVIEW_H

#include "ExerciseViewModel.h"
#include <iostream>
#include "Utils.h"
#include "View.h"

/**
 * @class ExerciseView
 * @brief Handles the user interface for displaying and managing exercises.
 *
 * This class provides methods to display the exercise menu and handle user interactions.
 */
class ExerciseView : public View
{
public:
    /**
     * @brief Constructs an ExerciseView object.
     *
     * @param viewModel A reference to the ExerciseViewModel object.
     */
    ExerciseView(ExerciseViewModel& viewModel);

    /**
     * @brief Displays the exercise menu and handles user interactions.
     */
    void display();

private:
    ExerciseViewModel& viewModel; ///< Reference to the ExerciseViewModel object.
    std::vector<MenuOption> menuOptions; ///< List of menu options for the exercise view.

    /**
     * @brief Imports exercises from a file.
     *
     * This method is used to import exercises from a specified file.
     */
    void importFromFile();
};

#endif // EXERCISEVIEW_H
