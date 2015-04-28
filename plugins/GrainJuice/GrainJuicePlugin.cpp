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
#include <iostream>
#include <math.h>
#include <cmath>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

GrainJuicePlugin::GrainJuicePlugin()
	: Plugin(paramCount, 1, 0) { // 1 program, 0 states
	// set default values
	d_setProgram(0);
}

// -----------------------------------------------------------------------
// Init

void GrainJuicePlugin::d_initParameter(uint32_t index, Parameter& parameter) {
	switch (index) {
	case paramSize:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Size";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramScatter:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Scatter";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramGain:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Gain";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramDensity:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Density";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramLPF:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "LPF";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramHPF:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "HPF";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;

	case paramSizeR:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Size";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramScatterR:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Size";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramGainR:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Size";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramDensityR:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Size";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramLPFR:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Size";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;
	case paramHPFR:
		parameter.hints      = kParameterIsAutomable;
		parameter.name       = "Size";
		parameter.symbol     = "siz";
		parameter.unit       = "";
		parameter.ranges.def = 0.5f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 1.0f;
		break;

	}
}

void GrainJuicePlugin::d_initProgramName(uint32_t index, d_string& programName) {
	if (index != 0)
		return;

	programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float GrainJuicePlugin::d_getParameterValue(uint32_t index) const {
	switch (index) {
	case paramSize:
		return size;
	case paramScatter:
		return scatter;
	case paramGain:
		return gain;
	case paramDensity:
		return density;
	case paramLPF:
		return LPF;
	case paramHPF:
		return HPF;

	case paramSizeR:
		return sizeR;
	case paramScatterR:
		return scatterR;
	case paramGainR:
		return gainR;
	case paramDensityR:
		return densityR;
	case paramLPFR:
		return LPFR;
	case paramHPFR:
		return HPFR;
	default:
		return 0.0f;
	}
}

void GrainJuicePlugin::d_setParameterValue(uint32_t index, float value) {
	switch (index) {
	case paramSize:
		size = value;
		break;
	case paramScatter:
		scatter = value;
		break;
	case paramGain:
		gain = value;
		break;
	case paramDensity:
		density = value;
		break;
	case paramLPF:
		LPF = value;
		break;
	case paramHPF:
		HPF = value;
		break;


	case paramSizeR:
		sizeR = value;
		break;
	case paramScatterR:
		scatterR = value;
		break;
	case paramGainR:
		gainR = value;
		break;
	case paramDensityR:
		densityR = value;
		break;
	case paramLPFR:
		LPFR = value;
		break;
	case paramHPFR:
		HPFR = value;
		break;
	}
}

void GrainJuicePlugin::d_setProgram(uint32_t index) {
	if (index != 0)
		return;

	/* Default parameter values */
	size=scatter=gain=density=HPF=LPF=1.f;
	sizeR=scatterR=gainR=densityR=HPFR=LPFR=1.f;

	prevTotalGrains = 0;

	/* Default variable values */
	srand (time(NULL));
	nSample = new float[2];
	prevSample = new float[2];
	std::cout << "Starting." << std::endl;

	for (int i=0; i<1000; i++) {
		logTable[i] = expf((logf(0.999f)-logf(0.001f))*(i/1000.0f)+logf(0.999f));
	}
	logTable[0] = 0.0f;
	
	concurrentFilling = 0;

	d_activate();
}
// -----------------------------------------------------------------------
// GRAINS



GrainJuicePlugin::CGrain::CGrain(uint32_t nLength, uint32_t nDelay, float lpf, float hpf, float nGain) {
	length = nLength;
	readyForPlayback = false;
	delay = nDelay;
	playhead = 0;
	gain = nGain;

	//highPass = new HPF[2];
	//lowPass = new LPF[2];
	highPass[0].setSampleRate(48000);
	highPass[1].setSampleRate(48000);
	highPass[0].setReso(0.1f);
	highPass[1].setReso(0.1f);
	highPass[0].setFreq(hpf);
	highPass[1].setFreq(hpf);
	highPass[0].compute();
	highPass[1].compute();
	

	lowPass[0].setSampleRate(48000);
	lowPass[1].setSampleRate(48000);
	lowPass[0].setReso(1.4f);
	lowPass[1].setReso(1.4f);
	lowPass[0].setFreq(lpf);
	lowPass[1].setFreq(lpf);
	lowPass[0].compute();
	lowPass[1].compute();
}


bool GrainJuicePlugin::CGrain::wantsSample() {
	if (playhead<length && !readyForPlayback) {
		return true;
	} else {
		return false;
	}
}

void GrainJuicePlugin::CGrain::fillSample(float *nSample) {
	//std::cout << "omnom" << std::endl;
	//std::cout << "playhead: " << playhead << std::endl;
	//std::cout << "length: " << length << std::endl;
	samples[playhead][0] = nSample[0];
	samples[playhead][1] = nSample[1];
	playhead++;
	if (playhead==length-5) {
		readyForPlayback = true;
		applyEnvelope();
		playhead = length-5;
	}
}

float *GrainJuicePlugin::CGrain::getSample() {
	playhead--;
	float coeff = 0.5f * (1 - cosf((2.f * M_PI * playhead)/(length-1)));
	float newSample[2];
	for (int i = 0; i < 2; i++) {
		newSample[i] = samples[playhead][i];
		newSample[i] *= coeff*gain;
		newSample[i] = lowPass[i].process(newSample[i]);
		//newSample[i] = highPass[i].process(newSample[i]);
	}
	
	samples[playhead][0] = newSample[0];
	samples[playhead][1] = newSample[1];
	return samples[playhead];
}

bool GrainJuicePlugin::CGrain::inDelay() {
	if (delay>0) {
		playhead = length;
		delay--;
		return true;
	} else {
		return false;
	}
}

uint32_t GrainJuicePlugin::CGrain::getLength() {
	return length;
}

bool GrainJuicePlugin::CGrain::donePlaying() {
	if (playhead<1) { //TODO: fix so all the samples get played/recorded
		return true;
	} else {
		return false;
	}
}
void GrainJuicePlugin::CGrain::applyEnvelope() {
	
}


void GrainJuicePlugin::CGrain::updateParams(float nDensity, float nScatter, uint32_t nSRT) {
	density = nDensity;
	scatter = nScatter;
	SRT = nSRT;
}

void GrainJuicePlugin::CGrain::setDelay(uint32_t nDelay) {
	delay = nDelay;
}

float GrainJuicePlugin::CGrain::inspectSample(uint32_t index, int channel) {
	return samples[index][channel];
}

void GrainJuicePlugin::newGrain(bool first) {
// create a new grain
	concurrentFilling = 0;
	bool create = false;
	if (first) {
		create = true;
	} else if (grains.size()+1 <= density*MAXGRAINS) {
		create = true;
	}

	if (create) {
		uint32_t newGrainSize =(int) size*d_getSampleRate()*MAXGRAINSIZE;
		
		newGrainSize = rand() % newGrainSize-1000;
		newGrainSize += 1000;
		
		uint32_t delayChance = (1000 - (rand() % (int) (density*1000.f)))/25+1;
		//std::cout << "grain fill!" << std::endl;
		//std::cout << "chance: " <<  delayChance << std::endl;;
		//delayChance = 2;
		for (int d=0; d<delayChance; d++) {
			if (grains.size()+1 > density*MAXGRAINS) {
				break;
			}
			
			int newDelayTime = rand() % (int) (MAXSCATTER*scatter*d_getSampleRate());
			newDelayTime += 100;
			
			int newLPF = LPF*998;
			int random = (rand() % (int) (LPFR*1000+1))-(rand() % (int) (LPFR*500+1));
			newLPF = limit(newLPF-random);
			int LPFLimit = newLPF;
			newLPF = logTable[newLPF]*20+100;
			if (newLPF>20000) newLPF = 20000;
			if (newLPF<100) newLPF = 100;

			
			int newHPF = HPF*998;
			random = (rand() % (int) (HPFR*1000+1))-(rand() % (int) (HPFR*500+1));
			newHPF = limit(newHPF-random);
			newHPF = logTable[newHPF]*20+20;
			if (newHPF>20000) newHPF = 20000;
			newHPF *= newLPF/20000.f;
			if (newHPF<50) newHPF = 50;
			std::cout << newHPF << std::endl;
			//int newHPF = rand() % (int) (LPF);
			int newGain = rand() % (int) (1000);
			
			grains.push_back(new CGrain(newGrainSize, newDelayTime, newLPF, newHPF, newGain/1000.f));
			
			//grains.push_back(new CGrain(newGrainSize, newDelayTime));
			concurrentFilling++;
		}
	}
}

// -----------------------------------------------------------------------
// Process

void GrainJuicePlugin::d_activate() {
}

void GrainJuicePlugin::d_run(const float** inputs, float** outputs, uint32_t frames) {
	static int k = 0;
	for (uint32_t i = 0; i < frames; i++) {
		// RUNTIME CODE HERE
		//std::cout << "..record" << std::endl;
		//-------------------------------------
		//	RECORD
		//std::cout << "total grains:" << grains.size() << std::endl;
		//std::cout << "max grains:" << density*MAXGRAINS << std::endl;
		if (grains.size() <= density*MAXGRAINS) {
			//std::cout << "not enough full grains" << std::endl;
			if (grains.size() == 0) {
				newGrain(true);
			}
			if (grains.back() -> wantsSample()) {
					nSample[0] = inputs[0][i];
					nSample[1] = inputs[1][i];
					for (int q=0; q<concurrentFilling; q++) {
						grains[grains.size()-1-q] -> fillSample(nSample);
					}	
			} else {
				newGrain(false);
			}
		}

		
		//std::cout << "..playback" << std::endl;
		//-------------------------------------
		//	PLAYBACK
		outputs[0][i] = 0.0f;
		outputs[1][i] = 0.0f;
		eraseIndex = 0;
		int grainsPlaying = 0;
		int l = 0;
		for (uint32_t j = 0; j < grains.size(); j++) {
			if (!grains[j]->wantsSample()) {
				grainsPlaying++;
				if (!grains[j]->inDelay()) {
					//play this sample back
					
					grains[j]->updateParams(density, scatter, d_getSampleRate());
					
					if (grains[j]->donePlaying()) {
						// mark grains for erase
						eraseGrains[eraseIndex] = j;
						eraseIndex++;
						//grains.erase(grains.begin()+j);
						//j--; // COME ON BABY LIGHT MY FIRE
					} else {
						nSample = grains[j]->getSample();
						
						
						outputs[0][i] += nSample[0];
						outputs[1][i] += nSample[1];
					}
				}
			}
		}

		for (int j=0; j<eraseIndex; j++) {
			grains.erase(grains.begin()+eraseGrains[j]);
		}
		
		if (grains.size() != prevTotalGrains) {
			//std::cout << "total grains: " << grainsPlaying << " conc: " << concurrentFilling << " size: " << grains.size() << std::endl;
			//std::cout << "total grains playing: " << grainsPlaying << std::endl;
			prevTotalGrains = grainsPlaying;
		}
		if (k==9) k=0;
		
	}
	
	
	
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
	return new GrainJuicePlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
