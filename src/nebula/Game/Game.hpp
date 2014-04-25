#ifndef NEBULA_GAME_HPP
#define NEBULA_GAME_HPP


namespace neb {
  namespace Game {
    class Game {
      public:
        /** @brief %Scene.
         * Currently a game is fully defined by a single scene.
         * The game will load a scene from an Xml file.
         */
        std::weak_ptr<neb::scene>                       scene_;
        
        
        std::set<std::shared_ptr<neb::Game::Trigger> >  triggers_;
        
        
        gal::map<std::shared_ptr<neb::Game::Player> >   players_;
      
    };
  }
}


#endif

