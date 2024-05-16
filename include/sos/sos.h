#pragma once
#include <sos/process.h>
#include <sos/video/renderer.h>
#include <sos/video/window.h>

namespace sos::root {

/**
 * TODO:
 */
struct config {
  bool headless;
  video::window::config window;
};

/**
 * TODO:
 */
inline void init(const config &);

/**
 * TODO:
 */
inline void init();

/**
 * TODO:
 */
inline void quit();

} // namespace sos::root

#include <sos/sos.ipp>
