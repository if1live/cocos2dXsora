LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sora_static

LOCAL_MODULE_FILENAME := libsora

# sora
LOCAL_SRC_FILES := ../tinyxml/tinyxmlparser.cpp  \
../tinyxml/tinystr.cpp  \
../tinyxml/tinyxml.cpp  \
../tinyxml/tinyxmlerror.cpp  \
../angle.cpp  \
../ani.cpp  \
../ani_data.cpp  \
../ani_frame.cpp  \
../ani_manager.cpp  \
../ani_node.cpp  \
../ani_parser.cpp  \
../ani_prototype.cpp  \
../ani_reader.cpp  \
../ani_resource.cpp  \
../ani_writer.cpp  \
../class_attribute.cpp  \
../class_dict.cpp  \
../crc32.cpp  \
../data_define.cpp  \
../data_helper.cpp  \
../data_init.cpp  \
../file_helper.cpp  \
../gl_helper.cpp  \
../logger.cpp  \
../math_helper.cpp  \
../mem.cpp  \
../string_hash.cpp  \
../string_util.cpp  \
../struct_version_converter.cpp  \
../unit.cpp  \
../vertex.cpp  \
../xml_node.cpp  \
../xml_reader.cpp  \
../xml_writer.cpp  \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/..    \
$(LOCAL_PATH)/../../cocos2dx    \
$(LOCAL_PATH)/../../cocos2dx/include    \
$(LOCAL_PATH)/../../cocos2dx/kazmath/include    \
$(LOCAL_PATH)/../../cocos2dx/platform    \
$(LOCAL_PATH)/../../cocos2dx/platform/android    \
$(LOCAL_PATH)/../../external/Box2D  \
$(LOCAL_PATH)/../../external  \
                                 
include $(BUILD_STATIC_LIBRARY)


