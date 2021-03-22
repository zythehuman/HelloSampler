/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessorEditor::HelloSamplerAudioProcessorEditor (HelloSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumnail (p), mADSR(p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    auto image = juce::ImageCache::getFromMemory (BinaryData::PIC_png, BinaryData::PIC_pngSize);
    if (! image.isNull())
        mImageComponent.setImage (image, juce::RectanglePlacement::stretchToFit);
    else
        jassert(!image.isNull());
    
    
    addAndMakeVisible(mWaveThumnail);
    addAndMakeVisible(mADSR);
    addAndMakeVisible(mImageComponent);
    startTimerHz(30);
    setSize (600, 400);
}

HelloSamplerAudioProcessorEditor::~HelloSamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void HelloSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    //modifiedbyzyTheHuman
    g.fillAll(juce::Colours::black);
    
//    g.setColour(juce::Colours::white);
//    g.setFont( 15.0f);
//
//
//    if (audioProcessor.getNumSamplerSounds() > 0)
//    {
//        g.fillAll(juce::Colours::red);
//
//        g.drawFittedText("Sound Loaded", getWidth() /2 - 50, getHeight() /2 - 10, 100, 20, juce::Justification::centred, 10);
//    }
//    else
//    {
//        g.drawFittedText("Please load a sound", getWidth() /2 - 50, getHeight() /2 - 10, 100, 20, juce::Justification::centred, 10);
//    }
    

}

void HelloSamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //modifiedbyzyTheHuman
   // mLoadButton.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
    mWaveThumnail.setBoundsRelative(0.0f, 0.25f, 1.0f, 0.5);
    mADSR.setBoundsRelative(0.0f, 0.75f, 1.0f, 0.25f);
    mImageComponent.setBoundsRelative(0.0f, 0.0f, 0.12f, 0.25f); 
    
}

void HelloSamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}



//modifiedbyzyTheHuman
//void HelloSamplerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
//{
//    if (slider == &mAttackSlider)
//    {
//        audioProcessor.getADSRParams().attack = mAttackSlider.getValue();
//    }
//    else if (slider == &mDecaySlider)
//    {
//        audioProcessor.getADSRParams().decay = mDecaySlider.getValue();
//    }
//    else if (slider == &mSustainSlider)
//    {
//        audioProcessor.getADSRParams().sustain = mSustainSlider.getValue();
//    }
//    else if (slider == &mReleaseSlider)
//    {
//        audioProcessor.getADSRParams().release = mReleaseSlider.getValue();
//    }
//
//    audioProcessor.updateADSR();
//}
