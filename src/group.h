#pragma once

#include <list>

namespace sos {

/**
 * Group Participation Authority.
 *
 * Issues and revokes memberships, and coordinates between member participants.
 */
template <typename T> class group {
public:
  /**
   * A handle representing member participation lifecycle.
   *
   * Moving out of scope will forfeit membership and execution participation.
   *
   * NOTE: Consider implementing as an RAII wrapped list iterator
   */
  struct membership {};

  /**
   * Issue a membership token to an execution participant.
   */
  membership issue(T);

  /**
   * Revoke an execution participation token.
   */
  void revoke(membership m);

protected:
  std::list<T *> participants;
};

} // namespace sos
