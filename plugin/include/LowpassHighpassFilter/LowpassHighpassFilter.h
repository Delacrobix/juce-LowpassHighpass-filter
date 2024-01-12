#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include <vector>

namespace audio_plugin
{
class LowpassHighpassFilter
{
public:
  void setHighpass(bool highpass);
  void setCutoffFrequency(float cutoffFrequency);
  void setSamplingRate(float samplingRate);

  void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &);

private:
  bool highpass;
  float cutoffFrequency;
  float samplingRate;

  std::vector<float> dnBuffer;
};
}  // namespace audio_plugin