#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = VectorJuice

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	VectorJuicePlugin.cpp

FILES_UI  = \
	VectorJuiceArtwork.cpp \
	VectorJuiceUI.cpp

# --------------------------------------------------------------
# Do some magic

FILE_BROWSER_DISABLED = true
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

all: jack lv2_sep vst2 vst3

# --------------------------------------------------------------
