#pragma once
#include "../../../../Utils/Memory/Memory.hpp"
#include "../Core/HashedString.hpp"

class Item {
public:
	BUILD_ACCESS(this, std::string, AtlasTextureFile, 0xB0);
    BUILD_ACCESS(this, std::string, Namespace, 0x100);
    BUILD_ACCESS(this, std::string, name, 0xD8);
    BUILD_ACCESS(this, bool, Glint, 0x14A);
};