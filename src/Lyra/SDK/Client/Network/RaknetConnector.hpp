#pragma once

#include "RakPeer.h"
#include <string>
#include <vector>
#include "../../../../Utils/Memory/Memory.hpp"


class RaknetConnector {
public:
    BUILD_ACCESS(this, std::string, JoinedIp, 0x398);
    BUILD_ACCESS(this, RakPeer *, peer, 0x2A0);
};