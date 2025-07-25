#include <iostream>
#include "SetupAndRender.hpp"
#include "../../../Client.hpp"
#include "../../../../Utils/TessUtils/TessUtils.hpp"

SetupAndRenderHook::SetupAndRenderHook() : Hook("Setup And Render Hook", "? ? ? ? ? ? ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89")
{
}

void SetupAndRenderHook::enableHook()
{
	this->autoHook((void*)SetupAndRendeCallback, (void**)&func_original);
}

void SetupAndRenderHook::SetupAndRendeCallback(ScreenView* pScreenContext, MinecraftUIRenderContext* mcuirc)
{
	SDK::clientInstance = mcuirc->getclientInstance();
	SDK::screenView = pScreenContext;
	std::string TopLayer = SDK::screenView->VisualTree->root->LayerName;
	if (TopLayer != "toast_screen" and TopLayer != "debug_screen")
		SDK::TopScreen = TopLayer;

	TessUtils::update(mcuirc);

	SetupAndRenderEvent event(mcuirc);

    eventMgr.onPreMCRender(event);

    func_original(pScreenContext, mcuirc);

    eventMgr.onPostMCRender(event);

}