LOCAL_PATH := $(call my-dir)

#New AudioEngine
include $(CLEAR_VARS)

LOCAL_MODULE := audio

LOCAL_MODULE_FILENAME := libaudio

LOCAL_SRC_FILES := AudioEngine-inl.cpp \
                   ../AudioEngine.cpp \
                  AssetFd.cpp \
                  AudioDecoder.cpp \
                  AudioDecoderMp3.cpp \
                  AudioDecoderOgg.cpp \
                  AudioDecoderProvider.cpp \
                  AudioDecoderSLES.cpp \
                  AudioDecoderWav.cpp \
                  AudioMixer.cpp \
                  AudioMixerController.cpp \
                  AudioPlayerProvider.cpp \
                  AudioResampler.cpp \
                  AudioResamplerCubic.cpp \
                  CCThreadPool.cpp \
                  PcmAudioPlayer.cpp \
                  PcmAudioService.cpp \
                  PcmBufferProvider.cpp \
                  PcmData.cpp \
                  Track.cpp \
                  UrlAudioPlayer.cpp \
                  mp3reader.cpp \
                  tinysndfile.cpp \
                  audio_utils/format.c \
                  audio_utils/minifloat.cpp \
                  audio_utils/primitives.c \
                  utils/Utils.cpp




LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_EXPORT_LDLIBS := -lOpenSLES

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../platform/android \
                    $(LOCAL_PATH)/../../../external/android-specific \
                    $(LOCAL_PATH)/../../../external/android-specific/tremolo

LOCAL_STATIC_LIBRARIES += ext_vorbisidec ext_pvmp3dec
include $(BUILD_STATIC_LIBRARY)

$(call import-module,android-specific/tremolo)
$(call import-module,android-specific/pvmp3dec)
