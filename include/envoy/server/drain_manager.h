#pragma once

#include <functional>
#include <memory>

#include "envoy/network/drain_decision.h"

namespace Envoy {
namespace Server {

/**
 * Handles connection draining. This concept is used globally during hot restart / server draining
 * as well as on individual listeners when they are being dynamically removed.
 */
class DrainManager : public Network::DrainDecision {
public:
  /**
   * Invoked to begin the drain procedure. (Making drain close operations more likely).
   * @param completion supplies the completion that will be called when the drain sequence is
   *                   finished. The parameter is optional and can be an unassigned function.
   */
  virtual void startDrainSequence(std::function<void()> completion) PURE;

  /**
   * Invoked in the newly launched primary process to begin the parent shutdown sequence. At the end
   * of the sequence the previous primary process will be terminated.
   */
  virtual void startParentShutdownSequence() PURE;
};

typedef std::unique_ptr<DrainManager> DrainManagerPtr;

} // namespace Server
} // namespace Envoy
