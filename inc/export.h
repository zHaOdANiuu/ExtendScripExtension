#pragma once

#include "basic.h"

__export long ESGetVersion();

__export char* ESInitialize(const TaggedData**, long);

__export void ESFreeMem(void* p);

__export void ESTerminate();

__export int ESClientInterface(SoCClient_e, SoServerInterface*, SoHServer);

__export void* ESMallocMem(size_t);

__export AEGP_PluginInitFuncPrototype master;
