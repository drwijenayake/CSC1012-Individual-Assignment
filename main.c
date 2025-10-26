#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310
#define MAX_VEHICLES 3

//global variables
int cityCount = 0;
int deliveryCount = 0;

//global arrays
char cityNames[MAX_CITIES][50];
int distanceMatrix[MAX_CITIES][MAX_CITIES];

//delivery arrays
int srcList[MAX_DELIVERIES];
int destList[MAX_DELIVERIES];
float weightList[MAX_DELIVERIES];
float distanceList[MAX_DELIVERIES];
float costList[MAX_DELIVERIES];
float fuelUsedList[MAX_DELIVERIES];
float fuelCostList[MAX_DELIVERIES];
float totalCostList[MAX_DELIVERIES];
float profitList[MAX_DELIVERIES];
float chargeList[MAX_DELIVERIES];
float timeList[MAX_DELIVERIES];


//vehicle arrays
int vehicleTypeList[MAX_DELIVERIES];
char vehiclenames[MAX_VEHICLES][20];
int capacity[MAX_VEHICLES];
int ratePerKm[MAX_VEHICLES];
int avgSpeed[MAX_VEHICLES];
int fuelEfficiency[MAX_VEHICLES];


//function declarations
void manageCities();
void printCityIndices();
void manageDistances();
void addVehicleData();
void addDelivery();
void deliveryCalculations();

//file handling
void loadRoutes();
void saveRoutes();
void loadDeliveries();
void saveDeliveries();

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

            case 2:
                    manageDistances();
                    break;

            case 3:
                    addVehicleData();
                    break;

            case 4:
                    addDelivery();
                    break;

            case 5:
                    deliveryCalculations();
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
                    int l,m,k,p;

                    for(l=index1-1; l<cityCount-1; l++){
                        p=0;                                        //assigning the above name to the below index in the cityNames array
                        while ((cityNames[l][p] = cityNames[l + 1][p]) != '\0') {
                            p++;
                        }
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
                    cityCount--;
                    printf("City removed successfully!\n");

                    break;

            case 4:
                    printCityIndices();
                    break;

            case 5:
                    break;

        }

      } while (choice!=5);


}

void printCityIndices(){
    int n;
    for(n=0; n<cityCount; n++){
        printf("%d. %s\n",n+1, cityNames[n]);
    }
}

void manageDistances()
{
    int choice;
    do{
        printf("Enter choice: \n");

        printf("1. Add distance. \n");
        printf("2. Edit distance. \n");
        printf("3. Display distance table. \n");
        printf("4. Exit to main menu. \n");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                    int s,d,distance;
                    printf("Enter the source city index (1-%d) \n",cityCount);
                    scanf("%d",&s);
                    printf("Enter the destination city index (1-%d)", cityCount);
                    scanf("%d",&d);
                    if(s==d){
                        distanceMatrix[s][d]=distanceMatrix[d][s]=0;
                    }
                    else{
                        printf("Enter the distance between %s and %s in km (eg: 150)",cityNames[s],cityNames[d]);
                        scanf("%d",&distance);
                        distanceMatrix[s][d]=distance;
                        distanceMatrix[d][s]=distance;
                    }
                    break;

            case 2:
                    int s1,d1,distance1;
                    printf("Enter the source city index (1-%d) \n",cityCount);
                    scanf("%d",&s1);
                    printf("Enter the destination city index (1-%d)", cityCount);
                    scanf("%d",&d1);
                    if(s==d){
                        distanceMatrix[s1][d1]=distanceMatrix[d1][s1]=0;
                    }
                    else{
                        printf("Enter the new distance between %s and %s in km (eg: 200)",cityNames[s1],cityNames[d1]);
                        scanf("%d",&distance1);
                        distanceMatrix[s1][d1]=distance1;
                        distanceMatrix[d1][s1]=distance1;
                    }
                    break;

            case 3:
                    int  k, l, m;
                    printf("\t       ");
                    for(k=0; k<cityCount; k++){
                        printf("%-15s",cityNames[k]);
                    }
                    printf("\n");
                    for(l=0; l<cityCount; l++){
                        printf("%-15s",cityNames[l]);
                        for(m=0; m<cityCount; m++){
                            printf("%-15d", distanceMatrix[l][m]);
                        }
                        printf("\n");
                    }
                    break;

            case 4:
                    break;
        }
    } while(choice!=4);
}

//delivery functions


void addVehicleData(){
    vehicleTypeList[0] = 1;
    strcpy(vehiclenames[0], "Van");
    capacity[0] = 1000;
    ratePerKm[0] = 30;
    avgSpeed[0] = 60;
    fuelEfficiency[0] = 12;


    vehicleTypeList[1] = 2;
    strcpy(vehiclenames[1], "Truck");
    capacity[1] = 5000;
    ratePerKm[1] = 40;
    avgSpeed[1] = 50;
    fuelEfficiency[1] = 6;


    vehicleTypeList[2] = 3;
    strcpy(vehiclenames[2], "Lorry");
    capacity[2] = 10000;
    ratePerKm[2] = 80;
    avgSpeed[2] = 45;
    fuelEfficiency[2] = 4;
    printf("Vehicle data added successfully\n");
}



void addDelivery(){

    printf("Available city indices:\n");
    printCityIndices();
    printf("Enter source Index:\n");
    scanf("%d",&srcList[deliveryCount]);
    printf("Enter destination city index: \n");
    scanf("%d",&destList[deliveryCount]);
    if (srcList[deliveryCount] == destList[deliveryCount]){
        printf("Invalid city selection. \n");
        return;
    }
    printf("Enter package weight (kg): ");
    scanf("%f", &weightList[deliveryCount]);
    printf("Select vehicle type:\n");
    printf("1. Van \n");
    printf("2. Truck \n");
    printf("3. Lorry \n");
    printf("Enter choice: ");
    scanf("%d", &vehicleTypeList[deliveryCount]);

    int v = vehicleTypeList[deliveryCount] - 1;
    if (weightList[deliveryCount] > capacity[v]) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    int d = distanceMatrix[srcList[deliveryCount]][destList[deliveryCount]];
    if (d <= 0) {
        printf("Distance not set between the selected cities.\n");
        return;
    }
    printf("Data uploaded\n");

}

void deliveryCalculations(){
    int v= vehicleTypeList[deliveryCount]-1;
    if (weightList[deliveryCount] > capacity[v]) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    int d = distanceMatrix[srcList[deliveryCount]][destList[deliveryCount]];
    if (d <= 0) {
        printf("Distance not set between selected cities!\n");
        return;
    }

    float w = weightList[deliveryCount];
    float rate = ratePerKm[v];
    float spd = avgSpeed[v];
    float eff = fuelEfficiency[v];

    distanceList[deliveryCount] = d;
    costList[deliveryCount] = d * rate * (1 + (w / 10000.0));
    fuelUsedList[deliveryCount] = d / eff;
    fuelCostList[deliveryCount] = fuelUsedList[deliveryCount] * FUEL_PRICE;
    totalCostList[deliveryCount] = costList[deliveryCount] + fuelCostList[deliveryCount];
    profitList[deliveryCount] = costList[deliveryCount] * 0.25;
    chargeList[deliveryCount] = totalCostList[deliveryCount] + profitList[deliveryCount];
    timeList[deliveryCount] = d / spd;

    printf("\n=== DELIVERY SUMMARY ===\n");
    printf("From: %s\nTo: %s\nDistance: %d km\nVehicle: %s\nWeight: %.2f kg\n", cityNames[srcList[deliveryCount]], cityNames[destList[deliveryCount]], d, vehiclenames[v], w);
    printf("Base Cost: %.2f\nFuel Used: %.2f L\nFuel Cost: %.2f\nTotal Cost: %.2f\nProfit: %.2f\nCustomer Charge: %.2f\nEstimated Time: %.2f hours\n",
           costList[deliveryCount], fuelUsedList[deliveryCount], fuelCostList[deliveryCount],
           totalCostList[deliveryCount], profitList[deliveryCount], chargeList[deliveryCount], timeList[deliveryCount]);
    printf("=========================\n");

    deliveryCount++;
}


//file handling functions
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

void loadDeliveries() {
    FILE *fp = fopen("deliveries.txt", "r");
    if (fp == NULL) {
        deliveryCount = 0;
        return;
    }
    fscanf(fp, "%d", &deliveryCount);
    for (int i = 0; i < deliveryCount; i++) {
        fscanf(fp, "%d %d %f %d %f %f %f %f %f %f %f %f",
               &srcList[i], &destList[i], &weightList[i], &vehicleTypeList[i],
               &distanceList[i], &costList[i], &fuelUsedList[i],
               &fuelCostList[i], &totalCostList[i], &profitList[i],
               &chargeList[i], &timeList[i]);
    }
    fclose(fp);
}

void saveDeliveries() {
    FILE *fp = fopen("deliveries.txt", "w");
    if (fp == NULL) {
        printf("Error saving deliveries!\n");
        return;
    }
    fprintf(fp, "%d\n", deliveryCount);
    for (int i = 0; i < deliveryCount; i++) {
        fprintf(fp, "%d %d %.2f %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
                srcList[i], destList[i], weightList[i], vehicleTypeList[i],
                distanceList[i], costList[i], fuelUsedList[i],
                fuelCostList[i], totalCostList[i], profitList[i],
                chargeList[i], timeList[i]);
    }
    fclose(fp);
}
