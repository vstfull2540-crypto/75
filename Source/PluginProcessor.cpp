#include "PluginProcessor.h"
#include "PluginEditor.h"
static juce::AudioProcessorValueTreeState::ParameterLayout makeParams(){
 using FP=juce::AudioParameterFloat; std::vector<std::unique_ptr<juce::RangedAudioParameter>> p;
 p.push_back(std::make_unique<FP>("gain","Gain",juce::NormalisableRange<float>(0,100,0.1f),50));
 p.push_back(std::make_unique<FP>("peak","Peak Reduction",juce::NormalisableRange<float>(0,100,0.1f),35));
 p.push_back(std::make_unique<FP>("attack","Attack",juce::NormalisableRange<float>(0.1f,10,0.01f),1));
 p.push_back(std::make_unique<FP>("release","Release",juce::NormalisableRange<float>(50,5000,1),500));
 p.push_back(std::make_unique<juce::AudioParameterBool>("power","Power",true));
 p.push_back(std::make_unique<juce::AudioParameterBool>("limit","Limit / Compress",false)); return {p.begin(),p.end()};
}
ArmNongMuangLA2AAudioProcessor::ArmNongMuangLA2AAudioProcessor():AudioProcessor(BusesProperties().withInput("Input",juce::AudioChannelSet::stereo(),true).withOutput("Output",juce::AudioChannelSet::stereo(),true)),parameters(*this,nullptr,"PARAMETERS",makeParams()){}
void ArmNongMuangLA2AAudioProcessor::prepareToPlay(double sr,int n){juce::dsp::ProcessSpec s{sr,(juce::uint32)n,(juce::uint32)getTotalNumOutputChannels()}; compressor.prepare(s);outputGain.prepare(s);compressor.setAttack(10);compressor.setRelease(100);}
void ArmNongMuangLA2AAudioProcessor::releaseResources(){}
bool ArmNongMuangLA2AAudioProcessor::isBusesLayoutSupported(const BusesLayout& l)const{auto i=l.getMainInputChannelSet(),o=l.getMainOutputChannelSet();return i==o&&(o==juce::AudioChannelSet::mono()||o==juce::AudioChannelSet::stereo());}
void ArmNongMuangLA2AAudioProcessor::processBlock(juce::AudioBuffer<float>& b,juce::MidiBuffer&){juce::ScopedNoDenormals g;if(parameters.getRawParameterValue("power")->load()<.5f)return;
 float peak=parameters.getRawParameterValue("peak")->load(),gain=parameters.getRawParameterValue("gain")->load();
 compressor.setThreshold(-2-peak*.38f);compressor.setRatio(parameters.getRawParameterValue("limit")->load()>.5f?10:3);
 compressor.setAttack(parameters.getRawParameterValue("attack")->load());compressor.setRelease(parameters.getRawParameterValue("release")->load());outputGain.setGainDecibels((gain-50)*.24f);
 juce::dsp::AudioBlock<float> block(b);compressor.process(juce::dsp::ProcessContextReplacing<float>(block));outputGain.process(juce::dsp::ProcessContextReplacing<float>(block));}
void ArmNongMuangLA2AAudioProcessor::chooseNamFile(const juce::File& f){if(!f.existsAsFile()||f.getFileExtension().toLowerCase()!=".nam"){namStatus="Invalid file. Choose a .nam model.";return;}namPath=f.getFullPathName();namStatus="Selected "+f.getFileName()+"; NAM inference is not implemented.";}
void ArmNongMuangLA2AAudioProcessor::getStateInformation(juce::MemoryBlock& d){auto s=parameters.copyState();s.setProperty("namPath",namPath,nullptr);if(auto x=s.createXml())copyXmlToBinary(*x,d);}
void ArmNongMuangLA2AAudioProcessor::setStateInformation(const void* d,int n){if(auto x=getXmlFromBinary(d,n))if(x->hasTagName(parameters.state.getType()))parameters.replaceState(juce::ValueTree::fromXml(*x));}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new ArmNongMuangLA2AAudioProcessor();}

juce::AudioProcessorEditor* ArmNongMuangLA2AAudioProcessor::createEditor() { return new ArmNongMuangLA2AAudioProcessorEditor(*this); }
