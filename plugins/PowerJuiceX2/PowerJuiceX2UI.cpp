/*
 * Power Juice Plugin
 * Copyright (C) 2014 Andre Sklenar <andre.sklenar@gmail.com>, www.juicelab.cz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the doc/GPL.txt file.
 */

#include "PowerJuiceX2UI.hpp"

#include <cstdlib>
#include <ctime>

using DGL::Point;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PowerJuiceX2UI::PowerJuiceX2UI()
    : UI(PowerJuiceX2Artwork::backgroundWidth, PowerJuiceX2Artwork::backgroundHeight),
      fAboutWindow(this),
      dsp((PowerJuiceX2Plugin*)getPluginInstancePointer())
{
    DISTRHO_SAFE_ASSERT(dsp != nullptr);

    // background
    fImgBackground = Image(PowerJuiceX2Artwork::backgroundData, PowerJuiceX2Artwork::backgroundWidth, PowerJuiceX2Artwork::backgroundHeight, GL_BGR);

    // about
    Image imageAbout(PowerJuiceX2Artwork::aboutData, PowerJuiceX2Artwork::aboutWidth, PowerJuiceX2Artwork::aboutHeight, GL_BGR);
    fAboutWindow.setImage(imageAbout);

    // knobs
    Image knobImage(PowerJuiceX2Artwork::knobData, PowerJuiceX2Artwork::knobWidth, PowerJuiceX2Artwork::knobHeight);

    // knob Attack
    fKnobAttack = new ImageKnob(this, knobImage);
    fKnobAttack->setAbsolutePos(37, 213);
    fKnobAttack->setRange(0.1f, 1000.0f);
    fKnobAttack->setStep(0.1f);
    fKnobAttack->setValue(20.0f);
    fKnobAttack->setRotationAngle(270);
    fKnobAttack->setCallback(this);

    // knob Release
    fKnobRelease = new ImageKnob(this, knobImage);
    fKnobRelease->setAbsolutePos(136, 213);
    fKnobRelease->setRange(0.1f, 1000.0f);
    fKnobRelease->setValue(0.1f);
    fKnobRelease->setRotationAngle(270);
    fKnobRelease->setCallback(this);

    // knob Threshold
    fKnobThreshold = new ImageKnob(this, knobImage);
    fKnobThreshold->setAbsolutePos(235, 213);
    fKnobThreshold->setRange(-60.0f, 0.0f);
    fKnobThreshold->setValue(0.0f);
    fKnobThreshold->setRotationAngle(270);
    fKnobThreshold->setCallback(this);

    // knob Ratio
    fKnobRatio = new ImageKnob(this, knobImage);
    fKnobRatio->setAbsolutePos(334, 213);
    fKnobRatio->setRange(1.0f, 10.0f);
    fKnobRatio->setValue(1.0f);
    fKnobRatio->setRotationAngle(270);
    fKnobRatio->setCallback(this);

    // knob Make-Up
    fKnobMakeup = new ImageKnob(this, knobImage);
    fKnobMakeup->setAbsolutePos(433, 213);
    fKnobMakeup->setRange(0.0f, 20.0f);
    fKnobMakeup->setValue(0.0f);
    fKnobMakeup->setRotationAngle(270);
    fKnobMakeup->setCallback(this);

    // knob Mix
    fKnobMix = new ImageKnob(this, knobImage);
    fKnobMix->setAbsolutePos(532, 213);
    fKnobMix->setRange(0.0f, 1.0f);
    fKnobMix->setValue(1.0f);
    fKnobMix->setRotationAngle(270);
    fKnobMix->setCallback(this);

    // about button
    Image aboutImageNormal(PowerJuiceX2Artwork::aboutButtonNormalData, PowerJuiceX2Artwork::aboutButtonNormalWidth, PowerJuiceX2Artwork::aboutButtonNormalHeight);
    Image aboutImageHover(PowerJuiceX2Artwork::aboutButtonHoverData, PowerJuiceX2Artwork::aboutButtonHoverWidth, PowerJuiceX2Artwork::aboutButtonHoverHeight);
    fButtonAbout = new ImageButton(this, aboutImageNormal, aboutImageHover, aboutImageHover);
    fButtonAbout->setAbsolutePos(502, 17);
    fButtonAbout->setCallback(this);

    // set default values
    programLoaded(0);
}

// -----------------------------------------------------------------------
// DSP Callbacks

void PowerJuiceX2UI::parameterChanged(uint32_t index, float value)
{
    switch (index)
    {
    case PowerJuiceX2Plugin::paramAttack:
        fKnobAttack->setValue(value);
        break;
    case PowerJuiceX2Plugin::paramRelease:
        fKnobRelease->setValue(value);
        break;
    case PowerJuiceX2Plugin::paramThreshold:
        fKnobThreshold->setValue(value);
        break;
    case PowerJuiceX2Plugin::paramRatio:
        fKnobRatio->setValue(value);
        break;
    case PowerJuiceX2Plugin::paramMakeup:
        fKnobMakeup->setValue(value);
        break;
    case PowerJuiceX2Plugin::paramMix:
        fKnobMix->setValue(value);
        break;
    }
}

void PowerJuiceX2UI::programLoaded(uint32_t index)
{
    if (index != 0)
        return;

    // Default values
    fKnobAttack->setValue(20.0f);
    fKnobRelease->setValue(200.0f);
    fKnobThreshold->setValue(0.0f);
    fKnobRatio->setValue(1.0f);
    fKnobMakeup->setValue(0.0f);
    fKnobMix->setValue(1.0f);
}

// -----------------------------------------------------------------------
// Widget Callbacks

void PowerJuiceX2UI::imageButtonClicked(ImageButton* button, int)
{
    if (button != fButtonAbout)
        return;

    fAboutWindow.exec();
}

void PowerJuiceX2UI::imageKnobDragStarted(ImageKnob* knob)
{
    if (knob == fKnobAttack)
        editParameter(PowerJuiceX2Plugin::paramAttack, true);
    else if (knob == fKnobRelease)
        editParameter(PowerJuiceX2Plugin::paramRelease, true);
    else if (knob == fKnobThreshold)
        editParameter(PowerJuiceX2Plugin::paramThreshold, true);
    else if (knob == fKnobRatio)
        editParameter(PowerJuiceX2Plugin::paramRatio, true);
    else if (knob == fKnobMakeup)
        editParameter(PowerJuiceX2Plugin::paramMakeup, true);
    else if (knob == fKnobMix)
        editParameter(PowerJuiceX2Plugin::paramMix, true);
}

void PowerJuiceX2UI::imageKnobDragFinished(ImageKnob* knob)
{
    if (knob == fKnobAttack)
        editParameter(PowerJuiceX2Plugin::paramAttack, false);
    else if (knob == fKnobRelease)
        editParameter(PowerJuiceX2Plugin::paramRelease, false);
    else if (knob == fKnobThreshold)
        editParameter(PowerJuiceX2Plugin::paramThreshold, false);
    else if (knob == fKnobRatio)
        editParameter(PowerJuiceX2Plugin::paramRatio, false);
    else if (knob == fKnobMakeup)
        editParameter(PowerJuiceX2Plugin::paramMakeup, false);
    else if (knob == fKnobMix)
        editParameter(PowerJuiceX2Plugin::paramMix, false);
}

void PowerJuiceX2UI::imageKnobValueChanged(ImageKnob* knob, float value)
{
    if (knob == fKnobAttack) 
        setParameterValue(PowerJuiceX2Plugin::paramAttack, value);
    else if (knob == fKnobRelease)
        setParameterValue(PowerJuiceX2Plugin::paramRelease, value);
    else if (knob == fKnobThreshold)
        setParameterValue(PowerJuiceX2Plugin::paramThreshold, value);
    else if (knob == fKnobRatio)
        setParameterValue(PowerJuiceX2Plugin::paramRatio, value);
    else if (knob == fKnobMakeup)
        setParameterValue(PowerJuiceX2Plugin::paramMakeup, value);
    else if (knob == fKnobMix)
        setParameterValue(PowerJuiceX2Plugin::paramMix, value);

}

void PowerJuiceX2UI::uiIdle()
{
    if (dsp != nullptr && dsp->repaintNeeded())
        repaint();
}

void PowerJuiceX2UI::onDisplay()
{
    fImgBackground.draw();

    if (dsp == nullptr)
        return;

    int w = 563; //waveform plane size, size of the plane in pixels;
    int w2 = 1126; //wavefowm array
    int h = 121; //waveform plane height
    int x = 27; //waveform plane positions
    int y = 53;
    int dc = 113; //0DC line y position


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);



    float thresholdPosition = (-toIEC(fKnobThreshold->getValue()))/200*h+h+y;

    //draw waveform
    /*
    glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
    glLineWidth(1.2f);
    for (int i=0; i<w; i++) {

        glBegin(GL_LINES);
            glVertex2i(x+i, -toIEC(shmData->input[i])/200*h+h+y);
            glVertex2i(x+i, y+h);
        glEnd();
    }
    */
    //draw RMS

    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (int i=2; i<w; i++) {
            float value = dsp->getRMSHistory(i);
            if (value<thresholdPosition) {
                glColor4f(0.0f, 0.5f, 0.0f, 1.0f);
            } else {
                glColor4f(0.0f, 0.5f, 0.2f, 1.0f);
            }
            glVertex2i(x+i, value);
    }
    glEnd();
	
    //draw gain reduction
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i=2; i<w; i++) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
        float value = dsp->getGainReductionHistory(i);
	   
          glVertex2i(x+i, value);
        glVertex2i(x+i, y);

        value = dsp->getRMSHistory(i);
        glColor4f(0.0f, 0.5f, 0.2f, 0.1f);
          glVertex2i(x+i, value);
        glVertex2i(x+i, y+h);
    }
    glEnd();
	

    //draw Threshold
    glLineWidth(2.0f);
    glColor4f(0.4f, 0.4f, 1.0f, 0.8f);
    //float thresholdPosition = ((60-fKnobThreshold->getValue())/60);
    glBegin(GL_LINES);
            glVertex2i(x, thresholdPosition);
            glVertex2i(x+w, thresholdPosition);
    glEnd();

    // reset color
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new PowerJuiceX2UI();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
