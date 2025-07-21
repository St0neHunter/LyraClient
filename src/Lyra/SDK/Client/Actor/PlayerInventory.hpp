#pragma once
#include "../../../../Utils/Memory/Memory.hpp"
#include "Container.hpp"

class PlayerInventory {
public:
	BUILD_ACCESS(this, Container*, mContainer, 0xB8);
	BUILD_ACCESS(this, int, SelectedSlot, 0x010);
};