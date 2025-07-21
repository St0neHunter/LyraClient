#include "../Hook.hpp"
#include "../../../../Utils/Utils.hpp"

class FontDrawTransformedHook : public Hook {
private:

    static void
    FontDrawTransformedCallback(void *_this, void *screenContext, std::string &str, float x, float y, const MCCColor& color,
                                int angle, float s, bool centered, float maxWidth) {

        std::string txt("Lyra!");
        funcOriginal(_this, screenContext, txt, x, y, MCCColor(202, 3, 252), angle, s, centered, maxWidth);

    }

public:
    typedef void(__thiscall *FontDrawTransformedOriginal)(void *, void *, std::string &, float, float, MCCColor, int,
                                                          float, bool, float);

    static inline FontDrawTransformedOriginal funcOriginal = nullptr;

    FontDrawTransformedHook() : Hook("Font drawTransformed Hook",
                                     "48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 8D A8 48 FF") {}

    void enableHook() override {

        this->autoHook((void *) FontDrawTransformedCallback, (void **) &funcOriginal);

    }
};
