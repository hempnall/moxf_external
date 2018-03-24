#!/bin/bash

file_suffix=$(date "+%s")
xcodebuild -project moxf.xcodeproj/ -alltargets
#cp -r build/Development/moxf.mxo build/Development/$file_suffix.mxo
#cp -r build/Development/moxf.mxo build/Development/moxf.midiin.mxo
#cp -r build/Development/moxf.mxo build/Development/moxf.midiout.mxo

echo "wrote to moxf$file_suffix"
