/**
  * Glow ESP made by Float & helped by v952
  thanks to v9 for helping
**/

// module files locale
#include "modules/framework/CDrawManager.h"
#include "modules/framework/SDK.h"
#include "modules/framework/Util.h"
#include "modules/Main/color.h"
#include "modules/Main/Entity.h"

// define local of glow in cheat
#include "Visual/Glow.h"
// team 3: 0.490000 0.660000 0.770000 blue
// team 2: 0.740000 0.230000 0.230000 red

// these are some HORRIBLE MACROS
// one of the worst things i have ever done
#define REDCOLORFLOAT (float)0.490000, (float)0.660000, (float)0.770000
#define BLUCOLORFLOAT (float)0.740000, (float)0.230000, (float)0.230000

Color healthToColor(int health, int maxHealth)
{
    int r = 0, g = 0, b = 0;

    if(health > maxHealth)
    {
        b = health - maxHealth;
        health = maxHealth;
    }

    int percent = (health / maxHealth) * 100;

    r = 0 + percent * (255 - 0);
    g = 255 + percent * (0 - 255);
    //double resultBlue = color1.blue + percent * (color2.blue - color1.blue);

    return Color{r, g, b, 255};
}

//=======================================
int Glow::registerGlowObject(CBaseEntity *ent, float r, float g, float b, float a, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot)
{
    typedef int(__thiscall *registerFn)(GlowManager *, CBaseEntity *, Vector &, float, bool, bool, int);
    static DWORD dwFn = gSingatures.GetClientSignature("55 8B EC 51 53 56 8B F1 57 8B 5E 14");
    static registerFn Register = (registerFn)dwFn;

    return Register(pGlowOgjectManager, ent, Vector{r, g, b}, a, bRenderWhenOccluded, bRenderWhenUnoccluded, nSplitScreenSlot);
}

const char *Glow::name() const{
    return "Glow";
}

//================
bool Glow::init()
{
  // get the Glow
  DWORD dwGlowLoc = gSingatures.GetClientSignature("8B 0D ? ? ? ? A1 ? ? ? ? 56 8B 37") + 0x2;
  XASSERT(dwGlowLoc);
  pGlowOgjectManager = *(GlowManager **)dwGlowLoc;
  XASSERT(pGlowOgjectManager);
  return true;
}

bool Glow::paint(){
    if(variables[2].bGet() || !variables[0].bGet())
      return true;
    for(auto &glowObj : pGlowOgjectManager->glowObjects)
    {
        if(glowObj.hEntity != -1){
            CEntity<> ent{HANDLE2INDEX(glowObj.hEntity)};

            if(ent == NULL)
              continue;
            if(ent->IsDormant())
              continue;

              //Color c = healthToColor(ent.get<int>(gEntVars.iHealth), getMaxHealth(ent));

  			//glowObj.r = c.r() / 255.0f; // red
  			//glowObj.g = c.g() / 255.0f; // green
  			//glowObj.b = c.b() / 255.0f; // blue
  			//glowObj.a = 1.0f; // 100% alpha

  			//Log::Console("team %d: %f %f %f", ent.get<int>(gEntVars.iTeam), glowObj.r, glowObj.g, glowObj.b);
        }
    }

    return true;
}

bool Glow::inEntityLoop(int index){
    if(index == me)
      return false;

      // player
      CEntity<> player(index);

      // if no nulls are returned
      if(player.isNull()){
        if(glowObjects[index])
          glowObjects[index] = false;
        return false;
      }

      classId id = player->GetClientClass()->iClassID;
        if(id == clasId::CTFPlayer){
          // no dormants
          if(player->IsDormant() || player.get<BYTE>(gEntVars.iLifeState) != LIFE_ALIVE || !variables[0].get<bool>() || (variables[1].get<bool>() && gLocalPlayerVars.team == player.get<int>(gEntVars.iTeam)))
          {
            player.set<bool>(gEntVars.gGlowEnabled, false);
            player.castToPointer<CBaseCombatCharacter>()->DestroyGlowEffect();
            return false;
          }

          // glow disabled
          if(player.get<bool>(gEntVars.bGlowEnabled))
            return false;

          // Glow bGlowEnable
          player.set<bool>(gEntVars.bGlowEnabled, true);
          player.castToPointer<CBaseCombatCharacter>()->UpdateGlowEffect();
            return true;
        }

        else if(id == classId::CObjectDispenser || id == classId::CObjectSentrygun || id == classId::CObjectTeleporter || id == classId::CBaseObject ||
		            id == classId::CTFProjectile_Arrow || id == classId::CTFProjectile_Cleaver || id == classId::CTFProjectile_Flare || id == classId::CTFProjectile_Rocket ||
		            id == classId::CTFProjectile_SentryRocket || id == classId::CTFGrenadePipebombProjectile)
    {
      int team = player.get<int>(gEntVars.iTeam);
      if(glowObjects[index] == false && (variables[1].get<bool>() && gLocalPlayerVars.team == team))
      {
          if(team == 3){
              registerGlowObject(player.castToPointer<CBaseEntity>(), BLUCOLORFLOAT, 1.0f, true, false, 0);
          else if(team == 2){
              registerGlowObject(player.castToPointer<CBaseEntity>(), REDCOLORFLOAT, 1.0f, true, false, 0);

              }
              glowObjects[index] = true;
          }
          else if(player->IsDormant())
            glowObjects[index] = false;
      }
      return false;
    }
}
