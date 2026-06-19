#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

class MeuPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    MeuPluginAudioProcessor();
    ~MeuPluginAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    // Alterado para permitir a criação da interface gráfica (UI)
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; } 

    const juce::String getName() const override { return "Meu Primeiro Plugin"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}
    
    // Métodos para salvar e carregar as configurações do plugin na DAW
    void getStateInformation (juce::MemoryBlock&) override;
    void setStateInformation (const void*, int) override;
    
    // Objeto público que gere os parâmetros e comunica com os Sliders da UI
    juce::AudioProcessorValueTreeState apvts;

private:
    // Função privada para definir a estrutura dos parâmetros (ex: slider de volume)
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeuPluginAudioProcessor)
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter();