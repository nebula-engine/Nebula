#include <fstream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <gal/log/log.hpp>

#include <Nebula/util/debug.hpp>


int main(int ac, char** av) {

	if(ac == 2) {

		std::ofstream f;
		f.open("debug_options.xml", std::ofstream::out | std::ofstream::trunc);

		boost::archive::xml_oarchive ar(f);

		neb::util::debug_options o;

		o.map_["debug"]		= debug;
		o.map_["info"]		= info;
		o.map_["warning"]	= warning;
		o.map_["error"]		= error;
		o.map_["critical"]	= critical;

		o.serialize(ar,0);


	} else {



		std::ifstream f;
		f.open("debug_options.xml", std::ofstream::in);

		boost::archive::xml_iarchive ar(f);

		neb::util::debug_options o;

		o.serialize(ar,0);

		for(auto p : o.map_) {
			std::cout << p.first << " " << p.second << std::endl;
		}
	}

}

