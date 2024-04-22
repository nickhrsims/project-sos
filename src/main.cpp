#include "sos.h"
#include <cstdlib>

// NOTE: Until hashable is defined, will cause panic
struct callback_action : std::function<void()> {
  static callback_action up;
  static callback_action down;
};
callback_action callback_action::up{[]() { spdlog::info("Got UP!"); }};
callback_action callback_action::down([]() { spdlog::info("Got DOWN!"); });

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

  enum class player_any { quit, report };
  enum class player_1 { up, down };
  enum class player_2 { up, down };

  // --- Relate actions to an input type
  sos::input::action(player_any::quit, sos::input::keyboard::key_q);
  sos::input::action(player_any::report, sos::input::mouse::button_left);
  sos::input::action(player_1::up, sos::input::keyboard::key_a);
  sos::input::action(player_1::down, sos::input::keyboard::key_z);
  sos::input::action(player_2::up, sos::input::keyboard::key_k);
  sos::input::action(player_2::down, sos::input::keyboard::key_m);

  // --- Input Subscription
  [[maybe_unused]] auto player_any_input_subscription =
      sos::input::on<player_any>([&](auto action) {
        switch (action) {
        case player_any::quit:
          sos::process::stop();
          break;
        case player_any::report:
          spdlog::info("Player 1 :: {} | Player 2 :: {}", p1_pos, p2_pos);
          break;
        default:
          break;
        }
      });

  [[maybe_unused]] auto callback_action_input_subscription =
      sos::input::on<callback_action>([](const auto &action) { action(); });

  // ---------------------------------
  // Primary Simulation Loop
  // ---------------------------------

  sos::process::start([&](float) {
    using sos::input::action;
    p1_pos = action(player_1::down) - action(player_1::up);
    p2_pos = action(player_2::down) - action(player_2::up);
  });

  // ---------------------------------
  // Cleanup
  // ---------------------------------

  sos::root::quit();

  return EXIT_SUCCESS;
}
