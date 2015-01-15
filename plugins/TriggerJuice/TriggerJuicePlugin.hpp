/*
 * Trigger Juice Plugin
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

#ifndef TRIGGERJUICEPLUGIN_HPP_INCLUDED
#define TRIGGERJUICEPLUGIN_HPP_INCLUDED

#include "DistrhoPlugin.hpp"
#include "CStream.hxx"


START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class TriggerJuicePlugin : public Plugin
{
public:
    enum Parameters
    {
        paramAttack = 0,
		paramRelease,
		paramSplit,
		paramRev,
		paramMS,
        paramCount
    };

	inline float smoothParameter(float in, int axis) {
		sZ[axis] = (in * sB[axis]) + (sZ[axis] * sA[axis]); return sZ[axis];
	}



    TriggerJuicePlugin();
    ~TriggerJuicePlugin() override;

protected:
    // -------------------------------------------------------------------
    // Information

    const char* d_getLabel() const noexcept override
    {
        return "TriggerJuice";
    }

    const char* d_getMaker() const noexcept override
    {
        return "Andre Sklenar";
    }

    const char* d_getLicense() const noexcept override
    {
        return "GPL v2+";
    }

    uint32_t d_getVersion() const noexcept override
    {
        return 0x1000;
    }

    long d_getUniqueId() const noexcept override
    {
        return d_cconst('T', 'r', 'g', 'J');
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
    void d_deactivate() override;
    void d_run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;

    // -------------------------------------------------------------------

private:
	CStream left, right;
	
    float attack, release;
    float rev, split, MS;

	

	//parameter smoothing, for subOrbitX and subOrbitY
	float sA[2], sB[2], sZ[2];
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // TRIGGERJUICE_HPP_INCLUDED
