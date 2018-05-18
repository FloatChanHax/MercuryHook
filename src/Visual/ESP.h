#pragma once
#include "/modules/framework/SDK.h"

class
{
public:
  void Run(CBaseEntity* pLocal);

private:
  void Player_ESP(CBaseEntity* pLocal, CBaseEntity* pEntity);

  // more functions here

  void DrawBone(CBaseEntity* pEntity, int* iBones, int count, Color clrCol);
}
extern CESP gESP;
