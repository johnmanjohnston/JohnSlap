/*
  ==============================================================================

    SlapSynth.cpp
    Created: 28 Jul 2024 3:59:09pm
    Author: Ethan John

  ==============================================================================
*/

#include "SlapSynth.h"
#include "Common.h"

void SlapSynth::setup()
{
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());

    afm.registerBasicFormats();
    noteRange.setRange(MINIMUM_NOTE - TRIGGER_NOTES_COUNT, MAXIMUM_NOTE - MINIMUM_NOTE + TRIGGER_NOTES_COUNT + 1, true);

    juce::ScopedPointer<juce::File> file = new juce::File("C:\\Users\\USER\\OneDrive\\Documents\\Ableton\\Live Recordings\\2024-03-09 130654 Temp Project\\Samples\\Processed\\Consolidate\\GrandPiano C3 f [2024-03-09 130834].wav");
    juce::ScopedPointer<juce::AudioFormatReader> reader = afm.createReaderFor(*file.get());

    addSound(new juce::SamplerSound("default", *reader, noteRange, 69, 0.f, 0.2f, 2.f));

    DBG(MAXIMUM_NOTE - MINIMUM_NOTE + TRIGGER_NOTES_COUNT);
}

void SlapSynth::updateSampleSource(juce::MidiBuffer& midiMessages)
{
    if (midiMessages.isEmpty()) return;

    for (const auto midiData : midiMessages) {
        const auto msg = midiData.getMessage();
        const auto noteNumber = msg.getNoteNumber(); 
        const auto noteName = msg.getMidiNoteName(noteNumber, false, false, 3);

        DBG(noteNumber);

        // juce::String fpath = "C:\\Users\\USER\\other-nerd-stuff\\projects\\JohnSlap\\samples\\trbx174\\";
        juce::String fpath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::globalApplicationsDirectory)
            .getChildFile("johnmanjohnston/johnslap/samples/")
            .getFullPathName();

        fpath.append("/trbx174/", 9);

        // play a note on the bass
        if (noteNumber >= MINIMUM_NOTE) 
        {
            // slap or pop?
            if (noteNumber >= 52) fpath.append("pop/", 4);
            else fpath.append("slap/", 5);

            fpath.append(noteName, 3);
            fpath.append("5", 1);

            // get variation number
            int variation = (std::rand() % 2);
            fpath.append(juce::String(variation), 1);
        }

        // play a trigger note
        else 
        {
            fpath.append("/misc/", 6);

            int triggerNumber = -1 * ((MINIMUM_NOTE - TRIGGER_NOTES_COUNT) - noteNumber);
            fpath.append(juce::String(triggerNumber), 1);
        }

        fpath.append(".wav", 4);
        juce::File* file = new juce::File(fpath);

        if (file->exists()) 
        {
            DBG(fpath);
            latestNoteNumber = noteNumber;
            removeSound(0);
            juce::ScopedPointer<juce::AudioFormatReader> reader = afm.createReaderFor(*file);
            addSound(new juce::SamplerSound("default", *reader, noteRange, noteNumber, attackTime, releaseTime, 2.f));
        }


        else { DBG(fpath + " does not exist"); }
    }
}

void SlapSynth::updateParamsIfNeeded(float attack, float release)
{
    if (attack == this->attackTime && release == this->releaseTime) return;

    attackTime = attack;
    releaseTime = release;

    juce::File* file = new juce::File(latestSamplePath);

    if (file->exists())
    {
        removeSound(0);
        juce::ScopedPointer<juce::AudioFormatReader> reader = afm.createReaderFor(*file);
        addSound(new juce::SamplerSound("default", *reader, noteRange, latestNoteNumber, attackTime, releaseTime, 2.f));
    }
}
