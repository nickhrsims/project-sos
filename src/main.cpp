#include "sos.h"
#include <cstdlib>

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

  // --- Players and their actions
  enum class player_any { none, quit, report };
  enum class player_1 { none, up, down };
  enum class player_2 { none, up, down };

  // --- Configure "null" actions
  // (not necessary if first action is a null action)
  sos::input::reset<player_any>(player_any::none);
  sos::input::reset<player_1>(player_1::none);
  sos::input::reset<player_2>(player_2::none);

  // --- Relate actions to an input type
  sos::input::action(player_any::quit, sos::input::keyboard::key_q);
  sos::input::action(player_any::report, sos::input::mouse::button_left);
  sos::input::action(player_1::up, sos::input::keyboard::key_a);
  sos::input::action(player_1::down, sos::input::keyboard::key_z);
  sos::input::action(player_2::up, sos::input::keyboard::key_k);
  sos::input::action(player_2::down, sos::input::keyboard::key_m);

  // ---------------------------------
  // Primary Simulation Loop
  // ---------------------------------

  sos::process::start([](float) {
    using sos::input::action;

    int player_1_pos = action(player_1::down) - action(player_1::up);
    int player_2_pos = action(player_2::down) - action(player_2::up);

    if (action(player_any::report)) {
      spdlog::info("Player 1 :: {} | Player 2 :: {}", player_1_pos,
                   player_2_pos);
    }

    if (action(player_any::quit)) {
      sos::process::stop();
    }
  });

  // ---------------------------------
  // Cleanup
  // ---------------------------------

  sos::root::quit();

  return EXIT_SUCCESS;
}
