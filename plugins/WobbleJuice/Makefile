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

OBJS_DSP = \
	WobbleJuicePlugin.cpp.o

OBJS_UI  = \
	WobbleJuiceArtwork.cpp.o \
	WobbleJuiceUI.cpp.o

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
