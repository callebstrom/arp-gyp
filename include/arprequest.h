#ifndef ARPREQUEST_H
#define ARPREQUEST_H

#include "arppacket.h"

struct __attribute__((packed)) ArpRequest
{
	unsigned short hw_type = htons(0x0001);
	unsigned short p_type = htons(0x0800);
	byte hw_addr_len = 0x06;
	byte p_addr_len = 0x04;
	unsigned short op = htons(ARPOP_REQUEST);
	std::array<byte,6> src_hw_addr;
	std::array<byte,4> src_p_addr;
	std::array<byte,6> dst_hw_addr;
	std::array<byte,4> dst_p_addr;
};

#endif
