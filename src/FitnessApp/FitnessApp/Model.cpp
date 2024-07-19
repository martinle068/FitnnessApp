#include "Model.h"
#include <iostream>



void calculateNutritionalValues(const std::map<std::string, FoodItem>& foodItemMap)
{
    std::string name;
    float quantity;

    std::cout << "Enter food name: ";
    std::getline(std::cin >> std::ws, name);

    getValidInput(quantity, "Enter quantity (grams): ");

    auto it = foodItemMap.find(name);
    if (it != foodItemMap.end())
    {
        it->second.displayNutritionalValues(quantity);
    }
    else
    {
        std::cout << "Food item not found.\n";
    }
}
