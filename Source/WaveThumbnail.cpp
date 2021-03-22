/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 18 Mar 2021 9:59:52pm
    Author:  Zhiyang Yu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail(HelloSamplerAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveThumbnail::~WaveThumbnail()
{
}

//modifiedbyzyTheHuman
void WaveThumbnail::paint (juce::Graphics& g)
{
    
    
    g.fillAll (juce::Colours::cadetblue.darker());
    //new file dropped?
        //if yes
            //get the waveform form the processor
            //find ratio: sample = 44100 (1 sec)... x axis of window = 600 sampleLength / getwidth()
            //values of audiofile -1 to 1... size of y axis is 200
            //use the ratio to take values from the audio buffer and put in vector to display
            //draw the waveform
    auto waveform = processor.getWaveForm();
    
    if (waveform.getNumSamples() > 0)
    {
        juce::Path p;
        p.clear();
        mAudioPoints.clear();
        
        
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);
        
        //scale audio file to window on x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
        {
            mAudioPoints.push_back (buffer[sample]);
        }
        
        g.setColour(juce::Colours::yellow);
        p.startNewSubPath(0, getHeight() / 2);
        
        //scale on y axis
        for (int sample = 0; sample <mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float> (mAudioPoints[sample], -1, 1, getHeight(), 0);
            p.lineTo (sample, point);
        }
        
        g.strokePath(p, juce::PathStrokeType(2));
        
        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        
        auto textbounds = getLocalBounds().reduced(10, 10);
        
        g.drawFittedText(mFileName, textbounds, juce::Justification::topRight, 1);
        
        auto playHeadPosition = juce::jmap<int> (processor.getSampleCount(), 0, processor.getWaveForm().getNumSamples(), 0, getWidth());
        
        g.setColour(juce::Colours::white);
        g.drawLine(playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);
        g.setColour(juce::Colours::black.withAlpha(0.2f));
        g.fillRect(0, 0, playHeadPosition, getHeight());
     
    }
    else
    {
        g.setColour(juce::Colours::white);
        g.setFont(40.0f);
        g.drawFittedText("Drop an Audio File to Load", getLocalBounds(), juce::Justification::centred, 1);
    }
    
}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

//modifiedbyzyTheHuman
bool WaveThumbnail::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files)
    {
        if(file.contains(".wav") || file.contains(".mp3"))
        {
            return true;
        }
    }
    
    return false;
}

//modifiedbyzyTheHuman
void WaveThumbnail::filesDropped(const juce::StringArray& files, int x, int y)
{
 
    for (auto file : files)
    {
        if (isInterestedInFileDrag (file))
        {
            auto myFile = std::make_unique<juce::File>(file);
            mFileName = myFile->getFileNameWithoutExtension();
            
            //load this file
            processor.loadFile(file);
        }
    }
    repaint();
}
