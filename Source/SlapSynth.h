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
    void setup();
    void updateSampleSource(juce::MidiBuffer& midiMessages);
    juce::BigInteger noteRange;

    void updateParamsIfNeeded(float attack, float release);

private:
    void addSamplerSoundToSampler();

    juce::AudioFormatManager afm;
    std::unique_ptr<juce::AudioFormatReader> reader;

    float attackTime = 0.f;
    float releaseTime = 0.02f;

    juce::String latestSamplePath = "";
    int latestNoteNumber = -1;

    juce::String johnslapSamplesDirectory = "";
};