#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class ArmNongMuangLA2AAudioProcessorEditor final:public juce::AudioProcessorEditor{
public: explicit ArmNongMuangLA2AAudioProcessorEditor(ArmNongMuangLA2AAudioProcessor&);void paint(juce::Graphics&)override;void resized()override;
private: ArmNongMuangLA2AAudioProcessor& processor;juce::Image background;juce::Slider gain,peak,attack,release;juce::ToggleButton power,limit;juce::ComboBox meter;juce::TextButton loadNam{"LOAD .NAM"};juce::Label status;std::unique_ptr<juce::FileChooser> chooser;void setup(juce::Slider&,const juce::String&);
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArmNongMuangLA2AAudioProcessorEditor)
};
