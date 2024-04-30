#include <unordered_map>

#include <spdlog/spdlog.h>

#include <catch2/catch_test_macros.hpp>

#include "SDL_scancode.h"
#include "input/keyboard.h"
#include "toolkit.h"

TEST_CASE("smoke test", "[keyboard]") {

  toolkit::setup();

  namespace keyboard = sos::input::keyboard;

  std::unordered_map<keyboard::keycode, bool> was_keycode_pressed;
  std::unordered_map<keyboard::scancode, bool> was_scancode_pressed;

  auto const observation = keyboard::on_event([&](keyboard::event event) {
    was_scancode_pressed[event.scancode] = true;
    was_keycode_pressed[event.keycode] = true;
  });

  toolkit::send_keydown_event(keyboard::scancode::scancode_a,
                              keyboard::keycode::key_a);
  toolkit::send_keydown_event(keyboard::scancode::scancode_b,
                              keyboard::keycode::key_b);
  toolkit::send_keydown_event(keyboard::scancode::scancode_c,
                              keyboard::keycode::key_c);

  SDL_Event sdl_event;

  while (SDL_PollEvent(&sdl_event)) {
    if (sdl_event.type == SDL_KEYDOWN) {
      keyboard::handle_event(sdl_event.key);
    }
  }

  REQUIRE(was_scancode_pressed[keyboard::scancode::scancode_a]);
  REQUIRE(was_scancode_pressed[keyboard::scancode::scancode_b]);
  REQUIRE(was_scancode_pressed[keyboard::scancode::scancode_c]);

  REQUIRE(was_keycode_pressed[keyboard::keycode::key_a]);
  REQUIRE(was_keycode_pressed[keyboard::keycode::key_b]);
  REQUIRE(was_keycode_pressed[keyboard::keycode::key_c]);

  toolkit::teardown();
}
