#include "PluginProcessor.h"
#include "PluginEditor.h"

MeuPluginAudioProcessor::MeuPluginAudioProcessor()
 : AudioProcessor (BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
       apvts (*this, nullptr, "Parameters", createParameterLayout()) // <--- Adicione isto
{}

MeuPluginAudioProcessor::~MeuPluginAudioProcessor() {}

void MeuPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}
void MeuPluginAudioProcessor::releaseResources() {}

// É aqui que o áudio da DAW passa e é modificado em tempo real
void MeuPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Limpa canais de saída extras se houver inconsistência
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Lê o valor atual do slider "volume" de forma segura para áudio
    auto volumeGain = apvts.getRawParameterValue("volume")->load();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = channelData[sample] * volumeGain;
        }
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MeuPluginAudioProcessor();
}

// 1. Crie a função que define o Slider (coloque isto no fundo do ficheiro)
juce::AudioProcessorValueTreeState::ParameterLayout MeuPluginAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // Cria um parâmetro com ID "volume", Nome "Volume", min 0.0, max 1.0, padrão 0.5
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("volume", 1), 
        "Volume", 
        0.0f, 
        1.0f, 
        0.5f));
        
    return layout;
}

juce::AudioProcessorEditor* MeuPluginAudioProcessor::createEditor()
{
    return new MeuPluginAudioEditor (*this);
}

// 5. Funções para salvar e carregar o estado do plugin na DAW (Opcional, mas obrigatório implementar)
void MeuPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Guarda os valores dos Sliders quando fecha o projeto na DAW
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MeuPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Restaura os valores dos Sliders quando abre o projeto na DAW
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}
