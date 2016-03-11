#ifndef ARPREQUEST_H
#define ARPREQUEST_H

#include "arppacket.h"

struct arprequest : public arppacket
{
	byte* opCode = (byte*)0x0002;
};

#endif
