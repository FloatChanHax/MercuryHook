#include "/modules/framework/CHackState"
#include "/modules/main/Client.h"
#include "/modules/framework/panels.h"
#include <thread>

void clientModeThread(){
  PVOID tempCM;
  do {
    DWORD dwClientModeAddress = gSingatures.GEtClientSignature(Xosstrings("8B 0D ? ? ? ? 8B 02 D9 05"));
    XASSERT(dwClientModeAddress);
    //gInts.ClientMode = **reinterpret_cast<ClientModeShared ***>(dwClientModeAddress + 2);
    tempCM = **reinterpret_cast<void ***>(dwClientModeAddress + 0x2);

  } while(temCM == nullptr);

  gInts.ClientMode = static_cast<ClientModeShared *>(tempCM);

  // client mode not nullptr hook it
  VMTBaseManager *clientModeHook = new VMTBaseManager();
  clientModeHook->Init(gInts.ClientMode);
  clientModeHook->HookMethod(&Hooked_CreateMove, gOffsets.createMoveOffsets);
  clientModeHook->Rehook();

  HState::instance()-?addStatus(HState::hackStatus::clientModeInited);
  return;
}

void steam() {
    if(gInts.steam.client == nullptr)
    {
      auto steamClientFactory = srcFactory(GetProcAddress(gSingatures.GetModuleHandleSafe("steamClient.dll"), "CreateInterface"));
      gInts.steam.client = steamClientFactory.get<IsteamClient017 *>(STEAMCLIENT_INTERFACE_VERSION_017, NULL);
      HSteamPipe hNewPipe = gInts.steam.client->CreateSteamPipe();
      HSteamUser hNewUser = gInts.steam.client->ConnectToGlobalUser(hNewPipe);
      gInts.steam.friends == reinterpret_cast<ISteamFriends002 *>(gInts.steam.client->GetISteamFriends(hNewUser, hNewPipe, STEAMFRIENDS_INTERFACE_VERSION_002));
      gInts.steam.user = reinterpret_cast<ISteamUser017 *>(gInts.steam.client->GetISteamUser(hNewUser, hNewPipe, STEAMUSER_INTERFACE_VERSION_017));
      gInts.steam.userStats = reinterpret_cast<ISteamUserStats011 *>(gInts.steam.client->GetISteamUserStats(hNewUser, hNewPipe, STEAMUSERSTATS_INTERFACE_VERSION_011));
    }

    HState::instance()->addStatus(HState::hackStatus::steamInited);
    return ;
}


//=====================================================
void HState::init()
{
  // spawn these threads first
	std::thread{clientModeThread}.detach();

	std::thread{steam}.detach();

	if(gInts.Client == nullptr) //Prevent repeat callings.
	{
		// == CLIENT ==
		auto ClientFactory = srcFactory(GetProcAddress(gSignatures.GetModuleHandleSafe("client.dll"), "CreateInterface"));

		gInts.Client = ClientFactory.get<CHLClient *>("VClient017");

		gInts.EntList = ClientFactory.get<CEntList *>("VClientEntityList003");

		gInts.Prediction = ClientFactory.get<CPrediction *>("VClientPrediction001");

		// == ENGINE ==
		auto EngineFactory = srcFactory(GetProcAddress(gSignatures.GetModuleHandleSafe("engine.dll"), "CreateInterface"));

		gInts.Engine = EngineFactory.get<EngineClient *>("VEngineClient013");

		gInts.ModelInfo = EngineFactory.get<CModelInfo *>("VModelInfoClient006");

		gInts.EngineTrace = EngineFactory.get<CEngineTrace *>("EngineTraceClient003");

		gInts.RandomStream = EngineFactory.get<CUniformRandomStream *>("VEngineRandom001");

		// == VGUI ==
		auto VGUIFactory = srcFactory(GetProcAddress(gSignatures.GetModuleHandleSafe(XorString("vguimatsurface.dll")), XorString("CreateInterface")));

		gInts.Surface = VGUIFactory.get<ISurface *>("VGUI_Surface030");

		// == VSTDLIB ==
		auto CvarFactory = srcFactory(GetProcAddress(gSignatures.GetModuleHandleSafe(XorString("vstdlib.dll")), XorString("CreateInterface")));

		gInts.Cvar = CvarFactory.get<ICvar *>("VEngineCvar004");

		// == VGUI2 ==
		auto VGUI2Factory = srcFactory(GetProcAddress(gSignatures.GetModuleHandleSafe(XorString("vgui2.dll")), XorString("CreateInterface")));
		gInts.Panels	  = VGUI2Factory.get<IPanel *>("VGUI_Panel009");

		// with new not_nulls, panels is garenteed not to be null
		VMTBaseManager *panelHook = new VMTBaseManager(); //Setup our VMTBaseManager for Panels.
		panelHook->Init(gInts.Panels);
		panelHook->HookMethod(&Hooked_PaintTraverse, gOffsets.paintTraverseOffset);
		panelHook->Rehook();

		// TODO change this if we use its
		CreateInterfaceFn AppSysFactory = nullptr;
		DWORD dwAppSystem = gSignatures.GetEngineSignature("A1 ? ? ? ? 8B 11 68");
		XASSERT(dwAppSystem);
		if(dwAppSystem)
		{
			gInts.Globals = *reinterpret_cast<CGlobals **>(dwAppSystem + 8);

			DWORD dwAppSystemAddress = **reinterpret_cast<PDWORD *>((dwAppSystem) + 1);
			AppSysFactory			= reinterpret_cast<CreateInterfaceFn>(dwAppSystemAddress);
		}

		// get dwWriteUserCmd
		// do this before we hook it
		gOffsets.dwWriteUserCmd = gSignatures.GetClientSignature("55 8B EC 8B 45 10 83 EC 08 8B 40 04"); //Grab WriteUserCmd from client.dll.
		XASSERT(gOffsets.dwWriteUserCmd);																 //Make sure it's not 0.

		VMTBaseManager *CHLClientHook = new VMTBaseManager(); // set up for chlclient.
		CHLClientHook->Init(gInts.Client);
		CHLClientHook->HookMethod(&Hooked_Key_Event, gOffsets.keyEvent); // hook in key event.
		CHLClientHook->Rehook();

		DWORD dwInputPointer = (gSignatures.dwFindPattern((DWORD)CHLClientHook->GetMethod<DWORD>(gOffsets.createMoveOffset), ((DWORD)CHLClientHook->GetMethod<DWORD>(gOffsets.createMoveOffset)) + 0x100, "8B 0D")) + (0x2); //Find the pointer to CInput in CHLClient::CreateMove.
		gInts.Input		  = **reinterpret_cast<CInput ***>(dwInputPointer);

		// hook getusercmd from CInput
		VMTBaseManager *inputHook = new VMTBaseManager();
		inputHook->Init(gInts.Input);
		inputHook->HookMethod(&Hooked_GetUserCmd, gOffsets.getUserCmdOffset);
		inputHook->Rehook();

		// update the status
		HState::instance()->addStatus(hackStatus::baseInited);
  }
  return;
}
/===================================
void HState::think()
{
  if(checkStatus(baseInitied) && checkStatus(clientModeInited) && checkStatus(steamInited))
  {
    addStatus(FullyInited);
  }
}
