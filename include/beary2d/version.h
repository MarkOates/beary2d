#ifndef __BEARY2D_VERSION_HEADER
#define __BEARY2D_VERSION_HEADER




#define PROGRAM_NAME beary2d
#define MAJOR_VERSION 0 
#define MINOR_VERSION 0
#define MACRO_VERSION 0
#define BUILD_COUNT 1 


#include <string>
#include <sstream>
std::string get_version_str()
{
	std::stringstream ss;
	ss << MAJOR_VERSION << "." << MINOR_VERSION << "." << MACRO_VERSION << " build " << BUILD_COUNT;
	return ss.str();
}



#endif

