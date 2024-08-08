#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Utility.h"

//==============================================================================
JohnSlapAudioProcessorEditor::JohnSlapAudioProcessorEditor (JohnSlapAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), kbComponent(p.kbState, juce::KeyboardComponentBase::horizontalKeyboard),
      gainSliderAttachment(*p.gainParameter, gainSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WIDTH, HEIGHT);

    addAndMakeVisible(kbComponent);
    addAndMakeVisible(gainSlider);

    p.kbState.addListener(&kbListener);
    kbListener.addChangeListener(this);

    this->minNote = p.minNote;
    this->maxNote = p.maxNote;
}

JohnSlapAudioProcessorEditor::~JohnSlapAudioProcessorEditor()
{
    gainSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void JohnSlapAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour(10, 10, 10));
    g.setFont(getHelveticaLight());

    g.setFont(34.f);
    g.setColour(juce::Colour(100, 100, 100));
    g.drawText("JohnSlap", 14, 0, 150, 50, juce::Justification::left, false);

    g.addTransform(AffineTransform::scale(0.9));
    juce::Image bassImg = juce::ImageCache::getFromMemory(BinaryData::bass_img_png, BinaryData::bass_img_pngSize);
    g.drawImageWithin(bassImg, 74, 144, 816, 265, NULL);

    for (auto noteNumber : kbListener.activeNotes) 
    {
        if (noteNumber > maxNote || noteNumber < minNote) 
            continue;

        juce::Image fretMarker = juce::ImageCache::getFromMemory(BinaryData::fretmarker_png, BinaryData::fretmarker_pngSize);
        int* fretCoordinates = getFretCoordinates(noteNumber);
        g.drawImageWithin(fretMarker, fretCoordinates[0], fretCoordinates[1], 10, 10, NULL);
    }

    // slider
    gainSlider.setLookAndFeel(&jsLookAndFeel);
}

void JohnSlapAudioProcessorEditor::resized()
{
    kbComponent.setBounds(0, HEIGHT - 80, 850, 80);
    gainSlider.setBounds(100, 200, 200, 50);
}

void JohnSlapAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}