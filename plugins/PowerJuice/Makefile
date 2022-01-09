#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = PowerJuice

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	PowerJuicePlugin.cpp

FILES_UI  = \
	PowerJuiceArtwork.cpp \
	PowerJuiceUI.cpp

# --------------------------------------------------------------
# Do some magic

FILE_BROWSER_DISABLED = true
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

all: jack lv2 vst2 vst3

# --------------------------------------------------------------
