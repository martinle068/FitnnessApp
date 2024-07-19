#include "Exercise.h"

/**
 * @brief Parses an exercise from a CSV stream.
 *
 * @param str Input stream to read from.
 * @return True if parsing was successful, false otherwise.
 */
bool Exercise::fromCSV(std::istream& str)
{
    std::string line;
    if (std::getline(str, line))
    {
        std::istringstream iss(line);
        std::string repetitionsStr, setsStr, typeStr;
        if (std::getline(iss, name, ',') &&
            std::getline(iss, typeStr, ',') &&
            std::getline(iss, muscleGroup, ',') &&
            std::getline(iss, repetitionsStr, ',') &&
            std::getline(iss, setsStr, ','))
        {
            type = stringToExerciseType(typeStr);
            repetitions = std::stoi(repetitionsStr);
            sets = std::stoi(setsStr);
            return true;
        }
    }
    return false;
}

/**
 * @brief Serializes the exercise to a CSV stream.
 *
 * @param str Output stream to write to.
 */
void Exercise::toCSV(std::ostream& str) const
{
    str << name << ',' << exerciseTypeToString(type) << ',' << muscleGroup << ',' << repetitions << ',' << sets << '\n';
}

/**
 * @brief Converts a string to an ExerciseType.
 *
 * @param str String to convert.
 * @return Corresponding ExerciseType.
 */
Exercise::ExerciseType Exercise::stringToExerciseType(const std::string& str)
{
    if (str == "Strength") return ExerciseType::STRENGTH;
    if (str == "Hypertrophy") return ExerciseType::HYPERTROPHY;
    if (str == "Endurance") return ExerciseType::ENDURANCE;
    if (str == "Flexibility") return ExerciseType::FLEXIBILITY;
    if (str == "Balance and Stability") return ExerciseType::BALANCE_AND_STABILITY;
    if (str == "Power") return ExerciseType::POWER;
    if (str == "Functional") return ExerciseType::FUNCTIONAL;
    if (str == "Aerobic") return ExerciseType::AEROBIC;
    if (str == "Anaerobic") return ExerciseType::ANAEROBIC;
    if (str == "Recovery and Regeneration") return ExerciseType::RECOVERY_AND_REGENERATION;
    return ExerciseType::UNKNOWN;
}

/**
 * @brief Converts an ExerciseType to a string.
 *
 * @param type ExerciseType to convert.
 * @return Corresponding string representation.
 */
std::string Exercise::exerciseTypeToString(ExerciseType type)
{
    switch (type)
    {
    case ExerciseType::STRENGTH: return "Strength";
    case ExerciseType::HYPERTROPHY: return "Hypertrophy";
    case ExerciseType::ENDURANCE: return "Endurance";
    case ExerciseType::FLEXIBILITY: return "Flexibility";
    case ExerciseType::BALANCE_AND_STABILITY: return "Balance and Stability";
    case ExerciseType::POWER: return "Power";
    case ExerciseType::FUNCTIONAL: return "Functional";
    case ExerciseType::AEROBIC: return "Aerobic";
    case ExerciseType::ANAEROBIC: return "Anaerobic";
    case ExerciseType::RECOVERY_AND_REGENERATION: return "Recovery and Regeneration";
    default: return "Unknown";
    }
}
