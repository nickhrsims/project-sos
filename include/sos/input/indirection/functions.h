#pragma once

#include <sos/input/indirection/indirection_map.h>

namespace sos::input::indirection {

/**
 * Subscribe to values of a given type.
 */
template <typename value_type>
indirection_map<value_type>::membership
on_value(std::function<void(value_type)> callback);

/**
 * Reset the global input-value mappings.
 */
template <typename value_type> void reset();

/**
 * Query the state of a value.
 */
template <typename value_type> bool is_value_pressed(value_type value);

/**
 * Relate a value with a keyboard key.
 */
template <typename value_type>
void relate_value(value_type value, keyboard::scancode scancode);

/**
 * Relate a value with a mouse button.
 */
template <typename value_type>
void relate_value(value_type value, mouse button);

} // namespace sos::input::indirection

#include <sos/input/indirection/functions.ipp>
