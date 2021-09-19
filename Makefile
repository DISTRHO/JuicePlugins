#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

include dpf/Makefile.base.mk

all: dgl plugins gen

# --------------------------------------------------------------

dgl:
ifeq ($(HAVE_CAIRO_OR_OPENGL),true)
	$(MAKE) -C dpf/dgl
endif

plugins: dgl
	$(MAKE) all -C plugins/PowerJuice
	$(MAKE) all -C plugins/PowerJuiceX2
	$(MAKE) all -C plugins/TriggerJuice
	$(MAKE) all -C plugins/VectorJuice
	$(MAKE) all -C plugins/WobbleJuice

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen:
endif

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/PowerJuice
	$(MAKE) clean -C plugins/PowerJuiceX2
	$(MAKE) clean -C plugins/StutterJuice
	$(MAKE) clean -C plugins/TriggerJuice
	$(MAKE) clean -C plugins/VectorJuice
	$(MAKE) clean -C plugins/WobbleJuice
	rm -rf bin build

# --------------------------------------------------------------

.PHONY: plugins
