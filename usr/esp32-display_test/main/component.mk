#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)


BUILD_DIR = `pwd`/../../build/esp32-release/source
COMPONENT_ADD_LDFLAGS += -L$(BUILD_DIR) -llwiot

