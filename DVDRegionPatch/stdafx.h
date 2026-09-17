#pragma once

#include <xtl.h>
#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	LONG XexGetModuleHandle(PCHAR, PHANDLE);
	LONG XexGetProcedureAddress(HANDLE, DWORD, PVOID);

	unsigned long __cdecl DbgPrint(char *, ...);
	
	typedef long			NTSTATUS;
	#define STATUS_SUCCESS 0x00000000

#ifdef __cplusplus
}
#endif


#ifdef NDEBUG
#define DBG(str, ...) /**/
#else
#define DBG(str, ...) DbgPrint("[DVDRegion] " str "\n", __VA_ARGS__)
#endif