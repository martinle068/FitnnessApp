#ifndef GOALS_H
#define GOALS_H

#include "Profile.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief The Goals class represents a user's fitness goals and calculates daily caloric needs based on the profile.
 */
class Goals
{
public:
    /**
     * @brief Enumeration representing different fitness goals.
     */
    enum class FitnessGoal
    {
        WEIGHT_LOSS,
        MUSCLE_GAIN,
        MAINTENANCE
    };

    /**
     * @brief Constructs a Goals object with default values.
     */
    Goals();

    /**
     * @brief Sets the profile to be used for caloric calculations.
     *
     * @param profile A pointer to the Profile object.
     */
    void setProfile(const Profile* profile);

    /**
     * @brief Sets the fitness goals for the user.
     *
     * @param targetWeight The target weight in kilograms.
     * @param bodyFatPercentage The target body fat percentage.
     * @param fitnessGoal The fitness goal (weight loss, muscle gain, maintenance).
     */
    void setGoals(float targetWeight, float bodyFatPercentage, FitnessGoal fitnessGoal);

    /**
     * @brief Displays the current goals to the console.
     */
    void displayGoals() const;

    /**
     * @brief Sets custom daily caloric intake.
     *
     * @param calories The custom daily calories.
     */
    void setCustomCalories(float calories);

    /**
     * @brief Resets to calculated daily caloric intake based on profile and fitness goals.
     */
    void resetToCalculatedCalories();

    /**
     * @brief Gets the daily caloric needs based on either custom or calculated value.
     *
     * @return The daily caloric intake.
     */
    float getDailyCalories() const;

    /**
     * @brief Saves the goals information to a CSV file.
     *
     * @param filename The name of the file to save the goals information.
     */
    void saveToCSV(const std::string& filename) const;

    /**
     * @brief Loads the goals information from a CSV file.
     *
     * @param filename The name of the file to load the goals information from.
     * @return true if the file was successfully loaded, false otherwise.
     */
    bool loadFromCSV(const std::string& filename);

    /**
     * @brief Gets the current fitness goal.
     *
     * @return The current fitness goal.
     */
    FitnessGoal getFitnessGoal() const;

    /**
     * @brief Gets the current weight from the profile.
     *
     * @return The current weight.
     */
    float getWeight() const;

    /**
     * @brief Gets the target body fat percentage.
     *
     * @return The target body fat percentage.
     */
    float getBodyFatPercentage() const;

    /**
     * @brief Gets the target weight.
     *
     * @return The target weight.
     */
    float getTargetWeight() const;

    /**
     * @brief Gets the string representation of the current fitness goal.
     *
     * @return The string representation of the fitness goal.
     */
    std::string getFitnessGoalString() const;

private:
    float targetWeight; ///< The target weight in kilograms.
    float bodyFatPercentage; ///< The target body fat percentage.
    FitnessGoal fitnessGoal; ///< The fitness goal.
    float customCalories; ///< The custom daily caloric intake.
    bool useCustomCalories; ///< Flag indicating if custom calories are used.
    const Profile* profile; ///< Pointer to the Profile object.

    /**
     * @brief Calculates the daily caloric needs based on the profile and fitness goals.
     *
     * @return The calculated daily calories.
     */
    float calculateDailyCalories() const;

    /**
     * @brief Recalculates daily calories if custom calories are not used.
     */
    void recalculateDailyCalories();
};

#endif // GOALS_H
