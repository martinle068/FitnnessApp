#include "WorkoutPlanViewModel.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <set>

/**
 * @brief Construct a new Workout Plan ViewModel object
 *
 * @param file The filename to read workout plans from
 */
WorkoutPlanViewModel::WorkoutPlanViewModel(const std::string& file) : filename(file)
{
    reload();
}

/**
 * @brief Print view options for the workout plans
 *
 * @return int The number of options available
 */
int printViewOptions()
{
    std::cout << "View Options:\n";
    std::cout << "1. View All\n";
    std::cout << "2. View by Type\n";
    std::cout << "3. Cancel\n";

    return 3;
}

/**
 * @brief Display the workout plans based on user choice
 */
void WorkoutPlanViewModel::view()
{
    if (workoutPlanMap.empty())
    {
        std::cout << "No workout plans available.\n";
        return;
    }

    int viewChoice;
    int count = printViewOptions();

    getValidInput(viewChoice, "Enter choice: ", 1, count);

    if (viewChoice == 3)
    {
        return;
    }

    if (viewChoice == 1)
    {
        displayAllWorkoutPlans();
    }
    else if (viewChoice == 2)
    {
        displayWorkoutPlansByType();
    }
}

/**
 * @brief Display all workout plans
 */
void WorkoutPlanViewModel::displayAllWorkoutPlans() const
{
    for (const auto& pair : workoutPlanMap)
    {
        displayWorkoutPlan(pair.second);
    }
}

/**
 * @brief Display workout plans filtered by type
 */
void WorkoutPlanViewModel::displayWorkoutPlansByType() const
{
    std::cout << "Workout Plan Types:\n";
    std::cout << "1. Strength\n";
    std::cout << "2. Power\n";
    std::cout << "3. Hypertrophy\n";
    std::cout << "4. Conditioning\n";
    std::cout << "5. Push\n";
    std::cout << "6. Pull\n";
    std::cout << "7. Legs\n";

    printWindowSizedSeparator();

    int typeChoice;
    getValidInput(typeChoice, "Enter choice: ", 1, 7);

    WorkoutPlan::PlanType selectedType = static_cast<WorkoutPlan::PlanType>(typeChoice - 1);

    for (const auto& pair : workoutPlanMap)
    {
        const auto& plan = pair.second;
        if (plan.type == selectedType)
        {
            displayWorkoutPlan(plan);
        }
    }
}

/**
 * @brief Display the details of a given workout plan
 *
 * @param plan The workout plan to display
 */
void WorkoutPlanViewModel::displayWorkoutPlan(const WorkoutPlan& plan) const
{
    std::cout << "Name: " << plan.name << ", Type: " << WorkoutPlan::planTypeToString(plan.type) << "\n";

    for (const auto& day : DAYS_OF_WEEK)
    {
        auto it = plan.weeklyPlan.find(day);
        if (it != plan.weeklyPlan.end())
        {
            std::cout << "  " << day << ":\n";
            if (it->second.empty())
            {
                std::cout << "    Rest Day\n";
            }
            else
            {
                for (const auto& exercise : it->second)
                {
                    std::cout << "    " << exercise.exerciseName << " - " << exercise.sets << "x" << exercise.reps << "\n";
                }
            }
        }
    }

    printWindowSizedSeparator();
}

/**
 * @brief Edit the daily exercises for a specific day
 *
 * @param day The day to edit exercises for
 * @param exercises The list of exercises for the day
 * @param exerciseMap The map of all available exercises
 */
void WorkoutPlanViewModel::editDailyExercises(const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap)
{
    bool modifyingExercises = true;

    while (modifyingExercises)
    {
        clearScreen();
        printLabel("Exercises for " + day);
        displayCurrentExercisesForDay(day, exercises);

        std::cout << "Options:\n1. Add an exercise\n2. Delete an exercise\n3. Done\n";
        int exerciseChoice;
        getValidInput(exerciseChoice, "Enter choice: ", 1, 3);

        switch (exerciseChoice)
        {
        case 1:
            addExerciseToDay(day, exercises, exerciseMap);
            break;
        case 2:
            deleteExerciseFromDay(exercises);
            break;
        case 3:
            modifyingExercises = false;
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Display the current exercises for a specific day
 *
 * @param day The day to display exercises for
 * @param exercises The list of exercises for the day
 */
void WorkoutPlanViewModel::displayCurrentExercisesForDay(const std::string& day, const std::vector<WorkoutPlan::ExerciseDetails>& exercises) const
{
    std::cout << "Current exercises for " << day << ":\n";
    for (size_t i = 0; i < exercises.size(); ++i)
    {
        std::cout << i + 1 << ". " << exercises[i].exerciseName << " - " << exercises[i].sets << "x" << exercises[i].reps << "\n";
    }
    printWindowSizedSeparator();
}

/**
 * @brief Add an exercise to the day
 *
 * @param day The day to add an exercise to
 * @param exercises The list of exercises for the day
 * @param exerciseMap The map of all available exercises
 */
void WorkoutPlanViewModel::addExerciseToDay(const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap)
{
    clearScreen();
    printLabel("Exercises for " + day);
    displayMuscleGroupOptions(exerciseMap, day, exercises);
}

/**
 * @brief Display options for muscle groups when adding exercises
 *
 * @param exerciseMap The map of all available exercises
 * @param day The day to add exercises to
 * @param exercises The list of exercises for the day
 */
void WorkoutPlanViewModel::displayMuscleGroupOptions(std::map<std::string, Exercise>& exerciseMap, const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises)
{
    std::cout << "Enter exercises for " << day << " (choose muscle group, 'cancel' to stop adding exercises for this day, or 'done' to finish):\n";
    std::set<std::string> muscleGroups;
    for (const auto& pair : exerciseMap)
    {
        muscleGroups.insert(pair.second.muscleGroup);
    }

    std::vector<std::string> muscleGroupsVec(muscleGroups.begin(), muscleGroups.end());
    for (size_t i = 0; i < muscleGroupsVec.size(); ++i)
    {
        std::cout << i + 1 << ". " << muscleGroupsVec[i] << "\n";
    }

    size_t size = muscleGroupsVec.size();
    std::cout << ++size << ". Enter new exercise\n";
    std::cout << ++size << ". Done\n";
    std::cout << ++size << ". Cancel\n";

    int muscleGroupChoice;
    getValidInput(muscleGroupChoice, "Enter choice: ", 1, static_cast<int>(size));

    handleMuscleGroupChoice(muscleGroupChoice, muscleGroupsVec, day, exercises, exerciseMap);
}

/**
 * @brief Handle the muscle group choice when adding exercises
 *
 * @param choice The user's choice for the muscle group
 * @param muscleGroupsVec The vector of muscle groups
 * @param day The day to add exercises to
 * @param exercises The list of exercises for the day
 * @param exerciseMap The map of all available exercises
 */
void WorkoutPlanViewModel::handleMuscleGroupChoice(int choice, const std::vector<std::string>& muscleGroupsVec, const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap)
{
    if (choice == muscleGroupsVec.size() + 1)
    {
        addCustomExercise(day, exercises, exerciseMap);
    }
    else if (choice == muscleGroupsVec.size() + 2)
    {
        return;
    }
    else if (choice == muscleGroupsVec.size() + 3)
    {
        std::cout << "Cancelling exercise addition.\n";
        return;
    }
    else
    {
        addExistingExerciseToDay(muscleGroupsVec[choice - 1], exercises, exerciseMap);
    }
}

/**
 * @brief Add a custom exercise to the list of exercises
 *
 * @param day The day to add the custom exercise to
 * @param exercises The list of exercises for the day
 * @param exerciseMap The map of all available exercises
 */
void WorkoutPlanViewModel::addCustomExercise(const std::string& day, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap)
{
    Exercise newExercise;
    std::cout << "Enter exercise name: ";
    std::getline(std::cin >> std::ws, newExercise.name);

    std::string muscleGroup;
    std::cout << "Enter muscle group: ";
    std::getline(std::cin >> std::ws, muscleGroup);
    newExercise.muscleGroup = toLower(muscleGroup);

    int typeChoice;
    std::cout << "Select exercise type:\n";
    int count = displayExerciseTypes();
    getValidInput(typeChoice, "Enter choice: ", 1, count);
    newExercise.type = static_cast<Exercise::ExerciseType>(typeChoice - 1);

    getValidInput(newExercise.repetitions, "Enter repetitions: ");
    getValidInput(newExercise.sets, "Enter sets: ");

    exerciseMap[newExercise.name] = newExercise;
    writeToCSV("exercises.csv", newExercise);

    WorkoutPlan::ExerciseDetails ed;
    ed.exerciseName = newExercise.name;
    ed.reps = newExercise.repetitions;
    ed.sets = newExercise.sets;
    exercises.push_back(ed);
}

/**
 * @brief Display the available exercise types
 *
 * @return int The number of exercise types available
 */
int WorkoutPlanViewModel::displayExerciseTypes() const
{
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

    return 10;
}

/**
 * @brief Add an existing exercise to the list of exercises for a specific day
 *
 * @param muscleGroup The muscle group of the exercise
 * @param exercises The list of exercises for the day
 * @param exerciseMap The map of all available exercises
 */
void WorkoutPlanViewModel::addExistingExerciseToDay(const std::string& muscleGroup, std::vector<WorkoutPlan::ExerciseDetails>& exercises, std::map<std::string, Exercise>& exerciseMap)
{
    clearScreen();
    printLabel("Exercises for muscle group - " + muscleGroup);

    std::vector<Exercise> filteredExercises;
    displayExercisesByMuscleGroup(exerciseMap, muscleGroup, filteredExercises);

    while (true)
    {
        std::cout << "\nEnter the number of the exercise to add or 'done' to finish: ";
        std::string input;
        std::getline(std::cin >> std::ws, input);

        if (input == "done")
        {
            break;
        }

        int exerciseChoice;
        try
        {
            size_t pos;
            exerciseChoice = std::stoi(input, &pos);
            if (pos < input.size())
            {
                std::cout << "Invalid input. Please enter a valid number.\n";
                continue;
            }
        }
        catch (const std::exception&)
        {
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (exerciseChoice < 1 || exerciseChoice > filteredExercises.size())
        {
            std::cout << "Invalid choice. Please enter a valid number.\n";
            continue;
        }

        WorkoutPlan::ExerciseDetails ed;
        ed.exerciseName = filteredExercises[exerciseChoice - 1].name;
        ed.reps = filteredExercises[exerciseChoice - 1].repetitions;
        ed.sets = filteredExercises[exerciseChoice - 1].sets;
        exercises.push_back(ed);

        std::cout << "Exercise added.\n";
    }
}

/**
 * @brief Display exercises filtered by muscle group
 *
 * @param exerciseMap The map of all available exercises
 * @param muscleGroup The muscle group to filter by
 * @param filteredExercises The vector to store the filtered exercises
 */
void WorkoutPlanViewModel::displayExercisesByMuscleGroup(const std::map<std::string, Exercise>& exerciseMap, const std::string& muscleGroup, std::vector<Exercise>& filteredExercises)
{
    size_t index = 1;
    for (const auto& pair : exerciseMap)
    {
        if (pair.second.muscleGroup == muscleGroup)
        {
            std::cout << index << ". " << pair.second.name << " (Type: " << Exercise::exerciseTypeToString(pair.second.type)
                << ", Muscle Group: " << pair.second.muscleGroup
                << ", Repetitions: " << pair.second.repetitions << ", Sets: " << pair.second.sets << ")\n";
            filteredExercises.push_back(pair.second);
            index++;
        }
    }
}

/**
 * @brief Delete an exercise from the list of exercises for a specific day
 *
 * @param exercises The list of exercises for the day
 */
void WorkoutPlanViewModel::deleteExerciseFromDay(std::vector<WorkoutPlan::ExerciseDetails>& exercises)
{
    int deleteIndex;
    getValidInput(deleteIndex, "Enter the number of the exercise to delete (or 0 to cancel): ", 0, exercises.size());

    if (deleteIndex == 0)
    {
        return;
    }

    exercises.erase(exercises.begin() + deleteIndex - 1);
    std::cout << "Exercise deleted.\n";
}

/**
 * @brief Add a new workout plan
 */
void WorkoutPlanViewModel::add()
{
    std::string name;
    std::map<std::string, std::vector<WorkoutPlan::ExerciseDetails>> weeklyPlan;
    std::map<std::string, Exercise> exerciseMap = readFromCSV<Exercise>("exercises.csv");

    std::cout << "Enter workout plan name: ";
    std::getline(std::cin >> std::ws, name);

    if (!confirmOverwrite(workoutPlanMap, name))
    {
        std::cout << "Workout plan not modified.\n";
        return;
    }

    int typeChoice;
    std::cout << "\nSelect workout plan type:\n";
    displayWorkoutPlanTypes();
    getValidInput(typeChoice, "Enter choice: ", 1, 6);

    WorkoutPlan::PlanType type = static_cast<WorkoutPlan::PlanType>(typeChoice - 1);

    for (const auto& day : DAYS_OF_WEEK)
    {
        std::vector<WorkoutPlan::ExerciseDetails> exercises;
        editDailyExercises(day, exercises, exerciseMap);
        weeklyPlan[day] = exercises;
    }

    WorkoutPlan plan(name, type, weeklyPlan);
    workoutPlanMap[name] = plan;
    overwriteCSV(filename, workoutPlanMap);
}

/**
 * @brief Display the available workout plan types
 */
void WorkoutPlanViewModel::displayWorkoutPlanTypes() const
{
    std::cout << "1. Strength\n";
    std::cout << "2. Hypertrophy\n";
    std::cout << "3. Conditioning\n";
    std::cout << "4. Push\n";
    std::cout << "5. Pull\n";
    std::cout << "6. Legs\n";
}

/**
 * @brief Modify an existing workout plan
 */
void WorkoutPlanViewModel::modify()
{
    if (workoutPlanMap.empty())
    {
        std::cout << "No workout plans available to modify.\n";
        return;
    }

    std::cout << "Select a workout plan to modify:\n";
    std::vector<std::string> planNames;
    int index = 1;
    for (const auto& pair : workoutPlanMap)
    {
        std::cout << index << ". " << pair.first << "\n";
        planNames.push_back(pair.first);
        ++index;
    }

    std::cout << index << ". Cancel\n";

    int choice;
    getValidInput(choice, "Enter choice: ", 1, planNames.size() + 1);

    if (choice == index)
    {
        std::cout << "Modify operation cancelled.\n";
        return;
    }

    std::string selectedPlanName = planNames[choice - 1];
    auto& selectedPlan = workoutPlanMap[selectedPlanName];

    modifyWorkoutPlan(selectedPlan);
    workoutPlanMap[selectedPlanName] = selectedPlan;
    overwriteCSV(filename, workoutPlanMap);
    std::cout << "Workout plan modified.\n";
}

/**
 * @brief Modify the details of a workout plan
 *
 * @param plan The workout plan to modify
 */
void WorkoutPlanViewModel::modifyWorkoutPlan(WorkoutPlan& plan)
{
    std::string newName;
    int typeChoice;

    std::cout << "Enter new workout plan name (or press enter to keep current): ";
    std::getline(std::cin, newName);
    if (!newName.empty())
    {
        plan.name = newName;
    }

    std::cout << "\nCurrent workout plan type: " << WorkoutPlan::planTypeToString(plan.type) << "\n";
    std::cout << "Select new workout plan type (or press enter to keep current):\n";
    displayWorkoutPlanTypes();

    std::string typeInput;
    std::getline(std::cin, typeInput);
    if (!typeInput.empty())
    {
        typeChoice = std::stoi(typeInput);
        if (typeChoice >= 1 && typeChoice <= 6)
        {
            plan.type = static_cast<WorkoutPlan::PlanType>(typeChoice - 1);
            std::cout << "Current workout plan type: " << WorkoutPlan::planTypeToString(plan.type) << "\n";
            std::cout << "Press enter to continue.\n";
            std::cin.ignore();
        }
        else
        {
            std::cout << "Invalid choice, keeping the current type.\n";
            std::cout << "Current workout plan type: " << WorkoutPlan::planTypeToString(plan.type) << "\n";
            std::cout << "Press enter to continue.\n";
            std::cin.ignore();
        }
    }

    for (const auto& day : DAYS_OF_WEEK)
    {
        std::vector<WorkoutPlan::ExerciseDetails> exercises = plan.weeklyPlan[day];
        editDailyExercises(day, exercises, exerciseMap);
        plan.weeklyPlan[day] = exercises;
    }
}

/**
 * @brief Remove an existing workout plan
 */
void WorkoutPlanViewModel::remove()
{
    if (workoutPlanMap.empty())
    {
        std::cout << "No workout plans available to delete.\n";
        return;
    }

    std::cout << "Select a workout plan to delete:\n";
    std::vector<std::string> planNames;
    int index = 1;
    for (const auto& pair : workoutPlanMap)
    {
        std::cout << index << ". " << pair.first << "\n";
        planNames.push_back(pair.first);
        ++index;
    }
    std::cout << index << ". Cancel\n";

    int choice;
    getValidInput(choice, "Enter choice: ", 1, planNames.size() + 1);

    if (choice == index)
    {
        std::cout << "Delete operation cancelled.\n";
        return;
    }

    std::string selectedPlanName = planNames[choice - 1];
    workoutPlanMap.erase(selectedPlanName);
    overwriteCSV(filename, workoutPlanMap);

    std::cout << "Workout plan '" << selectedPlanName << "' deleted.\n";
}

/**
 * @brief Import workout plans from a CSV file
 *
 * @param filename The name of the CSV file to import workout plans from
 */
void WorkoutPlanViewModel::importFromFile(const std::string& filename)
{
    auto items = readFromCSV<WorkoutPlan>(filename);

    for (const auto& item : items)
    {
        if (workoutPlanMap.find(item.first) != workoutPlanMap.end())
        {
            overwriteWorkoutPlan(item);
        }
        else
        {
            workoutPlanMap[item.first] = item.second;
        }

        for (const auto& day : item.second.weeklyPlan)
        {
            for (const auto& exercise : day.second)
            {
                if (exerciseMap.find(exercise.exerciseName) == exerciseMap.end())
                {
                    addExerciseToList(exercise.exerciseName, exerciseMap);
                }
            }
        }
    }

    overwriteCSV("workout_plans.csv", workoutPlanMap);
    overwriteCSV("exercises.csv", exerciseMap);
}

/**
 * @brief Overwrite an existing workout plan with a new one
 *
 * @param item The new workout plan to overwrite with
 */
void WorkoutPlanViewModel::overwriteWorkoutPlan(const std::pair<std::string, WorkoutPlan>& item)
{
    const auto& currentPlan = workoutPlanMap[item.first];
    const auto& newPlan = item.second;

    std::cout << "Workout plan '" << item.first << "' already exists.\n";
    std::cout << "Current plan:\n";
    displayWorkoutPlan(currentPlan);
    std::cout << "New plan:\n";
    displayWorkoutPlan(newPlan);

    if (confirmOverwrite(workoutPlanMap, item.first))
    {
        workoutPlanMap[item.first] = newPlan;
    }
}

/**
 * @brief Reload workout plans and exercises from CSV files
 */
void WorkoutPlanViewModel::reload()
{
    exerciseMap = readFromCSV<Exercise>("exercises.csv");
    workoutPlanMap = readFromCSV<WorkoutPlan>(filename);
}

/**
 * @brief Add a new exercise to the exercise list
 *
 * @param exerciseName The name of the exercise to add
 * @param exerciseMap The map of all available exercises
 */
void WorkoutPlanViewModel::addExerciseToList(const std::string& exerciseName, std::map<std::string, Exercise>& exerciseMap)
{
    Exercise newExercise;
    newExercise.name = exerciseName;
    newExercise.muscleGroup = "Unknown"; // Or ask for this information
    newExercise.repetitions = 0; // Default value, should be updated
    newExercise.sets = 0; // Default value, should be updated
    newExercise.type = Exercise::ExerciseType::UNKNOWN; // Default value, should be updated

    exerciseMap[exerciseName] = newExercise;
    overwriteCSV("exercises.csv", exerciseMap);
}
