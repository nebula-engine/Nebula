#ifndef __GLUTPP_ATTRIBUTE_H__
#define __GLUTPP_ATTRIBUTE_H__

namespace glutpp
{
	class attribute
	{
		public:
			attribute();
			void		init(window*,int,char const *);
			void		enable();
			void		disable();
			
			window *	window_;
			char const *	name_;
			GLuint		o_;
	};
}

#endif
