#include "ProfileView.h"
#include "Utils.h"

/**
 * @brief Prompts the user for optional string input.
 *
 * @param prompt The message to display to the user.
 * @param currentValue The current value to display as default.
 * @return std::string The user's input or the current value if no input was given.
 */
std::string getOptionalStringInput(const std::string& prompt, const std::string& currentValue)
{
    std::string input;
    std::cout << prompt << " (" << currentValue << "): ";
    std::getline(std::cin, input);
    return input.empty() ? currentValue : input;
}

/**
 * @brief Prompts the user for optional integer input.
 *
 * @param prompt The message to display to the user.
 * @param currentValue The current value to display as default.
 * @return int The user's input or the current value if no input was given.
 */
int getOptionalIntInput(const std::string& prompt, int currentValue)
{
    std::string input;
    int intValue;
    std::cout << prompt << " (" << currentValue << "): ";
    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty())
        {
            return currentValue;
        }
        if (stringToInt(input, intValue) && intValue >= 0)
        {
            return intValue;
        }
        std::cout << "Invalid input. " << prompt << " (" << currentValue << "): ";
    }
}

/**
 * @brief Prompts the user for optional float input.
 *
 * @param prompt The message to display to the user.
 * @param currentValue The current value to display as default.
 * @return float The user's input or the current value if no input was given.
 */
float getOptionalFloatInput(const std::string& prompt, float currentValue)
{
    std::string input;
    float floatValue;
    std::cout << prompt << " (" << currentValue << "): ";
    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty())
        {
            return currentValue;
        }
        if (stringToFloat(input, floatValue) && floatValue >= 0)
        {
            return floatValue;
        }
        std::cout << "Invalid input. " << prompt << " (" << currentValue << "): ";
    }
}

/**
 * @brief Constructs a new ProfileView object.
 *
 * @param profile Reference to the Profile object.
 * @param goals Reference to the Goals object.
 */
ProfileView::ProfileView(Profile& profile, Goals& goals) : profile(profile), goals(goals)
{
    menuOptions = {
        {"View Profile", [this]() { printLabel("Viewing Profile"); this->profile.displayProfileInformation(); this->goals.displayGoals(); }},
        {"Set Profile Information", [this]() { printLabel("Setting Profile Information"); setProfileInformation(); }},
        {"Set Goals", [this]() { printLabel("Setting Goals"); setGoals(); }},
        {"Set Custom Calories", [this]() { printLabel("Setting Custom Calories"); setCustomCalories(); }},
        {"Reset to Calculated Calories", [this]() { printLabel("Resetting to Calculated Calories"); resetToCalculatedCalories(); }},
        {"Back", [this]() { return; }}
    };

    // Load profile information from file
    if (profile.loadFromCSV("profile.csv"))
    {
        goals.setProfile(&profile);
    }

    // Load goals information from file
    goals.loadFromCSV("goals.csv");
}

/**
 * @brief Displays the profile view menu.
 */
void ProfileView::display()
{
    displayAndHandleSubMenu("Profile", menuOptions, true);
}

/**
 * @brief Prompts the user to select an activity level.
 *
 * @param currentActivityLevel The current activity level to display as default.
 * @return Profile::ActivityLevel The selected activity level or the current value if no input was given.
 */
Profile::ActivityLevel ProfileView::getActivityLevel(Profile::ActivityLevel currentActivityLevel)
{
    int activityChoice;
    std::string input;

    std::cout << "Select activity level:\n";
    std::cout << "1. Sedentary: little or no exercise\n";
    std::cout << "2. Lightly Active: exercise 1-3 times/week\n";
    std::cout << "3. Moderately Active: daily exercise or intense exercise 4-5 times/week\n";
    std::cout << "4. Very Active: intense exercise 6-7 times/week\n";
    std::cout << "5. Extra Active: physical job or daily intense exercise\n";
    std::cout << "Enter choice (" << profile.getActivityLevelString() << "): ";

    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty())
        {
            return currentActivityLevel;
        }

        if (stringToInt(input, activityChoice) && activityChoice >= 1 && activityChoice <= 5)
        {
            switch (activityChoice)
            {
            case 1:
                return Profile::ActivityLevel::SEDENTARY;
            case 2:
                return Profile::ActivityLevel::LIGHTLY_ACTIVE;
            case 3:
                return Profile::ActivityLevel::MODERATELY_ACTIVE;
            case 4:
                return Profile::ActivityLevel::VERY_ACTIVE;
            case 5:
                return Profile::ActivityLevel::EXTRA_ACTIVE;
            default:
                std::cout << "Invalid choice, setting to Sedentary.\n";
                return Profile::ActivityLevel::SEDENTARY;
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter a number between 1 and 5, or press Enter to keep current activity level: ";
        }
    }
}

/**
 * @brief Prompts the user to select a gender.
 *
 * @param gender The current gender to display as default.
 * @return Profile::Gender The selected gender or the current value if no input was given.
 */
Profile::Gender ProfileView::getGender(Profile::Gender gender)
{
    std::string input;
    int genderChoice;

    std::cout << "Select gender (" << (gender == Profile::Gender::MALE ? "Male" : "Female") << "):\n";
    std::cout << "1. Male\n";
    std::cout << "2. Female\n";
    std::cout << "Enter choice (" << profile.getGenderString() << "): ";
    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty())
        {
            break;
        }

        if (stringToInt(input, genderChoice) && (genderChoice == 1 || genderChoice == 2))
        {
            gender = (genderChoice == 1) ? Profile::Gender::MALE : Profile::Gender::FEMALE;
            break;
        }
        else
        {
            std::cout << "Invalid choice, please enter 1 or 2.\n";
        }
    }

    return gender;
}

/**
 * @brief Sets the profile information with optional inputs.
 */
void ProfileView::setProfileInformation()
{
    std::cout << "Enter new value (or press enter to keep current value)\n";

    std::string name = getOptionalStringInput("Enter name", profile.getName());
    int age = getOptionalIntInput("Enter age", profile.getAge());
    Profile::Gender gender = getGender(profile.getGender());
    float height = getOptionalFloatInput("Enter height (cm)", profile.getHeight());
    float weight = getOptionalFloatInput("Enter weight (kg)", profile.getWeight());
    Profile::ActivityLevel activityLevel = getActivityLevel(profile.getActivityLevel());

    profile.setProfileInformation(name, age, gender, height, weight, activityLevel);
    profile.saveToCSV("profile.csv");
    goals.setProfile(&profile);
    goals.saveToCSV("goals.csv");
}

/**
 * @brief Prints the fitness goal options.
 *
 * @return int The number of options available.
 */
int printFitnessGoalOptions()
{
    std::cout << "Select fitness goal:\n";
    std::cout << "1. Weight Loss\n";
    std::cout << "2. Muscle Gain\n";
    std::cout << "3. Maintenance\n";

    return 3;
}

/**
 * @brief Prompts the user to select a fitness goal.
 *
 * @param currentGoal The current fitness goal to display as default.
 * @return Goals::FitnessGoal The selected fitness goal or the current value if no input was given.
 */
Goals::FitnessGoal ProfileView::getFitnessGoal(Goals::FitnessGoal currentGoal)
{
    int goalChoice;
    std::string input;

    std::cout << "Select fitness goal:\n";
    std::cout << "1. Weight Loss\n";
    std::cout << "2. Muscle Gain\n";
    std::cout << "3. Maintenance\n";
    std::cout << "Enter choice (" << goals.getFitnessGoalString() << "): ";

    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty())
        {
            return currentGoal;
        }

        if (stringToInt(input, goalChoice) && goalChoice >= 1 && goalChoice <= 3)
        {
            switch (goalChoice)
            {
            case 1:
                return Goals::FitnessGoal::WEIGHT_LOSS;
            case 2:
                return Goals::FitnessGoal::MUSCLE_GAIN;
            case 3:
                return Goals::FitnessGoal::MAINTENANCE;
            default:
                std::cout << "Invalid choice, setting to Weight Loss.\n";
                return Goals::FitnessGoal::WEIGHT_LOSS;
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter a number between 1 and 3, or press Enter to keep current goal: ";
        }
    }
}

/**
 * @brief Sets the goals with optional inputs.
 */
void ProfileView::setGoals()
{
    std::cout << "Enter new value (or press enter to keep current value)\n";
    float targetWeight = getOptionalFloatInput("Enter target weight (kg)", goals.getTargetWeight());
    float bodyFatPercentage = getOptionalFloatInput("Enter body fat percentage", goals.getBodyFatPercentage());
    Goals::FitnessGoal fitnessGoal = getFitnessGoal(goals.getFitnessGoal());

    goals.setGoals(targetWeight, bodyFatPercentage, fitnessGoal);
    goals.saveToCSV("goals.csv");
}

/**
 * @brief Sets custom daily calories.
 */
void ProfileView::setCustomCalories()
{
    float customCalories;
    getValidInput(customCalories, "Enter custom daily calories: ");
    goals.setCustomCalories(customCalories);
    goals.saveToCSV("goals.csv");
}

/**
 * @brief Resets to calculated daily calories.
 */
void ProfileView::resetToCalculatedCalories()
{
    goals.resetToCalculatedCalories();
    goals.saveToCSV("goals.csv");
}
