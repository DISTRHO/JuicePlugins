#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

all: libs plugins gen

# --------------------------------------------------------------

libs:
	$(MAKE) -C dpf/dgl

plugins: libs
	$(MAKE) all -C plugins/PowerJuice
	$(MAKE) all -C plugins/PowerJuiceX2
	$(MAKE) all -C plugins/StutterJuice
	$(MAKE) all -C plugins/TriggerJuice
	$(MAKE) all -C plugins/VectorJuice
	$(MAKE) all -C plugins/WobbleJuice

gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator

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

# --------------------------------------------------------------

.PHONY: plugins
