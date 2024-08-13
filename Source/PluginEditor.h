#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "JSMidiKeyboardComponent.h"
#include "JSLookAndFeel.h"

//==============================================================================
class JohnSlapAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    JohnSlapAudioProcessorEditor (JohnSlapAudioProcessor&);
    ~JohnSlapAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

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

    int knownActiveNotesSize = -1;
    int knownLastNote = -1;

    void timerCallback() override
    {
        if (knownActiveNotesSize != audioProcessor.activeNotes.size() || audioProcessor.lastNote != knownLastNote)
            repaint(74, 24, 816, 265);
    }

private:
    JohnSlapAudioProcessor& audioProcessor;

    int HEIGHT = 350;
    int WIDTH = 800;

    juce::Slider gainSlider;
    juce::SliderParameterAttachment gainSliderAttachment;

    juce::Slider attackSlider;
    juce::SliderParameterAttachment attackSliderAttachment;

    juce::Slider releaseSlider;
    juce::SliderParameterAttachment releaseSliderAttachment;

    JSLookAndFeel jsLookAndFeel;

    void styleSlider(juce::Slider& slider, juce::String suffix);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JohnSlapAudioProcessorEditor)
};