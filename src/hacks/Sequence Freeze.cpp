/**
 * Author v952
 * created on Apr 29 18
 * 
 * 
 * 
 **/

#include "../modules/framework/SDK.h"
#include "../modules/common.hpp"

namespace hacks
{
namespace gui
{
namespace modules
{

CSequnceFreeze gRemoveCond;

gCvars.SequenceFreeze(CV_FLOAT, "0", "cond_enabled", "RemoveCond");
gCvars.absoluteframetime(DV_FLOAT, "0", "recond_num", "1-2", "RemoveCond_Number");

void CSequenceFreeze::Run(CBaseEntity* pLocal, CBaseEntity* pEntity);

void RemoveCond::Button_t(CV_DWORD, "Button_Key", int, FALSE, FALSE, 
(struct Button_t::Key_R), true);

// Check Key is active
  gCvars.SequenceFreeze = -1;
  if(!SequenceFreeze.removecond_enabled)
  return -1;
  
  if(!SDK->KeyIsPressg(gCvars.SequenceFreeze_KEY_R))
  return -1;




}}};
