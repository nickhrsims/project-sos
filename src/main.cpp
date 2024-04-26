#include <cstdlib>
int main() {
  /*
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

    // --- Relate actions to an input type
    sos::input::action(control::quit, sos::input::keyboard::key_q);
    sos::input::action(control::report, sos::input::mouse::button_left);
    sos::input::action(player_1::up, sos::input::keyboard::key_a);
    sos::input::action(player_1::down, sos::input::keyboard::key_z);
    sos::input::action(player_2::up, sos::input::keyboard::key_k);
    sos::input::action(player_2::down, sos::input::keyboard::key_m);

    // --- Input Subscription
    [[maybe_unused]] auto player_any_input_subscription =
        sos::input::on<control>([&](auto action) {
          switch (action) {
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
      using sos::input::action;
      p1_pos = action(player_1::down) - action(player_1::up);
      p2_pos = action(player_2::down) - action(player_2::up);
    });

    // ---------------------------------
    // Cleanup
    // ---------------------------------

    sos::root::quit();
  */
  return EXIT_SUCCESS;
}
