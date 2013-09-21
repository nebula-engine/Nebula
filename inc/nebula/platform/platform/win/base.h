#include <memory>
#include <map>

#include <Platform/Platform/PL_PL_Platform.h>

using namespace std;

namespace Framework {
	class App;
};
namespace Platform {
	class Window;
};



namespace Platform
{
	namespace Platform
	{
		namespace Win
		{
			/// %Platform
			class Platform: public PL_PL_Platform
			{
			public:
				/// Ctor
										Platform();
				/// Dtor
										~Platform();
		
		
		
				/// Initialize
				void					VInit(Void*);
				/// Shutdown
				void					VShutdown(Void*);
				/// Update
				void					VUpdate(Void*);
				/// Window
				void					VCreateWindow( PL_WI_Window*& window );
		
			private:
		
		
			};
		}
	}
}




