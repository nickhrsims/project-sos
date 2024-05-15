#include "input/indirection.h"
#include "sos.h"

int main() {
  // ---------------------------------
  // Initialize
  // ---------------------------------

  sos::root::init({
      false,
      {"Example SOS App", 64, 64, 200, 200},
      {},
  });

  // ---------------------------------
  // Player Input Configuration
  // ---------------------------------

  // --- Player Data & Actions
  int p1_pos = 0;
  int p2_pos = 0;

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
        case control::report:
          spdlog::info("Player 1 :: {} | Player 2 :: {}", p1_pos, p2_pos);
          break;
        default:
          break;
        }
      });

  // ---------------------------------
  // Primary Simulation Loop
  // ---------------------------------

  sos::process::start([&](float) {
    p1_pos = action::is_value_pressed(player_1::down) -
             action::is_value_pressed(player_1::up);
    p2_pos = action::is_value_pressed(player_2::down) -
             action::is_value_pressed(player_2::up);
  });

  // ---------------------------------
  // Cleanup
  // ---------------------------------

  sos::root::quit();
  return EXIT_SUCCESS;
}
