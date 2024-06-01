#include "SDL2/SDL.h"
#include "SDL_scancode.h"
namespace sos::input::keyboard {
enum class scancode {
    scancode_a = SDL_SCANCODE_A,
    scancode_b = SDL_SCANCODE_B,
    scancode_c = SDL_SCANCODE_C,
    scancode_z = SDL_SCANCODE_Z,
    scancode_k = SDL_SCANCODE_K,
    scancode_m = SDL_SCANCODE_M,
    scancode_q = SDL_SCANCODE_Q,

    scancode_left  = SDL_SCANCODE_LEFT,
    scancode_right = SDL_SCANCODE_RIGHT,
    scancode_up    = SDL_SCANCODE_UP,
    scancode_down  = SDL_SCANCODE_DOWN,

    scancode_lshift = SDL_SCANCODE_LSHIFT,
};
}
