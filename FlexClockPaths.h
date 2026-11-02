#ifndef FLEXCLOCK_PATHS_H
#define FLEXCLOCK_PATHS_H

// Use the C API even in Objective-C++: this project builds NSStrings at runtime.
// Resolve paths when used, after injection, rather than in global initializers.
#if defined(THEOS_PACKAGE_SCHEME_ROOTHIDE)
#include <roothide.h>
#define FC_PACKAGE_PATH(path) jbroot((const char *)(path))
#define FC_DATA_PATH(path) jbroot((const char *)(path))
#elif defined(THEOS_PACKAGE_SCHEME_ROOTLESS)
#define FC_PACKAGE_PATH(path) "/var/jb" path
#define FC_DATA_PATH(path) path
#else
#define FC_PACKAGE_PATH(path) path
#define FC_DATA_PATH(path) path
#endif

#define kBuiltinPacks FC_PACKAGE_PATH("/Library/Application Support/FlexClock/Packs")
#define kBundlePath FC_PACKAGE_PATH("/Library/PreferenceBundles/FlexClockPreferences.bundle")
#define kUserPacks FC_DATA_PATH("/var/mobile/Library/FlexClock/Packs")

#endif
