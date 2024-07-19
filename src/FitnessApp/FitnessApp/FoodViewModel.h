#ifndef FOODVIEWMODEL_H
#define FOODVIEWMODEL_H

#include "ViewModel.h"
#include "FoodItem.h"
#include <map>

/**
 * @class FoodViewModel
 * @brief ViewModel class for handling food items.
 *
 * This class provides functionalities to view, add, modify, remove,
 * and import food items from a file. It inherits from the ViewModel
 * base class.
 */
class FoodViewModel : public ViewModel
{
public:
    /**
     * @brief Construct a new FoodViewModel object
     *
     * @param file The filename to read food items from.
     */
    FoodViewModel(const std::string& file);

    /**
     * @brief View the food items.
     *
     * This method is used to display food items either by categories
     * or all food items.
     */
    void view() override;

    /**
     * @brief Add a new food item.
     *
     * This method is used to add a new food item to the foodItemMap.
     */
    void add() override;

    /**
     * @brief Modify an existing food item.
     *
     * This method is used to modify the details of an existing food item.
     */
    void modify() override;

    /**
     * @brief Remove a food item.
     *
     * This method is used to remove a food item from the foodItemMap.
     */
    void remove() override;

    /**
     * @brief Import food items from a file.
     *
     * This method is used to import food items from a specified CSV file.
     *
     * @param filename The name of the file to import food items from.
     */
    void importFromFile(const std::string& filename) override;

    /**
     * @brief Reload the food items from the CSV file.
     *
     * This method reloads the food items from the CSV file to refresh the foodItemMap.
     */
    void reload() override;

private:
    std::string filename; ///< The filename containing the food items.
    std::map<std::string, FoodItem> foodItemMap; ///< Map to store food items.

    /**
     * @brief Display the categories of a given food item.
     *
     * @param foodItem The food item whose categories will be displayed.
     */
    void displayCategoriesOfFoodItem(const FoodItem& foodItem) const;

    /**
     * @brief Display the details of a given food item.
     *
     * @param foodItem The food item whose details will be displayed.
     */
    void displayFoodItem(const FoodItem& foodItem) const;

    /**
     * @brief Display the list of food items.
     *
     * @param foodMap The map containing the food items to be displayed.
     */
    void displayFoodItems(const std::map<std::string, FoodItem>& foodMap) const;

    /**
     * @brief Display food items filtered by categories.
     */
    void displayFoodItemsByCategories();

    /**
     * @brief Display the categories of food items in a map.
     *
     * @param categoryVec The vector of categories to be displayed.
     */
    void displayCategoriesOfFoodItemMap(const std::vector<std::string>& categoryVec) const;

    /**
     * @brief Handle the selection of a category and filter food items accordingly.
     *
     * @param filteredFoodItems The map to store the filtered food items.
     */
    void handleCategorySelection(std::map<std::string, FoodItem>& filteredFoodItems);

    /**
     * @brief Handle the modification of a food item.
     *
     * @param foodItem The food item to be modified.
     */
    void handleFoodModification(FoodItem& foodItem);

    /**
     * @brief Handle the deletion of food items.
     *
     * @param filteredFoodItems The map of filtered food items to be displayed and deleted.
     */
    void handleFoodDeletion(std::map<std::string, FoodItem>& filteredFoodItems);

    /**
     * @brief Confirm and delete a food item from the food item map.
     *
     * @param name The name of the food item to delete.
     */
    void confirmAndDeleteFoodItem(const std::string& name);

    /**
     * @brief Modify the categories of a food item.
     *
     * @param foodItem The food item whose categories will be modified.
     */
    void modifyCategories(FoodItem& foodItem);
};

#endif // FOODVIEWMODEL_H
