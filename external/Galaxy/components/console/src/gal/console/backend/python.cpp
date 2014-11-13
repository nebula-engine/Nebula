

#include <gal/console/backend/python.hpp>

PythonStdIoRedirect::ContainerType PythonStdIoRedirect::m_outputs;


gal::console::backend::python::python() {
	prompt_end_ = ">>> ";
}
void			gal::console::backend::python::init() {
	// startup
	Py_Initialize();


	main_module_ = bp::import("__main__");
	main_namespace_ = main_module_.attr("__dict__");


	// expose redirect class
	main_namespace_["PythonStdIoRedirect"] = bp::class_<PythonStdIoRedirect>("PythonStdIoRedirect", bp::init<>())
		.def("write", &PythonStdIoRedirect::Write);

	// set redirect
	PythonStdIoRedirect python_stdio_redirector;
	bp::import("sys").attr("stderr") = python_stdio_redirector;
	bp::import("sys").attr("stdout") = python_stdio_redirector;

}
void			gal::console::backend::python::eval(::std::string const & s) {

	bp::object o;
	try
	{
		o = bp::eval(s.c_str(), main_namespace_);

		if(!o.is_none()) {
			//std::cout << "not none\n";
			main_namespace_["temp_obj"] = o;
			bp::exec("print temp_obj", main_namespace_);
		}

	}
	catch(bp::error_already_set const &)
	{

		PyErr_Clear();

		//PyErr_Print();
		//std::cout << "exec\n";

		try
		{
			o = bp::exec(s.c_str(), main_namespace_, bp::object());
		}
		catch(bp::error_already_set const &)
		{
			PyErr_Print();
		}

	}

	auto output = PythonStdIoRedirect::GetOutputContainer();

	for(auto it = output.begin(); it != output.end(); ++it) {
		write_line(*it);//.insert(lines_.end(), output.begin(), output.end());
	}
}


