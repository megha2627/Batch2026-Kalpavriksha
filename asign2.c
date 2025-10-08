
/*
Assignment 2: CRUD Operations in File using C Language

Description:
Write a program where user records are stored as a list of users with fields 
such as unique ID, Name, and Age. The file is named "users.txt". The program 
should allow performing CRUD operations on the file: Create, Read, Update, 
and Delete user records.

Operations:
1. Create: Add a new user to the file.
2. Read: Display all users stored in the file.
3. Update: Modify the details of a user based on their ID.
4. Delete: Remove a user by their ID.

Requirements:
1. The data should be stored in a structured format (using struct).
2. Use text files to store the data.
3. Implement functions to:
   - Create a new file if it doesn't exist.
   - Read the file and display the contents.
   - Update a specific record based on ID.
   - Delete a record by modifying the file content.

File Name:
- The file storing user data should be named "users.txt".

Note:
- Ensure that all operations are performed safely and the file remains consistent
  after any modification.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    int userId;
    char userName[50];
    int userAge;
};


int getIntInput(const char *prompt) {
    char inputBuffer[100];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
            continue;
        if (sscanf(inputBuffer, "%d", &value) == 1)
            return value;
        printf("Invalid input! Please enter a valid number.\n");
    }
}


int isUserIdExists(int id) {
    FILE *file = fopen("users.txt", "r");
    if (!file) return 0;

    struct User tempUser;
    while (fscanf(file, "%d %49s %d", &tempUser.userId, tempUser.userName, &tempUser.userAge) == 3) {
        if (tempUser.userId == id) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void addUser() {
    FILE *file = fopen("users.txt", "a");
    if (!file) {
        printf("Error: Cannot open 'users.txt' for writing.\n");
        return;
    }

    struct User newUser;
    do {
        newUser.userId = getIntInput("Enter User ID: ");
        if (isUserIdExists(newUser.userId))
            printf("Error: This User ID already exists. Try another.\n");
        else
            break;
    } while (1);

    printf("Enter User Name: ");
    fgets(newUser.userName, sizeof(newUser.userName), stdin);
    newUser.userName[strcspn(newUser.userName, "\n")] = '\0';

    newUser.userAge = getIntInput("Enter User Age: ");

    fprintf(file, "%d %s %d\n", newUser.userId, newUser.userName, newUser.userAge);
    fclose(file);
    printf("User added successfully.\n");
}


void displayUsers() {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("No users found.\n");
        return;
    }

    struct User user;
    printf("\n%-10s %-20s %-5s\n", "UserID", "UserName", "Age");
    printf("-----\n");

    while (fscanf(file, "%d %49s %d", &user.userId, user.userName, &user.userAge) == 3) {
        printf("%-10d %-20s %-5d\n", user.userId, user.userName, user.userAge);
    }
    fclose(file);
}

void updateUser() {
    int targetId, found = 0;
    struct User user;

    FILE *file = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Error: Cannot access files.\n");
        return;
    }

    targetId = getIntInput("Enter User ID to update: ");

    while (fscanf(file, "%d %49s %d", &user.userId, user.userName, &user.userAge) == 3) {
        if (user.userId == targetId) {
            found = 1;
            printf("Enter New User Name: ");
            getchar(); 
            fgets(user.userName, sizeof(user.userName), stdin);
            user.userName[strcspn(user.userName, "\n")] = '\0';
            user.userAge = getIntInput("Enter New User Age: ");
        }
        fprintf(tempFile, "%d %s %d\n", user.userId, user.userName, user.userAge);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User updated successfully.\n");
    } else {
        remove("temp.txt");
        printf("User ID not found.\n");
    }
}


void deleteUser() {
    int targetId, found = 0;
    struct User user;

    FILE *file = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Error: Cannot access files.\n");
        return;
    }

    targetId = getIntInput("Enter User ID to delete: ");

    while (fscanf(file, "%d %49s %d", &user.userId, user.userName, &user.userAge) == 3) {
        if (user.userId != targetId)
            fprintf(tempFile, "%d %s %d\n", user.userId, user.userName, user.userAge);
        else
            found = 1;
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("User ID not found.\n");
    }
}

int main() {
    int choice;
    char inputBuffer[20];

    while (1) {
        printf("\nUSER MANAGEMENT MENU\n");
        printf("1. Add User\n");
        printf("2. Display Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
            continue;

        if (sscanf(inputBuffer, "%d", &choice) != 1) {
            printf("Invalid input! Please enter a number between 1-5.\n");
            continue;
        }

        switch (choice) {
            case 1: addUser(); break;
            case 2: displayUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5: printf("Exiting program...\n"); exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}







