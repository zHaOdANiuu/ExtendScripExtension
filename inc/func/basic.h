#pragma once

#include "AEConfig.h"
#include "AEGP_SuiteHandler.h"
#include "AE_GeneralPlug.h"
#include "SoCClient.h"
#include "SoSharedLibDefs.h"
#include "entry.h"

#ifdef AE_OS_WIN
#include <windows.h>
#define __export extern "C" __declspec(dllexport)
#define strdup _strdup
#elif defined AE_OS_MAC
#include <dlfcn.h>
#define __export extern "C"(__APPLE__) __attribute__((visibility("default")))
#endif

#define InitError() int err = 0;
#define ListenError(f) \
    if (err == 0)      \
        err = f;
#define GetError() err;

extern struct SPBasicSuite* globalPicaBasicPtr;

typedef void (*Type_SPBasicSuite)(SPBasicSuite**);

static void initSPBasicSuite();

template <typename T>
static T loadFunctionFromLibrary(const char* libPath, const char* funcName);
