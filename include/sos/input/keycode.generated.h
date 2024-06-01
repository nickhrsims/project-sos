#include <SDL2/SDL.h>

namespace sos::input::keyboard {
enum class keycode {
    key_a = SDLK_a,
    key_b = SDLK_b,
    key_c = SDLK_c,

    key_k = SDLK_k,
    key_m = SDLK_m,
    key_q = SDLK_q,

    key_z = SDLK_z,

    key_left  = SDLK_LEFT,
    key_right = SDLK_RIGHT,
    key_up    = SDLK_UP,
    key_down  = SDLK_DOWN,
};
}
