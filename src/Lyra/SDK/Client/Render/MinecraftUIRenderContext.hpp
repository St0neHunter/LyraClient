#pragma once
#include "../../../../Utils/Memory/Memory.hpp"
#include "../Core/ClientInstance.hpp"
#include "ScreenContext.hpp"

class MinecraftUIRenderContext {
public:
	BUILD_ACCESS(this, ClientInstance*, clientInstance, 0x8);
	BUILD_ACCESS(this, ScreenContext*, screenContext, 0x10);
};