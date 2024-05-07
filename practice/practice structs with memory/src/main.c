#include <usart.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int gargenPlot;
} VEGETABLE;

typedef struct {
    char* make;
    char* model;
    int year;
} CAR;

int main() {
    //enable serial communication
    initUSART();

    /*
    VEGETABLE* vegPointerArray[5];

    char data[5][15] = { "chives", "carrot", "broccoli", "pepper", "corn"};

    for (int i = 0; i < 5; i++){
        vegPointerArray[i] = malloc(sizeof(VEGETABLE));
        vegPointerArray[i]->name = malloc(sizeof(data[i]) + 1);
        strcpy(vegPointerArray[i]->name, data[i]); 
        vegPointerArray[i]->gargenPlot = i + 1;
        printf("vegetable name: %s,  plot: %d \n", (*vegPointerArray[i]).name, (*vegPointerArray[i]).gargenPlot);
    }
    */

    char carMakes[3][15] = {"Toyota", "Honda", "Ford"};
    char carModels[3][15] = {"Land Cruiser", "Accord", "Focus"};
    int  carYears[3] = {2011, 2001, 2005};

    CAR* carPointerArray[3];

    for (int i = 0; i < 3; i++){
        carPointerArray[i] = malloc(sizeof(CAR));
        //short notation
        carPointerArray[i]->make = malloc(sizeof(carMakes[i]) + 1);
        //full notation
        (*carPointerArray[i]).model = malloc(sizeof(carModels[i]) + 1);

        strcpy(carPointerArray[i]->make, carMakes[i]);
        strcpy((*carPointerArray[i]).model, carModels[i]);
        (*carPointerArray[i]).year = carYears[i];

        printf("Car: %s %s, produced in %d \n", carPointerArray[i]->make,carPointerArray[i]->model,carPointerArray[i]->year);

    }

    free(carPointerArray);
    
    
};