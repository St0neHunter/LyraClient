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


GameModeAttackHook::GameModeAttackHook() : Hook("GameModeAttack", "48 8D 05 ? ? ? ? 48 89 01 48 89 51 08 48 C7 41 ? ? ? ? ? C7 41 ? ? ? ? ?") {}


void GameModeAttackHook::enableHook() {
    auto base = Memory::findSig(this->signature);
    int offset = *reinterpret_cast<int *>(base + 3);
    auto **vft = reinterpret_cast<uintptr_t **>(base + offset + 7);

    this->manualHook(vft[14], (void *) callback, (void **) &funcOriginal);
}
