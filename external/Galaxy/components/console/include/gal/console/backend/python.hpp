#ifndef GAL_STD_TERMINAL_PYTHON_HPP
#define GAL_STD_TERMINAL_PYTHON_HPP

#include <boost/python.hpp>

#include <sstream>

#include <gal/console/base.hpp>

namespace bp = boost::python;


class PythonStdIoRedirect {
	public:
		//typedef boost::circular_buffer<::std::string> ContainerType;
		//typedef ::std::vector< ::std::string > ContainerType;
		typedef ::std::stringstream ContainerType;

		void Write( std::string const& str ) {
			
			m_outputs << str;
			
			//if (m_outputs.capacity()<100)
			//	m_outputs.resize(100);
			/*
			if(m_outputs.empty()) {
				m_outputs.push_back(str);
				return;
			}
			
			if(m_outputs.back().back() == '\n') {
				m_outputs.push_back(str);
				return;
			}*/
			
			
		}

		static std::string GetOutput()
		{
			std::string ret;
			
			ret =  m_outputs.str();
		
			
			m_outputs.clear();
			return ret;
		}
		static ::std::vector< ::std::string >		GetOutputContainer() {
			
			::std::vector< ::std::string > ret;

			std::string token;
			
			while(std::getline(m_outputs, token, '\n')) {
				 ret.push_back(token);
			}

			m_outputs.clear();
			return ret;
		}
	private:
		static ContainerType m_outputs; // must be static, otherwise output is missing
};



namespace gal { namespace console { namespace backend {


	class python: virtual public gal::console::base {
		public:
			python();

			virtual void		init();
			virtual void		eval(::std::string const & s);

		public:

			bp::object		main_module_;
			bp::object		main_namespace_;

	};



}}}

#endif

