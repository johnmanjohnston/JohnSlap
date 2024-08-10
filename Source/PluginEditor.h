#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "JSMidiKeyboardComponent.h"
#include "JSLookAndFeel.h"

//==============================================================================
class KeyboardStateListener : public juce::MidiKeyboardState::Listener, public juce::ChangeBroadcaster {
public:
    std::vector<int> activeNotes;

    void handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override {
        activeNotes.push_back(midiNoteNumber);
        sendChangeMessage();
    }

    void handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override {
        for (auto it = activeNotes.begin(); it != activeNotes.end(); ++it) {
            if (*it == midiNoteNumber) {
                activeNotes.erase(it);
                break;
            }
        }
        sendChangeMessage();
    }
};

//==============================================================================
class JohnSlapAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::ChangeListener
{
public:
    JohnSlapAudioProcessorEditor (JohnSlapAudioProcessor&);
    ~JohnSlapAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source);

    JSMidiKeyboardComponent kbComponent;

    static const juce::Font getHelvetica()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::Helvetica_ttf, BinaryData::Helvetica_ttfSize);
        return typeface;
    }

    static const juce::Font getHelveticaLight()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::HelveticaLight_ttf, BinaryData::HelveticaLight_ttfSize);
        return typeface;
    }

    static const juce::Font getSpaceMono() 
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::SpaceMonoRegular_ttf, BinaryData::SpaceMonoRegular_ttfSize);
        return typeface;
    }

    KeyboardStateListener kbListener;
private:
    JohnSlapAudioProcessor& audioProcessor;

    int HEIGHT = 350;
    int WIDTH = 800;

    int minNote = -1;
    int maxNote = -1;

    juce::Slider gainSlider;
    juce::SliderParameterAttachment gainSliderAttachment;

    juce::Slider attackSlider;
    juce::SliderParameterAttachment attackSliderAttachment;

    juce::Slider releaseSlider;
    juce::SliderParameterAttachment releaseSliderAttachment;

    JSLookAndFeel jsLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JohnSlapAudioProcessorEditor)
};