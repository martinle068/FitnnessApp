#include "Profile.h"

/**
 * @brief Constructs a new Profile object with default values.
 */
Profile::Profile()
    : name(""), age(0), gender(Gender::MALE), height(0), weight(0), activityLevel(ActivityLevel::SEDENTARY)
{
}

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
void Profile::setProfileInformation(const std::string& name, int age, Gender gender, float height, float weight, ActivityLevel activityLevel)
{
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->height = height;
    this->weight = weight;
    this->activityLevel = activityLevel;
}

/**
 * @brief Displays the profile information to the console.
 */
void Profile::displayProfileInformation() const
{
    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Gender: " << (gender == Gender::MALE ? "Male" : "Female") << "\n";
    std::cout << "Height: " << height << " cm\n";
    std::cout << "Weight: " << weight << " kg\n";
    std::cout << "Activity Level: ";
    switch (activityLevel)
    {
    case ActivityLevel::SEDENTARY:
        std::cout << "Sedentary\n";
        break;
    case ActivityLevel::LIGHTLY_ACTIVE:
        std::cout << "Lightly Active\n";
        break;
    case ActivityLevel::MODERATELY_ACTIVE:
        std::cout << "Moderately Active\n";
        break;
    case ActivityLevel::VERY_ACTIVE:
        std::cout << "Very Active\n";
        break;
    case ActivityLevel::EXTRA_ACTIVE:
        std::cout << "Extra Active\n";
        break;
    }
}

/**
 * @brief Calculates the daily caloric needs based on the profile information.
 *
 * @return float The daily caloric needs.
 */
float Profile::calculateDailyCalories() const
{
    float bmr;
    if (gender == Gender::MALE)
    {
        bmr = 10 * weight + 6.25f * height - 5 * age + 5;
    }
    else
    {
        bmr = 10 * weight + 6.25f * height - 5 * age - 161;
    }

    float activityFactor{};
    switch (activityLevel)
    {
    case ActivityLevel::SEDENTARY:
        activityFactor = 1.2f;
        break;
    case ActivityLevel::LIGHTLY_ACTIVE:
        activityFactor = 1.375f;
        break;
    case ActivityLevel::MODERATELY_ACTIVE:
        activityFactor = 1.55f;
        break;
    case ActivityLevel::VERY_ACTIVE:
        activityFactor = 1.725f;
        break;
    case ActivityLevel::EXTRA_ACTIVE:
        activityFactor = 1.9f;
        break;
    }

    return bmr * activityFactor;
}

/**
 * @brief Saves the profile information to a CSV file.
 *
 * @param filename The name of the file to save the profile information.
 */
void Profile::saveToCSV(const std::string& filename) const
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << name << ',' << age << ',' << (gender == Gender::MALE ? "Male" : "Female") << ','
            << height << ',' << weight << ','
            << static_cast<int>(activityLevel) << '\n';
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

/**
 * @brief Loads the profile information from a CSV file.
 *
 * @param filename The name of the file to load the profile information.
 * @return true If the file was successfully loaded.
 * @return false If the file could not be opened.
 */
bool Profile::loadFromCSV(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        if (std::getline(file, line))
        {
            std::istringstream ss(line);
            std::string token;

            std::getline(ss, name, ',');
            std::getline(ss, token, ',');
            age = std::stoi(token);
            std::getline(ss, token, ',');
            gender = (token == "Male" ? Gender::MALE : Gender::FEMALE);
            std::getline(ss, token, ',');
            height = std::stof(token);
            std::getline(ss, token, ',');
            weight = std::stof(token);
            std::getline(ss, token, ',');
            activityLevel = static_cast<ActivityLevel>(std::stoi(token));
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
 * @brief Gets the weight of the user.
 *
 * @return float The weight of the user.
 */
float Profile::getWeight() const
{
    return weight;
}

/**
 * @brief Gets the age of the user.
 *
 * @return int The age of the user.
 */
int Profile::getAge() const
{
    return age;
}

/**
 * @brief Gets the name of the user.
 *
 * @return std::string The name of the user.
 */
std::string Profile::getName() const
{
    return name;
}

/**
 * @brief Gets the gender of the user.
 *
 * @return Profile::Gender The gender of the user.
 */
Profile::Gender Profile::getGender() const
{
    return gender;
}

/**
 * @brief Gets the height of the user.
 *
 * @return float The height of the user in cm.
 */
float Profile::getHeight() const
{
    return height;
}

/**
 * @brief Gets the activity level of the user.
 *
 * @return Profile::ActivityLevel The activity level of the user.
 */
Profile::ActivityLevel Profile::getActivityLevel() const
{
    return activityLevel;
}

/**
 * @brief Converts the gender to a string representation.
 *
 * @return std::string The string representation of the gender.
 */
std::string Profile::getGenderString() const
{
    switch (gender)
    {
    case Gender::MALE:
        return "Male";
    case Gender::FEMALE:
        return "Female";
    default:
        return "Unknown";
    }
}

/**
 * @brief Converts the activity level to a string representation.
 *
 * @return std::string The string representation of the activity level.
 */
std::string Profile::getActivityLevelString() const
{
    switch (activityLevel)
    {
    case ActivityLevel::SEDENTARY:
        return "Sedentary";
    case ActivityLevel::LIGHTLY_ACTIVE:
        return "Lightly Active";
    case ActivityLevel::MODERATELY_ACTIVE:
        return "Moderately Active";
    case ActivityLevel::VERY_ACTIVE:
        return "Very Active";
    case ActivityLevel::EXTRA_ACTIVE:
        return "Extra Active";
    default:
        return "Unknown";
    }
}
