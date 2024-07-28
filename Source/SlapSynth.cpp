/*
  ==============================================================================

    SlapSynth.cpp
    Created: 28 Jul 2024 3:59:09pm
    Author:  USER

  ==============================================================================
*/

#include "SlapSynth.h"

void SlapSynth::setup()
{
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());

    afm.registerBasicFormats();
    noteRange.setRange(0, 128, true);

    juce::File* file = new juce::File("C:\\Users\\USER\\OneDrive\\Documents\\Ableton\\Live Recordings\\2024-03-09 130654 Temp Project\\Samples\\Processed\\Consolidate\\GrandPiano C3 f [2024-03-09 130834].wav");
    juce::ScopedPointer<juce::AudioFormatReader> reader = afm.createReaderFor(*file);

    addSound(new juce::SamplerSound("default", *reader, noteRange, 69, 0.f, 0.2f, 2.f));
}
