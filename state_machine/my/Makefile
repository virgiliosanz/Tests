##############################################################
#	       CMake Project Wrapper Makefile	       #
##############################################################

SHELL := /bin/bash
RM    := rm -rf
MKDIR := mkdir

all: ./build/Makefile
	@ $(MAKE) -C build

tests:
	@ $(MAKE) test

./build/Makefile:
	@ $(MKDIR) build
	@ (cd build >/dev/null 2>&1 && cmake ..)

distclean:
	@- $(RM) build
#	@- (cd build >/dev/null 2>&1 && cmake .. >/dev/null 2>&1)
#	@- $(MAKE) --silent -C build clean || true
#	@- $(RM) ./build/* bin
#	@- $(RM) GPATH GRTAGS GTAGS


ifeq ($(findstring distclean,$(MAKECMDGOALS)),)

    $(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)

endif
