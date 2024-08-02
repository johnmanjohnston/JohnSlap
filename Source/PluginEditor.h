/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "JSMidiKeyboardComponent.h"

//==============================================================================
/**
*/
class JohnSlapAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JohnSlapAudioProcessorEditor (JohnSlapAudioProcessor&);
    ~JohnSlapAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    JSMidiKeyboardComponent kbComponent;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JohnSlapAudioProcessor& audioProcessor;

    int HEIGHT = 400;
    int WIDTH = 800;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JohnSlapAudioProcessorEditor)
};
