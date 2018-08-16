ifeq ($(MTK_BT_BLUEDROID_PLUS), yes)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/.. \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../btcore/include \
	$(LOCAL_PATH)/../stack/include \
	$(bluetooth_C_INCLUDES)

LOCAL_SRC_FILES := \
	./hci/hci_fw_core_dump_ctrl.c \

LOCAL_MODULE := libbt-mtk_cust
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := STATIC_LIBRARIES

LOCAL_CFLAGS += $(bluetooth_CFLAGS)
LOCAL_CONLYFLAGS += $(bluetooth_CONLYFLAGS)
LOCAL_CPPFLAGS += $(bluetooth_CPPFLAGS)


include $(BUILD_STATIC_LIBRARY)

endif #end of ifeq ($(MTK_BT_BLUEDROID_PLUS), yes)