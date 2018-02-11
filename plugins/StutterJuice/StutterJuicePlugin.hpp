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

#ifndef STUTTERJUICEPLUGIN_HPP_INCLUDED
#define STUTTERJUICEPLUGIN_HPP_INCLUDED

#include "DistrhoPlugin.hpp"
#include "CModule.hxx"


START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class StutterJuicePlugin : public Plugin
{
public:
	enum Parameters
	{
		p1 = 0, p2, p3, p4, p5, p6, p7, p8, p9,
		p11, p12, p13, p14, p15, p16, p17, p18,
		p19, p20, p21, p22, p23, p24, p25, p26,
		o1, o2, o3, o4, o5, o6, o7, o8, o9,
		paramCount
	};
	
	
	void prepareOutputParams() {
		
		for (int i=0; i<6; i++) {
			if (modules[i]->isActive()) {
				outputParams[i] = modules[i]->getOutputParam();
			} else {
				outputParams[i] = 0;
			}
		}
	}
	
	void rollLFOs() {
		
		float bar, tick, tickOffset, sinePos, percentage;
		
		for (int i=0; i<6; i++) {
			sinePos = modules[i]->getSinePos();
			float tempoDivider = modules[i]->getTempoDivider();
			//if (i==4)
				//printf("divider: %i\n", tempoDivider);
			/* sample count for one bar */
			const TimePosition& time(getTimePosition());
			bar = ((120.0/(time.bbt.valid ? time.bbt.beatsPerMinute : 120.0))*(getSampleRate())); //ONE, two, three, four
			tick = bar/(std::round(params[i][0]*16+2))*tempoDivider; //size of one target wob
			//if (time.bbt.valid) printf("hell yeah!\n");
			if (time.playing)
			{
				/* if rolling then sync to timepos */
				tickOffset = time.frame-std::floor(time.frame/tick)*tick; //how much after last tick

				if (tickOffset!=0) {
					//TODO: why do we need this??
					percentage = tickOffset/tick;
				} else {
					percentage = 0;
				}
				sinePos = (M_PI*2)*percentage;

				if (sinePos>2*M_PI) {
					//TODO: can this ever happen??
				  sinePos = 0;
				}
			}
			else
			{
				/* else just keep on wobblin' */
				sinePos += (2*M_PI)/(tick); //wtf, but works
				if (sinePos>2*M_PI) {
					sinePos = 0;
				}
			}
			modules[i]->setSinePos(sinePos);
			//printf("sinepos: %f\n", sinePos);
		}
	
	}
	

	StutterJuicePlugin();
	//~StutterJuicePlugin() override;

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "StutterJuice";
    }

    const char* getMaker() const noexcept override
    {
        return "Andre Sklenar";
    }

    const char* getLicense() const noexcept override
    {
        return "GPL v2+";
    }

    uint32_t getVersion() const noexcept override
    {
        return 0x1000;
    }

    long getUniqueId() const noexcept override
    {
        return d_cconst('S', 't', 't', 'J');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void  setParameterValue(uint32_t index, float value) override;
    void  loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;
    void deactivate() override;
    void run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;

    // -------------------------------------------------------------------

private:

	float params[9][3]; // left-> right, top->bottom
	bool moduleActive[9];
	float outputParams[9];
	
	
	
	CModule* modules[9];
	
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // TRIGGERJUICE_HPP_INCLUDED
