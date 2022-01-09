#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = WobbleJuice

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	WobbleJuicePlugin.cpp

FILES_UI  = \
	WobbleJuiceArtwork.cpp \
	WobbleJuiceUI.cpp

# --------------------------------------------------------------
# Do some magic

UI_TYPE = generic
FILE_BROWSER_DISABLED = true
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

all: jack lv2_sep vst2 vst3

# --------------------------------------------------------------
