#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <wpsh209buzzerlib.h>
#include <vellemanbuttons.h>
#include <wpsh209adclib.h>
#include <stdbool.h> 
#include <stdlib.h>

typedef struct
{
    float frequency;
    uint16_t duration;
} NOTE;

typedef struct
{
    char *name;
    NOTE **notes; 
} SONG;

// prototypes
void playNote(NOTE *note);
SONG *generateSong(char *name, uint16_t length);
void playFinalSong(SONG *song);

int main(){
    while (!buttonPushed(1))
    {
        _delay_ms(100);
    }

    char *nameSong = "nice_song";
    SONG *quietSong = generateSong(nameSong, 10);
    playFinalSong(quietSong);
}

void playNote(NOTE *note)
{
    playTone(note->frequency, note->duration);
}

SONG* generateSong(char *name, uint16_t length)
{
    //SONG *song; // create pointer

    // allocating memory for struct SONG
    // song = (SONG*) malloc(sizeof SONG); //this one doesn't work?
    SONG *song = malloc(sizeof *song);

    *song->name = (char *)malloc(sizeof(name) + 1); // allocates space for name of the song + 1 empty bit
    strcpy(song->name, name);                       // sets the name of the song

    *song->notes = (NOTE *)malloc(length * sizeof(NOTE)); // assign space for the array of notes

    void srand(readPotentioOnce); // seeding the randin

    for (int i = 0; i < length; i++)
    {
        uint16_t duration = 1;
        float frequency = C5;

        int lengthOption = rand() % (3 + 1); // random number between 0 (inclusive) and 3 (exclusive)

        // NOTE: this could be a single line, seeding a larger number, applying a modulo or division on it and then taking what's left.
        if (lengthOption == 1)
        {
            uint16_t duration = 1000;
        }
        else if (lengthOption == 2)
        {
            uint16_t duration = 500;
        }
        else
        {
            uint16_t duration = 250;
        }

        int noteOption = rand() % (8 + 1);

        switch (noteOption)
        {
        case 1:
            //int noteTone = (int)C5; //this is just an error, no declaration
            return (int)C5; 
            break;
        case 2:
            return (int)D5; //I don't understand this warning
            break;
        case 3:
            return (int)E5;
            break;
        case 4:
            return (int)F5;
            break;
        case 5:
            return (int)G5;
            break;
        case 6:
            return (int)A5;
            break;
        case 7:
            return (int)B5;
        case 8:
            return (int)C6;
        default:
            return (int)D6;
            break;
        }

        // assign the two randomly generated attributes!
        song->notes[i]->duration = duration;
        song->notes[i]->frequency = noteOption; //for now

        // test
        //int *a;
        //int b = &a;
    }
        return song;
}

void playFinalSong(SONG *song)
{
    int allNotes = sizeof(song->notes); // don't fully know how to fix
    for (int i = 0; i <= 3; i++)        // because it has to be played 4 times.
    {
        for (int i = 0; i < allNotes; i++)
        {
            playNote(song->notes[i]);
        }
    }
    // tada!
}