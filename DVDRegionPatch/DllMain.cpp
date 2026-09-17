#include "stdafx.h"
#include "Detour.h"
#include "xconfig.h"

Detour* ExGetXConfigSetting_Detour = NULL;

void* ResolveFunction(PCHAR moduleName, DWORD ordinal) {
	HANDLE handle; void* addr;
	XexGetModuleHandle(moduleName, &handle);
	XexGetProcedureAddress(handle, ordinal, &addr);
	return addr;
}

NTSTATUS WINAPI ExGetXConfigSetting_Hook(USHORT Category, USHORT Entry, LPVOID Buffer, DWORD cchBuffer, LPDWORD cchOutBuffer) {	
	NTSTATUS ret = ExGetXConfigSetting_Detour->GetOriginal<decltype(&ExGetXConfigSetting_Hook)>()(Category, Entry, Buffer, cchBuffer, cchOutBuffer);
	if(Buffer == NULL) return ret;
	if(ret != STATUS_SUCCESS) return ret;

	if( Category == CATEGORY_DVD &&  Entry == ENTRY_REGION) { // is it querying DVD region ?
		if(cchBuffer == sizeof(int)) // does an int fit into this buffer ?
		{
			DBG("Current region code: %x", *(int*)Buffer);
			
			*(int*)Buffer = REGION_FREE; // set region to REGION_FREE (0xFF)

			DBG("Patched region code: %x", *(int*)Buffer);
		}
	}
	
	return ret;
}

bool UnPatchDvd() {
	if(ExGetXConfigSetting_Detour != NULL) {		
		delete ExGetXConfigSetting_Detour;
		ExGetXConfigSetting_Detour = NULL;
		return true;
	}
	return false;
}
bool PatchDvd() {
	if(ExGetXConfigSetting_Detour == NULL) {
		void* ExGetXConfigSetting = ResolveFunction("xboxkrnl.exe", 0x10);
		DBG("ExGetXConfigSetting ptr: %p", ExGetXConfigSetting);
		if(ExGetXConfigSetting == NULL) return false;

		ExGetXConfigSetting_Detour = new Detour(ExGetXConfigSetting, &ExGetXConfigSetting_Hook);
		if(!ExGetXConfigSetting_Detour->Install()) {
			DBG("Failed to hook ExGetXConfigSetting");
			return false;
		}
	}
	return true;
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		return PatchDvd();
	} else if (dwReason == DLL_PROCESS_DETACH) {
		UnPatchDvd();
	}

	return TRUE;
}
