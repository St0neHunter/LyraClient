#include "ItemStack.hpp"

bool ItemStack::isValid() {
    return item.get() != nullptr;
}

Item* ItemStack::getItem() {
    return item.get();
}

short ItemStack::getDamageValue() {
    if (item.get() == nullptr)
        return 0;

    using getDamageValueFunc = short(__fastcall*)(Item*, void*);
    static auto getDamageValue = reinterpret_cast<getDamageValueFunc>(Memory::findSig("48 89 5C 24 ? 57 48 83 EC ? 48 8B DA 48 85 D2"));
    return getDamageValue(this->item.get(), this->tag);
}

short ItemStack::getMaxDamage() {
    using getMaxDamageFunc = short(__fastcall*)(ItemStack*);
    static auto getMaxDamage = reinterpret_cast<getMaxDamageFunc>(Memory::findSig("48 83 EC 28 48 8B 41 08 33 D2 48 85 C0 74 08 48 39 10 0F 94 C1 EB 05 B9 01 00 00 00 84 C9 75 20"));
    return getMaxDamage(this);
}