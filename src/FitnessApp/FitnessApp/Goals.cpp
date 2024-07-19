#include "Goals.h"

/**
 * @brief Default constructor for the Goals class.
 */
Goals::Goals()
    : targetWeight(0), bodyFatPercentage(0), fitnessGoal(FitnessGoal::MAINTENANCE), customCalories(0), useCustomCalories(false), profile(nullptr)
{
}

/**
 * @brief Sets the profile used for calculating daily calories.
 *
 * @param profile A pointer to the Profile object.
 */
void Goals::setProfile(const Profile* profile)
{
    this->profile = profile;
    recalculateDailyCalories();
}

/**
 * @brief Sets the goals for the user.
 *
 * @param targetWeight The target weight in kg.
 * @param bodyFatPercentage The target body fat percentage.
 * @param fitnessGoal The fitness goal (weight loss, muscle gain, maintenance).
 */
void Goals::setGoals(float targetWeight, float bodyFatPercentage, FitnessGoal fitnessGoal)
{
    this->targetWeight = targetWeight;
    this->bodyFatPercentage = bodyFatPercentage;
    this->fitnessGoal = fitnessGoal;
    useCustomCalories = false;
    recalculateDailyCalories();
}

/**
 * @brief Displays the goals information.
 */
void Goals::displayGoals() const
{
    std::cout << "Target Weight: " << targetWeight << " kg\n";
    std::cout << "Body Fat Percentage: " << bodyFatPercentage << " %\n";
    std::cout << "Fitness Goal: ";
    switch (fitnessGoal)
    {
    case FitnessGoal::WEIGHT_LOSS:
        std::cout << "Weight Loss\n";
        break;
    case FitnessGoal::MUSCLE_GAIN:
        std::cout << "Muscle Gain\n";
        break;
    case FitnessGoal::MAINTENANCE:
        std::cout << "Maintenance\n";
        break;
    }
    std::cout << "Daily Calories: " << getDailyCalories() << "\n";
}

/**
 * @brief Sets custom daily calories and saves it to a file.
 *
 * @param calories The custom daily calories.
 */
void Goals::setCustomCalories(float calories)
{
    customCalories = calories;
    useCustomCalories = true;
    saveToCSV("goals.csv");
}

/**
 * @brief Resets to calculated daily calories based on profile and fitness goals.
 */
void Goals::resetToCalculatedCalories()
{
    useCustomCalories = false;
    saveToCSV("goals.csv");
}

/**
 * @brief Gets the daily calories based on either custom or calculated value.
 *
 * @return float The daily calories.
 */
float Goals::getDailyCalories() const
{
    return useCustomCalories ? customCalories : calculateDailyCalories();
}

/**
 * @brief Calculates the daily caloric needs based on profile information and fitness goals.
 *
 * @return float The calculated daily calories.
 */
float Goals::calculateDailyCalories() const
{
    if (profile == nullptr)
    {
        return 2000; // Default value if profile is not set
    }

    float baseCalories = profile->calculateDailyCalories();

    switch (fitnessGoal)
    {
    case FitnessGoal::WEIGHT_LOSS:
        return baseCalories - 500;
    case FitnessGoal::MUSCLE_GAIN:
        return baseCalories + 500;
    case FitnessGoal::MAINTENANCE:
    default:
        return baseCalories;
    }
}

/**
 * @brief Recalculates daily calories if custom calories are not used.
 */
void Goals::recalculateDailyCalories()
{
    if (!useCustomCalories)
    {
        customCalories = calculateDailyCalories();
    }
}

/**
 * @brief Saves the goals information to a CSV file.
 *
 * @param filename The name of the file to save the goals information.
 */
void Goals::saveToCSV(const std::string& filename) const
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << targetWeight << ',' << bodyFatPercentage << ','
            << static_cast<int>(fitnessGoal) << ',' << customCalories << ',' << useCustomCalories << '\n';
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

/**
 * @brief Loads the goals information from a CSV file.
 *
 * @param filename The name of the file to load the goals information.
 * @return true If the file was successfully loaded.
 * @return false If the file could not be opened.
 */
bool Goals::loadFromCSV(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        if (std::getline(file, line))
        {
            std::istringstream ss(line);
            std::string token;

            std::getline(ss, token, ',');
            targetWeight = std::stof(token);
            std::getline(ss, token, ',');
            bodyFatPercentage = std::stof(token);
            std::getline(ss, token, ',');
            fitnessGoal = static_cast<FitnessGoal>(std::stoi(token));
            std::getline(ss, token, ',');
            customCalories = std::stof(token);
            std::getline(ss, token, ',');
            useCustomCalories = std::stoi(token);
        }
        file.close();
        return true;
    }
    else
    {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
        return false;
    }
}

/**
 * @brief Gets the fitness goal.
 *
 * @return FitnessGoal The fitness goal.
 */
Goals::FitnessGoal Goals::getFitnessGoal() const
{
    return fitnessGoal;
}

/**
 * @brief Gets the current weight from the profile.
 *
 * @return float The current weight.
 */
float Goals::getWeight() const
{
    return profile != nullptr ? profile->getWeight() : 0;
}

/**
 * @brief Gets the body fat percentage.
 *
 * @return float The body fat percentage.
 */
float Goals::getBodyFatPercentage() const
{
    return bodyFatPercentage;
}

/**
 * @brief Gets the target weight.
 *
 * @return float The target weight.
 */
float Goals::getTargetWeight() const
{
    return targetWeight;
}

/**
 * @brief Converts the fitness goal to a string representation.
 *
 * @return std::string The string representation of the fitness goal.
 */
std::string Goals::getFitnessGoalString() const
{
    switch (fitnessGoal)
    {
    case FitnessGoal::WEIGHT_LOSS:
        return "Weight Loss";
    case FitnessGoal::MUSCLE_GAIN:
        return "Muscle Gain";
    case FitnessGoal::MAINTENANCE:
    default:
        return "Maintenance";
    }
}
