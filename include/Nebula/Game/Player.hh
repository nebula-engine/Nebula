#ifndef NEBULA_PLAYER_HPP
#define NEBULA_PLAYER_HPP

namesapce neb {
namespace Game {
class Player {
public:
  
  /** @brief %Actor.
   * %Actor which the player controls
   */
  std::weak_ptr<neb::core::actor::Base>   actor_;
  
  
  
};
}
}

#endif
