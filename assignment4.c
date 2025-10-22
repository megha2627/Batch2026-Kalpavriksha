#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

//here we will calculate the size of array between 2 to 10
int calculateSize(){
    char sizeOfArray[50];
    while(1){
        printf("Enter the size of the array :\n ");
        fgets(sizeOfArray, sizeof(sizeOfArray), stdin);
        
        int valid = 1;
        if(sizeOfArray[0]=='-'){
            printf("enter the positive value\n");
            
            continue;
        }
         for(int i=0; sizeOfArray[i]!='\0'; i++){
            if(sizeOfArray[i]=='\n' ){
                sizeOfArray[i]='\0';
                break;
            }
           
        }
        for(int i=0; sizeOfArray[i]!='\0'; i++){
            if(!isdigit(sizeOfArray[i])){
                printf("Invalid input! Please enter a numeric value.\n");
                valid = 0;
                break;
            }
           
        }
        if(valid==1){
            int value = atoi(sizeOfArray);
            if(value<2 || value>10){
                printf("array dimension value must be between 2 and 10.\n");
                continue;
            }
            else{
                return value;
            }
        }
        
    }
    
}


//here we are calculate the vlaue of each cell between the range of 0 and 255
int calculateCellValue(int row,int column){
    int cellValue = rand() % 256;
    return cellValue;
}


//rotating the matrix by 90 degree clockwise
void rotatingMatrix(int sizeOfArray,int** matrix){
    for (int row = 0; row< sizeOfArray;row++){
        for (int column = row; column < sizeOfArray;column++){
            int temp=*(*(matrix+row)+column);
            *(*(matrix+row)+column)=*(*(matrix+column)+row);
            *(*(matrix+column)+row)=temp;
        }
    }

    for(int row = 0; row < sizeOfArray;row++){
        for (int column= 0; column < sizeOfArray/2;column++){
            int temp=*(*(matrix+row)+column);
            *(*(matrix+row)+column)=*(*(matrix+row)+(sizeOfArray-1-column));
            *(*(matrix+row)+(sizeOfArray-1-column))=temp;
            
        }
        
    }
}



//applying the 3*3 filter on the rotating matrix
int filterMatrix(int sizeOfArray,int** matrix,int row,int column){
    int directions[][2]={{-1,-1},{-1,0},{-1,1},
                        {0,-1},{0,0},{0,1},
                        {1,-1},{1,0},{1,1}};

    int sumOfAdjacentNeighbour=0;
    int count=0;
    for (int k = 0; k < 9;k++){
        int modifiedRow = directions[k][0] + row;
        int modifiedColumn = directions[k][1] + column;
        
        if(modifiedRow<0 || modifiedRow>=sizeOfArray || modifiedColumn<0 || modifiedColumn>=sizeOfArray){
            continue;
        }
        else{
            sumOfAdjacentNeighbour=sumOfAdjacentNeighbour+*(*(matrix+modifiedRow)+modifiedColumn);
            count++;
        }
    }
   
    return sumOfAdjacentNeighbour / count;
}






int main(){
    int sizeOfArray;
    sizeOfArray = calculateSize();
    srand(time(NULL));
    int **matrix = malloc(sizeOfArray * sizeof(int*));
    for (int row = 0; row < sizeOfArray; row++) {
        matrix[row] = malloc(sizeOfArray * sizeof(int));
    }
    for (int row = 0; row < sizeOfArray;row++){
        for (int column = 0; column < sizeOfArray;column++){
            int cellValue;
            cellValue = calculateCellValue(row,column);
            *(*(matrix+row)+column) = cellValue; 
        }
    }

    //now printing the original matrix
    printf("Original Matrix:\n");
    for (int row = 0; row < sizeOfArray;row++){
        for (int column = 0; column < sizeOfArray;column++){
            printf("%d ", *(*(matrix+row)+column));
        }
        printf("\n");
    }
    printf("\n");

    //now rotating the matrix by 90 degree clockwise
    rotatingMatrix(sizeOfArray, matrix);
     

    //now printing the rotated matrix
    printf("Rotated Matrix:\n");
    for (int row = 0; row < sizeOfArray;row++){
        for (int column = 0; column < sizeOfArray;column++){
            printf("%d ", *(*(matrix+row)+column));
        }
        printf("\n");
    }
     printf("\n");



    //now applying the 3*3 filter on the rotating matrix
     for (int row = 0; row < sizeOfArray;row++){
        for (int column= 0; column < sizeOfArray;column++){
            int newValue = filterMatrix(sizeOfArray, matrix, row, column); 
            *(*(matrix+row)+column) = newValue; 
           
        }
        
    }

    //now printing the final matrix after applying filter
    printf("Final Matrix after applying 3x3 filter:\n");
    for (int row = 0; row < sizeOfArray;row++){
        for (int column = 0; column< sizeOfArray;column++){
            printf("%d ", *(*(matrix+row)+column));
        }
        printf("\n");
    }

}