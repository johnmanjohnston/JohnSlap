#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Utility.h"
#include "Common.h"

//==============================================================================
JohnSlapAudioProcessorEditor::JohnSlapAudioProcessorEditor(JohnSlapAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), kbComponent(p.kbState, juce::KeyboardComponentBase::horizontalKeyboard),
    gainSliderAttachment(*p.gainParam, gainSlider), attackSliderAttachment(*p.attackParam, attackSlider), releaseSliderAttachment(*p.releaseParam, releaseSlider)
{
    setSize (WIDTH, HEIGHT);

    addAndMakeVisible(kbComponent);
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(releaseSlider);

    kbComponent.setAvailableRange(35, 119);
    startTimer(20);
}

JohnSlapAudioProcessorEditor::~JohnSlapAudioProcessorEditor()
{
    gainSlider.setLookAndFeel(nullptr);
    attackSlider.setLookAndFeel(nullptr);
    releaseSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void JohnSlapAudioProcessorEditor::paint (juce::Graphics& g)
{
    // set bg color
    g.fillAll(juce::Colour(10, 10, 10));

    // draw "JohnSlap" on top left
    juce::Image logo = juce::ImageCache::getFromMemory(BinaryData::jslogo_png, BinaryData::jslogo_pngSize);
    g.setOpacity(0.2f);
    g.drawImageWithin(logo, 12, 10, 269 / 2, 69 / 2, juce::Justification::left, false);

    // draw version on top right
    g.setColour(juce::Colours::white);
    g.setOpacity(0.2f);
    juce::String versionText = "v"; 
    versionText.append(JOHNSLAP_VERSION, 6);
    
    g.setFont(18.f);
    g.drawText(versionText, WIDTH - 61, 6, 50, 26, juce::Justification::right, false);

    g.setOpacity(1.f);

    // draw bass image
    g.addTransform(AffineTransform::scale(0.9f));
    juce::Image bassImg = juce::ImageCache::getFromMemory(BinaryData::bass_img_png, BinaryData::bass_img_pngSize);
    g.drawImageWithin(bassImg, 74, 24, 816, 265, NULL);

    // draw knob panel
    g.addTransform(AffineTransform::scale(1.12f));
    juce::Image panelImg = juce::ImageCache::getFromMemory(BinaryData::knobpanel_png, BinaryData::knobpanel_pngSize);
    g.drawImageWithin(panelImg, 0, HEIGHT - 140, WIDTH, 119, NULL);

    // draw fret markers
    knownActiveNotesSize = audioProcessor.activeNotes.size();
    knownLastNote = audioProcessor.lastNote;

    for (auto noteNumber : audioProcessor.activeNotes) 
    {
        DBG("active note:" << noteNumber);

        if (noteNumber <= MAXIMUM_NOTE && noteNumber >= MINIMUM_NOTE)
        {
            juce::Image fretMarker = juce::ImageCache::getFromMemory(BinaryData::fretmarker_png, BinaryData::fretmarker_pngSize);
            int* fretCoordinates = getFretCoordinates(noteNumber);
            g.drawImageWithin(fretMarker, fretCoordinates[0], fretCoordinates[1], 10, 10, NULL);
        }
    }

    // style sliders
    styleSlider(gainSlider, " - GAIN");
    styleSlider(attackSlider, " - ATTACK");
    styleSlider(releaseSlider, " - RELEASE");
}

void JohnSlapAudioProcessorEditor::resized()
{
    kbComponent.setBounds(0, HEIGHT - 80, 850, 80);

    gainSlider.setBounds((WIDTH / 3) - (250), 206, 250, 70);
    attackSlider.setBounds((WIDTH  / 2) - (250/ 2), 206, 250, 70);
    releaseSlider.setBounds(18 + (WIDTH / 3) + (250), 206, 250, 70);
}

void JohnSlapAudioProcessorEditor::styleSlider(juce::Slider& slider, juce::String suffix)
{
    // set isReadOnly to true for sliders because it looks bad when trying to edit the text
    slider.setTextBoxStyle(juce::Slider::TextBoxLeft, true, 110, 14);
    slider.setLookAndFeel(&jsLookAndFeel);
    slider.setTextValueSuffix(suffix);
}