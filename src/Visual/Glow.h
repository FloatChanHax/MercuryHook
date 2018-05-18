#pragma once


#include "modules/framework/IHack.h"
#include "modules/framework/SDK.h"
// #include "modules/Main/Trace.h"
#include "Visual/Glow.h"
#include "modules/Main/CUtlVector.h"
#include "modules/framework/CDrawManager.h"

#include <unordered_map>
// Check if Glow.cpp is defined
struct GlowOgkectDefinition_t
{
    CHandle hEntity;
    float r;
    float g;
    float b;
    float a;

    bool m_bRenderWhenOccluded;
    bool m_bRenderWhenUnoccluded;
    int m_nSplitScreenSlot;

    int m_nNextFreeSlot;

    static const int END_OF_FREE_LIST = -1;
    static const int ENTRY_IN_USE = -2;
};

class CGlowManager
{
    public:

    CUtlVector<GlowObjectDefinition_t> glowObjects;
};

class CGlow: public hack
{
    CGlowManager *pGlowObjectManager;

    var enabled_bool = var("Enabled", type_t::Bool);
    var enemy_bool = var("Enemy only", type_t::Bool);
    var team_color_bool = var("Team Colors", type_t::Bool);

    //int s = sizeof(GlowObjectDefinition_t);

    std::unordered_map<int, bool> glowObjects;
    int registerGlowObject(CBaseEntity *ent, float r, float g, float b, float a,
    bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot);

public:
  CGlow(){

      variables.push_back(enabled_bool);
      variables.push_back(enemy_bool);
      variables.push_back(team_color_bool);
  }

  const char *name() const override;
  bool init() override;
  bool paint() override;
  bool inEntityLoop(int index) override;
};
