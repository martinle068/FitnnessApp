#include "FitnessApp.h"

/**
 * @brief Constructs the FitnessApp object and initializes the view models and views.
 */
FitnessApp::FitnessApp()
    : exerciseViewModel("exercises.csv"),
    foodViewModel("food_items.csv"),
    workoutPlanViewModel("workout_plans.csv"),
    exerciseView(exerciseViewModel),
    foodView(foodViewModel),
    profileView(profile, goals),
    workoutPlanView(workoutPlanViewModel),
    nutritionPlanViewModel("nutrition_plans.csv"),
    nutritionPlanView(nutritionPlanViewModel),
    mainView(exerciseView, foodView, profileView, workoutPlanView, nutritionPlanView)
{
}

/**
 * @brief Runs the main loop of the application.
 */
void FitnessApp::run()
{
    mainView.display();
}
