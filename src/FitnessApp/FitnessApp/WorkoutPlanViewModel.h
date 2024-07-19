#ifndef WORKOUTPLANVIEWMODEL_H
#define WORKOUTPLANVIEWMODEL_H

#include <string>
#include <map>
#include <vector>
#include "WorkoutPlan.h"
#include "Exercise.h"
#include "ViewModel.h"

class WorkoutPlanViewModel : public ViewModel
{
public:
    /**
     * @brief Construct a new WorkoutPlanViewModel object
     *
     * @param file The filename to read workout plans from
     */
    WorkoutPlanViewModel(const std::string& file);

    /**
     * @brief Display the available workout plans
     */
    void view() override;

    /**
     * @brief Add a new workout plan
     */
    void add() override;

    /**
     * @brief Modify an existing workout plan
     */
    void modify() override;

    /**
     * @brief Remove an existing workout plan
     */
    void remove() override;

    /**
     * @brief Import workout plans from a CSV file
     *
     * @param filename The name of the CSV file to import workout plans from
     */
    void importFromFile(const std::string& filename) override;

    /**
     * @brief Reload workout plans and exercises from CSV files
     */
    void reload() override;

private:
    std::string filename;  ///< The filename to read/write workout plans
    std::map<std::string, WorkoutPlan> workoutPlanMap;  ///< The map of workout plans
    std::map<std::string, Exercise> exerciseMap;  ///< The map of exercises

    /**
     * @brief Display all workout plans
     */
    void displayAllWorkoutPlans() const;

    /**
     * @brief Display workout plans filtered by type
     */
    void displayWorkoutPlansByType() const;

    /**
     * @brief Display the details of a specific workout plan
     *
     * @param plan The workout plan to display
     */
    void displayWorkoutPlan(const WorkoutPlan& plan) const;

    /**
     * @brief Edit exercises for a specific day in the workout plan
     *
     * @param day The day of the week
     * @param exercises The list of exercises for the day
     * @param exerciseMap The map of all available exercises
     */
    void editDailyExercises(const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap);

    /**
     * @brief Display the current exercises for a specific day
     *
     * @param day The day of the week
     * @param exercises The list of exercises for the day
     */
    void displayCurrentExercisesForDay(const std::string& day, const std::vector<WorkoutPlan::ExerciseDetails>& exercises) const;

    /**
     * @brief Display exercises filtered by muscle group
     *
     * @param exerciseMap The map of all available exercises
     * @param muscleGroup The muscle group to filter by
     * @param filteredExercises The vector to store the filtered exercises
     */
    void displayExercisesByMuscleGroup(const std::map<std::string, Exercise>& exerciseMap, const std::string& muscleGroup, std::vector<Exercise>& filteredExercises);

    /**
     * @brief Add an exercise to a specific day in the workout plan
     *
     * @param day The day of the week
     * @param exercises The list of exercises for the day
     * @param exerciseMap The map of all available exercises
     */
    void addExerciseToDay(const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap);

    /**
     * @brief Display options for selecting a muscle group
     *
     * @param exerciseMap The map of all available exercises
     * @param day The day of the week
     * @param exercises The list of exercises for the day
     */
    void displayMuscleGroupOptions(std::map<std::string, Exercise>& exerciseMap, const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises);

    /**
     * @brief Handle the choice of muscle group selection
     *
     * @param choice The selected option
     * @param muscleGroupsVec The list of muscle groups
     * @param day The day of the week
     * @param exercises The list of exercises for the day
     * @param exerciseMap The map of all available exercises
     */
    void handleMuscleGroupChoice(int choice, const std::vector<std::string>& muscleGroupsVec, const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap);

    /**
     * @brief Add a custom exercise to the list of exercises for a specific day
     *
     * @param day The day of the week
     * @param exercises The list of exercises for the day
     * @param exerciseMap The map of all available exercises
     */
    void addCustomExercise(const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap);

    /**
     * @brief Add an existing exercise to the list of exercises for a specific day
     *
     * @param muscleGroup The muscle group of the exercise
     * @param exercises The list of exercises for the day
     * @param exerciseMap The map of all available exercises
     */
    void addExistingExerciseToDay(const std::string& muscleGroup, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap);

    /**
     * @brief Delete an exercise from the list of exercises for a specific day
     *
     * @param exercises The list of exercises for the day
     */
    void deleteExerciseFromDay(std::vector<WorkoutPlan::ExerciseDetails>& exercises);

    /**
     * @brief Display the available workout plan types
     */
    void displayWorkoutPlanTypes() const;

    /**
     * @brief Display the available exercise types
     *
     * @return int The number of exercise types available
     */
    int displayExerciseTypes() const;

    /**
     * @brief Modify the details of a workout plan
     *
     * @param plan The workout plan to modify
     */
    void modifyWorkoutPlan(WorkoutPlan& plan);

    /**
     * @brief Overwrite an existing workout plan with a new one
     *
     * @param item The new workout plan to overwrite with
     */
    void overwriteWorkoutPlan(const std::pair<std::string, WorkoutPlan>& item);

    /**
     * @brief Add a new exercise to the exercise list
     *
     * @param exerciseName The name of the exercise to add
     * @param exerciseMap The map of all available exercises
     */
    void addExerciseToList(const std::string& exerciseName, std::map<std::string, Exercise>& exerciseMap);
};

#endif // WORKOUTPLANVIEWMODEL_H
