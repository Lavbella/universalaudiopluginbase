#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

class MeuPluginAudioEditor  : public juce::AudioProcessorEditor
{
public:
    MeuPluginAudioEditor (MeuPluginAudioProcessor&);
    ~MeuPluginAudioEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider volumeSlider;
    
    // Vincula o Slider visual ao parâmetro "volume" do Processador
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;

    MeuPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeuPluginAudioEditor)
};