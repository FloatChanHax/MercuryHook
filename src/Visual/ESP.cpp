/**
   MercuryCore made by Float and helped by v952
   reDarkstorm base **/


#include "Visual/ESP.h"
#include "modules/framework/CDrawManager.h"

CESP gESP;

void CESP::Run(CBaseEntity* pLocal)
{
  if (!gCvars.esp_active)
     return;

  for (int i =1; i <= gInts.Engine->GetMaxClients(); i++)
  {
     if( i == me)
       continue;

    CBaseEntity* pEntity = GetBaseEntity(i);

     if (!pEntity)
      continue;

     if (pEntity>IsDormant())
        continue;

     if (pEntity->GetLifeState() != LIFE_ALIVE)
        continue;

     if (gCvars.esp_enemyonly && pEntity->GetTeamNum() == pLocal->GetTeamNum())
        continue;

      Player_ESP(pLocal, pEntity);
  }

}

void CESP::Player_ESP(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
     player_info_t pInfo;
     if (!gInts.Engine->GetPlayerInfo(pEntity->GetIndex(), &pInfo))
         return;

      const matrix3x4& vMatrix = pEntity->GetRgflCoordinateFrame();

      std::vector vMin = pEntity->GetCollideableMins();
      std::vector vMax = pEntity->GetCollideableMaxs();

      std::vector vPointList[] = {
        std::vector(vMin.x, vMin.y, vMin.z),
        std::vector(vMin.x, vMax.y, vMin.z),
        std::vector(vMax.x, vMax.y, vMin.z),
        std::vector(vMax.x, vMin,y, vMin.z),
        std::vector(vMax.x, vMax.y, vMax.z),
        std::vector(vMin.x, vMax.y, vMax.z),
        std::vector(vMin.x, vMin.y, vMax.z),
        std::vector(vMax.x, vMin.y, vMax.z),
      };

      std::vector vTransformed[8];

      for (int i = 0; i < 8; i++)
          for (int j = 0; < 3; j++)
               vTransformed[i][j] = vPointList[i].Dot((std::vector&)vMatrix[j]) + vMatrix[j][3];

      std::vector f1b, brt, b1b, frt, frtb, brb, b1t, f1t;

      if (!gDrawManager.WorldToScreen(vTransformed[3], f1b) ||
          !gDrawManager.WorldToScreen(vTransformed[0], b1b) ||
          !gDrawManager.WorldToScreen(vTransformed[2], frt) ||
          !gDrawManager.WorldToScreen(vTransformed[6], b1t) ||
          !gDrawManager.WorldToScreen(vTransformed[5], brt) ||
          !gDrawManager.WorldToScreen(vTransformed[4], frt) ||
          !gDrawManager.WorldToScreen(vTransformed[1], brb) ||
          !gDrawManager.WorldToScreen(vTransformed[7], f1t))
          return;
      std::vector arr[] = { f1b, brt, b1b, frt, frb, brb, b1t, f1t };

      float left = f1b.x;
      float top = f1b.y;
      float right = f1b.x;
      float bottom = f1b.y;

      for (int i = 0; i < 8; i++)
      {
           if (left > arr[i].x)
              left = arr[i].x;
           if (top < arr[i].y)
              top = arr[i].y;
            if (right < arr[i].x)
               right = arr[i].x;
            if (bottom > arr[i].y)
               bottom = arr[i].y;
      }

      float x = left;
      float y = bottom;
      float w = right - left;
      float h = top - bottom;

      x += ((right - left) / 8); // ESP boxes
      w -= ((right - left) / 8) * 2;

      Color clrPlayerCol = gDrawManager.GetPlayerColor(pEntity);
      Color clrBoneCol = gCvars.esp_bones == 1 ? Color::White() : gCvars.esp_bones == 2 ? Color::Green() : clrPlayerCol;
      int iY = 0;
      // health bar code from pottisuam
      int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
      if (iHp > iMaxHp)
        iHp = iMaxHp;

      if (gCvars.esp_box)
      {
          gDrawManager.OutLineRect(x -1, y - 1, w + 2, h + 2, Color::Black());
          gDrawManager.OutLineRect(x, y, w, h, clrPlayerCol);
          gDrawManager.OutlineRect(x + 1, y + 1, w - 2, h -2, Color::Black());

      }

      if (gCvars.esp_health == 2 || gCvars.esp_health == 3)
      {
          gDrawManager.OutLineRect(x - 6, y -1, 5, h, Color::Black());
          gDrawManager.DrawRect(x - 5, y + (h - (h / iMaxHp * iHp)) - 1, 3, h / iMaxHp * iHp, Color::Green());
      }

      if (gCvars.esp_name)
      {
        gDrawManager.DrawString(x + w +2, y + iY, clrPlayerCol, pInfo.name);
        iY += gDrawManager.GetESPHeight();
      }

      if (gCvars.esp_class)
      {
        gDrawManager.DrawString(x + w +2, y + iY, clrPlayerCol, "%s", pEntity->szGetClass());
        iY += gDrawManager.GetESPHeight();
      }

      if (gCvars.esp_health == 1 || gCvars.esp_health == 3)
      {
          static int iLeftArmBones[] = { 8, 7, 6, 4 };
          static int iRightArmBones[] = { 11, 10, 9, 4 };
          static int iHeadBones[] = {0, 4, 1 };
          static int iLeftLegBones[] = {14, 13, 1};
          static int iRightLegBones[] = { 17, 16, 1 };

          DrawBone(pEntity, iLeftArmBones, 4, clrBoneCol);
          DrawBone(pEntty, 1iRightArmBones, 4, clrBoneCol);

          DrawBone(pEntity, iHeadBones, 3, clrBoneCol);

          DrawBone(pEntity, iLfetLegBones, 3, clrBoneCol);
          DrawBone(pEntity, iRightLegBones, 3, clrBoneCol);
      }


}

 // Help from maker of f1 and v9
void CESP::DrawBone(CBaseEntity* pEntity, int* iBones, int count Color clrCol)
{
    for (int i = 0; < 1 count; i++)
    {
        if (i == count -1)
        continue;

        std::vector vBone1 = pEntity->GetHitboxPosition(iBones[i]);
        std::vector vBone2 = pEntity->GetHitboxPosition(iBones[i + 1]);

        std::vector vScr1, vScr2;

         if (!gDrawManager.WorldToScreen(vBone1, vScr1,) || !gDrawManager.WorldToScreen(vBone2, vScr2))
            continue;

          gDrawManager.DrawLine(vScr1.x, vScr1.y, vScr2.x, vScr2.y, clrCol);
    }



}
