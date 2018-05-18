/**
   * Aimbot made by Float + v9 and f1
    reDarkstorm is base and some help from v9 to make the inits
    if you crack this GG
**/

#pragma once
#include "../modules/framework/SDK.h"

class CAimbot
{
public:
  void Run(CBaseEntity* pLocal, CUserCmd* pCommand);
private:
   int GetBestTarget(CBaseEntity* pLocal);

   int GetBestHotbox(CBaseEntity* pLocal, CBaseEntity* pEntity);
};

extern CAimbot gAim; 
