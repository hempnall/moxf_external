FILE_SUFFIX:=$(shell date "+%s")
TARGET:=moxf
OUTPUT_DIR:=build/Development




$(OUTPUT_DIR)/$(TARGET)$(FILE_SUFFIX).mxo: $(OUTPUT_DIR)/$(TARGET).mxo 
	cp -r $< $@
	echo "wrote to moxf$@"

clean:
	rm -rf $(OUTPUT_DIR)/$(TARGET)*


$(OUTPUT_DIR)/$(TARGET).mxo: $(TARGET).xcodeproj
	xcodebuild -project $<  \
    GCC_PREPROCESSOR_DEFINITIONS='MAX_OBJ_NAME_SUFFIX="\"'$(FILE_SUFFIX)'\""'


