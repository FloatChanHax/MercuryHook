/**
  * Big credits to DurRud with this
  * author Float
  * Mercury Cheat
  **/

  #include "/modules/framework/SDK.h"
  #include "/modules/main/Client.h"
  #include "/modules/framework/panels.h"
  #include "/modules/main/unlinkpeb.h"
  #include "/modules/framework/CHackState.h"

  //======================
  COffset gOffsets;
  CHack gHack;
  CInterfaces gInts;
  CPlayerVaraiables gEntVars;
  playerVars_t gLocalPlyerVars;

  BOOL APIENTRY DLLMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
  {
      // manually map the dll file
      if(dwReason == DLL_PROCESS_ATTACH)
      {
        #ifndef ALT_BUILD
          //Disable Treads(hInstance);
          UnlinkModuleFromPEB(hInstance);
          RemovePEHeader((DOWRD)hInstance);
        #else
        #pragma message("ALT_BUILD ENABLED")
        #endif
            Log::Init(hInstance);

            gInts.thisDll = hInstance;

            // init call
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&HState::init, 0, 0, 0)
      }

      else if(dwReason == DLL_PROCESS_DETACH)
      {
          // code should never reach here
          gHack.~Chack();
      }
      return true;
  }
