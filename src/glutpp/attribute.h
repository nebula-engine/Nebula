#ifndef __GLUTPP_ATTRIBUTE_H__
#define __GLUTPP_ATTRIBUTE_H__

namespace glutpp
{
	class window;
	class attribute
	{
		public:
			attribute();
			void		init(std::shared_ptr<scene>,int,char const *);
			void		enable();
			void		disable();
			
			window *	window_;
			char const *	name_;
			GLuint		o_;
	};
}

#endif
