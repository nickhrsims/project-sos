#pragma once

#include <sos/input/indirection/data/dispatch_map.ipp>
#include <sos/input/keyboard.h>

namespace sos::input::indirection::__data__ {

/**
 * KeyboardEvent observer membership.
 *
 * Used to attach indirection system to existing event infrastructure.
 *
 * WARN: Do not utilize this as a dependency for static values that are not
 *       function-wrapped. (static initialization-order is undefined!)
 */
static inline input::keyboard::observer_group::membership keyboard_observer{
    keyboard::on_event([](const keyboard::event &lp_event) {
      input::keyboard::scancode scancode{lp_event.scancode};
      if (__data__::dispatch_map<keyboard::scancode>.contains(scancode)) {
        __data__::dispatch_map<keyboard::scancode>[scancode](scancode);
      }
    })};

// TODO: Account for multiple mice
// TODO: Adjust after mouse abstraction layer
// BUG: After latest refactor, will probably fire on both press and release!
//      This has not been tested, but should not be used until mouse abstraction
//      layer ensures discimination between button states!
// HACK: To avoid calls on both press & release, only call on
//       SDL_MOUSEBUTTONDOWN events!
/*
inline void handle_sdl_mousebutton_event(const SDL_MouseButtonEvent &p_event) {
  mouse button{static_cast<mouse>(p_event.button)};
  if (__data__::dispatch_map<mouse>.contains(button)) {
    __data__::dispatch_map<mouse>[button](button);
  }
}
*/

} // namespace sos::input::indirection::__data__
