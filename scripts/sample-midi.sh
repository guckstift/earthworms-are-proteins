#!/bin/bash

fluidsynth -nli -r 48000 -o synth.cpu-cores=2 -T oga -F $2 /usr/share/soundfonts/FluidR3_GM2-2.sf2 $1
