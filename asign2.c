/*
Assignment 2: CRUD Operations in File using C Language

Description:
Write a program where user records are stored as a list of users with fields such as
unique ID, Name, and Age. The file is named "users.txt". The program should
allow performing CRUD operations on the file: Create, Read, Update, and Delete
user records.

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


int isUserIdExists(int userId) {
    FILE *filePointer = fopen("users.txt", "r");
    if (filePointer == NULL) {
        return 0; 
    }

    struct User tempUser;
    while (fscanf(filePointer, "%d %s %d", &tempUser.id, tempUser.name, &tempUser.age) != EOF) {
        if (tempUser.id == userId) {
            fclose(filePointer);
            return 1; 
        }
    }

    fclose(filePointer);
    return 0;
}


void addUser() {
    FILE *filePointer = fopen("users.txt", "a");
    if (filePointer == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    struct User newUser;

    printf("Enter ID: ");
    scanf("%d", &newUser.id);

   
    if (isUserIdExists(newUser.id)) {
        printf("Error: User ID already exists. Please use a unique ID.\n");
        fclose(filePointer);
        return;
    }

    printf("Enter Name: ");
    scanf("%s", newUser.name);

    printf("Enter Age: ");
    scanf("%d", &newUser.age);

    fprintf(filePointer, "%d %s %d\n", newUser.id, newUser.name, newUser.age);
    fclose(filePointer);
    printf("✅ User added successfully.\n");
}


void showUsers() {
    FILE *filePointer = fopen("users.txt", "r");
    if (filePointer == NULL) {
        printf("No data found.\n");
        return;
    }

    struct User user;
    printf("\n%-10s %-20s %-5s\n", "ID", "Name", "Age");
    printf("----------------------------------\n");

    while (fscanf(filePointer, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        printf("%-10d %-20s %-5d\n", user.id, user.name, user.age);
    }

    fclose(filePointer);
}


void updateUser() {
    int targetId, found = 0;
    struct User user;
    FILE *filePointer = fopen("users.txt", "r");
    FILE *tempPointer = fopen("temp.txt", "w");

    if (filePointer == NULL || tempPointer == NULL) {
        printf("File error.\n");
        return;
    }

    printf("Enter ID to update: ");
    scanf("%d", &targetId);

    while (fscanf(filePointer, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == targetId) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", user.name);
            printf("Enter New Age: ");
            scanf("%d", &user.age);
        }
        fprintf(tempPointer, "%d %s %d\n", user.id, user.name, user.age);
    }

    fclose(filePointer);
    fclose(tempPointer);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("✅ User updated successfully.\n");
    } else {
        remove("temp.txt");
        printf("❌ Error: ID not found.\n");
    }
}


void deleteUser() {
    int targetId, found = 0;
    struct User user;
    FILE *filePointer = fopen("users.txt", "r");
    FILE *tempPointer = fopen("temp.txt", "w");

    if (filePointer == NULL || tempPointer == NULL) {
        printf("File error.\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &targetId);

    while (fscanf(filePointer, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id != targetId) {
            fprintf(tempPointer, "%d %s %d\n", user.id, user.name, user.age);
        } else {
            found = 1;
        }
    }

    fclose(filePointer);
    fclose(tempPointer);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("✅ User deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("❌ Error: ID not found.\n");
    }
}

int main() {
    FILE *checkFile = fopen("users.txt", "a");
if (checkFile == NULL) {
    printf("❌ Error: Unable to create users.txt file.\n");
    exit(1);
}
fclose(checkFile);

    int choice;
    while (1) {
        printf("\n======== USER MANAGEMENT MENU ========\n");
        printf("1. Add User\n");
        printf("2. Show Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("======================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                showUsers();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
