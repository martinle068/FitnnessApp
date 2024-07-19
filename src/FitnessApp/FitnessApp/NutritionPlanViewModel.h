#ifndef NUTRITION_PLAN_VIEW_MODEL_H
#define NUTRITION_PLAN_VIEW_MODEL_H

#include <map>
#include <string>
#include <vector>
#include "NutritionPlan.h"
#include "FoodItem.h"
#include "Goals.h"
#include "Profile.h"
#include "ViewModel.h"

/**
 * @brief Struct to represent total nutrients.
 */
struct TotalNutrients
{
    float calories = 0;
    float protein = 0;
    float carbs = 0;
    float fats = 0;
};

/**
 * @brief ViewModel class for managing and manipulating nutrition plans.
 */
class NutritionPlanViewModel : public ViewModel
{
public:
    /**
     * @brief Constructor to initialize the NutritionPlanViewModel with a file name.
     * @param filename The name of the file containing the nutrition plans.
     */
    NutritionPlanViewModel(const std::string& filename);

    /**
     * @brief Display the nutrition plans.
     */
    void view() override;

    /**
     * @brief Add a new nutrition plan.
     */
    void add() override;

    /**
     * @brief Modify an existing nutrition plan.
     */
    void modify() override;

    /**
     * @brief Remove a nutrition plan.
     */
    void remove() override;

    /**
     * @brief Import nutrition plans from a file.
     * @param filename The name of the file to import nutrition plans from.
     */
    void importFromFile(const std::string& filename) override;

    /**
     * @brief Reload the nutrition plans and food items from the CSV files.
     */
    void reload() override;

private:
    std::string filename; /**< The name of the file containing the nutrition plans. */
    std::map<std::string, NutritionPlan> nutritionPlanMap; /**< Map of nutrition plans. */
    std::map<std::string, FoodItem> foodItemMap; /**< Map of food items. */
    size_t currentPlanIndex = 0; /**< Current index of the nutrition plan. */
    std::vector<std::string> shuffledPlanNames; /**< Vector of shuffled plan names. */
    const int proteinPerHundredGrams = 15; /**< Protein amount per hundred grams. */

    /**
     * @brief Modify a nutrition plan.
     * @param selectedPlan The nutrition plan to modify.
     * @param foodItemMap The map of food items.
     */
    void modifyNutritionPlan(NutritionPlan& selectedPlan, const std::map<std::string, FoodItem>& foodItemMap);

    /**
     * @brief Generate the next nutrition plan based on the target calories and protein.
     * @param targetCalories The target calories.
     * @param targetProtein The target protein.
     * @return The generated nutrition plan.
     */
    NutritionPlan generateNextPlan(float targetCalories, float targetProtein);

    /**
     * @brief Shuffle the plan names.
     */
    void shufflePlanNames();

    /**
     * @brief Calculate the current calories and protein in a plan.
     * @param plan The nutrition plan.
     * @param currentCalories The calculated current calories.
     * @param currentProtein The calculated current protein.
     */
    void calculateCurrentValues(const NutritionPlan& plan, float& currentCalories, float& currentProtein);

    /**
     * @brief Adjust portions of the nutrition plan.
     * @param plan The nutrition plan.
     * @param currentCalories The current calories.
     * @param currentProtein The current protein.
     * @param target The target value for adjustment.
     * @param maxIterations The maximum number of iterations for adjustment.
     * @param isReducing Flag to indicate if the adjustment is for reducing or increasing.
     */
    void adjustPortions(NutritionPlan& plan, float& currentCalories, float& currentProtein, float target, int maxIterations, bool isReducing);

    /**
     * @brief Adjust the protein intake in the nutrition plan.
     * @param plan The nutrition plan.
     * @param currentProtein The current protein.
     * @param targetProtein The target protein.
     * @param currentCalories The current calories.
     * @param maxIterations The maximum number of iterations for adjustment.
     * @param isIncreasing Flag to indicate if the adjustment is for increasing or decreasing.
     */
    void adjustProtein(NutritionPlan& plan, float& currentProtein, float targetProtein, float& currentCalories, int maxIterations, bool isIncreasing);

    /**
     * @brief Add non-protein items to match the caloric needs.
     * @param plan The nutrition plan.
     * @param currentCalories The current calories.
     * @param targetCalories The target calories.
     * @param currentProtein The current protein.
     * @param maxIterations The maximum number of iterations for adjustment.
     */
    void adjustNonProteinItems(NutritionPlan& plan, float& currentCalories, float targetCalories, float& currentProtein, int maxIterations);

    /**
     * @brief Perform final adjustments to ensure the values are within the goals.
     * @param plan The nutrition plan.
     * @param currentCalories The current calories.
     * @param targetCalories The target calories.
     * @param currentProtein The current protein.
     * @param targetProtein The target protein.
     */
    void finalAdjustment(NutritionPlan& plan, float& currentCalories, float targetCalories, float& currentProtein, float targetProtein);

    // Helper functions for view and modification operations

    /**
     * @brief Display current foods in a meal.
     * @param mealItems The vector of food items and their quantities.
     */
    void displayCurrentFoods(const std::vector<std::pair<FoodItem, float>>& mealItems);

    /**
     * @brief Handle the addition of a food item to a meal.
     * @param selectedPlan The selected nutrition plan.
     * @param foodItemMap The map of food items.
     * @param mealName The name of the meal.
     */
    void handleAddFood(NutritionPlan& selectedPlan, const std::map<std::string, FoodItem>& foodItemMap, const std::string& mealName);

    /**
     * @brief Handle the removal of a food item from a meal.
     * @param selectedPlan The selected nutrition plan.
     * @param mealName The name of the meal.
     */
    void handleRemoveFood(NutritionPlan& selectedPlan, const std::string& mealName);

    /**
     * @brief Get the available categories from the food item map.
     * @param foodItemMap The map of food items.
     * @return A vector of available categories.
     */
    std::vector<std::string> getAvailableCategories(const std::map<std::string, FoodItem>& foodItemMap);

    /**
     * @brief View all nutrition plans.
     */
    void viewAllPlans();

    /**
     * @brief View a personalized nutrition plan based on goals.
     */
    void viewPersonalizedPlan();

    /**
     * @brief Display a nutrition plan.
     * @param plan The nutrition plan to display.
     */
    void displayPlan(const NutritionPlan& plan);

    /**
     * @brief Select a nutrition plan for modification or deletion.
     * @param action The action to be performed (modify/delete).
     * @return The name of the selected nutrition plan.
     */
    std::string selectPlan(const std::string& action);

    /**
     * @brief Confirm and remove a selected nutrition plan.
     * @param selectedPlanName The name of the selected nutrition plan.
     */
    void confirmAndRemovePlan(const std::string& selectedPlanName);

    /**
     * @brief Print a food item.
     * @param foodItem The food item to print.
     * @param quantity The quantity of the food item.
     */
    void printFoodItem(const FoodItem& foodItem, float quantity);

    /**
     * @brief Print the total nutrients for a meal.
     * @param mealName The name of the meal.
     * @param totalMeal The total nutrients for the meal.
     */
    void printMealTotal(const std::string& mealName, TotalNutrients totalMeal);

    /**
     * @brief Print the total nutrients for the entire plan.
     * @param totalPlan The total nutrients for the entire plan.
     */
    void printPlanTotal(TotalNutrients totalPlan);
};

#endif // NUTRITION_PLAN_VIEW_MODEL_H
