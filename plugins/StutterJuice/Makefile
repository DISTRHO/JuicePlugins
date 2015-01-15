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

OBJS_DSP = \
	StutterJuicePlugin.cpp.o

OBJS_UI  = \
	StutterJuiceArtwork.cpp.o \
	StutterJuiceUI.cpp.o

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
