CFLAG=-ffreestanding -mno-red-zone -c

arch ?= x86_64
kernel := build/kernel-$(arch).bin
c_os := build/C/main_c.o
iso := build/BenjiOS-$(arch).iso

linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source_files := $(wildcard src/arch/$(arch)/*.asm)
assembly_object_files := $(patsubst src/arch/$(arch)/%.asm, \
						 	build/arch/$(arch)/%.o, $(assembly_source_files))

C_SOURCES = $(wildcard src/kernel/*.c src/drivers/*.c)
HEADERS = $(wildcard src/kernel/*.h  src/drivers/*.h)
OBJ_FILES = ${C_SOURCES:.c=.o}



.PHONY: all clean run iso

all: $(kernel)

run: $(iso)
	@qemu-system-x86_64 -cdrom $(iso)

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
		@mkdir -p build/isofiles/boot/grub
		@cp $(kernel) build/isofiles/boot/kernel.bin
		@cp $(grub_cfg) build/isofiles/boot/grub
		@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
		@rm -r build/isofiles

$(kernel): $(OBJ_FILES) $(assembly_object_files) $(linker_script)
		@ld -n --gc-sections -T $(linker_script) -o $(kernel) $(assembly_object_files) $(OBJ_FILES)

%.o: %.c ${HEADERS}
	@gcc $(CFLAG) $< -o $@

# compile assembly files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@


clean: 
	$(RM) src/kernel/*.o
	$(RM) src/drivers/*.o