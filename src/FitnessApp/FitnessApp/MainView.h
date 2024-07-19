#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "View.h"
#include "WorkoutPlanView.h"
#include "ExerciseView.h"
#include "FoodView.h"
#include "ProfileView.h"
#include "NutritionPlanView.h"

/**
 * @class MainView
 * @brief The MainView class provides the main interface for the application.
 */
class MainView : public View
{
public:
    /**
     * @brief Constructs the MainView with references to the specific view components.
     *
     * @param exerciseView Reference to the ExerciseView component.
     * @param foodView Reference to the FoodView component.
     * @param profileView Reference to the ProfileView component.
     * @param workoutPlanView Reference to the WorkoutPlanView component.
     * @param nutritionPlanView Reference to the NutritionPlanView component.
     */
    MainView(ExerciseView& exerciseView, FoodView& foodView, ProfileView& profileView, WorkoutPlanView& workoutPlanView, NutritionPlanView& nutritionPlanView);

    /**
     * @brief Displays the main view menu.
     */
    void display();

private:
    ExerciseView& exerciseView; ///< Reference to the ExerciseView component.
    FoodView& foodView; ///< Reference to the FoodView component.
    ProfileView& profileView; ///< Reference to the ProfileView component.
    WorkoutPlanView& workoutPlanView; ///< Reference to the WorkoutPlanView component.
    NutritionPlanView& nutritionPlanView; ///< Reference to the NutritionPlanView component.
    std::vector<MenuOption> menuOptions; ///< Vector of menu options.
};

#endif // MAIN_VIEW_H
