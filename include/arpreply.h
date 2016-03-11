#ifndef ARPREPLY_H
#define ARPREPLY_H

#include "arppacket.h"

struct arpreply : public arppacket 
{
	byte* opCode = (byte*) 0x0002;
};

#endif

