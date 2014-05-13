#ifndef __GRU_WINDOW_DESC_H__
#define __GRU_WINDOW_DESC_H__


namespace Neb {
	namespace window {
		struct raw {
			public:
				raw();
				
				enum {
					title_length_max = 20
				};

				

		};
		class desc {
			public:
				desc(int, int, int, int, const char *);

				raw	raw_;		
		};
	}
}

#endif








