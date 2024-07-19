#ifndef WORKOUT_PLAN_VIEW_H
#define WORKOUT_PLAN_VIEW_H

#include "WorkoutPlanViewModel.h"
#include "View.h"

/**
 * @brief The WorkoutPlanView class represents the view for managing workout plans.
 * It provides a user interface for viewing, adding, modifying, and deleting workout plans.
 */
class WorkoutPlanView : public View
{
public:
    /**
     * @brief Constructs a new WorkoutPlanView object.
     * @param vm The WorkoutPlanViewModel to be used by this view.
     */
    WorkoutPlanView(WorkoutPlanViewModel& vm);

    /**
     * @brief Displays the workout plan view menu and handles user interaction.
     */
    void display();

private:
    WorkoutPlanViewModel& viewModel; ///< Reference to the view model for workout plans.
    std::vector<MenuOption> menuOptions; ///< List of menu options for user interaction.

    /**
     * @brief Prompts the user to enter a filename and imports workout plans from the specified file.
     */
    void importFromFile();
};

#endif // WORKOUT_PLAN_VIEW_H
