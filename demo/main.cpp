#include <sos/input/indirection.h>
#include <sos/sos.h>

#include "rect.h"
#include "vector2.h"

int main() {
  // ---------------------------------
  // Initialize
  // ---------------------------------

  sos::root::init({false, {"Example SOS App", 64, 64, 200, 200}});

  // ---------------------------------
  // Player Input Configuration
  // ---------------------------------

  // --- Player Data & Actions

  struct player {
    sos::demo::rect rect;
    sos::demo::vector2 vel;
  };

  enum class control { quit, report };
  enum class player_1 { up, down };
  enum class player_2 { up, down };

  using scancode = sos::input::keyboard::scancode;
  namespace action = sos::input::indirection;

  // --- Relate actions to an input type
  action::relate_value(control::quit, scancode::scancode_q);
  action::relate_value(control::report, scancode::scancode_c);
  action::relate_value(player_1::up, scancode::scancode_a);
  action::relate_value(player_1::down, scancode::scancode_z);
  action::relate_value(player_2::up, scancode::scancode_k);
  action::relate_value(player_2::down, scancode::scancode_m);

  // --- Input Subscription
  [[maybe_unused]] auto player_any_input_subscription =
      action::on_value<control>([&](auto action_value) {
        switch (action_value) {
        case control::quit:
          sos::process::stop();
          break;
        default:
          break;
        }
      });

  // ---------------------------------
  // Primary Simulation Loop
  // ---------------------------------

  player p1{
      .rect{8, 8, 16, 16},
      .vel{0, 0},
  };
  player p2;

  sos::process::start([&](float delta) {
    namespace gfx = sos::video::renderer;

    struct color {
      int r;
      int g;
      int b;
      int a;
    };

    static color black{0, 0, 0, 255};
    static color white{255, 255, 255, 255};

    // Input
    p1.vel.y = (action::is_value_pressed(player_1::down) -
                action::is_value_pressed(player_1::up)) *
               200;
    p2.vel.y = (action::is_value_pressed(player_2::down) -
                action::is_value_pressed(player_2::up)) *
               200;

    p1.rect.y += std::round(p1.vel.y * delta);

    gfx::set_color(black);
    gfx::clear();
    gfx::set_color(white);

    gfx::draw(p1.rect);

    gfx::show();
  });

  // ---------------------------------
  // Cleanup
  // ---------------------------------

  sos::root::quit();
  return EXIT_SUCCESS;
}
