/// %Content
/**
* TODO:
* - Console
*     - A command prompt that appears in-game and allows for use of text commands.
*     - Like cheat code systems in many pc games.
* - Vehicles
*     - Aricraft
*         - Physics
*         - AI
*     - Watercraft
*     - Aggregate vehicles
*         - tanks with turrents
* 
* 
* 
*/
namespace Content {
	/// %Scene
	/**
	* Scenes are divided based on clustering of non-static actors.
	* Several data clustering algorithms to investigate.
	* 
	*/
	namespace Scene
	{
		/// %Admin
		namespace Admin {}

		/// %Physics
		namespace Physics {
			/// %PhysX Implementation
			namespace PhysX {}
		}

		/// %Renderer
		namespace Renderer {}
	}
	
	/// %AI
	/**
	* - Path finding
	* - Automatic path generation
	* - Target finding, stalking, chacing
	* - decision making
	* - Evolutionary Algorithms
	*     - Could be method of AI.
	*     - Could create "peripheral devices" which connect to the generic outputs of the assembly language. Algorithm would then evolve to use the device no matter what the device is. This allows for game-specific customization of behavior using a generic assembly language by hard-coding object which can be controlled by the algorithm.
	* - Neural Networks
	* - Fuzzy Logic 
	* 
	*/
	namespace AI
	{}

	/// actors
	namespace Actor {

		/// %Actor %Admin
		/**
		* - receive and process messages
		* - store pose
		* - administration...
		*/
		namespace Admin {}

		/// %Actor %Physics
		/**
		* - move the actor
		*/
		namespace Physics {
			/// %PhysX Implementation
			namespace PhysX {}
		}

		/// %Actor %Renderer
		namespace Renderer {}
	}

	/// rigid shapes
	namespace Shape {

		/// %Admin
		namespace Admin {}

		/// %Physics
		/**
		* - store
		*     - density
		*     - material
		*/
		namespace Physics {
			/// %PhysX Implementation
			namespace PhysX {}
		}

		/// %Renderer
		namespace Renderer {}
	}
};

