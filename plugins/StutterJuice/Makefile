#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = StutterJuice

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	StutterJuicePlugin.cpp

FILES_UI  = \
	StutterJuiceArtwork.cpp \
	StutterJuiceUI.cpp

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)
all: jack lv2_sep vst
else
all: lv2_sep vst
endif

# --------------------------------------------------------------
