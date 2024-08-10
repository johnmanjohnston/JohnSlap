/*
  ==============================================================================

    Utility.h
    Created: 8 Aug 2024 6:59:11pm
    Author:  Ethan John

  ==============================================================================
*/

#pragma once

// FIXME: this returns wrong coordinates since you moved the position of the bass
int* getFretCoordinates(int noteNumber)
{
    static int retval[2] = { 0, 0 };

    // at fret 5, the positions of strings starts to get a little off
    int stringPositions[4] = { 299, 292, 283, 277 };

    // from frets 0 to 7
    //                      OPEN   1    2    3    4    5    6   7
    int fretPositions[8] = { 263, 288, 320, 350, 377, 404, 428, 450 };

    // note number 28 is E1
    int stringIndex = (noteNumber - 28 - 12) / 5;
    int fretIndex = (noteNumber - 28 - 12) % 5;

    retval[0] = fretPositions[fretIndex];
    retval[1] = stringPositions[stringIndex] - 120;

    return retval;
}