// 定义以太网帧头
/*
1. target Mac        6 Bytes        目标mac地址
2. source Mac        6 Bytes        源mac地址
3. type              2 Bytes        上层协议的类型
*/

# ifndef HDR
# define HDR

# include <stdint.h>

# define ETH_II_MAC_LENGTH 6
// Ethernet II Header 以太网帧头定义
typedef struct{
    uint8_t target_mac[ETH_II_MAC_LENGTH];
    uint8_t source_mac[ETH_II_MAC_LENGTH];
    uint16_t type;
} Eth_II_hdr;

Eth_II_hdr *eth_ii_parse(const unsigned char *data);
void eth_ii_print(Eth_II_hdr *eth_ii_hdr);
# endif