#include "LowpassHighpassFilter/PluginProcessor.h"

#include "LowpassHighpassFilter/LowpassHighpassFilter.h"
#include "LowpassHighpassFilter/PluginEditor.h"

//==============================================================================
namespace audio_plugin
{

AudioProcessor::AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : juce::AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                               .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                               .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                               ),
#else
    :
#endif

      parameters(*this, nullptr, juce::Identifier("LowpassAndHighpassPlugin"),
                 {std::make_unique<juce::AudioParameterFloat>(
                      "cutoff_frequency", "Cutoff Frequency",
                      juce::NormalisableRange{20.f, 20000.f, 0.1f, 0.2f, false}, 500.f),
                  std::make_unique<juce::AudioParameterBool>("highpass", "Highpass", false)})
{
  cutoffFrequencyParameter = parameters.getRawParameterValue("cutoff_frequency");
  highpassParameter = parameters.getRawParameterValue("highpass");
}

AudioProcessor::~AudioProcessor() {}

//==============================================================================
const juce::String AudioProcessor::getName() const
{
  return JucePlugin_Name;
}

bool AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double AudioProcessor::getTailLengthSeconds() const
{
  return 0.0;
}

int AudioProcessor::getNumPrograms()
{
  return 1;  // NB: some hosts don't cope very well if you tell them there are 0
             // programs, so this should be at least 1, even if you're not really
             // implementing programs.
}

int AudioProcessor::getCurrentProgram()
{
  return 0;
}

void AudioProcessor::setCurrentProgram(int index)
{
  juce::ignoreUnused(index);
}

const juce::String AudioProcessor::getProgramName(int index)
{
  juce::ignoreUnused(index);
  return {};
}

void AudioProcessor::changeProgramName(int index, const juce::String &newName)
{
  juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
  juce::ignoreUnused(samplesPerBlock);

  filter.setSamplingRate(static_cast<float>(sampleRate));
}

void AudioProcessor::releaseResources()
{
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
  juce::ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  // Some plugin hosts, such as certain GarageBand versions, will only
  // load plugins that support stereo bus layouts.
  if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void AudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
  // JUCE default code
  juce::ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());
  // end of the default code

  // retrieve and set the parameter values
  const auto cutoffFrequency = cutoffFrequencyParameter->load();
  // in C++, std::atomic<T> to T conversion is equivalent to a load
  const auto highpass = *highpassParameter < 0.5f ? false : true;
  filter.setCutoffFrequency(cutoffFrequency);
  filter.setHighpass(highpass);

  // perform the filtering
  filter.processBlock(buffer, midiMessages);
}

//==============================================================================
bool AudioProcessor::hasEditor() const
{
  return true;  // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *AudioProcessor::createEditor()
{
  return new AudioProcessorEditor(*this, parameters);
}

//==============================================================================
void AudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
  juce::ignoreUnused(destData);
}

void AudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
  // You should use this method to restore your parameters from this memory
  // block, whose contents will have been created by the getStateInformation()
  // call.
  juce::ignoreUnused(data, sizeInBytes);
}

}  // namespace audio_plugin

// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
  return new audio_plugin::AudioProcessor();
}