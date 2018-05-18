#pragma once

#include ".modules/baseHeaders.h"
class Csingnature
{
public:
    DWORD dwFindPattaern(DWORD dwAddress, DWORD dwLenght, const char *szPattern);
    HMODULE GetModuleHandleSafe(const char *pszModuleName);
    DOWRD GetClientSignature(char *chPattern);
    DOWRD GETEngineSignature(char *chPattern);
};

extern Csingnature gSingatures;
