#include "ExtendScripExtension.h"
#include <string>

struct SPBasicSuite* globalPicaBasicPtr = nullptr;

static char ESInitialize_FunctionSignatures[] = {
    "colorPicker_fs"
};

long ESGetVersion()
{
    return 0x10000;
};

char* ESInitialize(const TaggedData** argv, long argc)
{
    initSPBasicSuite();
    return ESInitialize_FunctionSignatures;
};

void ESFreeMem(void* p)
{
    delete (char*)(p);
};

void ESTerminate() {

};

int ESClientInterface(SoCClient_e kReason, SoServerInterface* pServer, SoHServer hServer)
{
    return 0;
};

void* ESMallocMem(size_t nbytes)
{
    void* p = malloc(nbytes);
    return p;
};

A_Err master(
    struct SPBasicSuite* pica_basicP,
    A_long major_versionL,
    A_long minor_versionL,
    AEGP_PluginID aegp_plugin_id,
    AEGP_GlobalRefcon* global_refconP)
{
    InitError();
    globalPicaBasicPtr = pica_basicP;
    return GetError();
}

static void initSPBasicSuite()
{
    if (globalPicaBasicPtr != nullptr)
        return;
    auto GetSPBasicSuite = loadFunctionFromLibrary<Type_SPBasicSuite>("PLUG", "PLUG_GetSPBasicSuite");
    if (GetSPBasicSuite == nullptr)
        GetSPBasicSuite = loadFunctionFromLibrary<Type_SPBasicSuite>("U", "U_SP_GetSPBasicSuite");
    if (GetSPBasicSuite == nullptr)
        GetSPBasicSuite(&globalPicaBasicPtr);
}

template <typename T>
static T loadFunctionFromLibrary(const char* libPath, const char* funcName)
{
    std::string tmp(libPath);
#ifdef AE_OS_WIN
    tmp.append(".dll");
    auto hModule = GetModuleHandleA(tmp.c_str());
#else
    tmp.append(".dylib");
    auto hModule = dlopen(tmp.c_str(), RTLD_LAZY);
#endif
    if (hModule == nullptr)
        return nullptr;
#ifdef AE_OS_WIN
    return (T)GetProcAddress(hModule, funcName);
#else
    return (T)dlsym(hModule, funcName);
#endif
}
