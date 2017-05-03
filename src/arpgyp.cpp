#include "../include/arpgyp.h"

int ArpGyp::s = -1;

ArpGyp::ArpGyp() {
	ArpGyp::s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); // Create a RAW socket
	if(s == -1) {
    	printf("Failed to create socket: %s", strerror(errno));
    	exit(1);
	}
}

ArpGyp::~ArpGyp() {

}

/**
 *	Convert a MAC address string to a byte array of 6 bytes
 */
std::array<byte,4> ArpGyp::stringToMac(std::string const& s) {
    byte a[6];
	std::array<byte,4> ret;
    int last = -1;
    int rc = sscanf(s.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx%n",
                    a + 0, a + 1, a + 2, a + 3, a + 4, a + 5,
                    &last);
    if(rc != 6 || s.size() != (unsigned int)last)
        throw std::runtime_error("invalid mac address format " + s);

    std::copy(a, a + 6, ret.data());

    return ret;
}

void ArpGyp::stringToIp(const std::string &src, std::array<byte,4> &dst) {
	std::stringstream s(src);
	int oct_1, oct_2, oct_3, oct_4;
	char ch;
	s >> oct_1 >> ch >> oct_2 >> ch >> oct_3 >> ch >> oct_4;
	dst[0] = oct_1;
	dst[1] = oct_2;
	dst[2] = oct_3;
	dst[3] = oct_4;

}

std::string ArpGyp::ByteToHex(byte inchar)
{
  std::ostringstream oss (std::ostringstream::out);
  oss << std::setw(2) << std::setfill('0') << std::hex << (int)(inchar);
  return oss.str();
}

int ArpGyp::GetIfIndex(std::string iface_s) {
	ifreq ifr;

	strncpy(ifr.ifr_name, iface_s.c_str(), IFNAMSIZ);
	if (ioctl(s, SIOCGIFINDEX, &ifr) == -1) {
	   perror("SIOCGIFINDEX");
	   exit(1);
	}
	return ifr.ifr_ifindex;
}
