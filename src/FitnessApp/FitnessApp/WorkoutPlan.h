#ifndef WORKOUT_PLAN_H
#define WORKOUT_PLAN_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

/**
 * @class WorkoutPlan
 * @brief Represents a workout plan consisting of a name, type, and weekly schedule of exercises.
 */
class WorkoutPlan
{
public:
    /**
     * @enum PlanType
     * @brief Enum representing different types of workout plans.
     */
    enum class PlanType
    {
        STRENGTH,       ///< Strength training
        POWER,          ///< Power training
        HYPERTROPHY,    ///< Hypertrophy training
        CONDITIONING,   ///< Conditioning training
        PUSH,           ///< Push workouts
        PULL,           ///< Pull workouts
        LEGS,           ///< Leg workouts
        // Add more types as needed
    };

    /**
     * @struct ExerciseDetails
     * @brief Represents details of an exercise including name, sets, and reps.
     */
    struct ExerciseDetails
    {
        std::string exerciseName; ///< Name of the exercise
        int sets;                 ///< Number of sets
        int reps;                 ///< Number of reps

        /**
         * @brief Overload the >> operator for ExerciseDetails to read from a stream.
         * @param is The input stream
         * @param ed The ExerciseDetails object to read into
         * @return The input stream
         */
        friend std::istream& operator>>(std::istream& is, ExerciseDetails& ed)
        {
            std::string token;
            std::getline(is, token, '-');
            ed.exerciseName = token;
            std::getline(is, token, 'x');
            ed.sets = std::stoi(token);
            std::getline(is, token);
            ed.reps = std::stoi(token);
            return is;
        }
    };

    /**
     * @brief Default constructor.
     */
    WorkoutPlan() = default;

    /**
     * @brief Constructs a new WorkoutPlan object.
     * @param name The name of the workout plan
     * @param type The type of the workout plan
     * @param weeklyPlan A map containing the weekly plan with days as keys and a vector of ExerciseDetails as values
     */
    WorkoutPlan(const std::string& name, PlanType type, const std::map<std::string, std::vector<ExerciseDetails>>& weeklyPlan);

    std::string name; ///< The name of the workout plan
    PlanType type;    ///< The type of the workout plan
    std::map<std::string, std::vector<ExerciseDetails>> weeklyPlan; ///< Key: Day of the week, Value: List of exercises

    /**
     * @brief Converts the PlanType enum to a string representation.
     * @param type The PlanType to convert
     * @return A string representation of the PlanType
     */
    static std::string planTypeToString(PlanType type);

    /**
     * @brief Converts a string representation of a plan type to the corresponding PlanType enum.
     * @param str The string representation of the plan type
     * @return The corresponding PlanType enum
     */
    static PlanType stringToPlanType(const std::string& str);

    /**
     * @brief Writes the workout plan to a CSV file.
     * @param file The ofstream object to write to
     */
    void toCSV(std::ofstream& file) const;

    /**
     * @brief Reads a workout plan from a CSV string stream.
     * @param ss The stringstream to read from
     * @return true if reading was successful, false otherwise
     */
    bool fromCSV(std::stringstream& ss);

private:
    /**
     * @brief Processes exercises for a given day and adds them to the weekly plan.
     * @param day The day of the week
     * @param dayExercises The exercises for the day in string format
     * @param weeklyPlan The map to add the processed exercises to
     */
    void processExercises(const std::string& day, const std::string& dayExercises, std::map<std::string, std::vector<ExerciseDetails>>& weeklyPlan);
};

#endif // WORKOUT_PLAN_H
