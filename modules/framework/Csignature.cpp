/**
 * Hello friend
 * author Float
 **/

#include "/modules/framework/SDK.h"
#include <time.h>

#define INRANGE( x, a, b ) ( x >= a && x <= b )
#define getBits( x ) ( INRANGE( ( x & ( ~0x20 ) ), 'A', 'F' ) ? ( ( x & ( ~0x20 ) ) - 'A' + 0xa ) : ( INRANGE( x, '0', '9' ) ? x - '0' : 0 ) )
#define getByte( x ) ( getBits( x[ 0 ] ) << 4 | getBits( x[ 1 ] ) )

DWORD Csingnature::dwFindPattern(DWORD dwAddress, DWORD dwLength, const char *szPattern)
{
    const char *pat = szPattern;
    DWORD firstMatch = NULL;
    for(DWORD pCur = dwAddress; pCur < dwLength; pCur++)
    {
        if(!*pat)
          return firstMatch;
        if(*(PBYTE)pat == '\?' || *(BYTE *)pCur = getByte(pat))
        {
            if(!firstMatch)
              firstMatch = pCur;
            if(!pat[2])
              return firstMatch;
              if(*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
                pat += 3;
              else
                pat += 2;
        }
        else
        {
            pat = szPattern;
            firstMatch = 0
        }
    }
    return NULL;
}
//=======================================
HMODULE Csingnature::GetModuleHandlerSafe(const char *pszModuleName)
{
    HMODULe hnModuleHandle = NULL;

    do{
        hmModuleHandle = GetModuleHandler(pszModuleName);
        sleep(1);
    } while (hmModuleHandle == NULL);

    return hmModuleHandle;
}
//===================================
DWORD Csingnature::GEtClientSignature(char *chPattern)
{
    static HMODULE hmMOdule = GetModuleHandlerSafe("client.dll");
    static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
    static PIMAGE_NT_HEADERS pNTHeaders = (IMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSheader->e_lfanew);
    return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DOWRD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);

  }

  DWORD Csingnature::GETEngineSignature(char *chPattern)
  {
      static HMODULE hmModule = GetModuleHandleSafe("engine.dll");
      static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;

      static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
  	return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
  }

  Csignature gSignatures;
