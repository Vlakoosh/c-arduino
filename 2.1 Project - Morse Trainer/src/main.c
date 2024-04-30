#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <vellemanbuttons.h>
#include <vellemanleds.h>
#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 

//number of total characters with their morse code
#define NUM_OF_CHARACTERS 26

//countdown before a letter is shown. (shield LEDs are enabled one by one)
//This is so the user can get ready to look at morse code flashes
void countdown(){
  lightDownAllLeds();
  _delay_ms(1000);
  lightUpOneLed(3);
  _delay_ms(1000);
  lightUpOneLed(2);
  _delay_ms(1000);
  lightUpOneLed(1);
  _delay_ms(1000);
  lightUpOneLed(0);
  _delay_ms(1000);
  lightDownAllLeds();
  _delay_ms(1000);
}

//takes a letter number and displays it as morse code (as LED flashes on the shield)
void flashLetter(int letter, int flashes[], int length){
  for (int i = 0; i < length; i++){
    if (flashes[i])
    {
      lightUpAllLeds();
      _delay_ms(1000);
      lightDownAllLeds();
    }
    else {
      lightUpAllLeds();
      _delay_ms(300);
      lightDownAllLeds();
    }
    _delay_ms(200);
  }
}

int main() {
  //create an array of pointers that will point to arrays of int of length 4
  int *alphabet[NUM_OF_CHARACTERS];
  //create an array of morse code lengthsin the same order as the corresponding characters
  int lengths[NUM_OF_CHARACTERS] = {2,4,4,3,1,4,3,4,2,4,3,4,2,2,3,4,4,3,3,1,3,4,3,4,4,4};

  //declare all letter morse code values
  int a[] = {0,1};
  int b[] = {1,0,0,0};
  int c[] = {1,0,1,0};
  int d[] = {1,0,0};
  int e[] = {0};
  int f[] = {0,0,1,0};
  int g[] = {1,1,0,};
  int h[] = {0,0,0,0};
  int i[] = {0,0};
  int j[] = {0,1,1,1};
  int k[] = {1,0,1};
  int l[] = {0,1,0,0};
  int m[] = {1,1};
  int n[] = {1,0};
  int o[] = {1,1,1};
  int p[] = {0,1,1,0};
  int q[] = {1,1,0,1};
  int r[] = {0,1,0};
  int s[] = {0,0,0};
  int t[] = {1};
  int u[] = {0,0,1};
  int v[] = {0,0,0,1};
  int w[] = {0,1,1};
  int x[] = {1,0,0,1};
  int y[] = {1,0,1,1};
  int z[] = {1,1,0,0};
  //declare all numbers morse code values
  int n0[] = {};
  int n1[] = {};
  int n2[] = {};
  int n3[] = {};
  int n4[] = {};
  int n5[] = {};
  int n6[] = {};
  int n7[] = {};
  int n8[] = {};
  int n9[] = {};

  //assign values to the pointer array.
  //set all letters in alphabet array manually.
  alphabet[0] = a;
  alphabet[1] = b;
  alphabet[2] = c;
  alphabet[3] = d;
  alphabet[4] = e;
  alphabet[5] = f;
  alphabet[6] = g;
  alphabet[7] = h;
  alphabet[8] = i;
  alphabet[9] = j;
  alphabet[10] = k;
  alphabet[11] = l;
  alphabet[12] = m;
  alphabet[13] = n;
  alphabet[14] = o;
  alphabet[15] = p;
  alphabet[16] = q;
  alphabet[17] = r;
  alphabet[18] = s;
  alphabet[19] = t;
  alphabet[20] = u;
  alphabet[21] = v;
  alphabet[22] = w;
  alphabet[23] = x;
  alphabet[24] = y;
  alphabet[25] = z;

  //initialize serial communication
  initUSART();

  //enable LEDs and buttons
  enableAllLeds();
  enableButton(1);
  enableButton(2);
  enableButton(3);

  //initial countdown/animation
  countdown();

  //begin quiz here; repeat 3 times
  for (int i = 0; i < 5; i++)
  {
    //change the random number generator seed to noise from analog pin 0
   // srand(analogRead(0));
    //set a random number to display as morse code
    int letterNumber = rand() % NUM_OF_CHARACTERS;
    

    //display the letter in morse code on the LEDs
    flashLetter(letterNumber, alphabet[letterNumber], lengths[letterNumber]);
    _delay_ms(1000);

    //change the random number generator seed to noise from analog pin 1
   // srand(analogRead(1));

    //create an array of answers to choose from
    int answers[] = {0, 0, 0};

    //set the answers randomly

    answers[rand() % 3] = letterNumber;
    printf("%d + %c%c%c", letterNumber, (char) answers[0] + 97, (char) answers[1] + 97, (char) answers[2] + 97);
    for (int i = 0; i < 3; i++)
    {
      if (answers[i] == 0)
      {
        answers[i] = rand() % NUM_OF_CHARACTERS;
      }
    }

    printf("what was the displayed character?");
    printf("Answer 1: %c   |   Answer 2: %c   | Answer 3: %c ", (char) answers[0] + 97, (char) answers[1] + 97, (char) answers[2] + 97);

    //wait until a button is pressed
    int isAnswered = 0;
    while (isAnswered == 0)
    {
      if (buttonPushed(1) && answers[0] == letterNumber)
      {
        isAnswered = 1;
      }
      else if (buttonPushed(2) && answers[1] == letterNumber)
      {
        isAnswered = 1;
      }
      else if (buttonPushed(3) && answers[2] == letterNumber)
      {
        isAnswered = 1;
      } else if (buttonPushed(1) || buttonPushed(2) || buttonPushed(3))
      {
        isAnswered = -1;
      }
    }
    if (isAnswered > 0) {
      printf("\n\n");
      printf("You answered correctly!");
    } else {
      printf("\n\n");
      printf("You answered wrong!! the correct answer is %c ", (char)letterNumber + 97);
    }
  }
  return 0;  
}

