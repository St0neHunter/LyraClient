#pragma once
#include "../../../../Utils/Memory/Memory.hpp"
#include "../Actor/LocalPlayer.hpp"
#include "../Block/BlockSource.hpp"
#include "../Render/GuiData.hpp"
#include "MCGame.hpp"
#include "../Level/LevelRender/LevelRender.hpp"
#include "../Network/LoopbackPacketSender.hpp"

class ClientInstance {
public:
	BUILD_ACCESS(this, GuiData*, guiData, 0x5B0);
	BUILD_ACCESS(this, float*, FovX, 0x748);
	BUILD_ACCESS(this, MCGame*, mcgame, 0xD0);
	BUILD_ACCESS(this, float*, FovY, 0x75C);

	void grabMouse() {
		Memory::CallVFunc<343, void>(this);
	}

	void releaseMouse() {
		Memory::CallVFunc<344, void>(this);
	}

	BlockSource* getBlockSource() {
		return Memory::CallVFunc<29, BlockSource*>(this);
	}

	LocalPlayer* getLocalPlayer() {
		return Memory::CallVFunc<30, LocalPlayer*>(this);
	}


	LevelRender* getLevelRenderer() {
		return Memory::direct_access<LevelRender*>(this, 0xE8);
	}

    LoopbackPacketSender *getPacketSender() {
        return *reinterpret_cast<LoopbackPacketSender **>((uintptr_t) this + 0xF8);
    }

    RaknetConnector *getRakNetConnector() {
        if (getPacketSender() == nullptr)
            return nullptr;

        return getPacketSender()->networkSystem->remoteConnectorComposite->rakNetConnector;
    }
};