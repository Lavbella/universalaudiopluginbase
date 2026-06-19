# universalaudiopluginbase
A cross-platform, universal audio plugin base built with JUCE and C++ for Linux and Windows DAWs.

# Universal Audio Plugin Base (JUCE + C++)

[Português]  
Este repositório contém a base estrutural de um plugin de áudio nativo para Linux desenvolvido em **C++** utilizando a framework **JUCE**. O projeto foi validado com sucesso na DAW **REAPER** (correndo em ambiente **Ubuntu 24.04** com suporte de áudio via **PipeWire/JACK**).

[English]  
This repository contains the structural foundation of a native Linux audio plugin developed in **C++** using the **JUCE** framework. The project was successfully validated inside **REAPER** DAW (running on **Ubuntu 24.04** with audio support via **PipeWire/JACK**).

---

## Arquitetura do Projeto / Project Architecture

**[PT]** A infraestrutura do plugin está dividida de forma limpa seguindo o padrão do JUCE:
* **`PluginProcessor`**: Trata o motor de áudio em tempo real dentro do método `processBlock`.
* **`PluginEditor`**: Gere a interface gráfica (UI) e os seus componentes visuais.
* **`AudioProcessorValueTreeState (APVTS)`**: Faz a ponte segura entre a UI (Sliders) e o processador de áudio, garantindo suporte nativo a automações dentro de qualquer DAW.

**[EN]** The plugin infrastructure is cleanly separated following standard JUCE architecture:
* **`PluginProcessor`**: Handles the real-time audio engine inside the `processBlock` method.
* **`PluginEditor`**: Manages the Graphical User Interface (UI) and its visual components.
* **`AudioProcessorValueTreeState (APVTS)`**: Acts as a thread-safe bridge between the UI (Sliders) and the processor, ensuring native automation support in any DAW.

---

## O Conceito: Tudo é Matemática / The Concept: It's All Math

**[PT]** A fundação do projeto demonstra que a diferença entre um modificador de ganho e qualquer outro efeito de áudio reside estritamente nas fórmulas de processamento digital de sinal (DSP) aplicadas no loop de amostras. Esta arquitetura serve como base para construir:
* **Efeitos de Guitarra**: Pedais de distorção (Hard/Soft clipping), Fuzz, Chorus, etc.
* **Processadores de Voz**: Compressores, Equalizadores, Delays, Reverbs ou corretores de pitch.
* **Sintetizadores Virtuais**: Geradores de som baseados em tabelas de ondas (Wavetables) e osciladores matemáticos.
* **Gestores de Presets**: Motores para guardar, serializar e carregar estados e configurações do plugin.

**[EN]** The foundation of this project proves that the difference between a gain stage and any other audio effect lies strictly within the Digital Signal Processing (DSP) formulas applied inside the sample loop. This architecture serves as a baseline to build:
* **Guitar Effects**: Distortion pedals (Hard/Soft clipping), Fuzz, Chorus, etc.
* **Voice Processors**: Compressors, Equalizers, Delays, Reverbs, or pitch correctors.
* **Virtual Synths**: Sound generators based on Wavetables and mathematical oscillators.
* **Preset Managers**: Engines to save, serialize, and recall plugin states and layouts.

```cpp
// Exemplo de manipulação de ganho em tempo real no processBlock
// Real-time gain manipulation example inside processBlock
auto volumeGain = apvts.getRawParameterValue("volume")->load();

for (int channel = 0; channel < totalNumInputChannels; ++channel)
{
    auto* channelData = buffer.getWritePointer (channel);
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        channelData[sample] = channelData[sample] * volumeGain;
    }
}
```

---

## Portabilidade Multiplataforma / Cross-Platform Portability (Windows / FL Studio)

**[PT]** Uma das maiores vantagens da framework JUCE é que o código fonte é totalmente agnóstico ao sistema operativo. Embora desenvolvido em Linux:
* O mesmo código pode ser aberto no **VS Code ou Visual Studio em Windows**.
* Pode ser compilado diretamente para gerar binários `.vst3` do Windows.
* Funciona nativamente em DAWs comerciais de topo como o **FL Studio**, Cubase ou Ableton Live sem necessidade de alterar uma única linha de C++.

**[EN]** One of the biggest advantages of the JUCE framework is that the source code is completely OS-agnostic. Even though it was developed on Linux:
* The exact same code can be opened in **VS Code or Visual Studio on Windows**.
* It can be compiled directly to generate Windows `.vst3` binaries.
* It works natively inside industry-standard commercial DAWs like **FL Studio**, Cubase, or Ableton Live without changing a single line of C++.

---

## Como Compilar / How to Build (Linux / CMake)

**[PT]** Certifique-se de que tem as bibliotecas de desenvolvimento do PipeWire/JACK instaladas no seu sistema.  
**[EN]** Make sure you have the PipeWire/JACK development libraries installed on your system.

```bash
# 1. Crie a pasta de build / Create the build directory
mkdir build && cd build

# 2. Gere os Makefiles através do CMake / Generate Makefiles via CMake
cmake ..

# 3. Compile o projeto (Gera o formato VST3 nativo) / Build the project (Generates native VST3)
cmake --build .
```

---

## Execução no REAPER / Running in REAPER (Ubuntu 24.04)

**[PT]** Para evitar conflitos com o motor de áudio do sistema, o plugin foi testado correndo a DAW com a ponte do PipeWire:  
**[EN]** To prevent conflicts with the system audio driver, the plugin was tested by running the DAW using the PipeWire bridge:

```bash
pw-jack ~/opt/REAPER/reaper &
```

---

## Próximos Passos / Next Steps

* **[PT]** Implementar algoritmos de **Hard/Soft Clipping** baseados em pedais de guitarra clássicos (Tube Screamer / Boss DS-1).
* **[PT]** Adicionar controlos de *Drive* e *Tone*.
* **[EN]** Implement **Hard/Soft Clipping** algorithms inspired by classic guitar pedals (Tube Screamer / Boss DS-1).
* **[EN]** Add *Drive* and *Tone* controls.
