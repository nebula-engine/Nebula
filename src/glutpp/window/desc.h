#ifndef __GRU_WINDOW_DESC_H__
#define __GRU_WINDOW_DESC_H__


namespace glutpp
{
	namespace window
	{
		struct raw
		{
			public:
				enum
				{
					title_length_max = 20
				};

				int	i_;

				int x_;
				int y_;
				int w_;
				int h_;
				char	title_[title_length_max];



		};
		class desc
		{
			public:
				desc(int, int, int, int, const char *);

				raw	raw_;		
		};
	}
}

#endif








