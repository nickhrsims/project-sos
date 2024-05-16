#include <catch2/catch_test_macros.hpp>

#include <sos/input/indirection.h>

#include "toolkit.h"

TEST_CASE("indirection events can be subscribed to", "[input/indirection]") {
  toolkit::setup();

  // --- Type Aliasing
  namespace keyboard = sos::input::keyboard;
  namespace indirection = sos::input::indirection;

  // --- Custom indirection-value type
  enum class action {
    alpha,
    bravo,
    charlie,
  };

  // --- Test flags to check for
  std::unordered_map<action, bool> was_action_pressed;

  // --- Register an indirection-value observer
  auto const observation = indirection::on_value<action>(
      [&](action lp_action) { was_action_pressed[lp_action] = true; });

  // --- Map custom values to keyboard inputs
  indirection::relate_value(action::alpha, keyboard::scancode::scancode_a);
  indirection::relate_value(action::bravo, keyboard::scancode::scancode_b);
  indirection::relate_value(action::charlie, keyboard::scancode::scancode_c);

  // --- Send simulated keyboard inputs
  toolkit::send_keydown_event(keyboard::scancode::scancode_a,
                              keyboard::keycode::key_a);
  toolkit::send_keydown_event(keyboard::scancode::scancode_b,
                              keyboard::keycode::key_b);
  toolkit::send_keydown_event(keyboard::scancode::scancode_c,
                              keyboard::keycode::key_c);

  // --- Test that flags are false before processing events.
  REQUIRE_FALSE(was_action_pressed[action::alpha]);
  REQUIRE_FALSE(was_action_pressed[action::bravo]);
  REQUIRE_FALSE(was_action_pressed[action::charlie]);

  // --- Process normal keyboard events,
  //     which should dispatch to keyboard-specific indirection handlers.
  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event)) {
    if (sdl_event.type == SDL_KEYDOWN) {
      keyboard::handle_event(sdl_event.key);
    }
  }

  // --- Test that flags are true after processing events.
  REQUIRE(was_action_pressed[action::alpha]);
  REQUIRE(was_action_pressed[action::bravo]);
  REQUIRE(was_action_pressed[action::charlie]);

  toolkit::teardown();
}
