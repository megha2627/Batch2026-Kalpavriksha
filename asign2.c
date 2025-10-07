
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
    int id;
    char name[50];
    int age;
};

// Function to get safe integer input from user
int getIntegerInput(char message[]) {
    int value;
    char c;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &value) == 1) {
            while ((c = getchar()) != '\n' && c != EOF); // clear buffer
            return value;
        } else {
            printf("Invalid input! Please enter a valid number.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

// Check if User ID already exists
int isUserIdExists(int userId) {
    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL) return 0;

    struct User tempUser;
    while (fscanf(userFile, "%d %49s %d", &tempUser.id, tempUser.name, &tempUser.age) != EOF) {
        if (tempUser.id == userId) {
            fclose(userFile);
            return 1;
        }
    }

    fclose(userFile);
    return 0;
}

// Add a new user
void addUser() {
    FILE *userFile = fopen("users.txt", "a");
    if (userFile == NULL) {
        printf("Error: Could not open 'users.txt' for writing.\n");
        return;
    }

    struct User newUser;
    do {
        newUser.id = getIntegerInput("Enter ID: ");
        if (isUserIdExists(newUser.id))
            printf("Error: This ID already exists. Try another.\n");
        else
            break;
    } while (1);

    printf("Enter Name: ");
    if (scanf("%49s", newUser.name) != 1) {
        printf("Invalid input for name.\n");
        fclose(userFile);
        return;
    }
    newUser.age = getIntegerInput("Enter Age: ");

    fprintf(userFile, "%d %s %d\n", newUser.id, newUser.name, newUser.age);
    fclose(userFile);
    printf("User added successfully.\n");
}

// Display all users
void showUsers() {
    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL) {
        printf("No data found.\n");
        return;
    }

    struct User u;
    printf("\n%-10s %-20s %-5s\n", "ID", "Name", "Age");
    printf("--------------------------------------\n");

    while (fscanf(userFile, "%d %49s %d", &u.id, u.name, &u.age) != EOF) {
        printf("%-10d %-20s %-5d\n", u.id, u.name, u.age);
    }

    fclose(userFile);
}

// Update a user by ID
void updateUser() {
    int id, found = 0;
    struct User u;

    FILE *userFile = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (userFile == NULL || tempFile == NULL) {
        printf("Error: Could not access 'users.txt'. Check file existence and permissions.\n");
        return;
    }

    id = getIntegerInput("Enter ID to update: ");

    while (fscanf(userFile, "%d %49s %d", &u.id, u.name, &u.age) != EOF) {
        if (u.id == id) {
            found = 1;
            printf("Enter New Name: ");
            if (scanf("%49s", u.name) != 1) {
                printf("Invalid input for name.\n");
                fclose(userFile);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }
            u.age = getIntegerInput("Enter New Age: ");
        }
        fprintf(tempFile, "%d %s %d\n", u.id, u.name, u.age);
    }

    fclose(userFile);
    fclose(tempFile);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User updated successfully.\n");
    } else {
        remove("temp.txt");
        printf("ID not found.\n");
    }
}

// Delete a user by ID
void deleteUser() {
    int id, found = 0;
    struct User u;

    FILE *userFile = fopen("users.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (userFile == NULL || tempFile == NULL) {
        printf("Error: Could not access 'users.txt'. Check file existence and permissions.\n");
        return;
    }

    id = getIntegerInput("Enter ID to delete: ");

    while (fscanf(userFile, "%d %49s %d", &u.id, u.name, &u.age) != EOF) {
        if (u.id != id) {
            fprintf(tempFile, "%d %s %d\n", u.id, u.name, u.age);
        } else {
            found = 1;
        }
    }

    fclose(userFile);
    fclose(tempFile);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("ID not found.\n");
    }
}

int main() {
    int choice;
    char input[20];
    while (1) {
        printf("\nUSER MANAGEMENT MENU\n");
        printf("1. Add User\n");
        printf("2. Show Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        

        printf("Enter your choice: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            continue;

        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input! Please enter a number between 1–5.\n");
            continue;
        }

        switch (choice) {
            case 1: addUser(); break;
            case 2: showUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5:
                printf("Exiting...!\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}
