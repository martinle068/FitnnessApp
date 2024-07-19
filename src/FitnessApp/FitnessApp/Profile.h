#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief The Profile class represents a user's profile with personal information and activity level.
 */
class Profile
{
public:
    /**
     * @brief Enumeration for gender.
     */
    enum class Gender
    {
        MALE,
        FEMALE
    };

    /**
     * @brief Enumeration for activity level.
     */
    enum class ActivityLevel
    {
        SEDENTARY,
        LIGHTLY_ACTIVE,
        MODERATELY_ACTIVE,
        VERY_ACTIVE,
        EXTRA_ACTIVE
    };

    /**
     * @brief Constructs a new Profile object with default values.
     */
    Profile();

    /**
     * @brief Sets the profile information with provided values.
     *
     * @param name The name of the user.
     * @param age The age of the user.
     * @param gender The gender of the user.
     * @param height The height of the user in cm.
     * @param weight The weight of the user in kg.
     * @param activityLevel The activity level of the user.
     */
    void setProfileInformation(const std::string& name, int age, Gender gender, float height, float weight, ActivityLevel activityLevel);

    /**
     * @brief Displays the profile information to the console.
     */
    void displayProfileInformation() const;

    /**
     * @brief Calculates the daily caloric needs based on the profile information.
     *
     * @return float The daily caloric needs.
     */
    float calculateDailyCalories() const;

    /**
     * @brief Saves the profile information to a CSV file.
     *
     * @param filename The name of the file to save the profile information.
     */
    void saveToCSV(const std::string& filename) const;

    /**
     * @brief Loads the profile information from a CSV file.
     *
     * @param filename The name of the file to load the profile information.
     * @return true If the file was successfully loaded.
     * @return false If the file could not be opened.
     */
    bool loadFromCSV(const std::string& filename);

    /**
     * @brief Gets the weight of the user.
     *
     * @return float The weight of the user.
     */
    float getWeight() const;

    /**
     * @brief Gets the name of the user.
     *
     * @return std::string The name of the user.
     */
    std::string getName() const;

    /**
     * @brief Gets the age of the user.
     *
     * @return int The age of the user.
     */
    int getAge() const;

    /**
     * @brief Gets the gender of the user.
     *
     * @return Gender The gender of the user.
     */
    Gender getGender() const;

    /**
     * @brief Gets the height of the user.
     *
     * @return float The height of the user in cm.
     */
    float getHeight() const;

    /**
     * @brief Gets the activity level of the user.
     *
     * @return ActivityLevel The activity level of the user.
     */
    ActivityLevel getActivityLevel() const;

    /**
     * @brief Converts the gender to a string representation.
     *
     * @return std::string The string representation of the gender.
     */
    std::string getGenderString() const;

    /**
     * @brief Converts the activity level to a string representation.
     *
     * @return std::string The string representation of the activity level.
     */
    std::string getActivityLevelString() const;

private:
    std::string name; ///< The name of the user.
    int age; ///< The age of the user.
    Gender gender; ///< The gender of the user.
    float height; ///< The height of the user in cm.
    float weight; ///< The weight of the user in kg.
    ActivityLevel activityLevel; ///< The activity level of the user.
};

#endif // PROFILE_H
