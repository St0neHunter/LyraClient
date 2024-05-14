#pragma once

#include <array>
#include "../Hook.hpp"

class KeyHook : public Hook
{
private:
    static inline std::array<bool, 256> keys;
    static void keyCallback(int key, bool state);

public:
    typedef void(__thiscall* KeyOriginal)(uint64_t keyId, bool held);
    static inline KeyOriginal func_original = 0;

    KeyHook();
    void enableHook() override;
};
