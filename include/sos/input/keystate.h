#include <SDL2/SDL.h>
namespace sos::input::keyboard {
enum class keystate {
  pressed = SDL_PRESSED,
  released = SDL_RELEASED,
};
}
