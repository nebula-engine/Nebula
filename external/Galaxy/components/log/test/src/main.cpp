<<<<<<< HEAD
#include <gal/log/log.hpp>

int main(int ac, char** av) {
	
	LOG(lg, info, info) << 1 << 2 << 3;
=======
#include <map>
#include <cstring>
#include <cassert>

#include <gal/log/log.hpp>

std::map<std::string, severity_level> sl_map;


//#define LOG2(l, c, s) static const char * cname = auto_channel_name(__PRETTY_FUNCTION__); LOG(l,c,s) << strings[s] << cname

#define LOG_PRE \
static const char * cname = auto_channel_name(__PRETTY_FUNCTION__);\
static const char * fmtcname = format_cname(cname);\
static const char * file = proc_file(__FILE__);\
static const char * fileline = proc_fileline(file, __LINE__);\
severity_level c = auto_sev(cname);

#define LOG2(l, c, s) LOG(l,c,s) << cname


#define LOG3(l, s) LOG(l,c,s)

#define LOG4(l, s) LOG(l,c,s) << strings[s] << fileline << fmtcname

#define LOG_FUNC(lg, c, sev) LOG(lg, c, sev) << __PRETTY_FUNCTION__

#define LOG_FUNC3(lg, sev) LOG3(lg, sev) << __PRETTY_FUNCTION__

#define LOG_FUNC4(lg, sev) LOG4(lg, sev) << __PRETTY_FUNCTION__

//#define LOG3(lg, sev) LOG3(lg, sev) << __PRETTY_FUNCTION__

static const char* strings[] = {
	"[debug]    ",
	"[info]     ",
	"[warning]  ",
	"[error]    ",
	"[critical] "
};

char const *	format_cname(char const * cname)
{
	size_t l = 16;

	char * buf1 = new char[strlen(cname) + l + 4];
	sprintf(buf1, "%s:", cname);

	char * buf2 = new char[strlen(cname) + l + 4];
	sprintf(buf2, "%-16s", buf1);

	return buf2;
}
char const *	auto_channel_name(char const * sig)
{
	LOG_FUNC(lg, debug, debug);

	char * s = new char[strlen(sig) + 1];
	
	memcpy(s, sig, strlen(sig)+1);
	
	char * c = strchr(s, '(');
	
	if(c == NULL) return "";
	
	*c = 0;
	c--;

	char * e = c;

	while(*c != ' ')
	{
		//std::cout << "*c = '" << (unsigned char)*c << "'" << std::endl;
		c--;
	}
	c++;

	while(*e != ':')
	{
		//std::cout << "*e = '" << (unsigned char)*e << "'" << std::endl;
		e--;
	}
	e--;

	*e = 0;
	
	char * ret = new char[strlen(c) + 1];

	memcpy(ret, c, strlen(c) + 1);

	delete[] s;
	
	return ret;
}

char const * 	proc_file(char const * file)
{
	LOG_FUNC(lg, debug, debug);
	
	static const char * filepre[] = {
		"/scratch/Programming/Nebula/external/Galaxy/components/log/test/src/"
	};
	
	
	char * ret = 0;
	
	for(char const ** s = filepre; s < (filepre + sizeof(filepre)/sizeof(char*)); s++)
	{
		if(strncmp(file, *s, strlen(*s)) == 0)
		{
			file += strlen(*s);

			size_t l = strlen(file);
			
			ret = new char[l+1];

			strcpy(ret, file);

			break;
		}
	}

	if(ret == 0) return "fail!";

	return ret;
}
char const * 	proc_fileline(char const * file, int const line)
{
	LOG_FUNC(lg, debug, debug);
	
	
	char * buf = new char[strlen(file) + 32];
	sprintf(buf, "%s:%i:", file, line);

	char * buf2 = new char[strlen(file) + 32];
	sprintf(buf2, "%-32s", buf);

	return buf2;
}
severity_level	auto_sev(char const * cname)
{
	LOG_FUNC(lg, debug, debug);



	std::string const s(cname);

	auto it = sl_map.find(s);

	if(it != sl_map.end())
	{
		return it->second;
	}
	else
	{
		abort();
		return debug;
	}
}

namespace ns1
{

	severity_level sl;

	void fun(int i)
	{

		LOG_PRE;
		//LOG_FUNC(lg, sl, debug);
		LOG_FUNC4(lg, debug);
		//std::cout << "0123456789abcdef0123456789abcdef" << std::endl;
		LOG4(lg, debug) << i;
	}
}

int main(int ac, char** av)
{

	sl_map["ns1"] = debug;

	ns1::sl = debug;

	ns1::fun(0);

	//sl_map["ns1"] = info;

	ns1::fun(1);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	return 0;

}


