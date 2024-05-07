#include <usart.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char make[15];
  char model[15];
  int year;
} CAR;

typedef CAR GARAGE[10];

typedef struct {
  char name[20];
  int numberOfCars;
  GARAGE garage;
} DEALER;

void printCar(CAR car){
  printf("make: %s, model: %s, year: %d \n", car.make, car.model, car.year);
}

void printGarage (GARAGE garage, int numberOfCars){
  for (int i = 0; i < numberOfCars; i++ ){
    printf("make: %s, model: %s, year: %d \n", garage[i].make, garage[i].model, garage[i].year);
  }
}

printDealer(DEALER dealer) {
  printf("Dealer %s has the following %d cars: \n", dealer.name, dealer.numberOfCars);
  for (int i = 0; i < dealer.numberOfCars; i++ ){
    printf("make: %s, model: %s, year: %d \n", dealer.garage[i].make, dealer.garage[i].model, dealer.garage[i].year);
  }
}

int main() {
  //enable serial communication
  initUSART();

  CAR car1;

  strcpy(car1.make, "Toyota");
  strcpy(car1.model, "Century");
  car1.year = 1993;

  //make car with instant initialization  
  CAR car2 = {"Ferrari", "Testarossa", 1990};

  CAR car3 = car1;

  CAR car4 = {"Honda", "Civic", 1999};

  GARAGE garage1 = {car1, car2, car3, car4};

  DEALER dealer1 = {"Szymon", 4, {car1, car2, car3, car4}}; 

  printGarage(garage1, 4);
  printf("\n\n");

  printDealer(dealer1);
}