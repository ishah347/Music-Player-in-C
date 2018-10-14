// Helper functions for music

// International standard is A4 = 440Hz
#define A440 440

// Header files to include
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction to eighths
int duration(string fraction)
{
    // Extract numeric parts of the fraction, converting ASCII to digits
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';

    // Convert to a whole number of eighth notes
    return 8.0 * (double) numerator / denominator;
}

// Calculates frequency of a note
int frequency(string note)
{
    // Buffer to store the note name (e.g. "A" or "Db")
    char n[3];
    int octave = 0;

    // Two-character notes are just tone and octave
    if (strlen(note) == 2)
    {
        // Copy note into buffer, null terminate it
        n[0] = note[0];
        n[1] = '\0';

        // Convert octave number from ASCII to digit
        octave = note[1] - '0';
    }

    // Three-character notes are tone, accidental, and octave
    else if (strlen(note) == 3)
    {
        // Copy note into buffer, null terminate it
        n[0] = note[0];
        n[1] = note[1];
        n[2] = '\0';

        // Convert octave number from ASCII to digit
        octave = note[2] - '0';
    }

    // Calculate relative to A440
    double f = A440;

    // Determine how many semitones to move
    int semitones = 0;
    switch (toupper((unsigned char) n[0]))
    {
        // Octaves start at C, so increase "octave number" for A and B (A4 is higher than C4)
        case 'A':
            octave++;
            break;
        case 'B':
            semitones = 2;
            octave++;
            break;

        // All other tones retain their octave number
        case 'C':
            semitones = 3;
            break;
        case 'D':
            semitones = 5;
            break;
        case 'E':
            semitones = 7;
            break;
        case 'F':
            semitones = 8;
            break;
        case 'G':
            semitones = 10;
            break;

        // Invalid notes are ignored
        default:
            f = 0;
    }

    // Sharps increase the note by a semitone
    if (n[1] == '#')
    {
        semitones++;
    }

    // Flats decrease the note by a semitone
    else if (n[1] == 'b')
    {
        semitones--;
    }

    // Compute the final frequency
    return round(f * pow(2.0, semitones / 12.0 + octave - 5.0));
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // Any empty string is a rest
    if (strlen(s) == 0)
    {
        return true;
    }

    // Otherwise, not a rest
    else
    {
        return false;
    }
}