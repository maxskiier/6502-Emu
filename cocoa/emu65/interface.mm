#import "../../headers/logic.hpp"

// static logic::ppu ppu;

struct ppuAPI
{
  void (*tick)();
  uint8_t* (*framebuffer)();
  void (*keyDown)(int);
};

static void tickImpl() {
    engine->cycle();
}

static uint8_t* framebufferImpl() {
    return ppu->fbPtrGetter();
}

static void keyDownImpl(int key) {
    engine.handleKey(key);
}


extern "C" ppuAPI getEngineApi() {
    return {
        tickImpl,
        framebufferImpl,
        keyDownImpl
    };
}
