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
#include <ctype.h>

#define MAX_NAME 50

struct User {
    int id;
    char name[MAX_NAME];
    int age;
};

// Check if user ID already exists
int isUserIdExists(int userId) {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) return 0;

    struct User temp;
    while (fscanf(fp, "%d %[^\n] %d", &temp.id, temp.name, &temp.age) != EOF) {
        if (temp.id == userId) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Read integer safely
int readInt(const char *prompt) {
    char buffer[100];
    int value;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;
        if (sscanf(buffer, "%d", &value) == 1) return value;
        printf("❌ Invalid input. Please enter a valid number.\n");
    }
}

// Read string safely
void readString(const char *prompt, char *output, int size) {
    printf("%s", prompt);
    fgets(output, size, stdin);
    output[strcspn(output, "\n")] = 0; // Remove newline
}

void addUser() {
    FILE *fp = fopen("users.txt", "a");
    if (!fp) {
        printf(" Error: Could not open users.txt for writing.\n");
        return;
    }

    struct User newUser;
    while (1) {
        newUser.id = readInt("Enter unique ID: ");
        if (!isUserIdExists(newUser.id)) break;
        printf(" User ID already exists. Try again.\n");
    }

    readString("Enter Name: ", newUser.name, MAX_NAME);
    newUser.age = readInt("Enter Age: ");

    fprintf(fp, "%d %s %d\n", newUser.id, newUser.name, newUser.age);
    fclose(fp);
    printf("✅ User added successfully.\n");
}

void showUsers() {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        printf("No data found.\n");
        return;
    }

    struct User u;
    printf("\n%-10s %-30s %-5s\n", "ID", "Name", "Age");
    printf("--------------------------------------------------\n");
    while (fscanf(fp, "%d %[^\n] %d", &u.id, u.name, &u.age) != EOF) {
        printf("%-10d %-30s %-5d\n", u.id, u.name, u.age);
    }
    fclose(fp);
}

void updateUser() {
    int targetId = readInt("Enter ID to update: ");
    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf(" File error.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    struct User u;
    int found = 0;
    while (fscanf(fp, "%d %[^\n] %d", &u.id, u.name, &u.age) != EOF) {
        if (u.id == targetId) {
            found = 1;
            readString("Enter New Name: ", u.name, MAX_NAME);
            u.age = readInt("Enter New Age: ");
        }
        fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf(" User updated successfully.\n");
    } else {
        remove("temp.txt");
        printf(" Error: ID not found.\n");
    }
}

void deleteUser() {
    int targetId = readInt("Enter ID to delete: ");
    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    struct User u;
    int found = 0;
    while (fscanf(fp, "%d %[^\n] %d", &u.id, u.name, &u.age) != EOF) {
        if (u.id != targetId) {
            fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("✅ User deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("Error: ID not found.\n");
    }
}

int main() {
    FILE *fp = fopen("users.txt", "a");
    if (!fp) {
        printf("rror: Cannot create users.txt file.\n");
        exit(1);
    }
    fclose(fp);

    while (1) {
        printf("\n======== USER MANAGEMENT MENU ========\n");
        printf("1. Add User\n2. Show Users\n3. Update User\n4. Delete User\n5. Exit\n");
        int choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: addUser(); break;
            case 2: showUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5: printf("Exiting... Goodbye!\n"); exit(0);
            default: printf("Invalid option. Try again.\n");
        }
    }
    return 0;
}
