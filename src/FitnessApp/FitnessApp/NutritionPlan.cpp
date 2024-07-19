#include "NutritionPlan.h"
#include <sstream>
#include <iostream>
#include "Utils.h"

/**
 * @brief Converts the nutrition plan to a CSV format and writes it to the given output stream.
 * @param os The output stream to write the CSV data to.
 */
void NutritionPlan::toCSV(std::ostream& os) const
{
    os << name << ",";

    for (const auto& mealName : MEAL_NAMES)
    {
        auto it = meals.find(mealName);
        if (it != meals.end())
        {
            for (size_t i = 0; i < it->second.size(); ++i)
            {
                const auto& foodPair = it->second[i];
                os << foodPair.first.name << "=" << foodPair.second;
                if (i < it->second.size() - 1)
                {
                    os << ";";
                }
            }
        }
        os << ",";
    }
    os << "\n";
}

/**
 * @brief Prompts the user to enter details for a new food item and returns the created FoodItem.
 * @param itemName The name of the food item.
 * @return The created FoodItem object.
 */
FoodItem getNewFoodItem(const std::string& itemName)
{
    std::set<std::string> categories;
    int calories;
    float protein, carbohydrates, fats, portion = 0;

    while (true)
    {
        std::string category;
        std::cout << "Enter category (or 'done' to finish): ";
        std::getline(std::cin >> std::ws, category);
        if (category == "done")
        {
            break;
        }
        categories.insert(toLower(category));
    }

    getValidInput(calories, "Enter calories per 100 grams: ");
    getValidInput(protein, "Enter protein per 100 grams: ");
    getValidInput(carbohydrates, "Enter carbohydrates per 100 grams: ");
    getValidInput(fats, "Enter fats per 100 grams: ");
    getOptionalInput(portion, "Enter portion size in grams (or press enter to skip): ");

    return FoodItem{ itemName, categories, calories, protein, carbohydrates, fats, portion };
}

/**
 * @brief Reads a new nutrition plan from a CSV string stream.
 * @param ss The stringstream to read the CSV data from.
 * @param items A map of available food items to look up by name.
 * @param mealName The name of the meal to read.
 */
void NutritionPlan::getNewNutritionPlan(std::istringstream& ss, const std::map<std::string, FoodItem>& items, const std::string& mealName)
{
    std::string token;

    if (std::getline(ss, token, ','))
    {
        std::vector<std::pair<FoodItem, float>> mealItems;
        std::stringstream mealStream(token);
        std::string itemToken;
        while (std::getline(mealStream, itemToken, ';'))
        {
            std::istringstream itemStream(itemToken);
            std::string itemName, portionStr;
            if (std::getline(itemStream, itemName, '=') && std::getline(itemStream, portionStr))
            {
                float portion = std::stof(portionStr);
                auto it = items.find(itemName);
                if (it != items.end())
                {
                    mealItems.emplace_back(it->second, portion);
                }
                else
                {
                    std::cerr << "Food item " << itemName << " not found in the provided items map.\n";

                    FoodItem foodItem = getNewFoodItem(itemName);

                    getValidInput(portion, "Enter portion size for this meal in grams: ");

                    mealItems.emplace_back(foodItem, portion);
                    writeToCSV("food_items.csv", foodItem);
                }
            }
        }
        meals[mealName] = mealItems;
    }
}

/**
 * @brief Loads the nutrition plan from a CSV format from the given input stream.
 * @param is The input stream to read the CSV data from.
 * @param items A map of available food items to look up by name.
 * @return True if the nutrition plan was successfully loaded, false otherwise.
 */
bool NutritionPlan::fromCSV(std::istream& is, const std::map<std::string, FoodItem>& items)
{
    std::string line;
    if (std::getline(is, line))
    {
        std::istringstream ss(line);
        if (std::getline(ss, name, ','))
        {
            for (const auto& mealName : MEAL_NAMES)
            {
                getNewNutritionPlan(ss, items, mealName);
            }
            return true;
        }
    }
    return false;
}

/**
 * @brief Displays the nutrition plan details to the standard output.
 */
void NutritionPlan::display() const
{
    std::cout << "Nutrition Plan: " << name << "\n";
    for (const auto& meal : meals)
    {
        std::cout << meal.first << ":\n";
        for (const auto& pair : meal.second)
        {
            std::cout << "  " << pair.first.name << " - " << pair.second << " grams\n";
        }
    }
}

/**
 * @brief Adjusts the portion sizes of all meals in the nutrition plan by a given factor.
 * @param factor The factor by which to adjust the portion sizes.
 */
void NutritionPlan::adjustPortionSizes(float factor)
{
    for (auto& meal : meals)
    {
        for (auto& pair : meal.second)
        {
            pair.second *= factor;
        }
    }
}
