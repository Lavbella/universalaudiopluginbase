#include "PluginProcessor.h"
#include "PluginEditor.h"

MeuPluginAudioEditor::MeuPluginAudioEditor (MeuPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Configura o estilo visual do Slider (Botão rotativo redondo)
    volumeSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible (volumeSlider);

    // Faz a ligação automática com a APVTS do Processor
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.apvts, "volume", volumeSlider);

    // Define o tamanho inicial da janela do Plugin (Largura, Altura)
    setSize (300, 300);
}

MeuPluginAudioEditor::~MeuPluginAudioEditor()
{
}

void MeuPluginAudioEditor::paint (juce::Graphics& g)
{
    // Preenche o fundo com uma cor escura
    g.fillAll (juce::Colours::darkgrey);

    // Adiciona um texto simples acima do Slider
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Volume do Plugin", getLocalBounds().withHeight(40), juce::Justification::centred, 1);
}

void MeuPluginAudioEditor::resized()
{
    // Posiciona o Slider mesmo no centro da janela
    volumeSlider.setBounds (100, 100, 100, 100);
}