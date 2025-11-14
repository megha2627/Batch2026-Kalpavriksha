#include<stdio.h>
#include "Players_data.h"
#include <string.h>
#include <stdlib.h>
#include<ctype.h>


int getValidChoice() {
    char input[50];

    while (1) {
        printf("Enter your choice (1-6): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';


      
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }

        
        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                printf("Entered value is not a number.\n");
                valid = 0;
                break;
            }
        }

        if (valid == 1) {
            int choice = atoi(input);

            return choice;
            
        }
    }
}



int getValidInteger(char message[]) {
    char input[50];

    while (1) {
        printf("%s", message);
        fgets(input, sizeof(input), stdin);

        // Remove newline
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }

        // Check numeric only (no spaces allowed)
        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Invalid input! Please enter a numeric value.\n");
            continue;
        }

        return atoi(input);
    }
}

int getValidPlayerID() {
    return getValidInteger("Enter Player ID: ");
}



void getValidName(char *dest) {
    char input[1000];

    while (1) {
        printf("Enter Player Name:\n ");
        fgets(input, sizeof(input), stdin);

        // Remove newline
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }

        int valid = 1;

        // Check name only contains alphabets & spaces
        for (int i = 0; input[i] != '\0'; i++) {
            
            if (!isalpha(input[i]) && input[i] != ' ') {
                printf("Invalid name! Only alphabets allowed.\n");
                valid = 0;
                break;
            }
            if (input[0] == ' ') {
            valid = 0;
            printf("Invalid name! Name cannot start with a space.\n");
            break;
        }
        }

        if (valid == 1) {
            if (strlen(input) < 1 || strlen(input) > 20) {
                printf("Name length must be between 1 and 20 characters.\n");
            } else {
                strcpy(dest, input);
                return;
            }
        }
    }
}

void getValidTeamName(char *dest) {
    char input[1000];
    
    while (1) {

        // clear leftover newline from previous scanf
        
       

        printf("Enter Team Name:\n ");
        fgets(input, sizeof(input), stdin);

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        int valid = 1;

        // Character validation
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isalpha(input[i])) {
                printf("Invalid team name! Only alphabets, spaces, and '-' allowed.\n");
                valid = 0;
                break;
            }
            if (input[0] == ' ') {
            valid = 0;
            printf("Invalid name! Name cannot start with a space.\n");
            break;
            }
            
        }

        // Length validation (FIXED)
        int len = strlen(input);
        if (len < 1 || len > 20) {
            printf("Team name must be 1 to 20 characters long.\n");
            valid = 0;
            continue;
        }

        if (valid) {
            strcpy(dest, input);
            return;
        }
    }
}
float getValidFloat(char message[]) {
    char input[100];
    float value;

    while (1) {
        printf("%s", message);
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';  // remove newline

        char *endptr;
        value = strtof(input, &endptr);

        if (endptr != input && *endptr == '\0' && value >= 0)
            return value;

        printf("Invalid input! Please enter a valid number.\n");
    }
}




int getValidTotalRuns() {
    return getValidInteger("Enter Total Runs: ");
}


float getValidBattingAverage() {
   return getValidFloat("Enter Batting Average: ");
}



float getValidStrikeRate() {
    return getValidFloat("Enter Strike Rate: ");
}




int getValidWicketsTaken() {
    return getValidInteger("Enter Wickets Taken: ");
}


float getValidEconomyRate() {
    return getValidFloat("Enter Economy Rate: ");
}



void getValidRoleChoice(char role[]) {
    char input[10];
    int choice;
   
    

    while (1) {
        printf("Enter Role (1-Batsman, 2-Bowler, 3-All-rounder):\n ");
        fgets(input, sizeof(input), stdin);

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        int valid = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Invalid input! Role must be numeric.\n");
            continue;
        }

        choice = atoi(input);

        if (choice == 1) {
            strcpy(role, "Batsman");
            return;
        }
        else if (choice == 2) {
            strcpy(role, "Bowler");
            return;
        }
        else if (choice == 3) {
            strcpy(role, "All-rounder");
            return;
        }
        else {
            printf("Invalid choice! Enter 1, 2, or 3.\n");
        }
    }
}

int getValidPlayerCount() {
    char input[20];
    int K;

    while(1){
        printf("Enter number of players (K): ");
        if(!fgets(input, sizeof(input), stdin)) continue;

        input[strcspn(input, "\n")] = '\0';

        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(!isdigit(input[i])){
                valid = 0;
                break;
            }
        }

        if(!valid){
            printf("Invalid input! Number of players must be numeric.\n");
            continue;
        }

        K = atoi(input);
        if(K <= 0){
            printf("Invalid input! Number of players must be greater than 0.\n");
            continue;
        }

        return K;
    }
}


int getValidTeamID() {
    char input[20];
    int teamID;

    while(1){
        printf("Enter Team ID: ");
        if(!fgets(input, sizeof(input), stdin)) continue;

        input[strcspn(input, "\n")] = '\0';  // remove newline

        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(!isdigit(input[i])){
                valid = 0;
                break;
            }
        }

        if(!valid){
            printf("Invalid input! Team ID must be numeric.\n");
            continue;
        }

        teamID = atoi(input);
        if(teamID <= 0){
            printf("Invalid Team ID! Must be greater than 0.\n");
            continue;
        }

        return teamID;
    }
}


team* createTeamNode(int id, char name[], int totalPlayers, float avgStrikeRate) {
    team *newNode = (team*)malloc(sizeof(team));
    newNode->teamID = id;
    strcpy(newNode->teamName, name);
    newNode->totalPlayers = totalPlayers;
    newNode->averageBattingStrikeRate = avgStrikeRate;
    newNode->next = NULL;
    return newNode;
}



Player* createPlayerNode(int id, const char name[], const char teamName[], const char role[],
                         int totalRuns, float battingAverage, float strikeRate,
                         int wicketsTaken, float economyRate) {
    Player *newNode = (Player*)malloc(sizeof(Player));

    newNode->playerID = id;
    strcpy(newNode->name, name);
    strcpy(newNode->teamName, teamName);
    strcpy(newNode->role, role);
    newNode->totalRuns = totalRuns;
    newNode->battingAverage = battingAverage;
    newNode->strikeRate = strikeRate;
    newNode->wicketsTaken = wicketsTaken;
    newNode->economyRate = economyRate;

  
    newNode->performanceIndex = (battingAverage * strikeRate) / 100.0;

    newNode->next = NULL;
    return newNode;
}

Player* initializePlayerList() {
    Player *head = NULL;
    Player *tail = NULL;
    int playerCount = sizeof(players) / sizeof(players[0]);

    for (int i = 0; i < playerCount; i++) { 
        Player *newNode = createPlayerNode(
            players[i].playerID,
            players[i].name,
            players[i].teamName,
            players[i].role,
            players[i].totalRuns,
            players[i].battingAverage,
            players[i].strikeRate,
            players[i].wicketsTaken,
            players[i].economyRate
        );

        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}







void displayAllPlayers(Player *head) {
    Player *temp = head;
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Team: %s | Role: %s | Runs: %d | Avg: %.2f | SR: %.2f | PI: %.2f\n",
       temp->playerID, temp->name, temp->teamName, temp->role,
       temp->totalRuns, temp->battingAverage, temp->strikeRate, temp->performanceIndex);

        temp = temp->next;
    }
}





team* initializeTeamList(Player *playerHead) {
    team *teamHead = NULL, *teamTail = NULL;
    int id = 1;

    Player *temp = playerHead;

    while (temp != NULL) {
    
        team *search = teamHead;
        int found = 0;
        while (search != NULL) {
            if (strcmp(search->teamName, temp->teamName) == 0) {
                found = 1;
                search->totalPlayers++;
                search->averageBattingStrikeRate += temp->strikeRate;  // Add up for average
                break;
            }
            search = search->next;
        }

        if (!found) {
            team *newTeam = createTeamNode(id++, temp->teamName, 1, temp->strikeRate);
            if (teamHead == NULL) {
                teamHead = teamTail = newTeam;
            } else {
                teamTail->next = newTeam;
                teamTail = newTeam;
            }
        }

        temp = temp->next;
    }

   
    team *t = teamHead;
    while (t != NULL) {
        t->averageBattingStrikeRate /= t->totalPlayers;
        t = t->next;
    }

    return teamHead;
}



void displayPlayersOfTeamByID(Player *playerHead, team *teamHead, int teamID) {
    team *teamTemp = teamHead;
    char teamName[50];
    int foundTeam = 0;

   
    while (teamTemp != NULL) {
        if (teamTemp->teamID == teamID) {
            strcpy(teamName, teamTemp->teamName);
            foundTeam = 1;
            break;
        }
        teamTemp = teamTemp->next;
    }

    if (!foundTeam) {
        printf("Invalid Team ID.\n");
        return;
    }

   
    printf("\nChoice 2 → Display All Players of a Specific Team\n");
    printf("Enter Team ID: %d\n", teamID);
    printf("Players of Team %s:\n", teamName);
    printf("====================================================================================\n");
    printf("ID\tName\t\tRole\t\tRuns\tAvg\tSR\tWkts\tER\tPerf.Index\n");
    printf("====================================================================================\n");

    
    Player *p = playerHead;
    int totalPlayers = 0;
    float totalStrikeRate = 0;

    while (p != NULL) {
        if (strcmp(p->teamName, teamName) == 0) {
            printf("%d\t%-15s%-15s%d\t%.1f\t%.1f\t%d\t%.1f\t%.2f\n",
                   p->playerID,
                   p->name,
                   p->role,
                   p->totalRuns,
                   p->battingAverage,
                   p->strikeRate,
                   p->wicketsTaken,
                   p->economyRate,
                   p->performanceIndex);

            totalPlayers++;
            totalStrikeRate += p->strikeRate;
        }
        p = p->next;
    }

    printf("====================================================================================\n");
    if (totalPlayers > 0)
        printf("Total Players: %d\nAverage Batting Strike Rate: %.1f\n",
               totalPlayers, totalStrikeRate / totalPlayers);
    else
        printf("No players found for this team.\n");
}





Player* addPlayerToTeam(Player *playerHead, team **teamHead) {
    Player *newPlayer = (Player *)malloc(sizeof(Player));

    //printf("\nEnter Player ID: ");
    newPlayer->playerID = getValidPlayerID();
   
    
    getValidName(newPlayer->name);
    getValidRoleChoice(newPlayer->role);
    
   
    getValidTeamName(newPlayer->teamName);
    
   
    newPlayer->totalRuns =getValidTotalRuns();
  
    newPlayer->battingAverage = getValidBattingAverage();
    newPlayer->strikeRate = getValidStrikeRate();
  
    newPlayer->wicketsTaken = getValidWicketsTaken();
  
    newPlayer->economyRate = getValidEconomyRate();
    
    newPlayer->performanceIndex = (newPlayer->battingAverage * newPlayer->strikeRate) / 100.0;

    newPlayer->next = NULL;

   
    if (playerHead == NULL) {
        playerHead = newPlayer;
    } else {
        Player *temp = playerHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newPlayer;
    }

  
    team *tempTeam = *teamHead;
    team *foundTeam = NULL;
    while (tempTeam != NULL) {
        if (strcmp(tempTeam->teamName, newPlayer->teamName) == 0) {
            foundTeam = tempTeam;
            break;
        }
        tempTeam = tempTeam->next;
    }

    
    if (foundTeam != NULL) {
        foundTeam->totalPlayers++;
        foundTeam->averageBattingStrikeRate =
            ((foundTeam->averageBattingStrikeRate * (foundTeam->totalPlayers - 1)) + newPlayer->strikeRate) /
            foundTeam->totalPlayers;
    } else {
       
        static int teamIDCounter = 100;
        team *newTeam = createTeamNode(teamIDCounter++, newPlayer->teamName, 1, newPlayer->strikeRate);

        newTeam->next = *teamHead;
        *teamHead = newTeam;
    }

    printf("\n Player '%s' added successfully to team '%s'!\n", newPlayer->name, newPlayer->teamName);

    return playerHead;
}


void displayTeamsByAverageStrikeRate(team *teamHead) {
    if (teamHead == NULL) {
        printf("No teams found!\n");
        return;
    }

    
    team *sortedList = NULL, *temp = teamHead;
    while (temp != NULL) {
        team *newNode = createTeamNode(temp->teamID, temp->teamName,
                                       temp->totalPlayers, temp->averageBattingStrikeRate);

        newNode->next = sortedList;
        sortedList = newNode;

        temp = temp->next;
    }

    for (team *i = sortedList; i != NULL; i = i->next) {
        for (team *j = i->next; j != NULL; j = j->next) {
            if (j->averageBattingStrikeRate > i->averageBattingStrikeRate) {
                // Swap all data fields
                int tempID = i->teamID;
                char tempName[50];
                strcpy(tempName, i->teamName);
                int tempPlayers = i->totalPlayers;
                float tempAvgSR = i->averageBattingStrikeRate;

                i->teamID = j->teamID;
                strcpy(i->teamName, j->teamName);
                i->totalPlayers = j->totalPlayers;
                i->averageBattingStrikeRate = j->averageBattingStrikeRate;

                j->teamID = tempID;
                strcpy(j->teamName, tempName);
                j->totalPlayers = tempPlayers;
                j->averageBattingStrikeRate = tempAvgSR;
            }
        }
    }

  
    printf("\n===============================================================================\n");
    printf("Teams Sorted by Average Batting Strike Rate\n");
    printf("===============================================================================\n");
    printf("%-10s %-25s %-15s %-20s\n", "Team ID", "Team Name", "Total Players", "Average SR");
    printf("-------------------------------------------------------------------------------\n");

    team *ptr = sortedList;
    while (ptr != NULL) {
        printf("%-10d %-25s %-15d %-20.2f\n",
               ptr->teamID, ptr->teamName, ptr->totalPlayers, ptr->averageBattingStrikeRate);
        ptr = ptr->next;
    }

    printf("===============================================================================\n");
}




void displayTopKPlayersByRole(Player *playerHead, team *teamHead) {
    int teamID, K;
    char roleChoice[20];

    printf("\nChoice 4  Display Top K Players of a Specific Team by Role\n");
   
     teamID = getValidTeamID();

  
    team *tempTeam = teamHead;
    char teamName[50];
    int foundTeam = 0;
    while (tempTeam != NULL) {
        if (tempTeam->teamID == teamID) {
            strcpy(teamName, tempTeam->teamName);
            foundTeam = 1;
            break;
        }
        tempTeam = tempTeam->next;
    }

    if (!foundTeam) {
        printf(" Invalid Team ID.\n");
        return;
    }
    getValidRoleChoice(roleChoice);

       

    
    K = getValidPlayerCount();

   
    Player *temp = playerHead;
    Player *filtered[100];
    int count = 0;

    while (temp != NULL) {
        if (strcmp(temp->teamName, teamName) == 0 &&
            strcasecmp(temp->role, roleChoice) == 0) {
            filtered[count++] = temp;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("No players found for this role in team %s.\n", teamName);
        return;
    }

    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (filtered[j]->performanceIndex > filtered[i]->performanceIndex) {
                Player *tempPlayer = filtered[i];
                filtered[i] = filtered[j];
                filtered[j] = tempPlayer;
            }
        }
    }

    if (K > count) K = count;

    
    printf("\nTop %d %ss of Team %s:\n", K, roleChoice, teamName);
    printf("====================================================================================\n");
    printf("ID\tName\t\tRole\t\tRuns\tAvg\tSR\tWkts\tER\tPerf.Index\n");
    printf("====================================================================================\n");

    for (int i = 0; i < K; i++) {
        Player *p = filtered[i];
        printf("%d\t%-15s%-15s%d\t%.1f\t%.1f\t%d\t%.1f\t%.2f\n",
               p->playerID,
               p->name,
               p->role,
               p->totalRuns,
               p->battingAverage,
               p->strikeRate,
               p->wicketsTaken,
               p->economyRate,
               p->performanceIndex);
    }
    printf("====================================================================================\n");
}


void displayPlayersByRoleAcrossTeams(Player *playerHead) {
    
    char selectedRole[20];

  
   

    getValidRoleChoice(selectedRole);
    

    printf("\nAll %ss of all teams:\n", selectedRole);
    printf("==========================================================================================================\n");
    printf("ID\tName\t\tTeam\t\tRole\t\tRuns\tAvg\tSR\tWkts\tER\tPerf.Index\n");
    printf("==========================================================================================================\n");

    
    Player *temp = playerHead;
    int count = 0;

    while (temp != NULL) {
        if (strcmp(temp->role, selectedRole) == 0) {
            printf("%d\t%-15s%-15s%-15s%d\t%.1f\t%.1f\t%d\t%.1f\t%.2f\n",
                   temp->playerID,
                   temp->name,
                   temp->teamName,
                   temp->role,
                   temp->totalRuns,
                   temp->battingAverage,
                   temp->strikeRate,
                   temp->wicketsTaken,
                   temp->economyRate,
                   temp->performanceIndex);
            count++;
        }
        temp = temp->next;
    }

    printf("======================================================================================\n");

    if (count == 0)
        printf("No players found for role: %s\n", selectedRole);
    else
        printf("Total %s(s): %d\n", selectedRole, count);
}





int main(){

    Player *playerHead = initializePlayerList();
    team *teamHead = initializeTeamList(playerHead);

    printf("==============================================================================\n");
    printf("ICC ODI Player Performance Analyzer\n");
    printf("==============================================================================\n");
    printf("\n");
    printf("1. Add Player to Team\n");
    printf("2. Display Players of a Specific Team\n");
    printf("3. Display Teams by Average Batting Strike Rate\n");
    printf("4. Display Top K Players of a Specific Team by Role\n");
    printf("5. Display all Players of specific role Across All Teams by performance index\n");
    printf("6. Exit\n");
    printf("\n");
    printf("==============================================================================\n");
    printf("\n");






    while(1){
        int choice;
        choice = getValidChoice();
        int teamID;
        switch(choice){
            case 1:
                //addPlayerToTeam();
                 playerHead = addPlayerToTeam(playerHead, &teamHead);
                
                break;
            case 2:
                //displayPlayersOfTeam();
                 teamID = getValidTeamID();
                displayPlayersOfTeamByID(playerHead,teamHead, teamID);
                break;
               
            case 3:
                //displayTeamsByAverageStrikeRate();
                displayTeamsByAverageStrikeRate(teamHead);
                break;
            case 4:
                //displayTopKPlayersByRole();
                displayTopKPlayersByRole(playerHead, teamHead);
                break;
            case 5:
                //displayPlayersByRoleAcrossTeams();
                displayPlayersByRoleAcrossTeams(playerHead);
                break;
            case 6:
                printf("Exiting the program\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                
        }
    }
    return 0;
}



//gcc performanceManagement.c -o one