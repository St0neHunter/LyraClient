#include <iostream>
#include "RenderGuiItemInChunkHook.hpp"
#include "../../../Client.hpp"
#include "../../../Module/ModuleManager.hpp"
#include "../../../Event/EventManager.hpp"
#include "../../../../Utils/RenderUtils.h"
#include "../../../SDK/Client/Actor/ItemStack.hpp"

RenderGuiItemInChunkHook::RenderGuiItemInChunkHook() : Hook("RenderGuiItemInChunk_hook", "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 A8 48 81 EC 58 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 40 44 89 4D")
{
}

void RenderGuiItemInChunkHook::enableHook()
{
	uintptr_t color = Memory::findSig("F3 0F 10 15 ? ? ? ? 48 8D 8C 24 ? ? ? ? F3 0F 10 0D ? ? ? ? 45 8B C4");
	uintptr_t ref = color + 4;
	uintptr_t deref = *reinterpret_cast<uint32_t*>(ref);
	uintptr_t result = ref + deref + sizeof(uint32_t);
	this->color = reinterpret_cast<mce::Color*>(result);
	this->original = *this->color;
	this->autoHook((void*)Callback, (void**)&func_original);
}

double RenderGuiItemInChunkHook::Callback(
	void* itemRenderer,
	void* renderContext,
	uint32_t itemRenderChunkType,
	ItemStack* item,
	float x,
	float y,
	float lightMultiplyer,
	float alphaMultiplyer,
	float scale,
	int frame,
	bool allowAnimation,
	float zOffset)
{
	auto i = item->getItem();
	if (i->getname() == "splash_potion") {
		*RenderGuiItemInChunkHook::color = mce::Color(0, 0, 255, 1);
		item->getItem()->setGlint(true);
	}
	else {
		*RenderGuiItemInChunkHook::color = RenderGuiItemInChunkHook::original;
	}
	return func_original(itemRenderer, renderContext, itemRenderChunkType, item, x, y, lightMultiplyer, alphaMultiplyer, scale, frame, allowAnimation, zOffset);
}