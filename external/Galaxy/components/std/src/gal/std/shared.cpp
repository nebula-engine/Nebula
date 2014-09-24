#include <gal/itf/registry.hpp>
#include <gal/itf/shared.hpp>

gal::itf::shared::shared(): _M_index(-1) {
}
gal::itf::shared::~shared()
{
	std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
}
void    				        gal::itf::shared::__init() {
	std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
	registry_.reg(shared_from_this());
	assert(_M_index != -1);
}
void						gal::itf::shared::release()
{
}
gal::itf::hash_type				gal::itf::shared::hash_code() const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::type_index type(typeid(*this));

	std::cout << type.name() << std::endl;
	std::cout << type.hash_code() << std::endl;

	return type.hash_code();
}
std::string					gal::itf::shared::name() const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	std::type_index type(typeid(*this));

	std::cout << type.name() << std::endl;
	std::cout << type.hash_code() << std::endl;

	return type.name();
}




gal::itf::hash_type			gal::itf::shared::to_hash_code(std::string const & str)
{
	auto it = map_string_hash_.find(str);
	if(it == map_string_hash_.cend())
	{
		std::cout << std::setw(64) << str << std::endl;

		for(auto p : map_string_hash_)
		{
			std::cout << std::setw(64) << p.first << std::setw(64) << p.second << std::endl;
		}
		throw 0;
	}
	return it->second;
}
std::string const &			gal::itf::shared::to_string(gal::itf::hash_type const & hash)
{
	auto it = map_hash_string_.find(hash);
	if(it == map_hash_string_.cend())
	{
		std::cout << std::setw(128) << hash << std::endl;
		for(auto p : map_string_hash_)
		{
			std::cout << std::setw(64) << p.first << std::setw(64) << p.second << std::endl;
		}
		throw 0;
	}
	return it->second;
}
void					gal::itf::shared::register_type(std::type_index new_index)
{
	map_hash_string_[new_index.hash_code()] = new_index.name();
	map_string_hash_[new_index.name()] = new_index.hash_code();
}
gal::itf::index_type const &		gal::itf::shared::static_get_index(std::shared_ptr<gal::itf::shared> ptr)
{
	return ptr->_M_index;
}




gal::itf::registry					gal::itf::shared::registry_;

std::map< gal::itf::hash_type, std::string >		gal::itf::shared::map_hash_string_;
std::map< std::string, gal::itf::hash_type >		gal::itf::shared::map_string_hash_;


