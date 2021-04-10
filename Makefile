ARDUINO_BIN := arduino
#ARDUINO_BIN := arduino-headless

BUILDDIR    := $(shell pwd)/build
SKETCH      := $(wildcard *.ino)

ifeq ($(strip $(SKETCH)),)
$(error No sketch found in current directory)
endif
ifneq ($(words $(SKETCH)),1)
$(error Multiple sketches in current directory)
endif

USB_TYPE = serialmidi

all: $(BUILDDIR)/$(SKETCH).hex

usbserial: USB_TYPE = serial
usbserial: all

usbmidi: USB_TYPE = midi
usbmidi: all

ARDUINO_OPTS = --board teensy:avr:teensy31:usb=$(USB_TYPE),speed=96,keys=en-us

teensy4: ARDUINO_OPTS = --board teensy:avr:teensy40:usb=$(USB_TYPE),speed=600,opt=o2std,keys=en-us
teensy4: all

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
