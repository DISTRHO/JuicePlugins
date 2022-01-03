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

#include "StutterJuicePlugin.hpp"
#include <iostream>



START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------



StutterJuicePlugin::StutterJuicePlugin()
    : Plugin(paramCount, 1, 0) // 1 program, 0 states
{
	
    // set default values
    loadProgram(0);
	
    // reset
    deactivate();
}


// -----------------------------------------------------------------------
// Init

void StutterJuicePlugin::initParameter(uint32_t index, Parameter& parameter)
{

	if (index<26) {
		parameter.hints      = kParameterIsAutomatable;
		parameter.name       = "";
		parameter.symbol     = "";
		parameter.unit       = "";
		parameter.ranges.def = 0.0f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
	} else {
		parameter.hints      = kParameterIsOutput;
		parameter.name       = "";
		parameter.symbol     = "";
		parameter.unit       = "";
		parameter.ranges.def = 0.0f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
	}
}

void StutterJuicePlugin::initProgramName(uint32_t index, String& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float StutterJuicePlugin::getParameterValue(uint32_t index) const
{
	if (index<26) {
		int module = index/3;
		int param = index%3;
		return params[module][param];
	} else {
		return outputParams[index-26];
	}
}

void StutterJuicePlugin::setParameterValue(uint32_t index, float value)
{
	int module = index/3;
	int param = index%3;
	params[module][param] = value;
	modules[module]->setParam(value, param);
	if (param ==2) {
		//modules[module]->resetSinePos();
	}
}

void StutterJuicePlugin::loadProgram(uint32_t index)
{
	
	if (index != 0)
		return;

	//default params[][] values
	for (int module=0; module<6; module++) {
		moduleActive[module] = false;
		for (int param=0; param<3; param++) {
			params[module][param] = 0.5;
		}
	}
	
	modules[0] = new CGate();
	modules[1] = new CReverse();
	modules[2] = new CRepeat();
	modules[3] = new CSequence();
	modules[4] = new CShift();
	modules[5] = new CFilter();
	
	for (int module=0; module<6; module++) {
		modules[module]->setSampleRate(getSampleRate());
		modules[module]->initBuffers();
	}
	
	activate();

}

// -----------------------------------------------------------------------
// Process

void StutterJuicePlugin::activate()
{

}

void StutterJuicePlugin::deactivate()
{
}			

void StutterJuicePlugin::run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount)
{

	
	for (uint32_t i; i<frames; i++) {	
		
		float audioL = inputs[0][i];
		float audioR = inputs[1][i];
		
		rollLFOs();
		
		prepareOutputParams();
		
		for (int i=0; i<6; i++) {
			modules[i]->process(audioL, audioR);
		}
		
		outputs[0][i] = audioL;
		outputs[1][i] = audioR;
		
	}

	

	for (uint32_t i; i<midiEventCount; i++) {
	
		int userNote = 48;//TODO
		int range=6;

		if (midiEvents[i].size > MidiEvent::kDataSize)
			continue;

		int mType = midiEvents[i].data[0] & 0xF0;
		int mChan = midiEvents[i].data[0] & 0x0F;
		int mNum = midiEvents[i].data[1];
		
		if (mNum>=userNote && mNum<userNote+range) {
			int module = mNum-userNote;
			//printf("note: %i\n", module);
			if (mType == 0x90) {
				//NOTE ON
				moduleActive[module] = true;
				modules[module]->activate();
			} else if (mType == 0x80) {
				//NOTE OFF
				moduleActive[module] = false;
				modules[module]->deactivate();
			}
		}
	}
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new StutterJuicePlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
