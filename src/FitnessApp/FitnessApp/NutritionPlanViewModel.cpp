#define NOMINMAX
#include "NutritionPlanViewModel.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <set>
#include <iomanip> 
#include <random>

/**
 * @brief Constructor to initialize NutritionPlanViewModel with a filename.
 * @param filename The filename from which to load nutrition plans.
 */
NutritionPlanViewModel::NutritionPlanViewModel(const std::string& filename) : filename(filename)
{
    reload();
}

/**
 * @brief Display food items by category.
 * @param foodItemMap The map of all food items.
 * @param category The category to filter food items by.
 * @param filteredFoodItems The vector to store the filtered food items.
 */
void displayFoodItemsByCategory(const std::map<std::string, FoodItem>& foodItemMap, const std::string& category, std::vector<FoodItem>& filteredFoodItems)
{
    size_t index = 1;
    std::cout << "Food items in the category '" << category << "':\n";
    for (const auto& pair : foodItemMap)
    {
        // Check if the food item belongs to the specified category
        if (pair.second.categories.find(category) != pair.second.categories.end())
        {
            // Display food item details
            std::cout << index << ". " << pair.second.name << " (Calories: " << pair.second.calories
                << " kcal, Protein: " << pair.second.protein << " g, Carbohydrates: " << pair.second.carbohydrates
                << " g, Fats: " << pair.second.fats << " g, Portion: " << pair.second.portion << " g)\n";
            filteredFoodItems.push_back(pair.second);
            index++;
        }
    }
    printWindowSizedSeparator();
}

/**
 * @brief Get available categories from the food item map.
 * @param foodItemMap The map of all food items.
 * @return A vector of available categories.
 */
std::vector<std::string> NutritionPlanViewModel::getAvailableCategories(const std::map<std::string, FoodItem>& foodItemMap)
{
    std::set<std::string> categories;
    for (const auto& pair : foodItemMap)
    {
        // Add all categories of each food item to the set
        categories.insert(pair.second.categories.begin(), pair.second.categories.end());
    }
    // Convert set to vector and return
    return std::vector<std::string>(categories.begin(), categories.end());
}

/**
 * @brief Handle adding food items to a meal in the nutrition plan.
 * @param selectedPlan The nutrition plan being modified.
 * @param foodItemMap The map of all food items.
 * @param mealName The name of the meal being modified.
 */
void NutritionPlanViewModel::handleAddFood(NutritionPlan& selectedPlan, const std::map<std::string, FoodItem>& foodItemMap, const std::string& mealName)
{
    // Get available categories
    auto categoryVec = getAvailableCategories(foodItemMap);

    // Display available categories
    for (size_t i = 0; i < categoryVec.size(); ++i)
    {
        std::cout << i + 1 << ". " << categoryVec[i] << "\n";
    }

    printWindowSizedSeparator();

    int categoryChoice;
    // Get user input for category selection
    getValidInput(categoryChoice, "Select a category by number: ", 1, static_cast<int>(categoryVec.size()));

    std::string category = categoryVec[categoryChoice - 1];
    std::vector<FoodItem> filteredFoodItems;

    while (true)
    {
        // Display food items in the selected category
        displayFoodItemsByCategory(foodItemMap, category, filteredFoodItems);

        int foodChoice;
        std::cout << "Select a food item by number (or '0' to go back): ";
        getValidInput(foodChoice, "Enter choice: ", 0, static_cast<int>(filteredFoodItems.size()));

        if (foodChoice == 0)
        {
            break;  // Exit the loop if the user chooses to go back
        }

        // Get the selected food item's name and quantity
        std::string foodName = filteredFoodItems[foodChoice - 1].name;
        float quantity;
        getValidInput(quantity, "Enter quantity in grams: ");
        // Add the food item to the selected meal in the nutrition plan
        selectedPlan.meals[mealName].emplace_back(foodItemMap.at(foodName), quantity);
        std::cout << "Food item added to " << mealName << ".\n";
        std::cout << "Press Enter to continue...\n";
        std::cin.get();
    }
}

/**
 * @brief Handle removing food items from a meal in the nutrition plan.
 * @param selectedPlan The nutrition plan being modified.
 * @param mealName The name of the meal being modified.
 */
void NutritionPlanViewModel::handleRemoveFood(NutritionPlan& selectedPlan, const std::string& mealName)
{
    std::cout << "Current foods in " << mealName << ":\n";
    int index = 1;
    std::vector<std::string> foodNames;
    for (const auto& foodPair : selectedPlan.meals[mealName])
    {
        // Display current food items in the meal
        std::cout << index << ". " << foodPair.first.name << " (" << foodPair.second << "g)\n";
        foodNames.push_back(foodPair.first.name);
        index++;
    }

    int removeChoice;
    while (true)
    {
        // Get user input for the food item to remove
        getValidInput(removeChoice, "Enter the number of the food item to remove (or '0' to cancel): ", 0, static_cast<int>(foodNames.size()));
        if (removeChoice == 0)
        {
            std::cout << "Remove operation cancelled.\n";
            break;  // Exit the loop if the user chooses to cancel
        }
        // Remove the selected food item from the meal
        auto it = selectedPlan.meals[mealName].begin() + (removeChoice - 1);
        selectedPlan.meals[mealName].erase(it);
        std::cout << "Food item removed from " << mealName << ".\n";
        std::cout << "Press Enter to continue...\n";
        std::cin.get();
        break;
    }
    printWindowSizedSeparator();
}

/**
 * @brief Modify a nutrition plan by adding or removing food items.
 * @param selectedPlan The nutrition plan being modified.
 * @param foodItemMap The map of all food items.
 */
void NutritionPlanViewModel::modifyNutritionPlan(NutritionPlan& selectedPlan, const std::map<std::string, FoodItem>& foodItemMap)
{
    std::string foodName;

    for (const auto& mealName : MEAL_NAMES)
    {
        while (true)
        {
            std::cout << "Current foods in " << mealName << ":\n";
            displayCurrentFoods(selectedPlan.meals[mealName]);

            std::cout << "Enter 'add' to add a new food, 'remove' to remove a food, 'done' to finish modifying " << mealName << ": ";
            std::getline(std::cin >> std::ws, foodName);

            printWindowSizedSeparator();

            if (foodName == "done")
            {
                break;  // Exit the loop if the user is done modifying
            }
            else if (foodName == "add")
            {
                handleAddFood(selectedPlan, foodItemMap, mealName);
            }
            else if (foodName == "remove")
            {
                handleRemoveFood(selectedPlan, mealName);
            }
            else
            {
                std::cout << "Invalid input.\n";
            }
        }
    }
}

/**
 * @brief Display current foods in a meal.
 * @param mealItems The list of food items in the meal.
 */
void NutritionPlanViewModel::displayCurrentFoods(const std::vector<std::pair<FoodItem, float>>& mealItems)
{
    for (size_t i = 0; i < mealItems.size(); ++i)
    {
        // Display each food item in the meal
        std::cout << i + 1 << ". " << mealItems[i].first.name << " (" << mealItems[i].second << "g)\n";
    }
}

/**
 * @brief Display view options for the user.
 * @return The number of options available.
 */
int viewOptions()
{
    std::cout << "View Options:\n";
    std::cout << "1. View All\n";
    std::cout << "2. Generate Plan by Goals\n";
    std::cout << "3. Cancel\n";

    return 3;
}

/**
 * @brief View nutrition plans based on user selection.
 */
void NutritionPlanViewModel::view()
{
    if (nutritionPlanMap.empty())
    {
        std::cout << "No nutrition plans available.\n";
        return;
    }

    int viewChoice;
    int optionsCount = viewOptions();
    getValidInput(viewChoice, "Enter choice: ", 1, optionsCount);

    printWindowSizedSeparator();

    switch (viewChoice)
    {
    case 1:
        viewAllPlans();
        break;
    case 2:
        viewPersonalizedPlan();
        break;
    case 3:
        std::cout << "View operation cancelled.\n";
        break;
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}

/**
 * @brief View all nutrition plans.
 */
void NutritionPlanViewModel::viewAllPlans()
{
    for (const auto& pair : nutritionPlanMap)
    {
        displayPlan(pair.second);
    }
}

/**
 * @brief Print the details of a single food item.
 * @param foodItem The food item to print.
 * @param quantity The quantity of the food item.
 */
void NutritionPlanViewModel::printFoodItem(const FoodItem& foodItem, float quantity)
{
    float calories = foodItem.calories * quantity / 100;
    float protein = foodItem.protein * quantity / 100;
    float carbs = foodItem.carbohydrates * quantity / 100;
    float fats = foodItem.fats * quantity / 100;

    // Display the details of the food item
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  " << foodItem.name << " - " << quantity << "g (Calories: " << calories
        << " kcal, Protein: " << protein << " g, Carbohydrates: " << carbs
        << " g, Fats: " << fats << " g, Portion: " << foodItem.portion << " g)\n";
}

/**
 * @brief Print the total nutrients for a single meal.
 * @param mealName The name of the meal.
 * @param totalMeal The total nutrients for the meal.
 */
void NutritionPlanViewModel::printMealTotal(const std::string& mealName, TotalNutrients totalMeal)
{
    // Display the total nutrients for the meal
    std::cout << "  Total for " << mealName << ": " << totalMeal.calories << " kcal"
        << " (Protein: " << totalMeal.protein << " g, Carbohydrates: " << totalMeal.carbs
        << " g, Fats: " << totalMeal.fats << " g)\n";
}

/**
 * @brief Print the total nutrients for the entire plan.
 * @param totalPlan The total nutrients for the plan.
 */
void NutritionPlanViewModel::printPlanTotal(TotalNutrients totalPlan)
{
    // Display the total nutrients for the plan
    std::cout << "Total for the plan: " << totalPlan.calories << " kcal"
        << " (Protein: " << totalPlan.protein << " g, Carbohydrates: " << totalPlan.carbs
        << " g, Fats: " << totalPlan.fats << " g)\n";
    printWindowSizedSeparator();
}

/**
 * @brief Display a nutrition plan with all its meals and food items.
 * @param plan The nutrition plan to display.
 */
void NutritionPlanViewModel::displayPlan(const NutritionPlan& plan)
{
    std::cout << "Name: " << plan.name << "\n";
    printWindowSizedSeparator();

    TotalNutrients totalPlan;

    for (const auto& mealName : MEAL_NAMES)
    {
        std::cout << mealName << ":\n";
        TotalNutrients totalMeal;

        for (const auto& foodPair : plan.meals.at(mealName))
        {
            const auto& foodItem = foodPair.first;
            float quantity = foodPair.second;

            // Print details of each food item
            printFoodItem(foodItem, quantity);

            // Calculate total nutrients for the meal
            totalMeal.calories += foodItem.calories * quantity / 100;
            totalMeal.protein += foodItem.protein * quantity / 100;
            totalMeal.carbs += foodItem.carbohydrates * quantity / 100;
            totalMeal.fats += foodItem.fats * quantity / 100;
        }

        // Print total nutrients for the meal
        printMealTotal(mealName, totalMeal);

        // Accumulate total nutrients for the entire plan
        totalPlan.calories += totalMeal.calories;
        totalPlan.protein += totalMeal.protein;
        totalPlan.carbs += totalMeal.carbs;
        totalPlan.fats += totalMeal.fats;
    }

    // Print total nutrients for the entire plan
    printPlanTotal(totalPlan);
}

/**
 * @brief Try loading profile and goals from CSV files.
 * @param profileFilename The filename of the profile CSV.
 * @param goalsFilename The filename of the goals CSV.
 * @param profile The Profile object to load data into.
 * @param goals The Goals object to load data into.
 * @return True if both profile and goals are loaded successfully, otherwise false.
 */
bool tryLoadProfileAndGoals(const std::string& profileFilename, const std::string& goalsFilename, Profile& profile, Goals& goals)
{
    if (!profile.loadFromCSV(profileFilename) || !goals.loadFromCSV(goalsFilename))
    {
        std::cerr << "Error loading profile or goals.\n";
        return false;
    }
    return true;
}

/**
 * @brief View a personalized nutrition plan based on goals.
 */
void NutritionPlanViewModel::viewPersonalizedPlan()
{
    Goals goals;
    Profile profile;

    if (!tryLoadProfileAndGoals("profile.csv", "goals.csv", profile, goals)) return;

    goals.setProfile(&profile);
    float requiredCalories = goals.getDailyCalories();
    float requiredProtein = (goals.getFitnessGoal() == Goals::FitnessGoal::MUSCLE_GAIN) ?
        profile.getWeight() * 2.2f : profile.getWeight() * 1.6f;

    while (true)
    {
        NutritionPlan randomPlan = generateNextPlan(requiredCalories, requiredProtein);

        clearScreen();
        printLabel("Viewing generated nutrition plan");
        displayPlan(randomPlan);

        std::string choice;
        do
        {
            std::cout << "Do you want to generate another plan? (yes/no) or save (save): ";
            std::getline(std::cin >> std::ws, choice);
        } while (choice != "yes" && choice != "no" && choice != "save");

        if (choice == "no")
        {
            break;
        }
        else if (choice == "save")
        {
            std::string planName;
            std::cout << "Enter plan name: ";
            std::getline(std::cin >> std::ws, planName);
            randomPlan.name = planName;
            std::map<std::string, NutritionPlan> newPlan;
            newPlan[planName] = randomPlan;

            overwriteCSV("personal_nutritional_plan.csv", newPlan);
            std::cout << "Plan saved.\n";
            break;
        }
    }
}

/**
 * @brief Add a new nutrition plan.
 */
void NutritionPlanViewModel::add()
{
    std::string name;
    std::map<std::string, std::vector<std::pair<FoodItem, float>>> meals;

    std::cout << "Enter nutrition plan name: ";
    std::getline(std::cin >> std::ws, name);

    if (nutritionPlanMap.find(name) != nutritionPlanMap.end())
    {
        if (!confirmOverwrite(nutritionPlanMap, name))
        {
            return;
        }
    }

    printWindowSizedSeparator();

    NutritionPlan plan(name, meals);
    modifyNutritionPlan(plan, foodItemMap);
    nutritionPlanMap[name] = plan;
    overwriteCSV(filename, nutritionPlanMap);
}

/**
 * @brief Modify an existing nutrition plan.
 */
void NutritionPlanViewModel::modify()
{
    if (nutritionPlanMap.empty())
    {
        std::cout << "No nutrition plans available to modify.\n";
        return;
    }

    std::string selectedPlanName = selectPlan("modify");

    if (selectedPlanName.empty())
    {
        std::cout << "Modify operation cancelled.\n";
        return;
    }

    auto& selectedPlan = nutritionPlanMap[selectedPlanName];
    modifyNutritionPlan(selectedPlan, foodItemMap);
    overwriteCSV(filename, nutritionPlanMap);
}

/**
 * @brief Remove an existing nutrition plan.
 */
void NutritionPlanViewModel::remove()
{
    if (nutritionPlanMap.empty())
    {
        std::cout << "No nutrition plans available to delete.\n";
        return;
    }

    std::string selectedPlanName = selectPlan("delete");

    if (selectedPlanName.empty())
    {
        std::cout << "Delete operation cancelled.\n";
        return;
    }

    confirmAndRemovePlan(selectedPlanName);
}

/**
 * @brief Import nutrition plans from a file.
 * @param filename The filename from which to import nutrition plans.
 */
void NutritionPlanViewModel::importFromFile(const std::string& filename)
{
    auto items = readFromCSV<NutritionPlan, FoodItem>(filename, foodItemMap);

    for (const auto& item : items)
    {
        auto it = nutritionPlanMap.find(item.first);
        if (it != nutritionPlanMap.end())
        {
            clearScreen();
            const auto& currentPlan = it->second;
            const auto& newPlan = item.second;

            std::cout << "Nutrition plan '" << item.first << "' already exists.\n";
            std::cout << "Current plan:\n";
            displayPlan(currentPlan);
            std::cout << "New plan:\n";
            displayPlan(newPlan);

            if (confirmOverwrite(nutritionPlanMap, item.first))
            {
                nutritionPlanMap[item.first] = newPlan;
            }
        }
        else
        {
            nutritionPlanMap[item.first] = item.second;
        }
    }

    overwriteCSV("nutrition_plans.csv", nutritionPlanMap);
}

/**
 * @brief Reload nutrition plans and food items from CSV files.
 */
void NutritionPlanViewModel::reload()
{
    foodItemMap = readFromCSV<FoodItem>("food_items.csv");
    nutritionPlanMap = readFromCSV<NutritionPlan, FoodItem>(filename, foodItemMap);
}

/**
 * @brief Select a nutrition plan for modification or deletion.
 * @param action The action to perform on the selected plan ("modify" or "delete").
 * @return The name of the selected nutrition plan.
 */
std::string NutritionPlanViewModel::selectPlan(const std::string& action)
{
    std::cout << "Select a nutrition plan to " << action << ":\n";
    int index = 1;
    std::vector<std::string> planNames;
    for (const auto& pair : nutritionPlanMap)
    {
        std::cout << index << ". " << pair.first << "\n";
        planNames.push_back(pair.first);
        ++index;
    }

    std::cout << index << ". Cancel\n";
    printWindowSizedSeparator();

    int choice;
    getValidInput(choice, "Enter choice: ", 1, index);

    if (choice == index)
    {
        return "";  // Return an empty string if the user chooses to cancel
    }

    return planNames[choice - 1];
}

/**
 * @brief Confirm and remove a selected nutrition plan.
 * @param selectedPlanName The name of the nutrition plan to remove.
 */
void NutritionPlanViewModel::confirmAndRemovePlan(const std::string& selectedPlanName)
{
    const auto& plan = nutritionPlanMap[selectedPlanName];

    std::cout << "Selected nutrition plan:\n";
    displayPlan(plan);

    std::string confirm;
    do
    {
        std::cout << "Are you sure you want to delete the nutrition plan '" << selectedPlanName << "'? (yes/no): ";
        std::getline(std::cin >> std::ws, confirm);
    } while (confirm != "yes" && confirm != "no");

    if (confirm != "yes")
    {
        std::cout << "Nutrition plan not deleted.\n";
        return;
    }

    nutritionPlanMap.erase(selectedPlanName);
    overwriteCSV(filename, nutritionPlanMap);
    std::cout << "Nutrition plan '" << selectedPlanName << "' deleted.\n";
}

/**
 * @brief Shuffle the names of the nutrition plans.
 */
void NutritionPlanViewModel::shufflePlanNames()
{
    shuffledPlanNames.clear();
    for (const auto& pair : nutritionPlanMap)
    {
        shuffledPlanNames.push_back(pair.first);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledPlanNames.begin(), shuffledPlanNames.end(), g);
}

/**
 * @brief Generate the next nutrition plan in the shuffled order.
 * @param targetCalories The target number of calories for the nutrition plan.
 * @param targetProtein The target amount of protein for the nutrition plan.
 * @return The generated nutrition plan.
 */
NutritionPlan NutritionPlanViewModel::generateNextPlan(float targetCalories, float targetProtein)
{
    if (nutritionPlanMap.empty())
    {
        throw std::runtime_error("No nutrition plans available");
    }

    // Shuffle the plan names if not already shuffled or all plans have been used
    if (shuffledPlanNames.empty() || currentPlanIndex >= shuffledPlanNames.size())
    {
        shufflePlanNames();
        currentPlanIndex = 0;
    }

    const int maxIterations = 1000;

    // Select the next plan in the shuffled order
    NutritionPlan selectedPlan = nutritionPlanMap.at(shuffledPlanNames[currentPlanIndex]);
    currentPlanIndex++;  // Move to the next plan

    NutritionPlan newPlan = selectedPlan;  // Start with a copy of the selected plan

    float currentCalories = 0;
    float currentProtein = 0;

    // Calculate the current calories and protein of the selected plan
    calculateCurrentValues(selectedPlan, currentCalories, currentProtein);

    // Reduce portions if the current calories are too high
    adjustPortions(newPlan, currentCalories, currentProtein, targetCalories, maxIterations, true);

    // Increase protein intake if it is below the target
    adjustProtein(newPlan, currentProtein, targetProtein, currentCalories, maxIterations, true);

    // Decrease protein intake if it is above the target
    adjustProtein(newPlan, currentProtein, targetProtein, currentCalories, maxIterations, false);

    // Add non-protein items to match caloric needs
    adjustNonProteinItems(newPlan, currentCalories, targetCalories, currentProtein, maxIterations);

    // Final adjustment to ensure the values are within the goals
    finalAdjustment(newPlan, currentCalories, targetCalories, currentProtein, targetProtein);

    return newPlan;
}

/**
 * @brief Calculate current calories and protein in a plan.
 * @param plan The nutrition plan to calculate values for.
 * @param currentCalories The current total calories in the plan.
 * @param currentProtein The current total protein in the plan.
 */
void NutritionPlanViewModel::calculateCurrentValues(const NutritionPlan& plan, float& currentCalories, float& currentProtein)
{
    currentCalories = 0;
    currentProtein = 0;
    for (const auto& meal : plan.meals)
    {
        for (const auto& foodPair : meal.second)
        {
            // Calculate total calories and protein based on the portion sizes
            currentCalories += foodPair.first.calories * foodPair.second / 100;
            currentProtein += foodPair.first.protein * foodPair.second / 100;
        }
    }
}

/**
 * @brief Adjust portions of food items in the plan based on target values.
 * @param plan The nutrition plan being modified.
 * @param currentCalories The current total calories in the plan.
 * @param currentProtein The current total protein in the plan.
 * @param target The target value to adjust towards (calories or protein).
 * @param maxIterations The maximum number of iterations to attempt adjustments.
 * @param isReducing True if reducing portions, false if increasing portions.
 */
void NutritionPlanViewModel::adjustPortions(NutritionPlan& plan, float& currentCalories, float& currentProtein, float target, int maxIterations, bool isReducing)
{
    int iterationCount = 0;

    while ((isReducing ? currentCalories > target : currentCalories < target) && iterationCount < maxIterations)
    {
        float adjustmentFactor = target / currentCalories;
        for (auto& meal : plan.meals)
        {
            for (auto& foodPair : meal.second)
            {
                // Adjust the portion sizes based on the adjustment factor
                foodPair.second = std::max(0.0f, foodPair.second * adjustmentFactor);
            }
        }
        // Recalculate the current calories and protein after adjustment
        calculateCurrentValues(plan, currentCalories, currentProtein);
        iterationCount++;
    }
}

/**
 * @brief Adjust protein intake in the plan to meet target values.
 * @param plan The nutrition plan being modified.
 * @param currentProtein The current total protein in the plan.
 * @param targetProtein The target protein value to adjust towards.
 * @param currentCalories The current total calories in the plan.
 * @param maxIterations The maximum number of iterations to attempt adjustments.
 * @param isIncreasing True if increasing protein intake, false if decreasing protein intake.
 */
void NutritionPlanViewModel::adjustProtein(NutritionPlan& plan, float& currentProtein, float targetProtein, float& currentCalories, int maxIterations, bool isIncreasing)
{
    int iterationCount = 0;

    while ((isIncreasing ? currentProtein < targetProtein : currentProtein > targetProtein) && iterationCount < maxIterations)
    {
        for (auto& meal : plan.meals)
        {
            for (auto& foodPair : meal.second)
            {
                if (foodPair.first.protein > proteinPerHundredGrams)
                {
                    // Adjust the portion size for protein-rich food items
                    float adjustmentQuantity = isIncreasing ? 10.0f : -10.0f;  // Add or reduce 10g increments
                    float newPortion = std::max(0.0f, foodPair.second + adjustmentQuantity);
                    if (newPortion == 0.0f && !isIncreasing) continue; // Avoid underflow

                    currentCalories += foodPair.first.calories * adjustmentQuantity / 100;
                    currentProtein += foodPair.first.protein * adjustmentQuantity / 100;
                    foodPair.second = newPortion;

                    if ((isIncreasing ? currentProtein >= targetProtein : currentProtein <= targetProtein))
                    {
                        return;
                    }
                }
            }
        }
        iterationCount++;
    }
}

/**
 * @brief Adjust non-protein items in the plan to meet caloric needs.
 * @param plan The nutrition plan being modified.
 * @param currentCalories The current total calories in the plan.
 * @param targetCalories The target caloric value to adjust towards.
 * @param currentProtein The current total protein in the plan.
 * @param maxIterations The maximum number of iterations to attempt adjustments.
 */
void NutritionPlanViewModel::adjustNonProteinItems(NutritionPlan& plan, float& currentCalories, float targetCalories, float& currentProtein, int maxIterations)
{
    int iterationCount = 0;

    while (currentCalories < targetCalories && iterationCount < maxIterations)
    {
        bool caloriesMatched = false;
        for (auto& meal : plan.meals)
        {
            for (auto& foodPair : meal.second)
            {
                if (foodPair.first.categories.find("protein") == foodPair.first.categories.end())
                {
                    // Add non-protein items to meet caloric needs
                    float additionalQuantity = 10;  // Add 10g increments
                    float newPortion = foodPair.second + additionalQuantity;
                    currentCalories += foodPair.first.calories * additionalQuantity / 100;
                    currentProtein += foodPair.first.protein * additionalQuantity / 100;
                    foodPair.second = newPortion;

                    if (currentCalories >= targetCalories)
                    {
                        caloriesMatched = true;
                        break;
                    }
                }
            }
            if (caloriesMatched)
            {
                break;
            }
        }
        iterationCount++;
    }
}

/**
 * @brief Final adjustment to ensure the plan meets target values for calories and protein.
 * @param plan The nutrition plan being modified.
 * @param currentCalories The current total calories in the plan.
 * @param targetCalories The target caloric value to adjust towards.
 * @param currentProtein The current total protein in the plan.
 * @param targetProtein The target protein value to adjust towards.
 */
void NutritionPlanViewModel::finalAdjustment(NutritionPlan& plan, float& currentCalories, float targetCalories, float& currentProtein, float targetProtein)
{
    const int maxIterations = 1000;
    int iterationCount = 0;

    // Final adjustment to reduce calories if they are too high
    if (currentCalories > targetCalories)
    {
        float reductionFactor = targetCalories / currentCalories;
        for (auto& meal : plan.meals)
        {
            for (auto& foodPair : meal.second)
            {
                float prevPortion = foodPair.second;
                // Reduce portion sizes proportionally
                foodPair.second = std::max(0.0f, foodPair.second * reductionFactor);
                currentCalories -= (prevPortion - foodPair.second) * foodPair.first.calories / 100;
            }
        }
    }

    // Final adjustment to reduce protein if it is too high
    adjustProtein(plan, currentProtein, targetProtein, currentCalories, maxIterations, false);

    // Final adjustment to add non-protein items if calories are too low
    while (currentCalories < targetCalories && iterationCount < maxIterations)
    {
        bool caloriesMatched = false;
        for (auto& meal : plan.meals)
        {
            for (auto& foodPair : meal.second)
            {
                if (foodPair.first.protein < proteinPerHundredGrams)
                {
                    // Add small increments of non-protein items
                    float additionalQuantity = 1;  // Add 1g increments
                    float newPortion = foodPair.second + additionalQuantity;
                    currentCalories += foodPair.first.calories * additionalQuantity / 100;
                    currentProtein += foodPair.first.protein * additionalQuantity / 100;
                    foodPair.second = newPortion;

                    if (currentCalories >= targetCalories)
                    {
                        caloriesMatched = true;
                        break;
                    }
                }
            }
            if (caloriesMatched)
            {
                break;
            }
        }
        iterationCount++;
    }
}
