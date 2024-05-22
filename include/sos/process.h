#pragma once

#include <concepts>
#include <cstdint>

namespace sos::process {

/**
 * Start the primary frame/event processing loop.
 * \sa stop
 */
template <typename Fn>
    requires std::invocable<Fn&, const float>
void start(Fn processing_function, uint8_t frames_per_second = 60);

/**
 * Stop a previously started frame/event processing loop.
 * Does nothing if not started.
 *
 * \sa start
 */
inline void stop();

} // namespace sos::process

#include <sos/process.ipp>
