#include "SDK.hpp"
#include "Client/Network/Packets/Packet.hpp"

ClientInstance* SDK::clientInstance = nullptr;
ScreenView* SDK::screenView = nullptr;
std::string SDK::TopScreen = "UnknownLayer";

std::shared_ptr<Packet> SDK::createPacket(int id) {

    static uintptr_t Address;

    if (Address == NULL) {
        Address = Memory::findSig("40 53 48 83 EC 30 45 33 C0 48 8B D9 FF CA 81 FA ? ? ? ? 0F 87 ? ? ? ? 48 63 C2 48 8D 0D ? ? ? ? 0F B6 84 01 ? ? ? ? 8B 94 81 ? ? ? ? 48 03 D1");
    }

    auto pFunction = reinterpret_cast<std::shared_ptr<Packet>(__fastcall *)(int)>(Address);
    return pFunction(id);
}


std::string SDK::getServerIP() {
    if (SDK::clientInstance != nullptr) {
        if (SDK::clientInstance->getLocalPlayer() != nullptr) {
            std::string ip{};
            if (SDK::clientInstance->getRakNetConnector() != nullptr) {
                ip = SDK::clientInstance->getRakNetConnector()->JoinedIp;
                if (!ip.empty()) {
                    return ip;
                }
            }
        }
    }
    return "world";
}
