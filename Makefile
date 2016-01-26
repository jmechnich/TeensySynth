SKETCH      := TeensySynth.ino

ARDUINO_BIN := arduino
#ARDUINO_BIN := arduino-headless
BUILDDIR    := $(shell pwd)/build

all: $(BUILDDIR)/$(SKETCH).hex

$(BUILDDIR)/$(SKETCH).hex : $(SKETCH) $(BUILDDIR)
# delete a few directories, build otherwise fails
	rm -rf $(BUILDDIR)/preproc
	rm -rf $(BUILDDIR)/sketch
# arduino won't exit with a proper return value, parse output instead
	$(ARDUINO_BIN) --upload --verbose --pref build.path=$(BUILDDIR) $< 2>&1 | tee compilation.out
	@! grep -q 'exit status 1' compilation.out

clean :
	rm -rf $(BUILDDIR) *~ compilation.out

$(BUILDDIR): 
	mkdir $@

.PHONY : clean
