#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <string>
#include <map>
#include <iostream>

/**
 * @brief Abstract base class for ViewModel, providing a common interface for managing items.
 */
class ViewModel
{
public:
    /**
     * @brief Pure virtual function to view items.
     */
    virtual void view() = 0;

    /**
     * @brief Pure virtual function to add a new item.
     */
    virtual void add() = 0;

    /**
     * @brief Pure virtual function to modify an existing item.
     */
    virtual void modify() = 0;

    /**
     * @brief Pure virtual function to remove an item.
     */
    virtual void remove() = 0;

    /**
     * @brief Pure virtual function to import items from a file.
     *
     * @param filename The name of the file to import items from.
     */
    virtual void importFromFile(const std::string& filename) = 0;

    /**
     * @brief Pure virtual function to reload the items.
     */
    virtual void reload() = 0;

    /**
     * @brief Prompts the user to confirm overwriting an existing item.
     *
     * @tparam T The type of the items in the map.
     * @param itemMap The map containing the items.
     * @param name The name of the item to be overwritten.
     * @return True if the item should be overwritten, false otherwise.
     */
    template<typename T>
    bool confirmOverwrite(std::map<std::string, T>& itemMap, const std::string& name)
    {
        if (itemMap.find(name) != itemMap.end())
        {
            std::string choice;
            do
            {
                std::cout << "Item '" << name << "' already exists. Do you want to overwrite it? (yes/no): ";
                std::getline(std::cin, choice);
            } while (choice != "yes" && choice != "no");

            if (choice != "yes")
            {
                std::cout << "Item not modified.\n";
                return false;
            }
        }
        return true;
    }
};

#endif // VIEWMODEL_H
