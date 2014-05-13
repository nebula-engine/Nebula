
#ifndef __GALAXY_FLAG_H__
#define __GALAXY_FLAG_H__

namespace gal {
	class flag {
		public:
			typedef unsigned long int flag_type;
			flag() {}
			void		set(flag_type fl)
			{
				f(f() | fl);
			}
			void		unset(flag_type fl)
			{
				f(f() & !fl);
			}
			void		toggle(flag_type fl)
			{
				f(f() ^ fl);
			}
			bool		all(flag_type fl)
			{
				//printf("%i %i\n",flag_,f);

				return ( ( f() & fl ) == fl );
			}
			bool		any(flag_type fl)
			{
				//printf("%i %i\n",flag_,f);

				return ( f() & fl );
			}
			flag_type	mask(flag_type fl)
			{
				return ( f() & fl );
			}
		private:
			virtual flag_type	f() = 0;
			virtual void		f(flag_type) = 0;
	};
}

#endif


