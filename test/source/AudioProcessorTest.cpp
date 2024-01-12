#include <gtest/gtest.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "LowpassHighpassFilter/PluginProcessor.h"

namespace audio_plugin_test
{
TEST(AudioPluginAudioProcessor, Foo)
{
  audio_plugin::AudioProcessor processor{};
  ASSERT_FALSE(true);
}
}  // namespace audio_plugin_test