#pragma once

#include <string>

#include <SDL_events.h>

// TODO: Tests
// TODO: Docs

namespace sos {
class app;
}

namespace sos::video {
class display {
public:
  friend class sos::app;
  friend class renderer;

  struct config {
    std::string window_title;
    unsigned int window_x;
    unsigned int window_y;
    unsigned int window_width;
    unsigned int window_height;
  };

  ~display();

  static display &get();

  void initialize(const config &config);

  void terminate();

  void handle_event(const SDL_Event &event);

private:
  SDL_Window *sdl_window;

  display();
  display(display &) = delete;
  display(display &&) = delete;
  display &operator=(const display &) = delete;
};
} // namespace sos::video
