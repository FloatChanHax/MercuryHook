/**
  * This cheat was made by Float + v9 + nullifiedcat
**/

#include "/src/Header/aimbot.h"
#include "/modules/framework/Util.h"



CAimbot gAim;

void CAimbot::Run(CbaseEntity* pLocal, CuserCmd* pCommand)
{

    gCvars.iAimbotIndex = -1;
      if (!gCvars.aimbot_active)
      return;

      if (!Util->IsKeyPressed(gCvars.aimbot_key))
      return;

      if (!pLocal->GetActiveWeapon())
      return;

      CBaseEntity* pEntity = GetBaseEntity(GetBaseTarget(pLocal));
        if (!pEntity)
            return;

             int iBestHitbox = GetBestHitbox(pLocal, pEntity);
              if (iBestHitbox == -1)
               return;

               std::vector vEntity = pEntity->GetHitboxPosition(ibestHitbox);

               std::vector vLocal = pLocal->GetEyePosition();

               std::vector vAngs;
               VectorAngles((vEntity - vLocal), vAngs);

                ClampAngle(vAngs);
                gCvars.iaimbotIndex = pEntity->GetIndex();
                pCommand->viewangles = vAngs;

                gInts.Engine->SetViewAngles(pCommand->viewangles);

                if (gCvars.aimbot_autoshoot)
                   pCommand->buttons |= IN_ATTACK;

               }

               int CAimbot::GetBestTarget(CBaseEntity* pLocal)
               {
                  int iBestTarget = -1;
                  // could be smaller then -1
                  float f1DistToBest = 9999.f;

                  std::vector vLocal = pLocal->GetBaseEntity(i);

                  for (int i  = 1; i <= gInts.Egine->GetMaxClients(); i++)
                  {
                      if (i == me)
                        continue;

                      CBaseEntity* pEntity = GetBaseEntity(i);

                      if (!pEntity)
                         continue;

                      if (pEntity->IsDormant())
                         continue;

                      int iBestHitbox = GetBestHitbox(pLocal, pEntity);

                      if (iBestHitbox == -1)
                      continue;

                      std::vector vEntity = pEntity->GetHitboxPosition(iBestHitbox); //pEntity->GetWorldSpaceCenter(vEntity);
                       if(!gCvars.PlayerMode[i])
                          continue;

                          if (pEntity->GetCond() & TFCond_Ubercharged ||
                              pEntity->GetCond() & TFCond_UberchargedFading ||
                              pEntity->GetCond() & TFCond_Bonked)
                            continue;

                            float f1DistToTarget = (vLocal - vEntity).Length();

                             if (f1f1DistToTarget < f1f1DistToBest){
                               f1f1DistToBest = f1f1DistToTarget;
                               iBestTarget = i;
                             }

                             if (gCvars.PlayerMode[i] == 2) //always aim at target first
                                return 1;
                  }

                return ibestTarget;

          }
int CAimbot::GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
    int iBestHitbox = -1;

    if (!gCvars.aimbot_hitbox)
    {
         if (Util->IsHeadshotWeapon(pLocal, pLocal->GetActiveWeapon()))
             iBestHitbox = 0;
         else
             iBestHitbox = 4;
      }
      else
      {
         iBestHitbox = gCvars.aimbot_hotbox - 1;
      }

      if (gCvars.aimbot_hitscan)
      {
          for (int i = 0; i < 17; i++)
          {
             if (Util->IsVisable(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(i)))
                return i;
          }
      }

       if (pEntity->GetHitboxPosition(iBestHitbox).IsZero())
        return -1;

       if (!Util->IsVisable(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(iBestHotbox)))
         return -1;

        return iBestHitbox;
}
