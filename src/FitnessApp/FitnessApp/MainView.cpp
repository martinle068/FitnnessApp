#include "MainView.h"
#include "Utils.h"
#include <iostream>

/**
 * @brief Constructs the MainView with references to the specific view components.
 *
 * @param ev Reference to the ExerciseView component.
 * @param fv Reference to the FoodView component.
 * @param pv Reference to the ProfileView component.
 * @param wpv Reference to the WorkoutPlanView component.
 * @param nv Reference to the NutritionPlanView component.
 */
MainView::MainView(ExerciseView& ev, FoodView& fv, ProfileView& pv, WorkoutPlanView& wpv, NutritionPlanView& nv)
    : exerciseView(ev), foodView(fv), profileView(pv), workoutPlanView(wpv), nutritionPlanView(nv)
{
    menuOptions = {
        {"Profile", [this]() { profileView.display(); }},
        {"Exercises", [this]() { exerciseView.display(); }},
        {"Food", [this]() { foodView.display(); }},
        {"Workout Plans", [this]() { workoutPlanView.display(); }},
        {"Nutrition Plans", [this]() { nutritionPlanView.display(); }},
        {"Exit", [this]() { exit(0); }}
    };
}

/**
 * @brief Displays the main view menu.
 */
void MainView::display()
{
    displayAndHandleSubMenu("Welcome to the Fitness Database", menuOptions, false);
}
