#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vellemandisplay.h>
#include <usart.h>

#define BUTTON1 PC1
#define BUTTON2 PC2
#define BUTTON3 PC3
#define START_NUMBER 10
#define MAX_TAKE 3
#define MIN_TAKE 1
#define true 1
#define false 0

//TODO:
// - implement generateRandomValue()
// - implement flashTurn()
// - create the struct for statistics
// - implement displayStatistics()
//implement displayGameStatistics()

typedef struct {
  int matchesTaken;
} STATS;

typedef struct {
  int *matchesLeft[START_NUMBER];
} GAME;

int generateRandomValue(int min, int max){
  //generate a random value based off the clock value
  return 1;
}

void displayGameState(int takeNumber, char currentPlayer, int matchesLeft){
  //display the given stats
  int displayValue = takeNumber*1000 + matchesLeft;
  writeNumber(displayValue);
  //here display the displayValue with library
  //here display the player char on second led digit with library
}

void displayGameStateAndWait(int takeNumber, char currentPlayer, int matchesLeft, int delay_ms){
  //display the given stats
  int displayValue = takeNumber*1000 + matchesLeft;
  writeNumberAndWait(displayValue, delay_ms);
  //here display the displayValue with library
  //here display the player char on second led digit with library
}

void displayGameStatistics(GAME* game, STATS playerStats, STATS computerStats, int currentMove){
  //display the players and how many matches they took total
  //display the moves and how many matches were left at that move
  printf(" \n");
  printf("Total matches taken by the player: %d \n", playerStats.matchesTaken);
  printf("Total matches taken by the computer: %d \n", computerStats.matchesTaken);
  printf(" \n");
  printf("The game started with %d matches:\n", START_NUMBER);
  for (int i = 0; i < currentMove; i++)
  {
    printf("After move #%d, there were %d matches left \n", i+1, game->matchesLeft[i]);
  }
  
}

void flashWinner(char playerChar){
  flashTurn(playerChar);
}

void waitForButton(int BUTTON, int takeNumber, char currentPlayer, int matchesLeft){
  int pressed = false;
  while (!pressed){
    displayGameState(takeNumber, currentPlayer, matchesLeft);
    if (bit_is_clear(PINC, BUTTON))
    {
      pressed = true;
      displayGameStateAndWait(takeNumber, currentPlayer, matchesLeft, 200);
    }
    
  }
}

void flashTurn(char currentPlayer) {
  //flash the player turn letter on 4 digit display
  int displayNumber = 0;
  if (currentPlayer == 'P')
  {
    displayNumber = 1111;
  }
  else{
    displayNumber = 2222;
  }
  
  for (int i = 0; i < 3; i++)
  {
    writeNumberAndWait(displayNumber, 400);
    _delay_ms(400);
  } 
}

int clamp(int value, int min, int max){
  if (value > max)
  {
    return max;
  }

  if (value < min)
  {
    return min;
  }
  return value;
}

void initializeGame(){
  //enable button pins 1-3 as input
  DDRC &= ~(1 << BUTTON1);
  DDRC &= ~(1 << BUTTON2);
  DDRC &= ~(1 << BUTTON3);

  //enable pullup on buttons 1-3
  PORTC |= (1 << BUTTON1);
  PORTC |= (1 << BUTTON2);
  PORTC |= (1 << BUTTON3);

  //initialize serial communication and display leds
  initUSART();
  initDisplay();
}

int main() {
  initializeGame();

  int matchesLeft = START_NUMBER;
  char currentPlayer = 'P';

  int takeNumber = 2;

  GAME* game = malloc(sizeof(GAME));
  int currentMove = 0;

  STATS playerStats = {0};
  STATS computerStats = {0};  

  while(1){
    //player turn
    if (currentPlayer == 'P')
    {
      //delay before computer starts
      flashTurn(currentPlayer);

      int done = false; //0 lol
      while (!done)
      {
        displayGameState(takeNumber, currentPlayer, matchesLeft);  
        //check if button 1 is pressed
        if (bit_is_clear(PINC, BUTTON1))
        {
          takeNumber -= 1;
          takeNumber = clamp(takeNumber, MIN_TAKE, MAX_TAKE);
          displayGameStateAndWait(takeNumber, currentPlayer, matchesLeft, 200); 
        }
        //check if button 2 is pressed
        if (bit_is_clear(PINC, BUTTON3))
        {
          takeNumber += 1;
          takeNumber = clamp(takeNumber, MIN_TAKE, MAX_TAKE);
          displayGameStateAndWait(takeNumber, currentPlayer, matchesLeft, 200); 
        }

        //check if button 1 is pressed
        if (bit_is_clear(PINC, BUTTON2))
        {
          done = true;
        }
        
      }
      //adding taken matches to taken matches total of the player
      playerStats.matchesTaken += takeNumber;
      
      //update the total amount of matches
      matchesLeft -= takeNumber;
      currentPlayer = 'C';

      //save the amount of matches taken for a specific move in game/move statistics
      game->matchesLeft[currentMove] = matchesLeft;
      currentMove++;
    }
    //computer turn
    else if (currentPlayer == 'C')
    {
      //delay before computer starts
      flashTurn(currentPlayer);

      waitForButton(BUTTON2, takeNumber, currentPlayer, matchesLeft);

      //computer calculation for making the move
      takeNumber = (matchesLeft - 1) % (MAX_TAKE + 1);
      if (takeNumber == 0){
        takeNumber = generateRandomValue(MIN_TAKE, MAX_TAKE);
      }

      waitForButton(BUTTON2, takeNumber, currentPlayer, matchesLeft);

      //adding taken matches to taken matches total of the computer
      computerStats.matchesTaken += takeNumber;

      matchesLeft -= takeNumber;
      currentPlayer = 'P';

      //save the amount of matches taken for a specific move in game/move statistics
      game->matchesLeft[currentMove] = matchesLeft;
      currentMove++;
    }
    
    if (matchesLeft <= 1)
    {
      break;
    }
    
    displayGameState(takeNumber, currentPlayer, matchesLeft);
    
  }

  printf("game over");
  displayGameStatistics(game, playerStats, computerStats, currentMove);
  flashWinner(currentPlayer);
  
}