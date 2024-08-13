#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JohnSlapAudioProcessor::JohnSlapAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    this->addParameter(gainParam = new juce::AudioParameterFloat(
        "gain",
        "Gain",
        0.f,
        1.f,
        0.8f
    ));
    
    this->addParameter(attackParam = new juce::AudioParameterFloat(
        "attack",
        "Attack Time",
        juce::NormalisableRange<float>(0.f, 2.f, .02f),
        0.f
    ));

    this->addParameter(releaseParam = new juce::AudioParameterFloat(
        "release",
        "Release Time",
        juce::NormalisableRange<float>(0.f, 2.f, .02f),
        0.2f
    ));
}

JohnSlapAudioProcessor::~JohnSlapAudioProcessor()
{
}

//==============================================================================
const juce::String JohnSlapAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JohnSlapAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JohnSlapAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JohnSlapAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JohnSlapAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JohnSlapAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JohnSlapAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JohnSlapAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JohnSlapAudioProcessor::getProgramName (int index)
{
    return {};
}

void JohnSlapAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JohnSlapAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    synth.setup();

    juce::dsp::ProcessSpec spec{};
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    spec.sampleRate = sampleRate;

    gain.prepare(spec);
}

void JohnSlapAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JohnSlapAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JohnSlapAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // handle on-screen keyboard
    kbState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    // handle synth
    synth.updateSampleSource(midiMessages);
    synth.updateParamsIfNeeded(attackParam->get(), releaseParam->get());
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    // handle params
    gain.setGainLinear(gainParam->get());

    // dsp
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    gain.process(context);

    for (const auto midiData : midiMessages) 
    {
        auto msg = midiData.getMessage();
        auto noteNumber = msg.getNoteNumber();

        if (msg.isNoteOn()) 
        {
            activeNotes.push_back(noteNumber);
            lastNote = noteNumber;
        }

        if (msg.isNoteOff()) 
        {
            for (auto it = activeNotes.begin(); it != activeNotes.end(); ++it) {
                if (*it == noteNumber) {
                    activeNotes.erase(it);
                    break;
                }
            }
        }
    }
}

//==============================================================================
bool JohnSlapAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JohnSlapAudioProcessor::createEditor()
{
    return new JohnSlapAudioProcessorEditor (*this);
}

//==============================================================================
void JohnSlapAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, true);
    stream.writeFloat(*gainParam);
    stream.writeFloat(*attackParam);
    stream.writeFloat(*releaseParam);
}

void JohnSlapAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);
    *gainParam = stream.readFloat();
    *attackParam = stream.readFloat();
    *releaseParam = stream.readFloat();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JohnSlapAudioProcessor();
}
