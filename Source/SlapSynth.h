/*
  ==============================================================================

    SlapSynth.h
    Created: 28 Jul 2024 3:59:09pm
    Author: Ethan John

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SlapSynth : public juce::Synthesiser {
public:
    void setup(int minNote, int maxNote);
    void updateSampleSource(juce::MidiBuffer& midiMessages);
    juce::BigInteger noteRange;
private:
    juce::AudioFormatManager afm;
};