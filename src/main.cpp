#include "../include/mitmhandler.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
	std::cout << "Sending payload..." << std::endl;
	std::string target1_s = "192.168.1.21", target2_s = "192.168.1.44";
	MitmHandler *mh = new MitmHandler(target1_s, target2_s);
	std::cout << "Payload sent :)" << std::endl;
	return 0;
}
