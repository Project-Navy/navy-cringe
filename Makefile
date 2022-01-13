CXX = clang++
CXXFLAGS =							\
		--target=x86_64-elf-none 	\
		-std=c++20					\
		-ggdb						\
		-Wall						\
		-Wextra						\
		-Werror						\
		-mno-80387 					\
		-mno-mmx 					\
		-mno-3dnow 					\
		-mno-sse 					\
		-mno-sse2 					\
		-mno-red-zone 				\
		-mcmodel=kernel				\
		-fno-stack-protector 		\
		-fno-use-cxa-atexit			\
		-fno-pic                	\
		-fno-exceptions				\
		-Wno-pointer-arith			\
		-ffreestanding				\
    	-m64                    	\
    	-masm=intel            		\
		-MD							\
		-Isrc/						\
		-Isrc/libs/

AS = nasm
ASFLAGS = -felf64

LD = ld.lld
LDFLAGS :=                  				    \
    -nostdlib               				    \
    -static                 				    \
    -Tsrc/kernel/link.ld						\
    -z max-page-size=0x1000 				    \
			
KERNEL = kernel.elf 
TARGETS = $(KERNEL)

SRC =											\
	$(shell find src/drivers/ -name "*.cpp")	\
	$(shell find src/kernel -name "*.cpp")		\
	$(wildcard src/libs/fmt/src/*.cc)

BUILD_DIRECTORY := build
DIRECTORY_GUARD = @mkdir -p $(@D)
SYSROOT = sysroot

OBJ := $(patsubst %.cpp, $(BUILD_DIRECTORY)/%.cpp.o, $(SRC)) \
        $(patsubst %.s, $(BUILD_DIRECTORY)/%.s.o, $(ASRC))

$(BUILD_DIRECTORY)/%.cpp.o: %.cpp
	@$(DIRECTORY_GUARD)
	@echo "[CXX] $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(BUILD_DIRECTORY)/%.s.o: %.s
	@$(DIRECTORY_GUARD)
	@echo "[AS] $<"
	@$(AS) $(ASFLAGS) $< -o $@

$(KERNEL): $(OBJ)
	@$(DIRECTORY_GUARD)
	@echo "[LD] $^"
	@$(LD) $(LDFLAGS) -o $@ $^
	nm kernel.elf -S > symbols.map

clean:
	rm -r $(BUILD_DIRECTORY)
	rm $(TARGETS)

all: $(TARGETS)

run: $(TARGETS)
	meta/scripts/make-image-x86.sh
	qemu-system-x86_64 -m 4G -serial stdio -cdrom navy.iso -enable-kvm 

.PHONY: all run run-debug
.DEFAULT_GOAL := all