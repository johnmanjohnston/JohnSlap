/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JohnSlapAudioProcessorEditor::JohnSlapAudioProcessorEditor (JohnSlapAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), kbComponent(p.kbState, juce::KeyboardComponentBase::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WIDTH, HEIGHT);

    addAndMakeVisible(kbComponent);

    p.kbState.addListener(&kbListener);
    kbListener.addChangeListener(this);
}

JohnSlapAudioProcessorEditor::~JohnSlapAudioProcessorEditor()
{
}

//==============================================================================
void JohnSlapAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(10, 10, 10));
    g.setFont(getHelveticaLight());

    g.setFont(34.f);
    g.setColour(juce::Colour(100, 100, 100));
    g.drawText("JohnSlap", 14, 0, 150, 50, juce::Justification::left, false);


    g.addTransform(AffineTransform::scale(0.9));
    juce::Image bassImg = juce::ImageCache::getFromMemory(BinaryData::bass_img_png, BinaryData::bass_img_pngSize);
    g.drawImageWithin(bassImg, 74, 144, 816, 265, 0);
}

void JohnSlapAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    kbComponent.setBounds(0, HEIGHT - 80, 850, 80);
}

void JohnSlapAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    // TODO: look at kbListener.activeNotes and draw icons on the corresponding frets, maybe you'll need to call repaint()? 
    DBG(kbListener.activeNotes.size());
}
