/*
 * Grain Juice Plugin
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

#ifndef GrainJUICEUI_HPP_INCLUDED
#define GrainJUICEUI_HPP_INCLUDED

#include "DistrhoUI.hpp"

#include "ImageAboutWindow.hpp"
#include "ImageButton.hpp"
#include "ImageKnob.hpp"

#include "GrainJuiceArtwork.hpp"

using DGL::Image;
using DGL::ImageAboutWindow;
using DGL::ImageButton;
using DGL::ImageKnob;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class GrainJuiceUI : public UI,
	public ImageButton::Callback,
	public ImageKnob::Callback {
public:
	GrainJuiceUI();

protected:

	// -------------------------------------------------------------------
	// DSP Callbacks

	void d_parameterChanged(uint32_t index, float value) override;
	void d_programChanged(uint32_t index) override;

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

	ScopedPointer<ImageButton> fButtonAbout;
	ScopedPointer<ImageKnob>   fKnobSize, fKnobScatter, fKnobGain;
	ScopedPointer<ImageKnob>   fKnobDensity, fKnobLPF, fKnobHPF;

	ScopedPointer<ImageKnob>   fKnobSizeR, fKnobScatterR, fKnobGainR;
	ScopedPointer<ImageKnob>   fKnobDensityR, fKnobLPFR, fKnobHPFR;

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrainJuiceUI)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // GrainJUICEUI_HPP_INCLUDED
