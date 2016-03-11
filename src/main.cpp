#include "../include/mitmhandler.h"

int main(int argc, char** argv)
{
	MitmHandler *mh = new MitmHandler("192.168.0.1", "192.168.0.44");	
	return 0;
}