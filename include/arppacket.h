#ifndef ARPPACKET_H
#define ARPPACKET_H

#include <stdlib.h> 
#include <iostream>

typedef unsigned char byte;
typedef struct { 
	unsigned int nBytes;
	byte* bytes;
} byteArr;

struct arppacket
{
	byte * hwType = (byte*) 0x0001;
	byte * pType = (byte*) 0x0800;
	byte * hwAddrLen = (byte*) 0x06;
	byte * pAddrLen = (byte*) 0x04;
	byte * srcHwAddr = (byte*) malloc (6);
	byte * srcPAddr = (byte*) malloc (4);
	byte * dstHwAddr = (byte*) malloc (6);
	byte * dstPAddr = (byte*) malloc (4);
};

#endif
