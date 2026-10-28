cmake_minimum_required(VERSION 3.22)
project(ArmNongMuangLA2A VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JUCE_BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 8.0.6
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(JUCE)
juce_add_binary_data(LA2AAssets SOURCES Assets/LA2A_Interface.png)
juce_add_plugin(ArmNongMuangLA2A
  COMPANY_NAME "Arm Nong Muang - Muepim Studio"
  BUNDLE_ID "com.armnongmuang.la2a"
  PLUGIN_MANUFACTURER_CODE Anmg
  PLUGIN_CODE La2a
  FORMATS VST3 Standalone
  PRODUCT_NAME "LA-2A Arm Nong Muang"
  IS_SYNTH FALSE NEEDS_MIDI_INPUT FALSE NEEDS_MIDI_OUTPUT FALSE IS_MIDI_EFFECT FALSE
  EDITOR_WANTS_KEYBOARD_FOCUS TRUE COPY_PLUGIN_AFTER_BUILD FALSE)
juce_generate_juce_header(ArmNongMuangLA2A)

target_sources(ArmNongMuangLA2A PRIVATE
  Source/PluginProcessor.cpp
  Source/PluginProcessor.h
  Source/PluginEditor.cpp
  Source/PluginEditor.h)
target_compile_definitions(ArmNongMuangLA2A PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 JUCE_VST3_CAN_REPLACE_VST2=0)
target_link_libraries(ArmNongMuangLA2A PRIVATE LA2AAssets juce::juce_audio_utils juce::juce_audio_processors juce::juce_dsp
  PUBLIC juce::juce_recommended_config_flags juce::juce_recommended_lto_flags juce::juce_recommended_warning_flags)
