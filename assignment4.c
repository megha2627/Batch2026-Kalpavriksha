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
int calculateCellValue(int numberOfRows,int numberOfColumns){
    int cellValue = rand() % 256;
    return cellValue;
}


//rotating the matrix by 90 degree clockwise
void rotatingMatrix(int sizeOfArray,int** matrix){
    for (int numberOfRows = 0; numberOfRows< sizeOfArray;numberOfRows++){
        for (int numberOfColumns = numberOfRows; numberOfColumns < sizeOfArray;numberOfColumns++){
            int temp=*(*(matrix+numberOfRows)+numberOfColumns);
            *(*(matrix+numberOfRows)+numberOfColumns)=*(*(matrix+numberOfColumns)+numberOfRows);
            *(*(matrix+numberOfColumns)+numberOfRows)=temp;
        }
    }

    for(int numberOfRows = 0; numberOfRows < sizeOfArray;numberOfRows++){
        for (int numberOfColumns= 0; numberOfColumns < sizeOfArray/2;numberOfColumns++){
            int temp=*(*(matrix+numberOfRows)+numberOfColumns);
            *(*(matrix+numberOfRows)+numberOfColumns)=*(*(matrix+numberOfRows)+(sizeOfArray-1-numberOfColumns));
            *(*(matrix+numberOfRows)+(sizeOfArray-1-numberOfColumns))=temp;
            
        }
        
    }
}



//applying the 3*3 filter on the rotating matrix
int filterMatrix(int sizeOfArray,int** matrix,int numberOfRows,int numberOfColumns){
    int directions[][2]={{-1,-1},{-1,0},{-1,1},
                        {0,-1},{0,0},{0,1},
                        {1,-1},{1,0},{1,1}};

    int sum=0;
    int count=0;
    for (int k = 0; k < 9;k++){
        int i1 = directions[k][0] + numberOfRows;
        int i2 = directions[k][1] + numberOfColumns;
        
        if(i1<0 || i1>=sizeOfArray || i2<0 || i2>=sizeOfArray){
            continue;
        }
        else{
            sum=sum+*(*(matrix+i1)+i2);
            count++;
        }
    }
   
    return sum / count;
}






int main(){
    int sizeOfArray;
    sizeOfArray = calculateSize();
    srand(time(NULL));
    int **matrix = malloc(sizeOfArray * sizeof(int*));
    for (int numberOfRows = 0; numberOfRows < sizeOfArray; numberOfRows++) {
        matrix[numberOfRows] = malloc(sizeOfArray * sizeof(int));
    }
    for (int numberOfRows = 0; numberOfRows < sizeOfArray;numberOfRows++){
        for (int numberOfColumns = 0; numberOfColumns < sizeOfArray;numberOfColumns++){
            int cellValue;
            cellValue = calculateCellValue(numberOfRows,numberOfColumns);
            *(*(matrix+numberOfRows)+numberOfColumns) = cellValue; 
        }
    }

    //now printing the original matrix
    printf("Original Matrix:\n");
    for (int numberOfRows = 0; numberOfRows < sizeOfArray;numberOfRows++){
        for (int numberOfColumns = 0; numberOfColumns < sizeOfArray;numberOfColumns++){
            printf("%d ", *(*(matrix+numberOfRows)+numberOfColumns));
        }
        printf("\n");
    }
    printf("\n");

    //now rotating the matrix by 90 degree clockwise
    rotatingMatrix(sizeOfArray, matrix);
     

    //now printing the rotated matrix
    printf("Rotated Matrix:\n");
    for (int numberOfRows = 0; numberOfRows < sizeOfArray;numberOfRows++){
        for (int numberOfColumns = 0; numberOfColumns < sizeOfArray;numberOfColumns++){
            printf("%d ", *(*(matrix+numberOfRows)+numberOfColumns));
        }
        printf("\n");
    }
     printf("\n");



    //now applying the 3*3 filter on the rotating matrix
     for (int numberOfRows = 0; numberOfRows < sizeOfArray;numberOfRows++){
        for (int numberOfColumns= 0; numberOfColumns < sizeOfArray;numberOfColumns++){
            int newValue = filterMatrix(sizeOfArray, matrix, numberOfRows, numberOfColumns); 
            *(*(matrix+numberOfRows)+numberOfColumns) = newValue; 
           
        }
        
    }

    //now printing the final matrix after applying filter
    printf("Final Matrix after applying 3x3 filter:\n");
    for (int numberOfRows = 0; numberOfRows < sizeOfArray;numberOfRows++){
        for (int numberOfColumns = 0; numberOfColumns< sizeOfArray;numberOfColumns++){
            printf("%d ", *(*(matrix+numberOfRows)+numberOfColumns));
        }
        printf("\n");
    }

}