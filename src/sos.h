#pragma once
#include "process.h"
#include "video/display.h"
#include "video/renderer.h"

namespace sos::root {

/**
 * TODO:
 */
struct config {
  bool headless;
  video::display::config display;
  video::renderer::config renderer;
};

/**
 * TODO:
 */
void init(const config &);

/**
 * TODO:
 */
void init();

/**
 * TODO:
 */
void quit();

} // namespace sos::root
