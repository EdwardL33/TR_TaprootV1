.PHONY: all build flash

all: build flash

build:
	scons build;

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg  -c "program ./build/hardware/scons-release/template-project.elf verify reset exit";