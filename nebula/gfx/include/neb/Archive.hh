#ifndef NEBULA_ARCHIVE_HPP
#define NEBULA_ARCHIVE_HPP

class ArchiveRead {
	public:
		template<class A> ArchiveRead&		operator&(A& rhs) {
			return operator<<(rhs);
		}
};

#endif

