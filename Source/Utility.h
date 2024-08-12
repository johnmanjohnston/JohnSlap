/*
  ==============================================================================

    Utility.h
    Created: 8 Aug 2024 6:59:11pm
    Author:  Ethan John

  ==============================================================================
*/

#pragma once
#include "Common.h"

int* getFretCoordinates(int noteNumber)
{
    static int retval[2] = { 0, 0 };

    int stringPositions[4] = { 160, 153, 146, 140 };
    int fretPositions[9] = { 234, 260, 286, 314, 338, 360, 380, 402, 422 };

    // note number 28 is E1
    int stringIndex = (noteNumber - 28 - 12) / 5;
    int fretIndex = (noteNumber - 28 - 12) % 5;

    // force fretmarker to be on G string
    if (noteNumber > 59) 
    {
        fretIndex = (noteNumber - 55);
        stringIndex = 3;
    }

    float stringDeviationWeights[4] = { .4f, .1f, -.1f, -.4f };
    float stringDeviation = fretIndex * stringDeviationWeights[stringIndex];

    retval[0] = fretPositions[fretIndex];
    retval[1] = stringPositions[stringIndex] + stringDeviation;

    DBG(stringIndex);
    DBG(fretIndex);

    return retval;
}