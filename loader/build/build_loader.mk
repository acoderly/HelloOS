HEAD_FILE_PATH = ../include/
LOADER_SRC_PATH = ../loader_src/
CCBUILDPATH = $(LOADER_SRC_PATH)

include parameters.mh
include objects.mh

.PHONY : all everything build_kernel
all: build_kernel

build_kernel:everything

everything: $(HEAD_OBJS) $(LOADER_OBJS) $(REALMODEFUNC_OBJS)

include build_rule.mh