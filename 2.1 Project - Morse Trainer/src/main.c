#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <vellemanbuttons.h>
#include <vellemanleds.h>
#include <stdlib.h>

#define NUM_OF_CHARACTERS 26

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
  int lengths[NUM_OF_CHARACTERS] = {2,4,4,3,1,4,3,4,2,4,3,3,2,2,3,4,4,3,3,1,3,4,3,4,4,4};

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
  int l[] = {1,1,1};
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

  int letter = 18;
  flashLetter(letter, alphabet[letter], lengths[letter]);
  _delay_ms(500);

  letter = 14;
  flashLetter(letter, alphabet[letter], lengths[letter]);
  _delay_ms(500);

  letter = 18;
  flashLetter(letter, alphabet[letter], lengths[letter]);
  _delay_ms(500);

  return 0;

  // int letterNumber = 5;
  // int length = lengths[letterNumber];
  // for (int i = 0; i < length; i++)
  // {
  //   if (alphabet[letterNumber][i])
  //   {
  //     /* code */
  //   }
  //   else {

  //   }
    
  // }
  
}

