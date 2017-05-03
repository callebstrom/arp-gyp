#ifndef ARPREPLY_H
#define ARPREPLY_H

#include "arppacket.h"

struct __attribute__((packed)) ArpReply
{
	unsigned short hwType = 0x0001;
	unsigned short pType = 0x0800;
	byte hwAddrLen = 0x06;
	byte pAddrLen = 0x04;
	unsigned short op = htons(ARPOP_REPLY);
	byte srcHwAddr[6];
	byte srcPAddr[4];
	byte dstHwAddr[6];
	byte dstPAddr[4];
};

#endif
