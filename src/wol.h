#define WOL_PORT 9
#define WOL_BCAST 0xFFFFFFFF

int send_wol(const char *hardware_addr, unsigned port, unsigned long bcast);