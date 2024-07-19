#include "WorkoutPlan.h"
#include <sstream>
#include "Utils.h"

/**
 * @brief Constructs a new WorkoutPlan object.
 *
 * @param name The name of the workout plan.
 * @param type The type of the workout plan.
 * @param weeklyPlan A map containing the weekly plan with days as keys and a vector of ExerciseDetails as values.
 */
WorkoutPlan::WorkoutPlan(const std::string& name, PlanType type, const std::map<std::string, std::vector<ExerciseDetails>>& weeklyPlan)
    : name(name), type(type), weeklyPlan(weeklyPlan)
{
}

/**
 * @brief Converts the PlanType enum to a string representation.
 *
 * @param type The PlanType to convert.
 * @return A string representation of the PlanType.
 */
std::string WorkoutPlan::planTypeToString(PlanType type)
{
    switch (type)
    {
    case PlanType::STRENGTH:
        return "Strength";
    case PlanType::POWER:
        return "Power";
    case PlanType::HYPERTROPHY:
        return "Hypertrophy";
    case PlanType::CONDITIONING:
        return "Conditioning";
    case PlanType::PUSH:
        return "Push";
    case PlanType::PULL:
        return "Pull";
    case PlanType::LEGS:
        return "Legs";
    default:
        return "Unknown";
    }
}

/**
 * @brief Converts a string representation of a plan type to the corresponding PlanType enum.
 *
 * @param str The string representation of the plan type.
 * @return The corresponding PlanType enum.
 */
WorkoutPlan::PlanType WorkoutPlan::stringToPlanType(const std::string& str)
{
    std::string strLower = toLower(str);

    if (strLower == "strength")
        return PlanType::STRENGTH;
    if (strLower == "power")
        return PlanType::POWER;
    if (strLower == "hypertrophy")
        return PlanType::HYPERTROPHY;
    if (strLower == "conditioning")
        return PlanType::CONDITIONING;
    if (strLower == "push")
        return PlanType::PUSH;
    if (strLower == "pull")
        return PlanType::PULL;
    if (strLower == "legs")
        return PlanType::LEGS;
    return PlanType::STRENGTH; // Default
}

/**
 * @brief Writes the workout plan to a CSV file.
 *
 * @param file The ofstream object to write to.
 */
void WorkoutPlan::toCSV(std::ofstream& file) const
{
    file << name << "," << planTypeToString(type) << ",";

    for (const auto& day : DAYS_OF_WEEK)
    {
        auto it = weeklyPlan.find(day);
        if (it != weeklyPlan.end())
        {
            for (size_t i = 0; i < it->second.size(); ++i)
            {
                const auto& exercise = it->second[i];
                file << exercise.exerciseName << "=" << exercise.sets << "x" << exercise.reps;
                if (i < it->second.size() - 1)
                {
                    file << ";";
                }
            }

            file << ",";
        }
    }
    file << "\n";
}

/**
 * @brief Processes exercises for a given day and adds them to the weekly plan.
 *
 * @param day The day of the week.
 * @param dayExercises The exercises for the day in string format.
 * @param weeklyPlan The map to add the processed exercises to.
 */
void WorkoutPlan::processExercises(const std::string& day, const std::string& dayExercises, std::map<std::string, std::vector<ExerciseDetails>>& weeklyPlan)
{
    std::vector<ExerciseDetails> exercises;
    if (dayExercises.empty() || dayExercises == " ")
    {
        weeklyPlan[day] = exercises;
        return;
    }
    std::stringstream ess(dayExercises);
    std::string exerciseDetails;
    while (std::getline(ess, exerciseDetails, ';'))
    {
        if (exerciseDetails.empty()) continue; // Skip empty entries
        ExerciseDetails details;
        std::string exerciseName = exerciseDetails.substr(0, exerciseDetails.find('='));
        std::string setsReps = exerciseDetails.substr(exerciseDetails.find('=') + 1);
        details.exerciseName = exerciseName;
        details.sets = std::stoi(setsReps.substr(0, setsReps.find('x')));
        details.reps = std::stoi(setsReps.substr(setsReps.find('x') + 1));
        exercises.push_back(details);
    }
    weeklyPlan[day] = exercises;
}

/**
 * @brief Reads a workout plan from a CSV string stream.
 *
 * @param ss The stringstream to read from.
 * @return true if reading was successful, false otherwise.
 */
bool WorkoutPlan::fromCSV(std::stringstream& ss)
{
    std::string typeStr;
    if (std::getline(ss, name, ',') && std::getline(ss, typeStr, ','))
    {
        type = stringToPlanType(typeStr);
        weeklyPlan.clear();
        std::string dayExercises;

        for (const auto& day : DAYS_OF_WEEK)
        {
            if (std::getline(ss, dayExercises, ','))
            {
                processExercises(day, dayExercises, weeklyPlan);
            }
        }

        return true;
    }
    return false;
}
