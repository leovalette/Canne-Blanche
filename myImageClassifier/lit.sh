#!/bin/bash
pico2wave -w /tmp/test.wav "$1"
aplay -q /tmp/test.wav
rm /tmp/test.wav
