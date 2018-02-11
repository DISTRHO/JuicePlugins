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

#ifndef POWERJUICEUI_HPP_INCLUDED
#define POWERJUICEUI_HPP_INCLUDED

#include "DistrhoUI.hpp"

#include "ImageWidgets.hpp"

#include "PowerJuiceX2Artwork.hpp"
#include "PowerJuiceX2Plugin.hpp"

#include <cmath>

using DGL::Image;
using DGL::ImageAboutWindow;
using DGL::ImageButton;
using DGL::ImageKnob;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PowerJuiceX2UI : public UI,
                       public ImageButton::Callback,
                       public ImageKnob::Callback
{
public:
    PowerJuiceX2UI();

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged(uint32_t index, float value) override;
    void programLoaded(uint32_t index) override;

    // -------------------------------------------------------------------
    // UI Callbacks

    void uiIdle() override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    void imageButtonClicked(ImageButton* button, int) override;
    void imageKnobDragStarted(ImageKnob* knob) override;
    void imageKnobDragFinished(ImageKnob* knob) override;
    void imageKnobValueChanged(ImageKnob* knob, float value) override;
    void onDisplay() override;

private:
    Image fImgBackground;
    ImageAboutWindow fAboutWindow;

    ScopedPointer<ImageKnob> fKnobAttack, fKnobRelease, fKnobThreshold;
    ScopedPointer<ImageKnob> fKnobRatio, fKnobMakeup, fKnobMix;
    ScopedPointer<ImageButton> fButtonAbout;

    PowerJuiceX2Plugin* const dsp;

    float fromDB(float gdb) {
        return (std::exp(gdb/20.f*std::log(10.f)));
    };

    float toDB(float g) {
        return (20.f*std::log10(g));
    }

    float toIEC(float db) {
         float def = 0.0f; /* Meter deflection %age */

         if (db < -70.0f) {
                 def = 0.0f;
         } else if (db < -60.0f) {
                 def = (db + 70.0f) * 0.25f;
         } else if (db < -50.0f) {
                 def = (db + 60.0f) * 0.5f + 5.0f;
         } else if (db < -40.0f) {
                 def = (db + 50.0f) * 0.75f + 7.5;
         } else if (db < -30.0f) {
                 def = (db + 40.0f) * 1.5f + 15.0f;
         } else if (db < -20.0f) {
                 def = (db + 30.0f) * 2.0f + 30.0f;
         } else if (db < 0.0f) {
                 def = (db + 20.0f) * 2.5f + 50.0f;
         } else {
                 def = 100.0f;
         }

         return (def * 2.0f);
    }
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // POWERJUICEUI_HPP_INCLUDED
