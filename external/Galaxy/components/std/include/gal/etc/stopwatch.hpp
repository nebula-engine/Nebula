#ifndef GAL_ETC_STOPWATCH_HPP
#define GAL_ETC_STOPWATCH_HPP

namespace gal { namespace etc {

	class stopwatch {
		public:
			stopwatch() {}
			void		start(double t)
			{
				start_ = t;
			}
			void		stop(double t)
			{
				count_++;
				total_ += t - start_;
			}
			double		getAvg()
			{
				double ret = total_ / (double)count_;
				total_ = 0;
				count_ = 0;
				return ret;
			}
		private:
			double		start_;
			size_t		count_;
			double		total_;
	};
}}

#endif
