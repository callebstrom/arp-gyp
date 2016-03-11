#include "../include/arpgyp.h"

ArpGyp::ArpGyp() {
	this->s = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW); // Create a RAW socket
	if (s==-1) {
    	printf("Failed to create socket: %s", strerror(errno));
    	exit(1);
	}
}

ArpGyp::~ArpGyp() {

}

/**
 *	Convert a MAC address string to a byte array of 6 bytes
 */
byte* ArpGyp::stringToMac(std::string const& s) {
    byte a[6];
    int last = -1;
    int rc = sscanf(s.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx%n",
                    a + 0, a + 1, a + 2, a + 3, a + 4, a + 5,
                    &last);
    if(rc != 6 || s.size() != (unsigned int)last)
        throw std::runtime_error("invalid mac address format " + s);

    // Allocate 6 byte memory on the heap
    byte *ret = (byte*) malloc(6);

    // Copy the byte array "a" to the newly allocated memory 
    memcpy(ret, a, 6);

    // Return the pointer
    return ret;
}

/**
 *	Convert an IP address string to a byte array of 4 bytes
 */
byte* ArpGyp::stringToIp(std::string const& s) {
    byte* a = (byte*) malloc(4);
    // Parse the string and store it in the byte arr
    sscanf(s.c_str(), "%s.%s.%s.%s",
	    &a[0], &a[1], &a[2], &a[3]
	);

    // Return the pointer
    return a;
}