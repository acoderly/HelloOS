include parameters.mh
include objects.mh

.PHONY: all everything build_kernel

all: build_kernel

build_kernel:everything build_bin img

everything:$(HEAD_ELF) $(LOADER_ELF) $(REALMODEFUNC_ELF)

build_bin:$(HEAD) $(LOADER) $(REALMODEFUNC)

$(HEAD_ELF):$(HEAD_LINK)
	$(LD) $(HEAD_LD_FLAGS) -o $@ $(HEAD_LINK)

$(LOADER_ELF):$(LOADER_LINK)
	$(LD) $(LOADER_LD_FLAGS) -o $@ $(LOADER_LINK)
	
$(REALMODEFUNC_ELF):$(REALMODEFUNC_LINK)
	$(LD) $(REALMODEFUNC_LD_FLAGS) -o $@ $(REALMODEFUNC_LINK)

$(HEAD):$(HEAD_ELF)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@
	@echo 'OBJCOPY -[M] 正在构建...' $@

$(LOADER):$(LOADER_ELF)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@
	@echo 'OBJCOPY -[M] 正在构建...' $@  

$(REALMODEFUNC):$(REALMODEFUNC_ELF)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@
	@echo 'OBJCOPY -[M] 正在构建...' $@  

img:
	$(IMG_MAKER) $(IMG_MAKER_FLAGS)  $(HEAD) -o HelloOS.eki -f $(LOADER) $(REALMODEFUNC)