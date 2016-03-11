#ifndef MITMHANDLER_H
#define MITMHANDLER_H

#include "arpgyp.h"

class MitmHandler : public ArpGyp
{
	public:
		MitmHandler(std::string const& target1, std::string const& target2);
		~MitmHandler();
	private:
		void send(std::string const& sIpAddr);
};

#endif