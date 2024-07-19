#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>

/**
 * @brief Class representing a food item with nutritional information.
 */
class FoodItem
{
public:
    std::string name; ///< Name of the food item.
    std::set<std::string> categories; ///< Categories the food item belongs to.
    int calories = 0; ///< Calories per 100 grams.
    float protein = 0; ///< Protein content per 100 grams.
    float carbohydrates = 0; ///< Carbohydrate content per 100 grams.
    float fats = 0; ///< Fat content per 100 grams.
    float portion = 0; ///< Portion size in grams.

    /**
     * @brief Default constructor.
     */
    FoodItem() = default;

    /**
     * @brief Parameterized constructor.
     *
     * @param name Name of the food item.
     * @param categories Categories the food item belongs to.
     * @param calories Calories per 100 grams.
     * @param protein Protein content per 100 grams.
     * @param carbohydrates Carbohydrate content per 100 grams.
     * @param fats Fat content per 100 grams.
     * @param portion Portion size in grams (default is 0).
     */
    FoodItem(std::string name, std::set<std::string> categories, int calories, float protein, float carbohydrates, float fats, float portion = 0)
        : name(std::move(name)), categories(std::move(categories)), calories(calories), protein(protein), carbohydrates(carbohydrates), fats(fats), portion(portion)
    {
    }

    /**
     * @brief Serializes the food item to a CSV stream.
     *
     * @param os Output stream to write to.
     */
    void toCSV(std::ostream& os) const;

    /**
     * @brief Parses a food item from a CSV stream.
     *
     * @param is Input stream to read from.
     * @return True if parsing was successful, false otherwise.
     */
    bool fromCSV(std::istream& is);

    /**
     * @brief Displays the nutritional values for a given quantity of the food item.
     *
     * @param quantity Quantity in grams.
     */
    void displayNutritionalValues(float quantity) const;
};

#endif // FOODITEM_H
