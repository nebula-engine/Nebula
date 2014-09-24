#ifndef GAL_ETC_SLOTS_HPP
#define GAL_ETC_SLOTS_HPP

#include <memory>

namespace gal { namespace etc {

	class slots: public std::enable_shared_from_this<slots> {

		public:

			class ticket {
				public:
					friend class slots;
					~ticket()
					{
						auto slots = slots_.lock();
						if(slots)
						{
							slots->release(index_);
						}
					}
					unsigned int const &		operator[](size_t i) const
					{
						assert(!slots_.expired());
						return index_[i];
					}

				private:
					std::vector<unsigned int>	index_;
					std::weak_ptr<slots>		slots_;
			};

		public:
			slots() {}
			slots(size_t n) {
				alloc(n);
			}
			void				alloc(unsigned int n) {
				assert(n > 0);

				tickets_ = std::vector< std::weak_ptr<ticket> >(n);
				s_ = std::vector<unsigned int>(n, 0);
			}
			std::shared_ptr<ticket>		reg(size_t n) {
				assert(n > 0);
				assert(count() >= n);

				auto t = std::make_shared<ticket>();
				
				t->slots_ = shared_from_this();
				
				tickets_.push_back(t);

				for(size_t i = 0; i < s_.size(); i++)
				{
					if(s_[i] == 0) {
						s_[i] = 1;
						t->index_.push_back(i);
	
						if(t->index_.size() == n) break;
					}
				}
				
				return t;
			}
			void				release(std::vector<unsigned int> indices) {
				for(size_t i = 0; i < indices.size(); i++)
				{
					assert(s_[indices[i]] == 1);
					s_[indices[i]] = 0;
				}
			}
			size_t				count() {
				size_t c = 0;
				for(size_t i = 0; i < s_.size(); i++)
				{
					if(s_[i] == 0) c++;
				}
				return c;
			}
		private:

			std::vector<std::weak_ptr<ticket> >	tickets_;
			std::vector<unsigned int>		s_;
	};

}}

#endif

