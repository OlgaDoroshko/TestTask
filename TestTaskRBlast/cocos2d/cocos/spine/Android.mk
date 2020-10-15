LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spine

LOCAL_MODULE_FILENAME := libspine

LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := $(shell find $(LOCAL_PATH)/ -type d)

LOCAL_SRC_FILES := $(foreach dir,$(LOCAL_C_INCLUDES),$(wildcard $(dir)/*.cpp))
LOCAL_SRC_FILES += $(foreach dir,$(LOCAL_C_INCLUDES),$(wildcard $(dir)/*.cc))

LOCAL_C_INCLUDES += $(LOCAL_PATH)/..

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_STATIC_LIBRARIES := cc_core

include $(BUILD_STATIC_LIBRARY)