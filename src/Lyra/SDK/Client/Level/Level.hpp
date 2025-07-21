#pragma once

#include <string>
#include <unordered_map>

//#include "../Actor/Actor.hpp"
#include "HitResult.hpp"
#include "../../../../Utils/Memory/Memory.hpp"

class Actor;

class mcUUID {
public:
    uint64_t mostSig, leastSig;
};

enum PlayerListPacketType : int8_t {
    AddPlayerEntry = 0x0,  // The names are just add and removed but i dont want to cause issues
    RemovePlayerEntry = 0x1,
};

class PlayerListEntry {
public:
    uint64_t id; // This is the ActorUniqueID
    mcUUID UUID;
    std::string name, XUID, platformOnlineId;
    int buildPlatform;
    char filler[0x164];
    //SerializedSkin skin;
    bool isTeacher, isHost;
};

class Level {
    using troll = std::unordered_map<mcUUID, PlayerListEntry>;

public:
    troll &getPlayerMap() {
        return direct_access<troll>(this, 0xB98);
    }

    HitResult &getHitResult() {
        return *hat::member_at<std::shared_ptr<HitResult>>(this, 0x248);
    }

    std::vector<Actor *> getRuntimeActorList() {
        static uintptr_t sig = Memory::findSig("48 89 5C 24 18 55 56 57 48 83 EC 40 48 8B FA 48 89 54 24 30");
        static auto getRuntimeActorList = *(decltype(&Level::getRuntimeActorList) *) &sig;
        return (this->*getRuntimeActorList)();
    }
};