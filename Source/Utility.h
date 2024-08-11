/*
  ==============================================================================

    Utility.h
    Created: 8 Aug 2024 6:59:11pm
    Author:  Ethan John

  ==============================================================================
*/

#pragma once

// FIXME: string positions start to get a little off as you move across the fretboard
int* getFretCoordinates(int noteNumber)
{
    static int retval[2] = { 0, 0 };

    // at fret 5, the positions of strings starts to get a little off
    int stringPositions[4] = { 160, 153, 145, 140 };

    // from frets 0 to 7
    //                      OPEN   1    2    3    4    5    6   7
    int fretPositions[8] = { 234, 260, 286, 314, 338, 360, 380, 402 };

    // note number 28 is E1
    int stringIndex = (noteNumber - 28 - 12) / 5;
    int fretIndex = (noteNumber - 28 - 12) % 5;

    // force fretmarker to be on G string
    if (noteNumber > 59) 
    {
        fretIndex = (noteNumber - 55);
        stringIndex = 3;

        std::cout << "index: " << fretIndex << "val" << fretPositions[fretIndex];
    }

    retval[0] = fretPositions[fretIndex];
    retval[1] = stringPositions[stringIndex];

    return retval;
}