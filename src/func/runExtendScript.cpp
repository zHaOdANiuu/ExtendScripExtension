#include "runExtendScript.h"

int runExtendScript(AEGP_SuiteHandler& suites, const char* code, const char** result)
{
    InitError();
    AEGP_MemorySuite1* MemorySuite = suites.MemorySuite1();
    AEGP_MemSize size = 0;
    AEGP_MemHandle outResult = NULL;
    AEGP_MemHandle outErrorString = NULL;
    AEGP_MemHandle* targetResult = nullptr;

    ListenError(suites.UtilitySuite5()->AEGP_ExecuteScript(0, code, false, &outResult, &outErrorString));

    if (outResult)
        targetResult = &outResult;
    else if (outErrorString)
        targetResult = &outErrorString;

    if (targetResult == nullptr)
        return GetError();

    ListenError(MemorySuite->AEGP_LockMemHandle(*targetResult, (void**)(result)));
    ListenError(MemorySuite->AEGP_UnlockMemHandle(*targetResult));
    ListenError(MemorySuite->AEGP_FreeMemHandle(*targetResult));
    return GetError();
}
