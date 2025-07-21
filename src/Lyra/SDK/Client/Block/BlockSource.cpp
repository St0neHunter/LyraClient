#include "BlockSource.hpp"


Block *BlockSource::getBlock(const Vec3 &bp) {
    return Memory::CallVFunc<2, Block *>(this, bp);
}

Biome *BlockSource::getBiome(const Vec3 &bp) {

    static uintptr_t sig;

    if (sig == NULL) sig = Memory::findSig("48 89 5C 24 18 57 48 83 EC 60 48 8B DA 48 8B F9 48 8B");

    using efunc = Biome *(__cdecl *)(BlockSource *, const Vec3 &);
    auto func = reinterpret_cast<efunc>(sig);
    return func(this, bp);
}