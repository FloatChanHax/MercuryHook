/**
 *  Dev Float & v952
 *  date : 4/23/18
 **/

// Include Files to find defintions
#include "MercuryCore/modules/framework/SDK.h"
#include "MercuryCore/modules/framework/panels.h"
#include "MercuryCore/modules/framework/CDrawManager.h"

//================================

// void function code here
void __fastcall Hooked_PaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanels, bool forceRepaint, bool allowForce)
{
    return gHack.paintTarverse(pPanels, edx, vguiPanels, forceRepaint, allowForce);

}
//=================== 

void Intro(){
    return gHack.intro();
}