/*
  ==============================================================================

    SlapSynth.h
    Created: 28 Jul 2024 3:59:09pm
    Author:  USER

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SlapSynth : public juce::Synthesiser {
public:
    void setup();
    juce::BigInteger noteRange;

private:
    juce::AudioFormatManager afm;
};