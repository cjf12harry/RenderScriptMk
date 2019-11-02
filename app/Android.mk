$(info In app make file)
LOCAL_PATH := $(call my-dir)
$(info $(LOCAL_PATH))
include $(CLEAR_VARS)

JNI_SRC_PATH := $(LOCAL_PATH)/src/main/cpp
include $(JNI_SRC_PATH)/Android.mk

