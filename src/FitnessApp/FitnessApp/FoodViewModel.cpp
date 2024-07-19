#include "FoodViewModel.h"
#include "Utils.h"
#include <iostream>
#include <set>

/**
 * @brief Construct a new FoodViewModel::FoodViewModel object
 *
 * @param file The filename to read food items from
 */
FoodViewModel::FoodViewModel(const std::string& file) : filename(file)
{
    foodItemMap = readFromCSV<FoodItem>(filename);
}

/**
 * @brief Display the categories of a given food item
 *
 * @param foodItem The food item whose categories will be displayed
 */
void FoodViewModel::displayCategoriesOfFoodItem(const FoodItem& foodItem) const
{
    std::cout << "Categories: ";
    for (auto it = foodItem.categories.begin(); it != foodItem.categories.end(); ++it)
    {
        if (it != foodItem.categories.begin())
        {
            std::cout << "; ";
        }
        std::cout << *it;
    }
}

/**
 * @brief Display the details of a given food item
 *
 * @param foodItem The food item whose details will be displayed
 */
void FoodViewModel::displayFoodItem(const FoodItem& foodItem) const
{
    std::cout << "Name: " << foodItem.name << ", ";
    displayCategoriesOfFoodItem(foodItem);
    std::cout << ", Calories: " << foodItem.calories
        << " kcal, Protein: " << foodItem.protein << " g, Carbohydrates: "
        << foodItem.carbohydrates << " g, Fats: " << foodItem.fats << " g, Portion: " << foodItem.portion << " g\n";
}

/**
 * @brief Display the list of food items
 *
 * @param foodMap The map containing the food items to be displayed
 */
void FoodViewModel::displayFoodItems(const std::map<std::string, FoodItem>& foodMap) const
{
    if (foodMap.empty())
    {
        std::cout << "No food items to display.\n";
        return;
    }

    std::cout << "Food Item List:\n";
    printWindowSizedSeparator();
    std::size_t index = 1;

    for (const auto& pair : foodMap)
    {
        const auto& foodItem = pair.second;

        std::cout << index++ << ". ";
        displayFoodItem(foodItem);
        printWindowSizedSeparator();
    }
}

/**
 * @brief Get the unique categories from the food item map
 *
 * @param foodItemMap The map containing the food items
 * @return std::vector<std::string> A vector of unique categories
 */
std::vector<std::string> getFoodItemCategories(const std::map<std::string, FoodItem>& foodItemMap)
{
    std::set<std::string> categories;
    for (const auto& pair : foodItemMap)
    {
        categories.insert(pair.second.categories.begin(), pair.second.categories.end());
    }

    return std::vector<std::string>(categories.begin(), categories.end());
}

/**
 * @brief Display the categories of food items
 *
 * @param categories The vector of categories to be displayed
 */
void FoodViewModel::displayCategoriesOfFoodItemMap(const std::vector<std::string>& categories) const
{
    for (size_t i = 0; i < categories.size(); ++i)
    {
        std::cout << i + 1 << ". " << categories[i] << "\n";
    }
}

/**
 * @brief Display food items filtered by categories
 */
void FoodViewModel::displayFoodItemsByCategories()
{
    std::map<std::string, FoodItem> filteredFoodItems;
    handleCategorySelection(filteredFoodItems);
    displayFoodItems(filteredFoodItems);
}

/**
 * @brief Display the available food items based on user choice (all or by category)
 */
void FoodViewModel::view()
{
    std::cout << "Do you want to view all food items or by category?\n";
    std::cout << "1. View all\n";
    std::cout << "2. View by category\n";

    int choice;
    getValidInput(choice, "Enter choice: ", 1, 2);

    if (choice == 1)
    {
        displayFoodItems(foodItemMap);
    }
    else if (choice == 2)
    {
        displayFoodItemsByCategories();
    }
    else
    {
        std::cout << "Invalid choice.\n";
    }
}

/**
 * @brief Add a new food item to the food item map
 */
void FoodViewModel::add()
{
    std::string name;
    std::set<std::string> categories;

    std::cout << "Enter food name: ";
    std::getline(std::cin >> std::ws, name);

    // Check if the food item already exists and confirm overwrite if it does
    if (!confirmOverwrite(foodItemMap, name))
    {
        return;
    }

    FoodItem foodItem;

    foodItem.name = name;
    modifyCategories(foodItem);

    getValidInput(foodItem.calories, "Enter calories per 100 grams: ");
    getValidInput(foodItem.protein, "Enter protein per 100 grams: ");
    getValidInput(foodItem.carbohydrates, "Enter carbohydrates per 100 grams: ");
    getValidInput(foodItem.fats, "Enter fats per 100 grams: ");
    getOptionalInput(foodItem.portion, "Enter portion size in grams (or press enter to skip): ");

    foodItemMap[name] = foodItem;
    writeToCSV(filename, foodItem);
}

/**
 * @brief Modify the categories of a food item
 *
 * @param foodItem The food item whose categories will be modified
 */
void FoodViewModel::modifyCategories(FoodItem& foodItem)
{
    while (true)
    {
        std::string categoryChoice;
        std::cout << "Current ";
        displayCategoriesOfFoodItem(foodItem);
        std::cout << "\nOptions:\n1. Add a category\n2. Delete a category\n3. Done\n";

        std::cout << "Enter choice: ";
        std::getline(std::cin, categoryChoice);

        if (categoryChoice == "1")
        {
            std::string newCategory;
            std::cout << "Enter new category: ";
            std::getline(std::cin >> std::ws, newCategory);
            foodItem.categories.insert(toLower(newCategory));
        }
        else if (categoryChoice == "2")
        {
            int deleteChoice;
            std::vector<std::string> categoryList(foodItem.categories.begin(), foodItem.categories.end());

            getValidInput(deleteChoice, "Enter the number of the category to delete: ", 1, static_cast<int>(categoryList.size()));
            foodItem.categories.erase(categoryList[deleteChoice - 1]);
        }
        else if (categoryChoice == "3")
        {
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }
}

/**
 * @brief Handle the modification of a food item
 *
 * @param foodItem The food item to be modified
 */
void FoodViewModel::handleFoodModification(FoodItem& foodItem)
{
    std::string newName;
    std::cout << "Enter new food name (or press enter to keep current): ";
    std::getline(std::cin, newName);
    if (!newName.empty())
    {
        foodItem.name = newName;
    }

    modifyCategories(foodItem);

    getOptionalInput(foodItem.calories, "Enter new calories per 100 grams (or press enter to keep current): ");
    getOptionalInput(foodItem.protein, "Enter new protein per 100 grams (or press enter to keep current): ");
    getOptionalInput(foodItem.carbohydrates, "Enter new carbohydrates per 100 grams (or press enter to keep current): ");
    getOptionalInput(foodItem.fats, "Enter new fats per 100 grams (or press enter to keep current): ");
    getOptionalInput(foodItem.portion, "Enter new portion size in grams (or press enter to keep current): ");
}

/**
 * @brief Modify an existing food item
 */
void FoodViewModel::modify()
{
    if (foodItemMap.empty())
    {
        std::cout << "No food items to modify.\n";
        return;
    }

    std::cout << "Do you want to display all food items or by category?\n";
    std::cout << "1. Display all\n";
    std::cout << "2. Display by category\n";

    int choice;
    getValidInput(choice, "Enter choice: ", 1, 2);

    std::map<std::string, FoodItem> filteredFoodItems;
    if (choice == 1)
    {
        filteredFoodItems = foodItemMap;
    }
    else if (choice == 2)
    {
        handleCategorySelection(filteredFoodItems);
    }
    else
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    std::cout << "Choose a food item to modify:\n";

    std::vector<std::string> names;
    for (const auto& pair : filteredFoodItems)
    {
        names.push_back(pair.first);
    }

    displayFoodItems(filteredFoodItems);
    std::size_t cancelIndex = filteredFoodItems.size() + 1;
    std::cout << cancelIndex << ". Cancel\n";

    getValidInput(choice, "Enter the number of the food item to modify: ", 1, static_cast<int>(cancelIndex));

    if (choice == cancelIndex)
    {
        std::cout << "Operation cancelled.\n";
        return;
    }

    handleFoodModification(foodItemMap[names[choice - 1]]);
    overwriteCSV(filename, foodItemMap);
    std::cout << "Food modified.\n";
}

/**
 * @brief Confirm and delete a food item from the food item map
 *
 * @param name The name of the food item to delete
 */
void FoodViewModel::confirmAndDeleteFoodItem(const std::string& name)
{
    const auto& foodItem = foodItemMap[name];
    std::string confirm;
    do
    {
        std::cout << "Are you sure you want to delete " << foodItem.name << " (Categories: ";
        displayCategoriesOfFoodItem(foodItem);
        std::cout << ", Calories: " << foodItem.calories
            << ", Protein: " << foodItem.protein << " g, Carbohydrates: " << foodItem.carbohydrates
            << " g, Fats: " << foodItem.fats << " g, Portion: " << foodItem.portion << " g)? (yes/no): ";
        std::getline(std::cin >> std::ws, confirm);
    } while (confirm != "yes" && confirm != "no");

    if (confirm == "yes")
    {
        foodItemMap.erase(name);
        overwriteCSV(filename, foodItemMap);
        std::cout << "Food item deleted.\n";
    }
    else
    {
        std::cout << "Food item not deleted.\n";
    }
}

/**
 * @brief Handle the selection of a category and filter food items accordingly
 *
 * @param filteredFoodItems The map to store the filtered food items
 */
void FoodViewModel::handleCategorySelection(std::map<std::string, FoodItem>& filteredFoodItems)
{
    std::vector<std::string> categories = getFoodItemCategories(foodItemMap);
    displayCategoriesOfFoodItemMap(categories);

    int categoryChoice;
    getValidInput(categoryChoice, "Select a category by number: ", 1, static_cast<int>(categories.size()));

    std::string selectedCategory = categories[categoryChoice - 1];
    for (const auto& pair : foodItemMap)
    {
        if (pair.second.categories.find(selectedCategory) != pair.second.categories.end())
        {
            filteredFoodItems[pair.first] = pair.second;
        }
    }
}

/**
 * @brief Handle the deletion of a food item
 * 
 * @param filteredFoodItems The map to store the filtered food items
 */
void FoodViewModel::handleFoodDeletion(std::map<std::string, FoodItem>& filteredFoodItems)
{
    displayFoodItems(filteredFoodItems);

    int cancelIndex = static_cast<int>(filteredFoodItems.size()) + 1;

    std::cout << cancelIndex << ". Cancel\n";

    int choice;
    getValidInput(choice, "Enter the number of the food item to delete: ", 1, cancelIndex);

    if (choice == cancelIndex)
    {
        std::cout << "Operation cancelled.\n";
        return;
    }

    std::vector<std::string> names;
    for (const auto& pair : filteredFoodItems)
    {
        names.push_back(pair.first);
    }
    confirmAndDeleteFoodItem(names[choice - 1]);
}

/**
 * @brief Remove a food item from the food item map
 */
void FoodViewModel::remove()
{
    if (foodItemMap.empty())
    {
        std::cout << "No food items to delete.\n";
        return;
    }

    std::cout << "Do you want to display all food items or by category?\n";
    std::cout << "1. Display all\n";
    std::cout << "2. Display by category\n";

    int choice;
    getValidInput(choice, "Enter choice: ", 1, 2);

    std::map<std::string, FoodItem> filteredFoodItems;
    if (choice == 1)
    {
        filteredFoodItems = foodItemMap;
    }
    else if (choice == 2)
    {
        handleCategorySelection(filteredFoodItems);
    }
    else
    {
        std::cout << "Invalid choice.\n";
        return;
    }

    handleFoodDeletion(filteredFoodItems);
}

/**
 * @brief Import food items from a CSV file
 *
 * @param filename The name of the CSV file to import food items from
 */
void FoodViewModel::importFromFile(const std::string& filename)
{
    auto items = readFromCSV<FoodItem>(filename);
    for (const auto& item : items)
    {
        auto it = foodItemMap.find(item.first);
        if (it != foodItemMap.end())
        {
            clearScreen();
            const auto& currentFoodItem = it->second;
            const auto& newFoodItem = item.second;

            std::cout << "Food item '" << item.first << "' already exists.\n";
            std::cout << "Current food item:\n";
            std::cout << "  Name: " << currentFoodItem.name << "\n";
            std::cout << "  Categories: ";
            displayCategoriesOfFoodItem(currentFoodItem);
            std::cout << "\n  Calories: " << currentFoodItem.calories << "\n";
            std::cout << "  Protein: " << currentFoodItem.protein << "\n";
            std::cout << "  Carbohydrates: " << currentFoodItem.carbohydrates << "\n";
            std::cout << "  Fats: " << currentFoodItem.fats << "\n";
            std::cout << "  Portion: " << currentFoodItem.portion << " g\n";
            std::cout << "New food item:\n";
            std::cout << "  Name: " << newFoodItem.name << "\n";
            std::cout << "  Categories: ";
            displayCategoriesOfFoodItem(newFoodItem);
            std::cout << "\n  Calories: " << newFoodItem.calories << "\n";
            std::cout << "  Protein: " << newFoodItem.protein << "\n";
            std::cout << "  Carbohydrates: " << newFoodItem.carbohydrates << "\n";
            std::cout << "  Fats: " << newFoodItem.fats << "\n";
            std::cout << "  Portion: " << newFoodItem.portion << " g\n";

            std::string choice;
            do
            {
                std::cout << "Do you want to overwrite the current food item with the new one? (yes/no): ";
                std::getline(std::cin >> std::ws, choice);
            } while (choice != "yes" && choice != "no");

            if (choice == "yes")
            {
                foodItemMap[item.first] = newFoodItem;
            }
        }
        else
        {
            foodItemMap[item.first] = item.second;
        }
    }
    overwriteCSV("food_items.csv", foodItemMap);
}

/**
 * @brief Reload the food items from the CSV file
 */
void FoodViewModel::reload()
{
    foodItemMap = readFromCSV<FoodItem>(filename);
}
