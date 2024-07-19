#ifndef NUTRITION_PLAN_VIEW_H
#define NUTRITION_PLAN_VIEW_H

#include "NutritionPlanViewModel.h"
#include "View.h"

/**
 * @brief Class representing the view for managing nutrition plans.
 */
class NutritionPlanView : public View
{
public:
    /**
     * @brief Constructs a NutritionPlanView with the given ViewModel.
     *
     * @param vm The ViewModel to be used by this view.
     */
    NutritionPlanView(NutritionPlanViewModel& vm);

    /**
     * @brief Displays the Nutrition Plan menu and handles user interaction.
     */
    void display();

private:
    NutritionPlanViewModel& viewModel; ///< The ViewModel used by this view.
    std::vector<MenuOption> menuOptions; ///< Menu options for the Nutrition Plan view.

    /**
     * @brief Prompts the user for a filename and imports nutrition plans from the specified file.
     */
    void importFromFile();
};

#endif // NUTRITION_PLAN_VIEW_H
