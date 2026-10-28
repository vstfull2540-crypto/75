#include "PluginEditor.h"
#include "BinaryData.h"
ArmNongMuangLA2AAudioProcessorEditor::ArmNongMuangLA2AAudioProcessorEditor(ArmNongMuangLA2AAudioProcessor& p):AudioProcessorEditor(p),processor(p){
 background=juce::ImageCache::getFromMemory(BinaryData::LA2A_Interface_png,BinaryData::LA2A_Interface_pngSize);setSize(1000,545);
 setup(gain,"GAIN");setup(peak,"PEAK REDUCTION");setup(attack,"ATTACK");setup(release,"RELEASE");
 for(auto*s:{&gain,&peak,&attack,&release})addAndMakeVisible(*s);
 gain.setRange(0,100,.1);gain.setValue(50);peak.setRange(0,100,.1);peak.setValue(35);attack.setRange(.1,10,.01);attack.setValue(1);release.setRange(50,5000,1);release.setValue(500);
 gain.onValueChange=[this]{processor.parameters.getParameter("gain")->setValueNotifyingHost((float)gain.getValue()/100);};
 peak.onValueChange=[this]{processor.parameters.getParameter("peak")->setValueNotifyingHost((float)peak.getValue()/100);};
 attack.onValueChange=[this]{processor.parameters.getParameter("attack")->setValueNotifyingHost((float)((attack.getValue()-.1)/9.9));};
 release.onValueChange=[this]{processor.parameters.getParameter("release")->setValueNotifyingHost((float)((release.getValue()-50)/4950));};
 addAndMakeVisible(power);power.setButtonText("POWER");power.setClickingTogglesState(true);power.setToggleState(true,juce::dontSendNotification);power.onClick=[this]{processor.parameters.getParameter("power")->setValueNotifyingHost(power.getToggleState()?1:0);};
 addAndMakeVisible(limit);limit.setButtonText("LIMIT / COMPRESS");limit.setClickingTogglesState(true);limit.onClick=[this]{processor.parameters.getParameter("limit")->setValueNotifyingHost(limit.getToggleState()?1:0);};
 addAndMakeVisible(meter);meter.addItem("INPUT",1);meter.addItem("OUTPUT",2);meter.addItem("GAIN REDUCTION",3);meter.setSelectedId(3);
 addAndMakeVisible(loadNam);loadNam.onClick=[this]{chooser=std::make_unique<juce::FileChooser>("Select LA-2A Classic - Medium.nam",juce::File{},"*.nam");chooser->launchAsync(juce::FileBrowserComponent::openMode|juce::FileBrowserComponent::canSelectFiles,[this](const juce::FileChooser& c){auto f=c.getResult();if(f.existsAsFile()){processor.chooseNamFile(f);status.setText(processor.getNamStatus(),juce::dontSendNotification);}});};
 addAndMakeVisible(status);status.setColour(juce::Label::textColourId,juce::Colours::black);status.setText(processor.getNamStatus(),juce::dontSendNotification);
}
void ArmNongMuangLA2AAudioProcessorEditor::setup(juce::Slider&s,const juce::String& n){s.setName(n);s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);s.setTextBoxStyle(juce::Slider::TextBoxBelow,false,64,18);s.setColour(juce::Slider::rotarySliderFillColourId,juce::Colours::black);s.setColour(juce::Slider::thumbColourId,juce::Colours::darkred);s.setColour(juce::Slider::textBoxTextColourId,juce::Colours::black);s.setColour(juce::Slider::textBoxOutlineColourId,juce::Colours::transparentBlack);}
void ArmNongMuangLA2AAudioProcessorEditor::paint(juce::Graphics&g){g.fillAll(juce::Colours::white);if(background.isValid())g.drawImage(background,getLocalBounds().toFloat());else{g.setColour(juce::Colours::black);g.drawFittedText("LA-2A PNG background missing",getLocalBounds(),juce::Justification::centred,1);}}
void ArmNongMuangLA2AAudioProcessorEditor::resized(){float x=getWidth()/1512.0f,y=getHeight()/824.0f;auto p=[&](juce::Component&c,float a,float b,float w,float h){c.setBounds((int)(a*x),(int)(b*y),(int)(w*x),(int)(h*y));};p(gain,185,370,205,230);p(peak,1070,370,205,230);p(attack,500,650,160,160);p(release,800,650,160,160);p(power,1310,720,125,55);p(limit,1360,450,130,70);p(meter,125,730,180,42);p(loadNam,785,105,220,45);p(status,430,780,650,28);}
