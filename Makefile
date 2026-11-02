ARCHS = arm64 arm64e
TARGET = iphone:clang:16.5:15.0
THEOS_PACKAGE_SCHEME = roothide
SDKVERSION = 16.5
INSTALL_TARGET_PROCESSES = SpringBoard

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = FlexClock
FlexClock_FILES = Tweak.xm
FlexClock_CFLAGS = -fobjc-arc -Wno-deprecated-declarations
FlexClock_FRAMEWORKS = UIKit CoreGraphics ImageIO QuartzCore
ifeq ($(THEOS_PACKAGE_SCHEME),roothide)
FlexClock_LIBRARIES += roothide
endif

include $(THEOS_MAKE_PATH)/tweak.mk

SUBPROJECTS += FlexClockPreferences
include $(THEOS_MAKE_PATH)/aggregate.mk
