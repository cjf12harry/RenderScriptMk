$(info into cpp mkfile)
LOCAL_PATH := $(call my-dir)
$(info local path $(LOCAL_PATH))
$(info ndk path $(ANDROID_NDK))
$(info host os base $(HOST_TAG))
$(info render script prebuilt root $(RENDERSCRIPT_TOOLCHAIN_PREBUILT_ROOT))
$(info RENDERSCRIPT_PLATFORM_HEADER $(RENDERSCRIPT_PLATFORM_HEADER))
$(info RENDERSCRIPT_TOOLCHAIN_HEADER $(RENDERSCRIPT_TOOLCHAIN_HEADER))
$(info LOCAL_RENDERSCRIPT_TARGET_API $(LOCAL_RENDERSCRIPT_TARGET_API))
$(info TARGET_ARCH $(TARGET_ARCH))


include $(CLEAR_VARS)
LOCAL_MODULE := rs-prebuilt
LOCAL_RS_PREBUILT_LIBS := $(RENDERSCRIPT_TOOLCHAIN_PREBUILT_ROOT)/platform/$(TARGET_ARCH)
LOCAL_SRC_FILES := $(LOCAL_RS_PREBUILT_LIBS)/libRScpp_static.a
LOCAL_EXPORT_C_INCLUDES := $(RENDERSCRIPT_PLATFORM_HEADER)/cpp \
                           $(RENDERSCRIPT_PLATFORM_HEADER)/
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := RSSupport
LOCAL_SRC_FILES := $(LOCAL_RS_PREBUILT_LIBS)/libRSSupport.so
include $(PREBUILT_SHARE_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := renderscript
LOCAL_SDK_VERSION := 21
LOCAL_NDK_STL_VARIANT := c++_static
LOCAL_SRC_FILES :=  threshold.rs RenderScript.cpp
LOCAL_C_INCLUDES += $(TARGET_OBJS)/$(LOCAL_MODULE)
$(info C_INCLUDES $(LOCAL_C_INCLUDES))
LOCAL_STATIC_LIBRARIES := rs-prebuilt
LOCAL_LDLIBS := -ljnigraphics -ldl -llog
include $(BUILD_SHARED_LIBRARY)

