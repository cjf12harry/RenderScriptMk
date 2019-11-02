$(info In app make file)
LOCAL_PATH := $(call my-dir)
JNI_SRC_PATH := $(LOCAL_PATH)/src/main/cpp
include $(CLEAR_VARS)

#The CLEAR_VARS variable points to a special GNU Makefile that clears many LOCAL_XXX variables for you, such as LOCAL_MODULE, LOCAL_SRC_FILES, and LOCAL_STATIC_LIBRARIES. Note that it does not clear LOCAL_PATH. This variable must retain its value because the system parses all build control files in a single GNU Make execution context where all variables are global. You must (re-)declare this variable before describing each module.
$(info $(CL_PATH))

LOCAL_CFLAGS := -std=c++11
LOCAL_MODULE := hello-libs
LOCAL_SRC_FILES := $(JNI_SRC_PATH)/hello.cpp
LOCAL_LDLIBS := -llog -landroid

include $(BUILD_SHARED_LIBRARY)

