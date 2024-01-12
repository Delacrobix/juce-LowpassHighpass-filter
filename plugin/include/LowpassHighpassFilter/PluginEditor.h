#pragma once

#include "PluginProcessor.h"

namespace audio_plugin
{

class AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
  // altered constructor to receive the value tree state object
  explicit AudioProcessorEditor(AudioProcessor &, juce::AudioProcessorValueTreeState &vts);
  ~AudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;
  //...
private:
  AudioProcessor &audioProcessor;

  juce::Slider cutoffFrequencySlider;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffFrequencyAttachment;
  juce::Label cutoffFrequencyLabel;

  juce::ToggleButton highpassButton;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> highpassAttachment;
  juce::Label highpassButtonLabel;

  // given by JUCE by default
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorEditor)
};

}  // namespace audio_plugin