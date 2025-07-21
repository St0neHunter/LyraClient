#include "GameModeAttack.hpp"
#include "../../../Event/Events/AttackEvent.hpp"
#include "../../../SDK/SDK.hpp"
#include "../../../Event/EventManager.hpp"

void GameModeAttackHook::callback(Gamemode *gamemode, Actor *actor) {
    if (SDK::clientInstance->getLocalPlayer() != nullptr) {
        if (SDK::clientInstance->getLocalPlayer() == gamemode->player) {
            AttackEvent event(actor);
            eventMgr.onAttack(event);
        }

    }
    funcOriginal(gamemode, actor);
}


GameModeAttackHook::GameModeAttackHook() : Hook("GameModeAttack", "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 55 41 ? 41 ? 41 ? 41 ? 48 8D ? ? ? ? ? ? 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? 45 0F ? ? 4C 8B ? 48 8B") {}


void GameModeAttackHook::enableHook() {
    // auto base = Memory::findSig(this->signature);
    // int offset = *reinterpret_cast<int *>(base + 3);
    // auto **vft = reinterpret_cast<uintptr_t **>(base + offset + 7);
    //
    // this->manualHook(vft[14], (void *) callback, (void **) &funcOriginal);
    static auto addr = Memory::findSig(this->signature);
    this->manualHook((void *) addr, (void *) callback, (void **) &funcOriginal);
}
