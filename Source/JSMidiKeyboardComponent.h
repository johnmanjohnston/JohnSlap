/*
  ==============================================================================

    JSMidiKeyboardComponent.h
    Created: 2 Aug 2024 8:20:30pm
    Author: Ethan John

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

using namespace juce;

class JSMidiKeyboardComponent : public juce::MidiKeyboardComponent
{
public:
    JSMidiKeyboardComponent(MidiKeyboardState& state, Orientation orientation);

protected:
    virtual void 	drawWhiteNote(int midiNoteNumber, Graphics& g, Rectangle< float > area, bool isDown, bool isOver, Colour lineColour, Colour textColour) override;
    virtual void 	drawBlackNote(int midiNoteNumber, Graphics& g, Rectangle< float > area, bool isDown, bool isOver, Colour noteFillColour) override;

    void addTriggerNoteOverlay(Graphics& g, Rectangle<float> area);

    static const juce::Font getHelveticaLight()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::HelveticaLight_ttf, BinaryData::HelveticaLight_ttfSize);
        return typeface;
    }
};