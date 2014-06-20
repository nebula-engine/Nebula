#include <Nebula/config.hh>
#include <Nebula/app/__gfx_glsl.hpp>
#include <Nebula/gfx/glsl/program.hh>

void	neb::app::__gfx_glsl::create_programs() {

	printf("%s\n", __PRETTY_FUNCTION__);

	std::shared_ptr<neb::glsl::program> p;

	// text
	{
		p.reset(new neb::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/text/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/text/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();

		p->add_attrib(neb::attrib_name::e::COOR, "coord", 0);

		//p->add_uniform("COLOR","font_color");
		//p->add_uniform("TEX","tex");

		p->scanUniforms();
		p->locate();

		programs_[neb::program_name::TEXT] = p;
	}
	// quad




	// light
	{
		p.reset(new neb::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/light/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/light/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();

		//p->add_uniform(neb::uniform_name::e::IMAGE, "image");

		p->add_attrib(neb::attrib_name::e::POSITION, "position", 1);
		p->add_attrib(neb::attrib_name::e::NORMAL, "normal", 2);

		//p->add_attrib(neb::attrib_name::e::TEXCOOR, "texcoor");

		p->scanUniforms();
		p->locate();

		programs_[neb::program_name::LIGHT] = p;


	}

	//light and image
	{
		p.reset(new neb::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/image/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/image/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();



		p->add_attrib(neb::attrib_name::e::POSITION, "position", 1);
		p->add_attrib(neb::attrib_name::e::NORMAL, "normal", 2);
		p->add_attrib(neb::attrib_name::e::TEXCOOR, "texcoor", 3);

		/*
		   p->add_uniform(neb::uniform_name::e::IMAGE, "image");


		   p->add_uniform(neb::uniform_name::e::LIGHT_COUNT,"light_count");
		   p->add_uniform(neb::uniform_name::e::MODEL,"model");
		   p->add_uniform(neb::uniform_name::e::VIEW,"view");
		   p->add_uniform(neb::uniform_name::e::PROJ,"proj");

		   p->add_uniform(neb::uniform_name::e::FRONT_AMBIENT,"front.ambient");
		   p->add_uniform(neb::uniform_name::e::FRONT_DIFFUSE,"front.diffuse");
		   p->add_uniform(neb::uniform_name::e::FRONT_SPECULAR,"front.specular");
		   p->add_uniform(neb::uniform_name::e::FRONT_EMISSION,"front.emission");
		   p->add_uniform(neb::uniform_name::e::FRONT_SHININESS,"front.shininess");

		   p->add_uniform(neb::uniform_name::e::LIGHT_POSITION, "lights", "position");
		   p->add_uniform(neb::uniform_name::e::LIGHT_AMBIENT, "lights","ambient");
		   p->add_uniform(neb::uniform_name::e::LIGHT_DIFFUSE, "lights","diffuse");
		   p->add_uniform(neb::uniform_name::e::LIGHT_SPECULAR, "lights","specular");
		   p->add_uniform(neb::uniform_name::e::LIGHT_SPOT_DIRECTION, "lights","spot_direction");
		   p->add_uniform(neb::uniform_name::e::LIGHT_SPOT_CUTOFF, "lights","spot_cutoff");
		   p->add_uniform(neb::uniform_name::e::LIGHT_SPOT_EXPONENT, "lights","spot_exponent");
		   p->add_uniform(neb::uniform_name::e::LIGHT_SPOT_LIGHT_COS_CUTOFF, "lights","spot_light_cos_cutoff");
		   p->add_uniform(neb::uniform_name::e::LIGHT_ATTEN_CONST, "lights","atten_const");
		   p->add_uniform(neb::uniform_name::e::LIGHT_ATTEN_LINEAR, "lights","atten_linear");
		   p->add_uniform(neb::uniform_name::e::LIGHT_ATTEN_QUAD, "lights","atten_quad");
		 */
		p->scanUniforms();
		p->locate();

		programs_[neb::program_name::IMAGE] = p;
	}

}
std::shared_ptr<neb::glsl::program> neb::app::__gfx_glsl::use_program(neb::program_name::e name){
	auto p = get_program(name);

	p->use();

	current_ = p;

	return p;
}
std::shared_ptr<neb::glsl::program> neb::app::__gfx_glsl::current_program(){
	assert(current_);

	return current_;
}
std::shared_ptr<neb::glsl::program> neb::app::__gfx_glsl::get_program(neb::program_name::e name){
	auto it = programs_.find(name);

	if(it == programs_.end())
	{
		printf("program '%i' not found\n", name);
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}



