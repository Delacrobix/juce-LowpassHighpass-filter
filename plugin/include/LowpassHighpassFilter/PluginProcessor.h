#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "LowpassHighpassFilter.h"

namespace audio_plugin
{

class AudioProcessor : public juce::AudioProcessor
{
public:
  AudioProcessor();
  ~AudioProcessor() override;

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

  // using juce::AudioProcessor::processBlock;

  juce::AudioProcessorEditor *createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String &newName) override;

  //==============================================================================
  void getStateInformation(juce::MemoryBlock &destData) override;
  void setStateInformation(const void *data, int sizeInBytes) override;

private:
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessor)

  juce::AudioProcessorValueTreeState parameters;
  std::atomic<float> *cutoffFrequencyParameter = nullptr;
  std::atomic<float> *highpassParameter = nullptr;

  LowpassHighpassFilter filter;
};
}  // namespace audio_plugin