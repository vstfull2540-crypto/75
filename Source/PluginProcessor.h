#pragma once
#include <JuceHeader.h>
class ArmNongMuangLA2AAudioProcessor final : public juce::AudioProcessor {
public:
 ArmNongMuangLA2AAudioProcessor();
 void prepareToPlay(double,int) override; void releaseResources() override;
 bool isBusesLayoutSupported(const BusesLayout&) const override;
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
 juce::AudioProcessorEditor* createEditor() override; bool hasEditor() const override{return true;}
 const juce::String getName() const override{return "LA-2A Arm Nong Muang";}
 bool acceptsMidi() const override{return false;} bool producesMidi() const override{return false;} bool isMidiEffect() const override{return false;}
 double getTailLengthSeconds() const override{return 0;} int getNumPrograms() override{return 1;} int getCurrentProgram() override{return 0;}
 void setCurrentProgram(int) override{} const juce::String getProgramName(int) override{return "Default";} void changeProgramName(int,const juce::String&) override{}
 void getStateInformation(juce::MemoryBlock&) override; void setStateInformation(const void*,int) override;
 juce::AudioProcessorValueTreeState parameters; void chooseNamFile(const juce::File&); juce::String getNamStatus() const{return namStatus;}
private:
 juce::dsp::Compressor<float> compressor; juce::dsp::Gain<float> outputGain; juce::String namPath;
 juce::String namStatus{"Built-in compressor active. NAM inference engine is not linked."};
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArmNongMuangLA2AAudioProcessor)
};
