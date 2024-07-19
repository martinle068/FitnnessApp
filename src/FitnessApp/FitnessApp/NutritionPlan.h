#ifndef NUTRITION_PLAN_H
#define NUTRITION_PLAN_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "FoodItem.h"

/**
 * @brief Represents a nutrition plan consisting of meals and their respective food items and portion sizes.
 */
class NutritionPlan
{
public:
    std::string name; ///< The name of the nutrition plan.
    std::map<std::string, std::vector<std::pair<FoodItem, float>>> meals; ///< Meal name to list of (FoodItem, portion size).

    /**
     * @brief Default constructor for NutritionPlan.
     */
    NutritionPlan() = default;

    /**
     * @brief Parameterized constructor for NutritionPlan.
     * @param name The name of the nutrition plan.
     * @param meals A map of meal names to their respective food items and portion sizes.
     */
    NutritionPlan(std::string name, std::map<std::string, std::vector<std::pair<FoodItem, float>>> meals)
        : name(std::move(name)), meals(std::move(meals))
    {
    }

    /**
     * @brief Converts the nutrition plan to CSV format and writes it to the given output stream.
     * @param os The output stream to write the CSV data to.
     */
    void toCSV(std::ostream& os) const;

    /**
     * @brief Loads the nutrition plan from CSV format from the given input stream.
     * @param is The input stream to read the CSV data from.
     * @param items A map of available food items to look up by name.
     * @return True if the nutrition plan was successfully loaded, false otherwise.
     */
    bool fromCSV(std::istream& is, const std::map<std::string, FoodItem>& items);

    /**
     * @brief Displays the nutrition plan details to the standard output.
     */
    void display() const;

    /**
     * @brief Adjusts the portion sizes of all meals in the nutrition plan by a given factor.
     * @param factor The factor by which to adjust the portion sizes.
     */
    void adjustPortionSizes(float factor);

    /**
     * @brief Gets a new nutrition plan for a specific meal name.
     * @param ss The input string stream containing the CSV data.
     * @param items A map of available food items to look up by name.
     * @param mealName The name of the meal to get the nutrition plan for.
     */
    void getNewNutritionPlan(std::istringstream& ss, const std::map<std::string, FoodItem>& items, const std::string& mealName);
};

#endif // NUTRITION_PLAN_H
