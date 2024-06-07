#include <stdlib.h>
#include <usart.h>
#include <string.h>
#include <util/delay.h>

#define MAX 36
#define COUNT 100

int main(){
    initUSART();
  char *sentence[COUNT];

  for (int i = 0; i < COUNT; i++)
  {
    sentence[i] = malloc(MAX*(sizeof(char)));

    strcpy(sentence[i],"I blew up a capacitor in my face.");
    printf("%d : %s\n", i+1,sentence[i]);
    free(sentence[i]); //frees memory
    _delay_ms(100); 
  }

  return 0;
}

//part two:
void writeLinesOnHeap(char sentence []);

int main(){
    initUSART();
    writeLinesOnHeap("szymon");

  return 0;
}

void writeLinesOnHeap(char sentence []){
    char *sentenceList[1000];
    int heapSize = 0;
    int i = 0;
    int length = strlen(sentence);

    while (1)
    {
    sentenceList[i] = malloc(length*(sizeof(char)));
    strcpy(sentenceList[i],sentence);
    length = length + length;
    printf("%d : %d bytes\n", i+1, length);
    // free(sentence[i]); //frees memory
    i++;
    _delay_ms(1000);
    }
}