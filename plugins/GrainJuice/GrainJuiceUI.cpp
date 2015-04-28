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

#include "GrainJuicePlugin.hpp"
#include "GrainJuiceUI.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

GrainJuiceUI::GrainJuiceUI()
	: UI(),
	  fAboutWindow(this) {

	setSize(GrainJuiceArtwork::backgroundWidth, GrainJuiceArtwork::backgroundHeight);

	// background
	fImgBackground = Image(GrainJuiceArtwork::backgroundData, GrainJuiceArtwork::backgroundWidth, GrainJuiceArtwork::backgroundHeight, GL_BGR);

	// about
	Image aboutImage(GrainJuiceArtwork::aboutData, GrainJuiceArtwork::aboutWidth, GrainJuiceArtwork::aboutHeight, GL_BGR);
	fAboutWindow.setImage(aboutImage);

	// knobs
	Image knobImage(GrainJuiceArtwork::knobData, GrainJuiceArtwork::knobWidth, GrainJuiceArtwork::knobHeight);

#define PX 56 //position top X
#define PY 98 //position top Y
#define SX 70 //spacing X
#define SY 86 //spacing Y

	// knob Size
	fKnobSize = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobSize->setId(GrainJuicePlugin::paramSize);
	fKnobSize->setAbsolutePos(PX, PY);
	fKnobSize->setRotationAngle(270);
	fKnobSize->setRange(0.0f, 1.0f);
	fKnobSize->setDefault(0.5f);
	fKnobSize->setStep(0.01f);
	fKnobSize->setCallback(this);

	// knob Scatter
	fKnobScatter = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobScatter->setId(GrainJuicePlugin::paramScatter);
	fKnobScatter->setAbsolutePos(PX+SX, PY);
	fKnobScatter->setRotationAngle(270);
	fKnobScatter->setRange(0.0f, 1.0f);
	fKnobScatter->setDefault(0.5f);
	fKnobScatter->setStep(0.01f);
	fKnobScatter->setCallback(this);

	// knob Gain
	fKnobGain = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobGain->setId(GrainJuicePlugin::paramGain);
	fKnobGain->setAbsolutePos(PX+SX*2, PY);
	fKnobGain->setRotationAngle(270);
	fKnobGain->setRange(0.0f, 1.0f);
	fKnobGain->setDefault(0.5f);
	fKnobGain->setStep(0.01f);
	fKnobGain->setCallback(this);

	// knob Density
	fKnobDensity = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobDensity->setId(GrainJuicePlugin::paramDensity);
	fKnobDensity->setAbsolutePos(PX+SX*3, PY);
	fKnobDensity->setRotationAngle(270);
	fKnobDensity->setRange(0.0f, 1.0f);
	fKnobDensity->setDefault(0.5f);
	fKnobDensity->setStep(0.01f);
	fKnobDensity->setCallback(this);

	// knob LPF
	fKnobLPF = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobLPF->setId(GrainJuicePlugin::paramLPF);
	fKnobLPF->setAbsolutePos(PX+SX*4, PY);
	fKnobLPF->setRotationAngle(270);
	fKnobLPF->setRange(0.0f, 1.0f);
	fKnobLPF->setDefault(0.5f);
	fKnobLPF->setStep(0.01f);
	fKnobLPF->setCallback(this);

	// knob HPF
	fKnobHPF = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobHPF->setId(GrainJuicePlugin::paramHPF);
	fKnobHPF->setAbsolutePos(PX+SX*5, PY);
	fKnobHPF->setRotationAngle(270);
	fKnobHPF->setRange(0.0f, 1.0f);
	fKnobHPF->setDefault(0.5f);
	fKnobHPF->setStep(0.01f);
	fKnobHPF->setCallback(this);




	//////////// RANDOMIZE KNOBS



	// knob Size
	fKnobSizeR = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobSizeR->setId(GrainJuicePlugin::paramSizeR);
	fKnobSizeR->setAbsolutePos(PX, PY+SY);
	fKnobSizeR->setRotationAngle(270);
	fKnobSizeR->setRange(0.0f, 1.0f);
	fKnobSizeR->setDefault(0.5f);
	fKnobSizeR->setStep(0.01f);
	fKnobSizeR->setCallback(this);

	// knob Scatter
	fKnobScatterR = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobScatterR->setId(GrainJuicePlugin::paramScatterR);
	fKnobScatterR->setAbsolutePos(PX+SX, PY+SY);
	fKnobScatterR->setRotationAngle(270);
	fKnobScatterR->setRange(0.0f, 1.0f);
	fKnobScatterR->setDefault(0.5f);
	fKnobScatterR->setStep(0.01f);
	fKnobScatterR->setCallback(this);

	// knob Gain
	fKnobGainR = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobGainR->setId(GrainJuicePlugin::paramGainR);
	fKnobGainR->setAbsolutePos(PX+SX*2, PY+SY);
	fKnobGainR->setRotationAngle(270);
	fKnobGainR->setRange(0.0f, 1.0f);
	fKnobGainR->setDefault(0.5f);
	fKnobGainR->setStep(0.01f);
	fKnobGainR->setCallback(this);

	// knob Density
	fKnobDensityR = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobDensityR->setId(GrainJuicePlugin::paramDensityR);
	fKnobDensityR->setAbsolutePos(PX+SX*3, PY+SY);
	fKnobDensityR->setRotationAngle(270);
	fKnobDensityR->setRange(0.0f, 1.0f);
	fKnobDensityR->setDefault(0.5f);
	fKnobDensityR->setStep(0.01f);
	fKnobDensityR->setCallback(this);

	// knob LPF
	fKnobLPFR = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobLPFR->setId(GrainJuicePlugin::paramLPFR);
	fKnobLPFR->setAbsolutePos(PX+SX*4, PY+SY);
	fKnobLPFR->setRotationAngle(270);
	fKnobLPFR->setRange(0.0f, 1.0f);
	fKnobLPFR->setDefault(0.5f);
	fKnobLPFR->setStep(0.01f);
	fKnobLPFR->setCallback(this);

	// knob HPF
	fKnobHPFR = new ImageKnob(this, knobImage, ImageKnob::Vertical);
	fKnobHPFR->setId(GrainJuicePlugin::paramHPFR);
	fKnobHPFR->setAbsolutePos(PX+SX*5, PY+SY);
	fKnobHPFR->setRotationAngle(270);
	fKnobHPFR->setRange(0.0f, 1.0f);
	fKnobHPFR->setDefault(0.5f);
	fKnobHPFR->setStep(0.01f);
	fKnobHPFR->setCallback(this);

	// about button
	Image aboutImageNormal(GrainJuiceArtwork::aboutButtonNormalData, GrainJuiceArtwork::aboutButtonNormalWidth, GrainJuiceArtwork::aboutButtonNormalHeight);
	Image aboutImageHover(GrainJuiceArtwork::aboutButtonHoverData, GrainJuiceArtwork::aboutButtonHoverWidth, GrainJuiceArtwork::aboutButtonHoverHeight);
	fButtonAbout = new ImageButton(this, aboutImageNormal, aboutImageHover, aboutImageHover);
	fButtonAbout->setAbsolutePos(390, 20);
	fButtonAbout->setCallback(this);

	// set default values
	d_programChanged(0);
}

// -----------------------------------------------------------------------
// DSP Callbacks

void GrainJuiceUI::d_parameterChanged(uint32_t index, float value) {
	switch (index) {
	case GrainJuicePlugin::paramSize:
		fKnobSize->setValue(value);
		break;
	case GrainJuicePlugin::paramScatter:
		fKnobScatter->setValue(value);
		break;
	case GrainJuicePlugin::paramGain:
		fKnobGain->setValue(value);
		break;
	case GrainJuicePlugin::paramDensity:
		fKnobDensity->setValue(value);
		break;
	case GrainJuicePlugin::paramLPF:
		fKnobLPF->setValue(value);
		break;
	case GrainJuicePlugin::paramHPF:
		fKnobHPF->setValue(value);
		break;

	case GrainJuicePlugin::paramSizeR:
		fKnobSizeR->setValue(value);
		break;
	case GrainJuicePlugin::paramScatterR:
		fKnobScatterR->setValue(value);
		break;
	case GrainJuicePlugin::paramGainR:
		fKnobGainR->setValue(value);
		break;
	case GrainJuicePlugin::paramDensityR:
		fKnobDensityR->setValue(value);
		break;
	case GrainJuicePlugin::paramLPFR:
		fKnobLPFR->setValue(value);
		break;
	case GrainJuicePlugin::paramHPFR:
		fKnobHPFR->setValue(value);
		break;
	}
}

void GrainJuiceUI::d_programChanged(uint32_t index) {
	if (index != 0)
		return;

	// Default values
	fKnobSize->setValue(0.5f);
	fKnobScatter->setValue(0.5f);
	fKnobGain->setValue(0.5f);
	fKnobDensity->setValue(0.5f);
	fKnobLPF->setValue(0.5f);
	fKnobHPF->setValue(0.5f);

	fKnobSizeR->setValue(0.5f);
	fKnobScatterR->setValue(0.5f);
	fKnobGainR->setValue(0.5f);
	fKnobDensityR->setValue(0.5f);
	fKnobLPFR->setValue(0.5f);
	fKnobHPFR->setValue(0.5f);
}

// -----------------------------------------------------------------------
// Widget Callbacks

void GrainJuiceUI::imageButtonClicked(ImageButton* button, int) {
	if (button != fButtonAbout)
		return;

	fAboutWindow.exec();
}

void GrainJuiceUI::imageKnobDragStarted(ImageKnob* knob) {
	d_editParameter(knob->getId(), true);
}

void GrainJuiceUI::imageKnobDragFinished(ImageKnob* knob) {
	d_editParameter(knob->getId(), false);
}

void GrainJuiceUI::imageKnobValueChanged(ImageKnob* knob, float value) {
	d_setParameterValue(knob->getId(), value);
}

void GrainJuiceUI::onDisplay() {
	fImgBackground.draw();
}

// -----------------------------------------------------------------------

UI* createUI() {
	return new GrainJuiceUI();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
