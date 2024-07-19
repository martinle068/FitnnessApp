#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include "View.h"
#include "Profile.h"
#include "Goals.h"

/**
 * @brief The ProfileView class is responsible for managing the profile and goals settings.
 * It inherits from the View class and provides options for viewing and modifying profile information and goals.
 */
class ProfileView : public View
{
public:
    /**
     * @brief Constructs a new ProfileView object.
     *
     * @param profile Reference to the Profile object.
     * @param goals Reference to the Goals object.
     */
    ProfileView(Profile& profile, Goals& goals);

    /**
     * @brief Displays the profile view menu.
     */
    void display();

private:
    Profile& profile; ///< Reference to the Profile object.
    Goals& goals; ///< Reference to the Goals object.
    std::vector<MenuOption> menuOptions; ///< Vector to store menu options.

    /**
     * @brief Sets the profile information with optional inputs.
     */
    void setProfileInformation();

    /**
     * @brief Sets the goals with optional inputs.
     */
    void setGoals();

    /**
     * @brief Sets custom daily calories.
     */
    void setCustomCalories();

    /**
     * @brief Resets to calculated daily calories.
     */
    void resetToCalculatedCalories();

    /**
     * @brief Prompts the user to select a fitness goal.
     *
     * @param currentGoal The current fitness goal to display as default.
     * @return Goals::FitnessGoal The selected fitness goal or the current value if no input was given.
     */
    Goals::FitnessGoal getFitnessGoal(Goals::FitnessGoal currentGoal);

    /**
     * @brief Prompts the user to select a gender.
     *
     * @param gender The current gender to display as default.
     * @return Profile::Gender The selected gender or the current value if no input was given.
     */
    Profile::Gender getGender(Profile::Gender gender);

    /**
     * @brief Prompts the user to select an activity level.
     *
     * @param currentActivityLevel The current activity level to display as default.
     * @return Profile::ActivityLevel The selected activity level or the current value if no input was given.
     */
    Profile::ActivityLevel getActivityLevel(Profile::ActivityLevel currentActivityLevel);
};

#endif // PROFILEVIEW_H
