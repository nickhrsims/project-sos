// --- stdlib
#include <functional>
#include <unordered_map>
#include <vector>

// --- spdlog
#include <spdlog/spdlog.h>

// --- Harness
#include "harness.ipp"

// --- Types
enum class test_actions { alpha, bravo, charlie };

TEST_CASE("input action subscription mechanics", "[input]") {

  // --- Setup
  sos::input::test::setup();
  std::vector<sos::input::group<test_actions>::membership> subscriptions;

  // --- Relate actions to an input type
  sos::input::action(test_actions::alpha, sos::input::keyboard::key_a);
  sos::input::action(test_actions::bravo, sos::input::keyboard::key_b);
  sos::input::action(test_actions::charlie, sos::input::keyboard::key_c);

  // --- Testing Flags
  std::unordered_map<test_actions, bool> action_was_received;

  // --- Input Subscription

  auto event_action_subscription =
      sos::input::on<test_actions>([&](auto action) {
        switch (action) {
        case test_actions::alpha:
          action_was_received[test_actions::alpha] = true;
          break;
        case test_actions::bravo:
          action_was_received[test_actions::bravo] = true;
          break;
        case test_actions::charlie:
          action_was_received[test_actions::charlie] = true;
          break;
        default:
          break;
        }
      });

  SECTION("keyboard keys corrospond exclusively to their assigned action") {

    SECTION("a -- alpha") {
      sos::input::test::simulate_keyboard_key_press(
          sos::input::keyboard::key_a);
      sos::input::test::run_event_loop(5);
      REQUIRE(action_was_received[test_actions::alpha]);
      REQUIRE_FALSE(action_was_received[test_actions::bravo]);
      REQUIRE_FALSE(action_was_received[test_actions::charlie]);
    }

    SECTION("b -- bravo") {
      sos::input::test::simulate_keyboard_key_press(
          sos::input::keyboard::key_b);
      sos::input::test::run_event_loop(5);
      REQUIRE(action_was_received[test_actions::bravo]);
      REQUIRE_FALSE(action_was_received[test_actions::alpha]);
      REQUIRE_FALSE(action_was_received[test_actions::charlie]);
    }

    SECTION("c -- charlie") {
      sos::input::test::simulate_keyboard_key_press(
          sos::input::keyboard::key_c);
      sos::input::test::run_event_loop(5);
      REQUIRE(action_was_received[test_actions::charlie]);
      REQUIRE_FALSE(action_was_received[test_actions::bravo]);
      REQUIRE_FALSE(action_was_received[test_actions::alpha]);
    }
  }

  // --- Teardown
  sos::input::test::teardown();
}
