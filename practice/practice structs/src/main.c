#include <usart.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char make[15];
    char model[15];
    int year;
} CAR;

void printCar(CAR car){
  printf("make: %s, model: %s, year: %d \n", car.make, car.model, car.year);
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

  printCar(car1);
  printCar(car2);

  printCar(car3);
  printCar(car1);
}