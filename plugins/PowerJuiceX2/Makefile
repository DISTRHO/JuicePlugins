#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = PowerJuiceX2

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	PowerJuiceX2Plugin.cpp

FILES_UI  = \
	PowerJuiceX2Artwork.cpp \
	PowerJuiceX2UI.cpp

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

all: jack lv2 vst2 vst3

# --------------------------------------------------------------
