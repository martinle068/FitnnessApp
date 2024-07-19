#include "FoodItem.h"

/**
 * @brief Serializes the food item to a CSV stream.
 *
 * @param os Output stream to write to.
 */
void FoodItem::toCSV(std::ostream& os) const
{
    os << name << ",";
    for (const auto& category : categories)
    {
        os << category << ";";
    }
    os << "," << calories << "," << protein << "," << carbohydrates << "," << fats << "," << portion << "\n";
}

/**
 * @brief Parses a food item from a CSV stream.
 *
 * @param is Input stream to read from.
 * @return True if parsing was successful, false otherwise.
 */
bool FoodItem::fromCSV(std::istream& is)
{
    std::string categoriesStr, calStr, proteinStr, carbStr, fatsStr, portionStr;
    if (std::getline(is, name, ',') && std::getline(is, categoriesStr, ',') &&
        std::getline(is, calStr, ',') && std::getline(is, proteinStr, ',') &&
        std::getline(is, carbStr, ',') && std::getline(is, fatsStr, ',') &&
        std::getline(is, portionStr))
    {
        std::stringstream ss(categoriesStr);
        std::string category;
        while (std::getline(ss, category, ';'))
        {
            categories.insert(category);
        }

        calories = std::stoi(calStr);
        protein = std::stof(proteinStr);
        carbohydrates = std::stof(carbStr);
        fats = std::stof(fatsStr);
        portion = std::stof(portionStr);
        return true;
    }
    return false;
}

/**
 * @brief Displays the nutritional values for a given quantity of the food item.
 *
 * @param quantity Quantity in grams.
 */
void FoodItem::displayNutritionalValues(float quantity) const
{
    std::cout << "Nutritional values for " << quantity << " grams of " << name << ":\n";
    std::cout << "Calories: " << (calories * quantity / 100) << " kcal\n";
    std::cout << "Protein: " << (protein * quantity / 100) << " g\n";
    std::cout << "Carbohydrates: " << (carbohydrates * quantity / 100) << " g\n";
    std::cout << "Fats: " << (fats * quantity / 100) << " g\n";
    std::cout << "Portion size: " << portion << " grams\n";
}
