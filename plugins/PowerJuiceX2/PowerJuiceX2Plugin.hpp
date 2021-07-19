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

#ifndef POWERJUICEPLUGIN_HPP_INCLUDED
#define POWERJUICEPLUGIN_HPP_INCLUDED

#include "DistrhoPlugin.hpp"

#include <cmath>

static const int kFloatStackCount = 563;


struct FloatStack { //history for GUI!
    int32_t start;
    float data[kFloatStackCount];
};

struct FloatRMSStack { //rms, sr-dependent
    int32_t start;
    float* data;
};

struct LookaheadStack { //lookahead buffer, sr-dependent
    int32_t start;
    float* data;
};

struct SharedMemData { //history for the GUI !
    float rms[kFloatStackCount];
    float gainReduction[kFloatStackCount];
};

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class PowerJuiceX2Plugin : public Plugin
{
public:
    enum Parameters
    {
        paramAttack = 0,
        paramRelease,
        paramThreshold,
        paramRatio,
        paramMakeup,
        paramMix,
        paramCount
    };

    PowerJuiceX2Plugin();
    ~PowerJuiceX2Plugin() override;

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "PowerJuiceX2";
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

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('P', 'w', 'J', 'X');
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
    void run(const float** inputs, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------

private:
    // params
    float attack, release, threshold, ratio, makeup, mix;
    float attackSamples, releaseSamples, makeupFloat;
    float balancer;
    float targetGR;
    float GR;

    SharedMemData history;

    float sum;
    float data;
    float difference;

    int w;  //waveform plane size, size of the plane in pixels;
    int w2; //wavefowm array
    int h;  //waveform plane height
    int x;  //waveform plane positions
    int y;
    int dc; //0DC line y position
    
    int kFloatRMSStackCount;
	int kFloatLookaheadStackCount;
    
    float refreshSkip;

    int averageCounter;
    float inputMax;
    FloatStack input, rms, gainReduction;
    struct FloatRMSStack RMSStack;
    struct LookaheadStack lookaheadStack;
    
    bool newRepaint;
    int repaintSkip;

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

    bool isNan(float& value ) {
        if (((*(uint32_t *) &value) & 0x7fffffff) > 0x7f800000) {
            return true;
        }
        return false;
    }

    void sanitizeDenormal(float& value) {
        if (isNan(value)) {
            //std::printf("Booo!\n");
            value = 0.f;
        }
    }

public:
    //methods
    float getRMSHistory(int n);
    float getGainReductionHistory(int n);
    bool repaintNeeded();
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // POWERJUICE_HPP_INCLUDED
