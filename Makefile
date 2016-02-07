ARDUINO_BIN := arduino
#ARDUINO_BIN := arduino-headless
ARDUINO_OPTS := --board teensy:avr:teensy31 --pref custom_usb=teensy31_midi --pref custom_keys=teensy31_en-us --pref custom_speed=teensy31_96opt

BUILDDIR    := $(shell pwd)/build
SKETCH      := $(wildcard *.ino)

ifeq ($(strip $(SKETCH)),)
$(error No sketch found in current directory)
endif
ifneq ($(words $(SKETCH)),1)
$(error Multiple sketches in current directory)
endif

all: $(BUILDDIR)/$(SKETCH).hex

$(BUILDDIR)/$(SKETCH).hex : $(SKETCH) $(BUILDDIR)
# delete a few directories, build otherwise fails
	rm -rf $(BUILDDIR)/preproc
	rm -rf $(BUILDDIR)/sketch
# arduino won't exit with a proper return value, parse output instead
	$(ARDUINO_BIN) $(ARDUINO_OPTS) --pref build.path=$(BUILDDIR) --upload --verbose $< 2>&1 | tee compilation.out
	@! grep -q 'exit status 1\|Error compiling' compilation.out

clean :
	rm -rf $(BUILDDIR) *~ compilation.out

$(BUILDDIR): 
	mkdir $@

.PHONY : clean
