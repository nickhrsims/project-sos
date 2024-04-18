#pragma once

#include <concepts>

namespace sos::process {

/**
 * Start the primary frame/event processing loop.
 * \sa stop
 */
template <typename Fn>
  requires std::invocable<Fn &, const float>
void start(Fn processing_function);

/**
 * Stop a previously started frame/event processing loop.
 * Does nothing if not started.
 *
 * \sa start
 */
void stop();

} // namespace sos::process

#include "process.ipp"
