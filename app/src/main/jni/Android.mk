LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := PlayAudio
LOCAL_LDLIBS += -llog -lz -landroid -lOpenSLES
LOCAL_SRC_FILES :=playAudio.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
include $(BUILD_SHARED_LIBRARY)