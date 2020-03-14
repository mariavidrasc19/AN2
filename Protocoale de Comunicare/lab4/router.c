#include "skel.h"

int interfaces[ROUTER_NUM_INTERFACES];
struct route_table_entry *rtable;
int rtable_size;

struct arp_entry *arp_table;
int arp_table_len;

/*
 Returns a pointer (eg. &rtable[i]) to the best matching route
 for the given dest_ip. Or NULL if there is no matching route.
*/
struct route_table_entry *get_best_route(__u32 dest_ip) {
	/* TODO 1: Implement the function */
	int mask = 0;
	int indice = -1;
	for (int i = 0; i < rtable_size; i++) {
		if ((dest_ip & rtable[i].mask) == rtable[i].prefix && rtable[i].mask > mask) {
			indice = i;
			mask = rtable[i].mask;
		}
	}
	if (indice == -1) {
		return NULL;
	} else {
		return &rtable[indice];
	}
}

/*
 Returns a pointer (eg. &arp_table[i]) to the best matching ARP entry.
 for the given dest_ip or NULL if there is no matching entry.
*/
struct arp_entry *get_arp_entry(__u32 ip) {
    /* TODO 2: Implement */
	for (int i = 0; i < arp_table_len; i++) {
		if (arp_table[i].ip == ip) {
			return &arp_table[i];
		}
	}
    return NULL;
}

int main(int argc, char *argv[])
{
	msg m;
	int rc;

	init();
	rtable = malloc(sizeof(struct route_table_entry) * 100);
	arp_table = malloc(sizeof(struct  arp_entry) * 100);
	DIE(rtable == NULL, "memory");
	rtable_size = read_rtable(rtable);
	parse_arp_table();
	/* Students will write code here */

	while (1) {
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		struct ether_header *eth_hdr = (struct ether_header *)m.payload;
		struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));
		/* TODO 3: Check the checksum */
		if (ip_checksum(ip_hdr, sizeof(struct iphdr)) != ip_hdr->check) {
			break;
		}
		

		/* TODO 4: Check TTL >= 1 */
		if (ip_hdr->ttl < 1) {
			break;
		}

		/* TODO 5: Find best matching route (using the function you wrote at TODO 1) */
		struct route_table_entry *r = get_best_route(ip_hdr->daddr);

		/* TODO 6: Update TTL and recalculate the checksum */
		ip_hdr->ttl--;
		if (ip_hdr->ttl < 1) {
			DIE(ip_hdr, "wrong TTL");
		}

		/* TODO 7: Find matching ARP entry and update Ethernet addresses */
		struct arp_entry *a = get_arp_entry(r->next_hop);
		get_interface_mac(r->interface, eth_hdr->ether_shost);

		/* TODO 8: Forward the pachet to best_route->interface */
		m.interface = r->interface;
		send_packet(m.interface, &m);
	}
}
