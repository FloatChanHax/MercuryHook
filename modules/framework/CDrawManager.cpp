#include "../../modules/framework/CDrawManager.h"

//=====================
CDrawManager gDrawManager;

#define ESP_HEIGHT 12
#define HUD_HEIGHT 14
//======================
void CDrawManager::Initialize()
{
    if (gInts.surface == nullptr)
        return;

    gInts.Engine->GetScreenSize(gScreenSize.iScreenWidth, gScreenSize.iScreenHeight);
     font_t font;

     font.setFont("")
}