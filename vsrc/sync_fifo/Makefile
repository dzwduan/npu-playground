MODULE ?= FIFO
SUFFIX ?= sv

compile:
	iverilog -g2005-sv -o  $(MODULE) $(MODULE)_tb.$(SUFFIX) $(MODULE).$(SUFFIX)

run:compile
	vvp $(MODULE)

vcd:
	gtkwave fifo_wave.vcd

clean: 
	@-rm $(MODULE) *.vcd