cmake_minimum_required(VERSION 3.15)

# CORREÇÃO: O projeto deve ser declarado apenas como CXX (C++)
project(MeuPlugin VERSION 1.0.0 LANGUAGES C CXX) 

# SOLUÇÃO DEFINITIVA PARA O GTK NO LINUX
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(WEBKIT REQUIRED webkit2gtk-4.1) 
pkg_check_modules(SOUP REQUIRED libsoup-3.0)

# 2. SOLUÇÃO GLOBAL: Injeta as diretórias do GTK, WebKit e Soup para TODOS os alvos do CMake
include_directories(${GTK3_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS} ${SOUP_INCLUDE_DIRS})
link_libraries(${GTK3_LIBRARIES} ${WEBKIT_LIBRARIES} ${SOUP_LIBRARIES})

# SOLUÇÃO PARA UBUNTU 24.04: Desativa o módulo WebKit (Web Browser) e o GTK antigo que o acompanha
set(JUCE_WEB_BROWSER 0 CACHE INTERNAL "")
set(JUCE_USE_CURL 0 CACHE INTERNAL "")
set(JUCE_VST3_CAN_REPLACE_VST2 0 CACHE INTERNAL "")

# Adiciona o JUCE ao projeto
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../JUCE" "${CMAKE_CURRENT_BINARY_DIR}/JUCE")

# Configura o seu componente de áudio
juce_add_plugin(MeuPlugin
    COMPANY_NAME "Lavbella"
    PLUGIN_MANUFACTURER_CODE MPlg
    PLUGIN_CODE Mpl1
    FORMATS CLAP VST3                   # Compila nos formatos CLAP e VST3
    PRODUCT_NAME "Paudiog05"
    IS_SYNTH FALSE                      # É um efeito, não um sintetizador
)

# Adiciona os arquivos de código que vamos criar
target_sources(MeuPlugin PRIVATE
    PluginProcessor.h
    PluginProcessor.cpp
    PluginEditor.cpp   # <-- ADICIONE ISTO
    PluginEditor.h  
)

# Vincula as bibliotecas de áudio necessárias do JUCE
# Mudamos para PUBLIC para garantir que as definições cheguem aos wrappers VST3/CLAP
target_link_libraries(MeuPlugin PUBLIC
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_gui_basics 
)

# Força as definições de pré-processador para evitar o erro de automação VST3
target_compile_definitions(MeuPlugin PUBLIC
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)