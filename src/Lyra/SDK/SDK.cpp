#include "SDK.hpp"
#include "Client/Network/Packets/Packet.hpp"

ClientInstance* SDK::clientInstance = nullptr;
ScreenView* SDK::screenView = nullptr;
std::string SDK::TopScreen = "UnknownLayer";

std::shared_ptr<Packet> SDK::createPacket(int id) {

    static uintptr_t Address;

    if (Address == NULL) {
        Address = Memory::findSig("48 89 5C 24 10 48 89 74 24 18 57 48 83 EC 50 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 48 48 8B D9 48 89");
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
