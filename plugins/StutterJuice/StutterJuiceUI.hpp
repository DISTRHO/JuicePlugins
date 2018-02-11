/*
 * Stutter Juice Plugin
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

#ifndef STUTTERJUICEUI_HPP_INCLUDED
#define STUTTERJUICEUI_HPP_INCLUDED

#include "DistrhoUI.hpp"

#include "ImageWidgets.hpp"

using DGL::Image;
using DGL::ImageAboutWindow;
using DGL::ImageButton;
using DGL::ImageKnob;
using DGL::ImageSlider;
using DGL::Rectangle;

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class StutterJuiceUI : public UI,
                       public ImageButton::Callback,
                       public ImageSlider::Callback
{
public:
    StutterJuiceUI();

protected:
	// -------------------------------------------------------------------
	// DSP Callbacks

	void parameterChanged(uint32_t index, float value) override;
	void programLoaded(uint32_t index) override;

	// -------------------------------------------------------------------
	// Widget Callbacks

	void imageButtonClicked(ImageButton* button, int) override;
	void imageSliderDragStarted(ImageSlider* slider) override;
	void imageSliderDragFinished(ImageSlider* slider) override;
	void imageSliderValueChanged(ImageSlider* slider, float value) override;

	void onDisplay() override;

private:
	Image fImgBackground;
	Image fImgOverlay;
	ImageAboutWindow fAboutWindow;
	
	float outputParams[9];
	
	void drawLFOs() {
		int oX = 18;
		int oY = 67;
		int wX = 223;
		wX /=4;
		int wY = 26;
		int mX = 228;
		int mY = 116;
		
		wX = 221+2;
		wY = 111;
		
		// set color
		
		for (int y=0; y<3; y++) {
			for (int x=0; x<3; x++) {
				if (outputParams[x+y*3]!=0) {
					glColor4f(0.0f, 0.0f, 1.0f, 0.5f - outputParams[x+y*3]/2);
					glBegin(GL_POLYGON);
						glVertex2i(oX+x*mX, oY+y*mY);
						glVertex2i(oX+x*mX, oY+y*mY+wY);
						glVertex2i(oX+x*mX+wX, oY+y*mY+wY);
						glVertex2i(oX+x*mX+wX, oY+y*mY);
					glEnd();
				}
			}
		}
		
		// reset color
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//sliders
	ScopedPointer<ImageSlider> fSliders[9][3];
	ScopedPointer<ImageButton> fButtonAbout;
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // TRIGGERJUICEUI_HPP_INCLUDED
