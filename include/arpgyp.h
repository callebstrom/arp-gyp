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
#include <arpa/inet.h>
#include <sstream>
#include <iomanip>
#include <sys/ioctl.h>

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

		static std::array<byte,4> stringToMac(std::string const& s);
		static void stringToIp(const std::string &src, std::array<byte,4> &dst);
		static std::string ByteToHex(unsigned char inchar);
		static int GetIfIndex(std::string iface_s);
		static int s;
};

#endif
