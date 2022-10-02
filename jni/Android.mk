LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := getcon
LOCAL_SRC_FILES := getcon.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDFLAGS := -L$(LOCAL_PATH)/prebuilts/$(TARGET_ARCH_ABI) -lselinux
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := setcon
LOCAL_SRC_FILES := setcon.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDFLAGS := -L$(LOCAL_PATH)/prebuilts/$(TARGET_ARCH_ABI) -lselinux
include $(BUILD_EXECUTABLE)
