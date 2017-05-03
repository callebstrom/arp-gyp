#ifndef MITMHANDLER_H
#define MITMHANDLER_H

#include "arpgyp.h"

class MitmHandler : public ArpGyp
{
	public:
		MitmHandler(std::string target1, std::string target2);
		~MitmHandler();
	private:
		void send(std::array<byte,4> src_p_addr, std::array<byte,4> dst_p_addr);
};

#endif
