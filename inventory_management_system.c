#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//gcc inventory_management_system.c -o inventory_management_system
// ./inventory_management_system


 struct Product{
        int ProductID;
        char ProductName[50];
        float Price;
        int Quantity;

        
};

//check the valid product for different crud operations
int inputProductId(){
    char input[50];
    while(1){
        printf("Product ID: ");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n'){
                input[i]='\0';
                break;
            }
        }
        for(int i=0; input[i]!='\0'; i++){
            if(!isdigit(input[i])){
                printf("Entered value is not a number. Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            return atoi(input);
        }
    }
}

//get the intial number of products
int getNumberOfProducts(){
    char input[50];
    while(1){
        printf("Enter initial number of products:");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n' ){
                input[i]='\0';
                break;
            }
        
        }
        for (int i = 0; input[i] != '\0';i++){
            if(!isdigit(input[i])){
                printf("Entered value is not a number. Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            if(atoi(input)<0 || atoi(input)>100){
                printf("Number must be in range between 0 and 100. Please try again.\n");
            }
            else{
                return atoi(input);
            }
        }
    }
    
}


//get the  product Id
int getProductId(struct Product **inventory,int *numberOfProducts){
    char input[50];
    while(1){
        printf("Product ID:");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n' ){
                input[i]='\0';
                break;
            }
        
        }
        for (int i = 0; input[i] != '\0';i++){
            if(!isdigit(input[i])){
                printf("Entered value is not a number. Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            if(atoi(input)<0 || atoi(input)>10000){
                printf("Number must be in range between 0 and 10000. Please try again.\n");
            }
            else{
                for(int j=0;j<(*numberOfProducts);j++){
                    if(atoi(input)==(*(*inventory+j)).ProductID){
                        printf("Product ID already exists. Please enter a unique Product ID.\n");
                        valid = 0;
                        
                    }
                }
                if(valid==1){
                    return atoi(input);
                }
                
                
            }
        }
    }
    
}

//get the product name
void getProductName(char *dest){
    char input[100];
    
    while(1){
        printf("Product Name:");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n' ){
                input[i]='\0';
                break;
            }
        
        }
        for (int i = 0;  input[i] != '\0';i++){
            if(isdigit(input[i])){
                printf("Entered value is  a number. Please enter a character.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            if(strlen(input)<1 || strlen(input)>50){
                printf("Enter size must be in range between 1 and 50. Please try again.\n");
            }
            else{
                
                strcpy(dest, input);
               return;
                        }
        }
    }
    

}

// get the product price
float getProductPrice(){
    char input[50];
    while(1){
        printf("Product Price:");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n' ){
                input[i]='\0';
                break;
            }
        
        }
        for (int i = 0; input[i] != '\0';i++){
            if(!isdigit(input[i]) && input[i]!='.'){
                printf("Entered value is not a number. Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            if(atof(input)<0 || atof(input)>100000){
                printf("Number must be in range between 0 and 100000. Please try again.\n");
            }
            else{
                return atof(input);
            }
        }
    }
    
}


//get the product quantity
int getProductQuantity(){
    char input[50];
    while(1){
        printf("Product Quantity:");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
        for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n' ){
                input[i]='\0';
                break;
            }
        
        }
        for (int i = 0;  input[i] != '\0';i++){
            if(!isdigit(input[i])){
                printf("Entered value is not a number. Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            if(atoi(input)<0 || atoi(input)>1000000){
                printf("Number must be in range between 0 and 1000000. Please try again.\n");
            }
            else{
                return atoi(input);
            }
        }
    }
    
}

//get the choice of menu
int getChoiceOfMenu(){
    char input[50];
    while(1){
        printf("Enter your choice:");
        fgets(input, sizeof(input), stdin);
        int valid = 1;
         for(int i=0; input[i]!='\0'; i++){
            if(input[i]=='\n' ){
                input[i]='\0';
                break;
            }
        
        }
       
        for (int i = 0; input[i] != '\0';i++){
            if(!isdigit(input[i])){
                printf("Entered value is not a number. Please enter a valid number.\n");
                valid = 0;
                break;
            }
        }
        if(valid==1){
            if(atoi(input)<1 || atoi(input)>8){
                printf("Number must be in range between 1 and 8. Please try again.\n");
            }
            else{
                return atoi(input);
            }
        }
    }
    
}

//add the new product
void addNewProduct(struct Product **inventory,int *numberOfProducts){
    (*numberOfProducts)++;
    *inventory=realloc(*inventory,(*numberOfProducts)*sizeof(struct Product));
    (*(*inventory+(*numberOfProducts)-1)).ProductID = getProductId(inventory,numberOfProducts);
    getProductName((*(*inventory + *numberOfProducts - 1)).ProductName);

    (*(*inventory+*numberOfProducts-1)).Price = getProductPrice();
    (*(*inventory+*numberOfProducts-1)).Quantity = getProductQuantity();
    printf("\n");
    printf("new product details:\n");
    printf("Product ID: %d\n",(*(*inventory+*numberOfProducts-1)).ProductID);
    printf("Product Name: %s\n",(*(*inventory + *numberOfProducts-1)).ProductName);
    printf("Product Price: %.2f\n",(*(*inventory+*numberOfProducts-1)).Price);
    printf("Product Quantity: %d\n",(*(*inventory+*numberOfProducts-1)).Quantity);
    printf("Product added successfully!\n");
}

//view the all products
void viewAllProducts(struct Product **inventory,int *numberOfProducts){
    printf("========= PRODUCT LIST =========\n");
    if((*numberOfProducts)==0){
        printf("No products available in the inventory.\n");
        return;
    }
    for (int i = 0;i<*numberOfProducts;i++){
        printf("Product ID: %d | ",(*(*inventory+i)).ProductID);
        printf("Product Name: %s | ",(*(*inventory + i)).ProductName);
        printf("Product Price: %.2f |",(*(*inventory+i)).Price);
        printf("Product Quantity: %d | ",(*(*inventory+i)).Quantity);
        printf("\n");
    }
}

//update the quantity
void updateQuantity(struct Product **inventory,int *numberOfProducts){
    printf("Enter Product ID to update quantity:\n");
    int productId = inputProductId();
    for(int i=0;i<*numberOfProducts;i++){
        if((*(*inventory+i)).ProductID==productId){
          
            printf("Enter new quantity \n");
            int newQuantity = getProductQuantity();
            (*(*inventory+i)).Quantity=newQuantity;
            printf("Quantity updated successfully!\n");
            return;
        }
    }
    printf("Product not found!\n");
}

//search product by ID
void searchProductByID(struct Product **inventory,int *numberOfProducts){
    printf("Enter Product ID to search\n");
    int productId = inputProductId();
    for(int i=0;i<*numberOfProducts;i++){
        if((*(*inventory+i)).ProductID==productId){
            printf("Product found:\n");
            printf("Product ID: %d | ",(*(*inventory+i)).ProductID);
            printf("Product Name: %s | ",(*(*inventory + i)).ProductName);
            printf("Product Price: %.2f |",(*(*inventory+i)).Price);
            printf("Product Quantity: %d | ",(*(*inventory+i)).Quantity);
            printf("\n");
            return;
        }
    }
    printf("Product not found!\n");
}

//search product by name
void searchProductByName(struct Product **inventory,int *numberOfProducts){
    printf("Enter Product Name to search(partial allowed):\n");
    char productName[100];
    getProductName(productName);
    for(int i=0;i<*numberOfProducts;i++){
        if(strstr((*(*inventory+i)).ProductName,productName)!=NULL){
            printf("Product found:");
            printf("Product ID: %d | ",(*(*inventory+i)).ProductID);
            printf("Product Name: %s | ",(*(*inventory + i)).ProductName);
            printf("Product Price: %f |",(*(*inventory+i)).Price);
            printf("Product Quantity: %d | ",(*(*inventory+i)).Quantity);
            printf("\n");
            return;
        }
    }
    printf("Product not found!\n");
}

void searchProductByPriceRange(struct Product **inventory,int *numberOfProducts){
   printf("Enter Minimum Price\n ");
   float minimumPrice = getProductPrice();
    printf("Enter Maximum Price\n ");
    float maximumPrice = getProductPrice();


    for(int i=0;i<*numberOfProducts;i++){
        if((*(*inventory+i)).Price>=minimumPrice && (*(*inventory+i)).Price<=maximumPrice){
            printf("Product found:");
            printf("Product ID: %d | ",(*(*inventory+i)).ProductID);
            printf("Product Name: %s | ",(*(*inventory + i)).ProductName);
            printf("Product Price: %f |",(*(*inventory+i)).Price);
            printf("Product Quantity: %d | ",(*(*inventory+i)).Quantity);
            printf("\n");
            return;
        }
    }
    printf("Product not found!\n");
}

//delete the product
void deleteProduct(struct Product **inventory,int *numberOfProducts){

    printf("Enter Product ID to delete\n");
    int productId = inputProductId();
    for(int i=0;i<(*numberOfProducts);i++){
        if((*(*inventory+i)).ProductID==productId){
            for(int j=i;j<(*numberOfProducts)-1;j++){
                (*(*inventory+j))=(*(*inventory+j+1));
            }
            (*numberOfProducts)--;
            *inventory=realloc(*inventory,(*numberOfProducts)*sizeof(struct Product));
            printf("Product deleted successfully!\n");
            return;
        }
    }
    printf("Product not found!\n");
}



//display the inventory menu
void getInventoryMenu(struct Product **inventory,int *numberOfProducts){
    int choice;
    while(1){
       printf("\n==============================\n");
        printf("        INVENTORY MENU        \n");
        printf("==============================\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Quantity\n");
        printf("4. Search Product by ID\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Price Range\n");
        printf("7. Delete Product\n");
        printf("8. Exit\n");
        printf("\n");
        
        printf("Please enter your choice (1-8): ");
        scanf("%d",&choice);
        getchar(); // to consume the newline character after scanf

        switch(choice){
            case 1:
                // Add New Product
                addNewProduct(inventory,numberOfProducts);
                break;
            case 2:
                // View All Products
                viewAllProducts(inventory,numberOfProducts);
                break;
            case 3:
                // Update Quantity
                updateQuantity(inventory,numberOfProducts);
                break;
            case 4:
                // Search Product by ID
                searchProductByID(inventory,numberOfProducts);
                break;
            case 5:
                // Search Product by Name
                searchProductByName(inventory,numberOfProducts);
                break;
            case 6:
                // Search Product by Price Range
                searchProductByPriceRange(inventory,numberOfProducts);
                break;
            case 7:
                // Delete Product
                deleteProduct(inventory,numberOfProducts);
                break;
            case 8:
                printf("Freeing up memory successfully!\n");
                free(*inventory);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");

        }

    }
}



int main(){
    int numberOfProducts;
    numberOfProducts = getNumberOfProducts();

   
    struct Product *inventory=calloc(numberOfProducts,sizeof(struct Product));
    for (int i = 0;i<numberOfProducts;i++){
        printf("Entering details for product  %d:\n",i+1);
        (*(inventory+i)).ProductID = getProductId(&inventory,&numberOfProducts);
       
        getProductName((*(inventory + i)).ProductName);
        (*(inventory+i)).Price = getProductPrice();
        (*(inventory+i)).Quantity = getProductQuantity();
    }


    //display the inventory menu
    getInventoryMenu(&inventory,&numberOfProducts);

    //free up the used memory
    free(inventory);
    
    return 0;
}