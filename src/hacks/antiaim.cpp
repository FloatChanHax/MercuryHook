/**
 * 
 *  AntiAim.cpp 
 * 
 *  Author Float & NullifiedCat
 * 
 **/ 
#include "../modules/framework/common.hpp"

namespace hacks
{
namespace shared
{
namespace antiaim
{

gCvars.communicate(CV_SWITCH, "indentity", "1", "identify","Auto identify for other MercuryCore Users");
gCVars.enabled(CV_SWITCH, "Anti_Enabled", "0", "Anti-Aim","Master AntiAim");
gCvars.trueang(CV_SWITCH, "Anti_realfakes", "0", "Anti-Aim","Do real fakeangles");
gCvars.yaw(CV_FLOAT, "aa_yaw", "0", "Yaw", "Static yaw (left/right)", 360.0);
gCvars.pitch(CV_FLOAT, "Anti_pitch", "-89.0", "Pitch", "Static pitch", "(up/down)", -89.0, 89.0);
gCvars.yaw_real(CV_FLOAT, "Anti_yaw_real", "0", "Real Yaw", "Static yaw (left/right)")

}}};

