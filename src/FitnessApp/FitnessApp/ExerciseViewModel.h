#ifndef EXERCISE_VIEW_MODEL_H
#define EXERCISE_VIEW_MODEL_H

#include <map>
#include <string>
#include <vector>
#include "Exercise.h"
#include "ViewModel.h"

/**
 * @brief ViewModel class for managing and displaying exercises.
 */
class ExerciseViewModel : public ViewModel
{
public:
    /**
     * @brief Construct a new ExerciseViewModel object.
     *
     * @param file The filename to read exercise items from.
     */
    ExerciseViewModel(const std::string& file);

    /**
     * @brief Display available exercises based on user's choice (all or by muscle group).
     */
    void view() override;

    /**
     * @brief Add a new exercise to the exercise map.
     */
    void add() override;

    /**
     * @brief Modify an existing exercise.
     */
    void modify() override;

    /**
     * @brief Remove an exercise from the exercise map.
     */
    void remove() override;

    /**
     * @brief Import exercises from a CSV file.
     *
     * @param filename The name of the CSV file to import exercises from.
     */
    void importFromFile(const std::string& filename) override;

    /**
     * @brief Reload the exercises from the CSV file.
     */
    void reload() override;

private:
    std::string filename; ///< The filename to read/write exercise items.
    std::map<std::string, Exercise> exerciseMap; ///< Map of exercise names to Exercise objects.

    /**
     * @brief Display all exercises.
     */
    void displayAllExercises() const;

    /**
     * @brief Display options for muscle groups.
     */
    void displayMuscleGroupOptions() const;

    /**
     * @brief Display exercises by muscle group.
     *
     * @param muscleGroup The muscle group to filter by.
     */
    void displayExercisesByMuscleGroup(const std::string& muscleGroup) const;

    /**
     * @brief Get the user's choice of muscle group.
     *
     * @return std::string The chosen muscle group.
     */
    std::string getMuscleGroupSelection() const;

    /**
     * @brief Confirm if the user wants to delete an exercise.
     *
     * @param name The name of the exercise to delete.
     * @return true If the user confirms deletion.
     * @return false If the user does not confirm deletion.
     */
    bool confirmDeletion(const std::string& name) const;

    /**
     * @brief Overwrite an existing exercise.
     *
     * @param item The pair containing the exercise name and details.
     */
    void overwriteExercise(const std::pair<std::string, Exercise>& item);

    /**
     * @brief Handle the modification of an exercise.
     *
     * @param exercise The exercise to be modified.
     */
    void handleExerciseModification(Exercise& exercise);

    /**
     * @brief Handle the deletion of an exercise.
     *
     * @param filteredExercises The map to store the filtered exercises.
     */
    void handleExerciseDeletion(std::map<std::string, Exercise>& filteredExercises);

    /**
     * @brief Handle the selection of a muscle group and filter exercises accordingly.
     *
     * @param filteredExercises The map to store the filtered exercises.
     */
    void handleMuscleGroupSelection(std::map<std::string, Exercise>& filteredExercises) const;

    /**
     * @brief Print the details of a given exercise.
     *
     * @param exercise The exercise whose details will be printed.
     */
    void printExercise(const Exercise& exercise) const;

    /**
     * @brief Print the details of a given exercise with a prefix.
     *
     * @param prefix The prefix string.
     * @param exercise The exercise whose details will be printed.
     */
    void printExerciseDetails(const std::string& prefix, const Exercise& exercise) const;

    /**
     * @brief Print the muscle group selection options.
     *
     * @param muscleGroups The vector of muscle groups to be displayed.
     */
    void printMuscleGroupSelection(const std::vector<std::string>& muscleGroups) const;
};

#endif // EXERCISE_VIEW_MODEL_H
