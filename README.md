Scanned Synthesis Oscillator
============================

This is the very early version of an oscillator using scanned synthesis physical modeling.
(http://www.billverplank.com/ScannedSynthesis.PDF)

It is intended to be a eurorack module, and is being prototyped on a Teensy 3.6.


- This projct template is taken from github.com/apmorton/teensy-template 
- The `teensy3` sub-folder is taken from [The Teensy 3 Cores](https://github.com/PaulStoffregen/cores/tree/master/teensy3)
- The `tools` sub-folder is taken from [Teensyduino](http://www.pjrc.com/teensy/td_download.html)
- The `Makefile` file is moved, modified from `teensy3/Makefile`
- The `49-teensy.rules` file is taken from [PJRC's udev rules](http://www.pjrc.com/teensy/49-teensy.rules)


TODO:

Functionality:

- Quantify range where system becomes numerically unstable
	- Enforce value ranges?  Change ranges dynamically?
	- If mass is too low, and spring k / damp z are too high, the system becomes unstable
	- The lower the update rate, the narrower the window becomes
	- The higher the update rate, the quicker the system loses energy to rounding errors

- Add input to excite system
  x Improve variety of pluck
  - Add excite input (not sure how this should work)

- Add add parameter control pots
  x coarse tune
  x fine tune
  x mass
  x spring k
  x damp
	x center
  x hammer quality
	- update rate

- Add CV inputs
  - hammer trigger
  - 1V/oct
  - mass
  - spring k
  - damp
  - hammer quality
	- update rate

Structure:
- Abstract from hardware slightly (module interfaces)
- Split DAC setup into DMAMUX/eDMA & DAC/PDB setups
- Make ADC setup per-module / re-usable 
x Make CV/pot value input / mapping a separate class from UI
- Improve event queue to accept functions with arbitrary signatures

Optimization:
- Improve state update algorithm
- Use DMA to control ADC read interleaving

Current Issues:
- Frequency input is noisy
- Hammer shape pot effects frequency ???

