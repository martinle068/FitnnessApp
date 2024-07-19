#ifndef APPLICATION_H
#define APPLICATION_H

#include "ExerciseView.h"
#include "ExerciseViewModel.h"
#include "FoodView.h"
#include "FoodViewModel.h"
#include "ProfileView.h"
#include "Profile.h"
#include "Goals.h"
#include "WorkoutPlanView.h"
#include "WorkoutPlanViewModel.h"
#include "MainView.h"
#include "NutritionPlanView.h"
#include "NutritionPlanViewModel.h"

/**
 * @brief The main application class that initializes and runs the fitness application.
 */
class FitnessApp
{
public:
    /**
     * @brief Constructs the FitnessApp object and initializes the view models and views.
     */
    FitnessApp();

    /**
     * @brief Runs the main loop of the application.
     */
    void run();

private:
    ExerciseViewModel exerciseViewModel; ///< The view model for exercises.
    FoodViewModel foodViewModel; ///< The view model for food items.
    Profile profile; ///< The user's profile.
    Goals goals; ///< The user's fitness goals.
    WorkoutPlanViewModel workoutPlanViewModel; ///< The view model for workout plans.
    ExerciseView exerciseView; ///< The view for displaying exercises.
    FoodView foodView; ///< The view for displaying food items.
    ProfileView profileView; ///< The view for displaying the user's profile.
    WorkoutPlanView workoutPlanView; ///< The view for displaying workout plans.
    NutritionPlanViewModel nutritionPlanViewModel; ///< The view model for nutrition plans.
    NutritionPlanView nutritionPlanView; ///< The view for displaying nutrition plans.
    MainView mainView; ///< The main view that combines all other views.
};

#endif // APPLICATION_H
