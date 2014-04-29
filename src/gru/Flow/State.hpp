#ifndef NEBULA_STATE_HPP
#define NEBULA_STATE_HPP

namespace Neb {
  namespace Flow {
    /** @brief State.
     * Construction and Destruction alters behavior of rendering and stepping, producing
     * a temporary change in the state of the program. */
    class State {
      public:
        virtual ~State() {}
    };
  }
}

#endif

