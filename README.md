# FitnessApp User Documentation

## Introduction

Welcome to the **FitnessApp**! This application is designed to help you manage and track your profile, fitness goals, exercises, food, workout, and nutrition plans. Whether you're looking to lose weight, gain muscle, or maintain a healthy lifestyle, FitnessApp provides the tools you need to create, view, modify, and manage your nutrition plans effectively.

## Getting Started

Project has been developed in Visual Studio.
The repo contains a `.vcxproj` file.
Build and run the project in Visual Studio.

## FitnessApp Program Hierarchy

### MainView

- **Profile (ProfileView)**
  - View Profile
  - Set Profile Information
  - Set Goals
  - Set Custom Calories
  - Reset to Calculated Calories
  - Back (to HomeView)

- **Exercises (ExerciseView)**
  - View Exercises
    - View all
    - View by muscle group
  - Add Exercise
  - Modify Exercise
  - Delete Exercise
  - Import from File
  - Back (to HomeView)

- **Food (FoodView)**
  - View Food Items
    - View all
    - View by category
  - Add Food Item
  - Modify Food Item
  - Delete Food Item
  - Import from File
  - Back (to HomeView)

- **Workout Plans (WorkoutPlanView)**
  - View Workout Plans
    - View all
    - View by Type
  - Add Workout Plan
  - Modify Workout Plan
  - Delete Workout Plan
  - Import Workout Plan from File
  - Back (to HomeView)

- **Nutrition Plans (NutritionView)**
  - View Meal Plans
    - View all
    - Generate Plan by Goals
  - Add Meal Plan
  - Modify Meal Plan
  - Delete Meal Plan
  - Import Meal Plan from File
  - Back (to HomeView)

- **Exit**

## Closer description of main functionality

### Profile (ProfileView)
- **View Profile**
  - Displays Name, Age, Gender, Height, Weight, Activity Level, Target Weight, Body Fat Percentage, Fitness Goal, Daily Calories.
- **Set Profile Information**
  - Sets Name, Age, Gender, Height, Weight, Activity Level.
- **Set Goals**
  - Sets Target Weight, Body Fat Percentage, Fitness Goal.
- **Set Custom Calories**
  - Allows user to define Daily Calories.
- **Reset to Calculated Calories**
  - Resets Daily Calories to the calculated value based on profile and goals.
- **Back (to HomeView)**
  - Returns to the MainView.

### Exercises (ExerciseView)
- **View Exercises**
  - **View all**
    - All exercises are displayed.
  - **View by muscle group**
    - Only exercises for the given muscle group are displayed.
- **Add Exercise**
  - Creating a new exercise by setting Name, Type, Muscle Group, repetitions, and sets.
  - If the user enters an existing name, they can choose to overwrite it or to cancel the action.
- **Modify Exercise**
  - Modify an existing exercise.
- **Delete Exercise**
  - Delete an existing exercise.
- **Import from File**
  - Import a set of exercises from a given file.
- **Back (to HomeView)**
  - Returns to the MainView.

### Food (FoodView)
- **View Food Items**
  - **View all**
    - All food items are displayed.
  - **View by category**
    - Only food items for the given category are displayed.
- **Add Food Item**
  - Creating a new food item by setting Name, Category, Calories, Protein, Carbohydrates, Fats, and Portion Size.
  - If the user enters an existing name, they can choose to overwrite it or to cancel the action.
- **Modify Food Item**
  - Modify an existing food item.
- **Delete Food Item**
  - Delete an existing food item.
- **Import from File**
  - Import a set of food items from a given file.
- **Back (to HomeView)**
  - Returns to the MainView.

### Workout Plans (WorkoutPlanView)
- **View Workout Plans**
  - **View all**
    - All workout plans are displayed.
  - **View by Type**
    - Only workout plans of a specific type are displayed.
- **Add Workout Plan**
  - Creating a new workout plan by setting Name, Type, and adding exercises.
  - If the user enters an existing name, they can choose to overwrite it or to cancel the action.
- **Modify Workout Plan**
  - Modify an existing workout plan.
- **Delete Workout Plan**
  - Delete an existing workout plan.
- **Import Workout Plan from File**
  - Import a workout plan from a given file.
- **Back (to HomeView)**
  - Returns to the MainView.

### Nutrition Plans (NutritionView)
- **View Meal Plans**
  - **View all**
    - All meal plans are displayed.
  - **Generate Plan by Goals**
    - Generates a personalized meal plan based on user goals and profile.
- **Add Meal Plan**
  - Creating a new meal plan by setting Name, adding meals, and adding food items to each meal.
  - If the user enters an existing name, they can choose to overwrite it or to cancel the action.
- **Modify Meal Plan**
  - Modify an existing meal plan.
- **Delete Meal Plan**
  - Delete an existing meal plan.
- **Import Meal Plan from File**
  - Import a meal plan from a given file.
- **Back (to HomeView)**
  - Returns to the MainView.

### Exit
- Closes the application.

When modifying items, it is possible to skip values that the User wants to keep.

## Data storing

Data is stored in CSV format.
Each data structure has its own implementation of a function to convert from the csv format to its internal implementation and vice versa.

## Sample Data

Example exercises, food, exercise and nutrition plans are provided for immediate program testing.

Each data groups are stored in separate csv files.

## More detailed description of the program

See `docs/html/index.html`.