/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//modifiedbyzyTheHuman
#include "WaveThumbnail.h"
#include "ADSRComponent.h"
//==============================================================================
/**
*/
class HelloSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor,
//modifiedbyzyTheHuman
                                          public juce::Timer
                                          //public juce::Slider::Listener

{
public:
    HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor&);
    ~HelloSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    
    //void sliderValueChanged (juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    //modifiedbyzyTheHuman
    //juce::TextButton mLoadButton { "LOAD" };

    WaveThumbnail mWaveThumnail;
    ADSRComponent mADSR;
    juce::ImageComponent mImageComponent;
   
    HelloSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloSamplerAudioProcessorEditor)
};
