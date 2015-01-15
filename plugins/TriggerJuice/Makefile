#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = TriggerJuice

# --------------------------------------------------------------
# Files to build

OBJS_DSP = \
	TriggerJuicePlugin.cpp.o

OBJS_UI  = \
	TriggerJuiceArtwork.cpp.o \
	TriggerJuiceUI.cpp.o

# --------------------------------------------------------------
# Do some magic

include ../Makefile.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)
all: jack lv2_sep vst
else
all: lv2_sep vst
endif

# --------------------------------------------------------------
