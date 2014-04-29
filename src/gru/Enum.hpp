#ifndef NEBULA_



static std::map<unsigned int, std::string>	map_int_string;
			static std::map<std::string, unsigned int>	map_string_int;

			static unsigned int		Convert(std::string str) {
				auto it = map_string_int.find(str);
				if(it == map_string_int.cend()) throw 0;
				return it->second;
			}
			static std::string		Convert(unsigned int i) {
				auto it = map_int_string.find(i);
				if(it == map_int_string.cend()) throw 0;
				return it->second;
			}

