#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310

//global variables
int cityCount = 0;
int deliveryCount = 0;

//global arrays
char cityNames[MAX_CITIES][50];              // Store city names
int distanceMatrix[MAX_CITIES][MAX_CITIES];

//function declarations
void manageCities();
void manageDistances();
void loadRoutes();
void saveRoutes();


int main()
{
    loadRoutes();
    saveRoutes();

    int choice;
    do{
        printf("Enter choice: \n");
        printf("1. City Management.\n");
        printf("2. Distance Management.\n");
        printf("3. Vehicle Management.\n");
        printf("4. Delivery request handling.\n");
        printf("5. Cost, Time,  Fuel Calculations.\n");
        printf("6. Delivery records.\n");
        printf("7. Performance reports. \n");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                manageCities();
                break;

        }

    } while(choice!=8);

    return 0;
}

void manageCities(){
    int choice;
    do{

        printf("Enter choice: \n");
        printf("1. Add a new city.\n");
        printf("2. Rename a city.\n");
        printf("3. Remove a city. \n");
        printf("4. Display city indices.\n");
        printf("5. Exit to main menu. \n");
        scanf("%d",&choice);

        switch (choice){
            case 1:
                    printf("Enter City Name:\n");
                    scanf("%s",&cityNames[cityCount]);
                    int i;
                    for(i=0; i<cityCount; i++){
                        distanceMatrix[cityCount][i]=0; //assigning  the distance from the newly added city to all other cities as 0
                        distanceMatrix[i][cityCount]=0;
                    }
                    cityCount++;
                    printf("New city has been successfully added!");
                    break;

            case 2:
                    int index=0;
                    printf("Enter the city number to be renamed (1-%d): \n",cityCount);
                    scanf("%d",&index);
                    printf("Enter the new name: \n");
                    scanf("%s",&cityNames[index-1]);
                    printf("City renamed to %s successfully!",cityNames[index-1]);
                    break;

            case 3:
                    int index1;
                    printf("Enter the city number to be removed (1-%d): \n",cityCount);
                    scanf("%d",&index1);
                    int l,m,k;

                    for(l=index1-1; l<cityCount-1; l++){         //assigning the above name to the below index in the cityNames array
                        cityNames[l][50]=cityNames[l+1][50];
                    }
                    for(l=index1-1; l<cityCount-1; l++){               //assigning the above row distance to the below row distance in the distanceMatrix
                        for(m=0; m<cityCount-1; m++){
                            distanceMatrix[l][m]=distanceMatrix[l+1][m];
                        }
                    }

                    for(m=index1-1; m<cityCount-1; m++){               //assigning thw above column distances to the below column distances in the distanceMatrix
                        for(k=0; k<cityCount-1; k++ ){
                           distanceMatrix[k][m]=distanceMatrix[k][m+1];
                        }
                    }

                    printf("City removed successfully!\n");
                    break;

            case 4:
                    int n;
                    for(n=0; n<cityCount; n++){
                        printf("%d. %s\n",n+1, cityNames[n]);
                    }
                    break;

            case 5:
                    break;

        }

      } while (choice!=5);


}


//manageDistances(){



void loadRoutes() {
    FILE *fp = fopen("routes.txt", "r");
    if (fp == NULL) {
        printf("No routes.txt found. Starting with empty data.\n");
        cityCount = 0;
        return;
    }
    fscanf(fp, "%d", &cityCount);

    for (int i = 0; i < cityCount; i++) {
        fscanf(fp, "%s", cityNames[i]);
    }

    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            fscanf(fp, "%d", &distanceMatrix[i][j]);
        }
    }
    fclose(fp);
    printf("Routes loaded successfully.\n");
}

void saveRoutes() {
    FILE *fp = fopen("routes.txt", "w");
    if (fp == NULL) {
        printf("Error saving routes!\n");
        return;
    }
    fprintf(fp, "%d\n", cityCount);
    for (int i = 0; i < cityCount; i++) {
        fprintf(fp, "%s\n", cityNames[i]);
    }
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            fprintf(fp, "%d ", distanceMatrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    printf("Routes saved\n");
    fclose(fp);
}
