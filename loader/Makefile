MAKEFLAGS = -sR

MKDIR = mkdir
RMDIR = rmdir
CP = cp
CD = cd
RM = rm
MAKE = make

BUILD_PATH = ./build
LOADER_MAKEFILE = -C $(BUILD_PATH) -f build_loader.mk
LOADER_LINK_MAKEFILE = -C $(BUILD_PATH) -f link_loader.mk
.PHONY : build print clean all


build:clean print all

all:
	$(MAKE) $(LOADER_MAKEFILE)
	$(MAKE) $(LOADER_LINK_MAKEFILE)
	@echo "Kernel loader build success!"
clean:
	$(CD) $(BUILD_PATH); $(RM) -f *.o *.bin *.i *.s *.map *.eki *.elf
	@echo "Kernel loader:Clean all build file."

print:
	@echo "**********Start build kernel loader**********"