#include "ExerciseViewModel.h"
#include "Utils.h"
#include <iostream>
#include <set>
#include <algorithm>

/**
 * @brief Construct a new ExerciseViewModel::ExerciseViewModel object
 *
 * @param file The filename to read exercise items from
 */
ExerciseViewModel::ExerciseViewModel(const std::string& file) : filename(file)
{
    exerciseMap = readFromCSV<Exercise>(filename);
}

/**
 * @brief Display all exercises
 */
void ExerciseViewModel::displayAllExercises() const
{
    if (exerciseMap.empty())
    {
        std::cout << "No exercises to display.\n";
        return;
    }

    std::cout << "Exercise List:\n";
    printWindowSizedSeparator();

    for (const auto& pair : exerciseMap)
    {
        printExercise(pair.second);
    }
}

/**
 * @brief Display options for muscle groups
 */
void ExerciseViewModel::displayMuscleGroupOptions() const
{
    std::string muscleGroup = getMuscleGroupSelection();
    if (!muscleGroup.empty())
    {
        clearScreen();
        std::cout << "Exercises for " + muscleGroup + ":\n";
        displayExercisesByMuscleGroup(muscleGroup);
    }
}

/**
 * @brief Get the user's choice of muscle group
 *
 * @return std::string The chosen muscle group
 */
std::string ExerciseViewModel::getMuscleGroupSelection() const
{
    std::vector<std::string> muscleGroups;
    for (const auto& pair : exerciseMap)
    {
        if (std::find(muscleGroups.begin(), muscleGroups.end(), pair.second.muscleGroup) == muscleGroups.end())
        {
            muscleGroups.push_back(pair.second.muscleGroup);
        }
    }

    printMuscleGroupSelection(muscleGroups);

    int muscleGroupChoice;
    getValidInput(muscleGroupChoice, "Enter the number of the muscle group: ");

    while (muscleGroupChoice < 1 || muscleGroupChoice > muscleGroups.size())
    {
        std::cout << "Invalid choice. Please enter a number between 1 and " << muscleGroups.size() << ".\n";
        getValidInput(muscleGroupChoice, "Enter the number of the muscle group: ");
    }

    return muscleGroups[muscleGroupChoice - 1];
}

/**
 * @brief Display exercises by muscle group
 *
 * @param muscleGroup The muscle group to filter by
 */
void ExerciseViewModel::displayExercisesByMuscleGroup(const std::string& muscleGroup) const
{
    bool found = false;
    for (const auto& pair : exerciseMap)
    {
        if (pair.second.muscleGroup == muscleGroup)
        {
            printExercise(pair.second);
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No exercises found for muscle group: " << muscleGroup << '\n';
    }
}

/**
 * @brief Display available exercises based on user's choice (all or by muscle group)
 */
void ExerciseViewModel::view()
{
    std::cout << "Do you want to view all exercises or by muscle group?\n";
    std::cout << "1. View all\n";
    std::cout << "2. View by muscle group\n";

    int choice;
    getValidInput(choice, "Enter choice: ", 1, 2);

    if (choice == 1)
    {
        displayAllExercises();
    }
    else if (choice == 2)
    {
        displayMuscleGroupOptions();
    }
    else
    {
        std::cout << "Invalid choice.\n";
    }
}

/**
 * @brief Add a new exercise to the exercise map
 */
void ExerciseViewModel::add()
{
    std::string name, muscleGroup;
    int repetitions, sets, typeChoice;
    Exercise::ExerciseType type;

    std::cout << "Enter exercise name: ";
    std::getline(std::cin >> std::ws, name);

    if (!confirmOverwrite(exerciseMap, name))
    {
        std::cout << "Exercise not modified.\n";
        return;
    }

    std::cout << "Select exercise type:\n";
    std::cout << "1. Strength\n";
    std::cout << "2. Hypertrophy\n";
    std::cout << "3. Endurance\n";
    std::cout << "4. Flexibility\n";
    std::cout << "5. Balance and Stability\n";
    std::cout << "6. Power\n";
    std::cout << "7. Functional\n";
    std::cout << "8. Aerobic\n";
    std::cout << "9. Anaerobic\n";
    std::cout << "10. Recovery and Regeneration\n";
    getValidInput(typeChoice, "Enter choice: ");
    type = static_cast<Exercise::ExerciseType>(typeChoice - 1);

    std::cout << "Enter muscle group: ";
    std::getline(std::cin >> std::ws, muscleGroup);

    getValidInput(repetitions, "Enter repetitions: ");
    getValidInput(sets, "Enter sets: ");

    Exercise exercise{ name, type, toLower(muscleGroup), repetitions, sets };
    exerciseMap[name] = exercise;
    writeToCSV(filename, exercise);
}

/**
 * @brief Modify an existing exercise
 */
void ExerciseViewModel::modify()
{
    if (exerciseMap.empty())
    {
        std::cout << "No exercises to modify.\n";
        return;
    }

    std::map<std::string, Exercise> filteredExercises;
    handleMuscleGroupSelection(filteredExercises);

    std::cout << "Choose an exercise to modify:\n";

    std::vector<std::string> names;
    for (const auto& pair : filteredExercises)
    {
        names.push_back(pair.first);
    }

    displayAllExercises();
    std::size_t cancelIndex = filteredExercises.size() + 1;
    std::cout << cancelIndex << ". Cancel\n";

    int choice;
    getValidInput(choice, "Enter the number of the exercise to modify: ", 1, static_cast<int>(cancelIndex));

    if (choice == cancelIndex)
    {
        std::cout << "Operation cancelled.\n";
        return;
    }

    handleExerciseModification(exerciseMap[names[choice - 1]]);
    overwriteCSV(filename, exerciseMap);
    std::cout << "Exercise modified.\n";
}

/**
 * @brief Remove an exercise from the exercise map
 */
void ExerciseViewModel::remove()
{
    if (exerciseMap.empty())
    {
        std::cout << "No exercises to delete.\n";
        return;
    }

    std::map<std::string, Exercise> filteredExercises;
    handleMuscleGroupSelection(filteredExercises);

    handleExerciseDeletion(filteredExercises);
}

/**
 * @brief Import exercises from a CSV file
 *
 * @param filename The name of the CSV file to import exercises from
 */
void ExerciseViewModel::importFromFile(const std::string& filename)
{
    auto items = readFromCSV<Exercise>(filename);
    for (const auto& item : items)
    {
        if (exerciseMap.find(item.first) != exerciseMap.end())
        {
            overwriteExercise(item);
        }
        else
        {
            exerciseMap[item.first] = item.second;
        }
    }
    overwriteCSV(this->filename, exerciseMap);
}

/**
 * @brief Reload the exercises from the CSV file
 */
void ExerciseViewModel::reload()
{
    exerciseMap = readFromCSV<Exercise>(filename);
}

/**
 * @brief Print the details of a given exercise
 *
 * @param exercise The exercise whose details will be printed
 */
void ExerciseViewModel::printExercise(const Exercise& exercise) const
{
    std::cout << "Name: " << exercise.name << ", Type: " << Exercise::exerciseTypeToString(exercise.type)
        << ", Muscle Group: " << toLower(exercise.muscleGroup)
        << ", Repetitions: " << exercise.repetitions << ", Sets: " << exercise.sets << '\n';
    printWindowSizedSeparator();
}

/**
 * @brief Print the details of a given exercise with a prefix
 *
 * @param prefix The prefix string
 * @param exercise The exercise whose details will be printed
 */
void ExerciseViewModel::printExerciseDetails(const std::string& prefix, const Exercise& exercise) const
{
    std::cout << prefix << exercise.name << " (Type: " << Exercise::exerciseTypeToString(exercise.type)
        << ", Muscle Group: " << exercise.muscleGroup
        << ", Repetitions: " << exercise.repetitions << ", Sets: " << exercise.sets << ")\n";
}

/**
 * @brief Print the muscle group selection options
 *
 * @param muscleGroups The vector of muscle groups to be displayed
 */
void ExerciseViewModel::printMuscleGroupSelection(const std::vector<std::string>& muscleGroups) const
{
    for (size_t i = 0; i < muscleGroups.size(); ++i)
    {
        std::cout << i + 1 << ". " << muscleGroups[i] << "\n";
    }
}

/**
 * @brief Confirm if the user wants to delete an exercise
 *
 * @param name The name of the exercise to delete
 * @return true If the user confirms deletion
 * @return false If the user does not confirm deletion
 */
bool ExerciseViewModel::confirmDeletion(const std::string& name) const
{
    const auto& exercise = exerciseMap.at(name);
    std::string confirm;
    do
    {
        std::cout << "Are you sure you want to delete " << exercise.name << " (Type: " << Exercise::exerciseTypeToString(exercise.type)
            << ", Muscle Group: " << exercise.muscleGroup
            << ", Repetitions: " << exercise.repetitions << ", Sets: " << exercise.sets << ")? (yes/no): ";
        std::getline(std::cin, confirm);
    } while (confirm != "yes" && confirm != "no");

    return confirm == "yes";
}

/**
 * @brief Overwrite an existing exercise
 *
 * @param item The pair containing the exercise name and details
 */
void ExerciseViewModel::overwriteExercise(const std::pair<std::string, Exercise>& item)
{
    const auto& currentExercise = exerciseMap[item.first];
    const auto& newExercise = item.second;

    std::cout << "Exercise '" << item.first << "' already exists.\n";
    std::cout << "Current exercise:\n";
    printExercise(currentExercise);
    std::cout << "New exercise:\n";
    printExercise(newExercise);

    if (confirmOverwrite(exerciseMap, item.first))
    {
        exerciseMap[item.first] = newExercise;
    }
}

/**
 * @brief Handle the modification of an exercise
 *
 * @param exercise The exercise to be modified
 */
void ExerciseViewModel::handleExerciseModification(Exercise& exercise)
{
    std::string newName, newMuscleGroup;
    int newTypeChoice;
    Exercise::ExerciseType newType = exercise.type;

    std::cout << "Enter new exercise name (or press enter to keep current): ";
    std::getline(std::cin, newName);
    if (!newName.empty())
    {
        exercise.name = newName;
    }

    std::cout << "Enter new muscle group (or press enter to keep current): ";
    std::getline(std::cin, newMuscleGroup);
    if (!newMuscleGroup.empty())
    {
        exercise.muscleGroup = newMuscleGroup;
    }

    getOptionalInput(newTypeChoice, "Enter new exercise type (or press enter to keep current): ");
    if (newTypeChoice >= 1 && newTypeChoice <= 10)
    {
        newType = static_cast<Exercise::ExerciseType>(newTypeChoice - 1);
    }
    exercise.type = newType;

    getOptionalInput(exercise.repetitions, "Enter new repetitions (or press enter to keep current): ");
    getOptionalInput(exercise.sets, "Enter new sets (or press enter to keep current): ");
}

/**
 * @brief Handle the deletion of an exercise
 *
 * @param filteredExercises The map to store the filtered exercises
 */
void ExerciseViewModel::handleExerciseDeletion(std::map<std::string, Exercise>& filteredExercises)
{
    displayAllExercises();

    int cancelIndex = static_cast<int>(filteredExercises.size()) + 1;
    std::cout << cancelIndex << ". Cancel\n";

    int choice;
    getValidInput(choice, "Enter the number of the exercise to delete: ", 1, cancelIndex);

    if (choice == cancelIndex)
    {
        std::cout << "Operation cancelled.\n";
        return;
    }

    std::vector<std::string> names;
    for (const auto& pair : filteredExercises)
    {
        names.push_back(pair.first);
    }

    if (confirmDeletion(names[choice - 1]))
    {
        exerciseMap.erase(names[choice - 1]);
        overwriteCSV(filename, exerciseMap);
        std::cout << "Exercise deleted.\n";
    }
    else
    {
        std::cout << "Exercise not deleted.\n";
    }
}

/**
 * @brief Handle the selection of a muscle group and filter exercises accordingly
 *
 * @param filteredExercises The map to store the filtered exercises
 */
void ExerciseViewModel::handleMuscleGroupSelection(std::map<std::string, Exercise>& filteredExercises) const
{
    std::string muscleGroup = getMuscleGroupSelection();
    for (const auto& pair : exerciseMap)
    {
        if (pair.second.muscleGroup == muscleGroup)
        {
            filteredExercises[pair.first] = pair.second;
        }
    }
}
