#pragma once
#include "ItemStack.hpp"

class Container {
public:
	std::vector<ItemStack*> getSlots() {
		std::vector<ItemStack*> out;
		Memory::CallVFunc<25, void, std::vector<ItemStack*>&>(this, out);
		return out;
	}

	ItemStack* getitem(int slot) {
		return Memory::CallVFunc<7, ItemStack *>(this, slot);
	}
};