#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
#include <sstream>

/**
 * @brief The Exercise class represents an exercise with its attributes.
 */
class Exercise
{
public:
    /**
     * @brief Enum class for different types of exercises.
     */
    enum class ExerciseType
    {
        STRENGTH,                   
        HYPERTROPHY,                
        ENDURANCE,                  
        FLEXIBILITY,               
        BALANCE_AND_STABILITY,      
        POWER,                   
        FUNCTIONAL,                
        AEROBIC,                   
        ANAEROBIC,                 
        RECOVERY_AND_REGENERATION, 
        UNKNOWN                     
    };

    /**
     * @brief Default constructor for the Exercise class.
     */
    Exercise() = default;

    /**
     * @brief Parameterized constructor for the Exercise class.
     *
     * @param name Name of the exercise.
     * @param type Type of the exercise.
     * @param muscleGroup Targeted muscle group of the exercise.
     * @param repetitions Number of repetitions.
     * @param sets Number of sets.
     */
    Exercise(const std::string& name, ExerciseType type, const std::string& muscleGroup, int repetitions, int sets)
        : name(name), type(std::move(type)), muscleGroup(muscleGroup), repetitions(repetitions), sets(sets)
    {
    }

    std::string name;               /**< Name of the exercise */
    ExerciseType type = ExerciseType::STRENGTH; /**< Type of the exercise */
    std::string muscleGroup;        /**< Targeted muscle group of the exercise */
    int repetitions = 0;            /**< Number of repetitions */
    int sets = 0;                   /**< Number of sets */

    /**
     * @brief Parses an exercise from a CSV stream.
     *
     * @param str Input stream to read from.
     * @return True if parsing was successful, false otherwise.
     */
    bool fromCSV(std::istream& str);

    /**
     * @brief Serializes the exercise to a CSV stream.
     *
     * @param str Output stream to write to.
     */
    void toCSV(std::ostream& str) const;

    /**
     * @brief Converts a string to an ExerciseType.
     *
     * @param str String to convert.
     * @return Corresponding ExerciseType.
     */
    static ExerciseType stringToExerciseType(const std::string& str);

    /**
     * @brief Converts an ExerciseType to a string.
     *
     * @param type ExerciseType to convert.
     * @return Corresponding string representation.
     */
    static std::string exerciseTypeToString(ExerciseType type);
};

#endif // EXERCISE_H
