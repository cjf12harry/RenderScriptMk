$(info into cpp mkfile)
LOCAL_PATH := $(call my-dir)
$(info local path $(LOCAL_PATH))

LOCAL_CFLAGS := -std=c++11
LOCAL_MODULE := hello-libs
LOCAL_SRC_FILES := $(LOCAL_PATH)/hello.cpp
LOCAL_LDLIBS := -llog -landroid
include $(BUILD_SHARED_LIBRARY)


