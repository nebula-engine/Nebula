#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>

#include <neb/core/app/__base.hpp>
#include <neb/core/rand.hpp>

int random_index = 0;
unsigned int* randoms = 0;

#define LEN 10000

void myrand_read(std::string f, unsigned int s)
{
	auto app = neb::core::app::__base::global();
	
	f = app->share_dir_ + f;
	
	std::string line;
	std::ifstream ifs;
	ifs.open(f);

	if(!ifs.is_open())
	{
		std::cout << f << std::endl;
		abort();
	}
	for(unsigned int i = s; i < (s + LEN); i++)
	{
		getline(ifs, line);
		randoms[i] = atoi(line.c_str());
		std::cout << line << std::endl;
	}
}

static const char * myrand_files[2]  = {
	"media/random/0.txt",
	"media/random/1.txt"
};

unsigned int myrand()
{
	if(randoms == 0)
	{
		int num_files = sizeof(myrand_files) / sizeof(char*);
		randoms = new unsigned int[num_files * LEN];
		for(int i = 0; i < num_files; i++)
			myrand_read(myrand_files[i], i * LEN);
	}

	if(random_index < (2 * LEN)) return randoms[random_index++];
	
	return (::rand() % 10000);
}

