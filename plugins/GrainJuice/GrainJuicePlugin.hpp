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

#ifndef GrainJUICEPLUGIN_HPP_INCLUDED
#define GrainJUICEPLUGIN_HPP_INCLUDED

#include "DistrhoPlugin.hpp"
#include <cstdlib>
#include <time.h>
#include <vector>

#define MAXGRAINSIZE 0.5f // in seconds
#define MAXSCATTER 3.f	// in seconds
#define MAXGRAINS 300	// in grains

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------




class GrainJuicePlugin : public Plugin {
public:
	enum Parameters {
		paramSize = 0,
		paramScatter,
		paramGain,
		paramDensity,
		paramLPF,
		paramHPF,
		paramSizeR,
		paramScatterR,
		paramGainR,
		paramDensityR,
		paramLPFR,
		paramHPFR,
		paramCount
	};

	GrainJuicePlugin();

protected:
	// -------------------------------------------------------------------
	// Information

	const char* d_getLabel() const noexcept override {
		return "GrainJuice";
	}

	const char* d_getMaker() const noexcept override {
		return "Andre Sklenar";
	}

	const char* d_getLicense() const noexcept override {
		return "GPL v2+";
	}

	uint32_t d_getVersion() const noexcept override {
		return 0x1000;
	}

	long d_getUniqueId() const noexcept override {
		return d_cconst('G', 'r', 'n', 'J');
	}

	// -------------------------------------------------------------------
	// Init

	void d_initParameter(uint32_t index, Parameter& parameter) override;
	void d_initProgramName(uint32_t index, d_string& programName) override;

	// -------------------------------------------------------------------
	// Internal data

	float d_getParameterValue(uint32_t index) const override;
	void  d_setParameterValue(uint32_t index, float value) override;
	void  d_setProgram(uint32_t index) override;

	// -------------------------------------------------------------------
	// Process

	void d_activate() override;
	void d_run(const float** inputs, float** outputs, uint32_t frames) override;

	// -------------------------------------------------------------------

private:
	float size, scatter, gain, density, LPF, HPF;
	float sizeR, scatterR, gainR, densityR, LPFR, HPFR;
	float *nSample;
	float *prevSample;
	int concurrentFilling;
	int eraseIndex;
	int eraseGrains[100];

	float logTable[1000];

	int limit(int what) {
		if (what>1000)
			return 999;
		if (what<0)
			return 0;
		return what;
		
	}


	void newGrain(bool first);
	//float *nSample;
	bool isNan(float& value ) {
			   if (((*(uint32_t *) &value) & 0x7fffffff) > 0x7f800000) {
				  return true;
			   }
			   return false;
			}

	uint32_t prevTotalGrains;

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GrainJuicePlugin)
	

	class CGrain {
		public:
			CGrain(uint32_t nLength, uint32_t nDelay, float lpf, float hpf, float nGain);
			uint32_t getLength();
			void fillSample(float *nSample);
			bool wantsSample();
			float *getSample();
			bool donePlaying();
			void cleanUp();
			bool inDelay();
			uint32_t length;
			bool repeat();
			void setDelay(uint32_t nDelay);
			void updateParams(float nDensity, float nScatter, uint32_t nSRT);
			float inspectSample(uint32_t index, int channel);
		private:
			void applyEnvelope();
			float samples[(int)(48000*MAXGRAINSIZE)][2];
			
			uint32_t playhead;
			bool readyForPlayback;
			uint32_t delay;
			float *emptySamples;
			float density;
			float scatter;
			float gain;
			uint32_t SRT;

			class CLPF
			{
				private:
					float r; // reso - 0.1 - 1.4
					float f; // freq in Hz
					float a1, a2, a3, b1, b2;
					float in, in1, in2;
					float out, out1, out2;
					float c;
					float sampleRate;
					
				
				public:
				
					CLPF() {
						r = 1.0f;
						f = 0.0f;
						a1=a2=a3=b1=b2=0.0f;
						in=in1=in2=out=out1=out2=0.0f;
					}

					void compute() {
						c = 1.0 / tan(M_PI * f / sampleRate);
						a1 = 1.0 / (1.0 + r*c + c*c);
						a2 = 2 * a1;
						a3 = a1;
						b1 = 2.0 * (1.0 - c*c) * a1;
						b2 = (1.0 - r*c + c*c) * a1;
					}
				
					void setFreq(float nFreq) {
						f = nFreq;
						if (f==0) {
							f=20;
						}
					}
					
					
					void setReso(float nReso) {
						r = nReso;
						if (r==0) {
							r = 0.1f;
						}
						r = 1.0f;
						f = 0.0f;
						a1=a2=a3=b1=b2=0.0f;
						in=in1=in2=out=out1=out2=0.0f;
					}
					
					void setSampleRate(float nSampleRate) {
						sampleRate = nSampleRate;
					}
					
				
					float process(float sample) {
						in = sample;
						out = a1 * in + a2 * in1 + a3 * in2 - b1*out1 - b2*out2;
						in2=in1;
						in1=in;
						out2=out1;
						out1 = out;
						
						return out;
					}


			};

			class CHPF
			{
				private:
					float r; // reso - 0.1 - 1.4
					float f; // freq in Hz
					float a1, a2, a3, b1, b2;
					float in, in1, in2;
					float out, out1, out2;
					float c;
					float sampleRate;
				
				public:
				
					CHPF() {
						r = 1.0f;
						f = 0.0f;
						a1=a2=a3=b1=b2=0.0f;
						in=in1=in2=out=out1=out2=0.0f;
					}

					void compute() {
						c = tan(M_PI * f / sampleRate);
						a1 = 1.0 / (1.0 + r*c + c*c);
						a2 = -2*a1;
						a3 = a1;
						b1 = 2.0 * (c*c - 1.0) * a1;
						b2 = (1.0 - r*c + c*c) * a1;
					}
				
					void setFreq(float nFreq) {
						f = nFreq;
						if (f==0) {
							f=20;
						}
					}
					
					void setReso(float nReso) {
						r = nReso;
						if (r==0) {
							r = 0.1f;
						}
					}
					
					void setSampleRate(float nSampleRate) {
						sampleRate = nSampleRate;
					}
					
				
					float process(float sample) {
						//compute();
						in = sample;
						out = a1 * in + a2 * in1 + a3 * in2 - b1*out1 - b2*out2;
						in2=in1;
						in1=in;
						out2=out1;
						out1 = out;
						
						return out;
					}


			};
			CHPF highPass[2];
			CLPF lowPass[2];
			
	};

	std::vector<CGrain*> grains;
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // GrainJUICE_HPP_INCLUDED
