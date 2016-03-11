#ifndef ARPGYP_H
#define ARPGYP_H

#define ETH_FRAME_LEN 1518

#include <stdlib.h> 
#include <iostream>
#include <memory.h>
#include <netinet/in.h>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#include "arpreply.h"
#include "arprequest.h"

class ArpGyp 
{
	public:
		ArpGyp();
		~ArpGyp();
		void mitm();
		void flood();
		void dos();
	protected:
		byte* stringToMac(std::string const& s);
		byte* stringToIp(std::string const& s);
		int s;
};

#endif