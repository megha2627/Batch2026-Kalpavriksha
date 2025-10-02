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

void addUser() {
    FILE *fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Could not open file.\n");
        return;
    }
    struct User u;
    printf("Enter ID: ");
    scanf("%d", &u.id);
    printf("Enter Name: ");
    scanf("%s", u.name);
    printf("Enter Age: ");
    scanf("%d", &u.age);
    fprintf(fp, "%d %s %d\n", u.id, u.name, u.age);
    fclose(fp);
    printf("User added.\n");
}

void showUsers() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("No data found.\n");
        return;
    }
    struct User u;
    printf("\nID\tName\tAge\n");
    while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) != EOF) {
        printf("%d\t%s\t%d\n", u.id, u.name, u.age);
    }
    fclose(fp);
}

void editUser() {
    int id, found = 0;
    struct User u;
    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("File error.\n");
        return;
    }
    printf("Enter ID to update: ");
    scanf("%d", &id);
    while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) != EOF) {
        if (u.id == id) {
            found = 1;
            printf("New Name: ");
            scanf("%s", u.name);
            printf("New Age: ");
            scanf("%d", &u.age);
        }
        fprintf(temp, "%d %s %d\n", u.id, u.name, u.age);
    }
    fclose(fp);
    fclose(temp);
    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        printf("User updated.\n");
    } else {
        remove("temp.txt");
        printf("ID not found.\n");
    }
}

void removeUser() {
    int id, found = 0;
    struct User u;
    FILE *fp = fopen("users.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("File error.\n");
        return;
    }
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    while (fscanf(fp, "%d %s %d", &u.id, u.name, &u.age) != EOF) {
        if (u.id != id) {
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
        printf("User deleted.\n");
    } else {
        remove("temp.txt");
        printf("ID not found.\n");
    }
}

int main() {
    int ch;
    while (1) {
        printf("\nMenu\n");
        printf("1. Add User\n");
        printf("2. Show Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addUser(); break;
            case 2: showUsers(); break;
            case 3: editUser(); break;
            case 4: removeUser(); break;
            case 5: exit(0);
            default: printf("Invalid option.\n");
        }
    }
    return 0;
}