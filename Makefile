#FILE_SUFFIX:=$(shell date "+%s")
TARGET:=moxf
OUTPUT_DIR:=build/Development
RELEASE_DIR:=../release


$(OUTPUT_DIR)/$(TARGET)$(FILE_SUFFIX).mxo: $(OUTPUT_DIR)/$(TARGET).mxo 
	cp -r $< $@
	cp -r $< $(OUTPUT_DIR)/moxf.midiin.mxo
	cp -r $< $(OUTPUT_DIR)/moxf.midiout.mxo	
	#cp -r $< ../../../externals/$(TARGET)$(FILE_SUFFIX).mxo
	#cp -r $< $(RELEASE_DIR)/$(TARGET)$(FILE_SUFFIX)
	echo "wrote to moxf$@"

clean:
	rm -rf $(OUTPUT_DIR)/$(TARGET)*
	rm -rf $(RELEASE_DIR)/*


split:
	cp -r /Users/jameshook/dev/src/max-sdk-7.3.3/externals/moxf.mxo /Users/jameshook/dev/src/max-sdk-7.3.3/externals/moxf.midiin.mxo
	cp -r /Users/jameshook/dev/src/max-sdk-7.3.3/externals/moxf.mxo /Users/jameshook/dev/src/max-sdk-7.3.3/externals/moxf.midiout.mxo


$(OUTPUT_DIR)/$(TARGET).mxo: $(TARGET).xcodeproj
	xcodebuild -project $<  \
    GCC_PREPROCESSOR_DEFINITIONS='MAX_OBJ_NAME_SUFFIX="\"'$(FILE_SUFFIX)'\""'




