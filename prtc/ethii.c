// 定义Ethernet II 使用到的函数
# include "hdr.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>     // 声明 malloc()
# include <arpa/inet.h> // 声明 ntohs()

Eth_II_hdr *eth_ii_parse(const unsigned char *data){
    Eth_II_hdr *eth_ii_hdr = malloc(sizeof(Eth_II_hdr));        // 动态分配14Bytes的内存
    if (eth_ii_hdr == NULL){
        return eth_ii_hdr;          // 分配失败返回NULL
    }
    memcpy(eth_ii_hdr, data, sizeof(Eth_II_hdr));       // 将原始的以太网帧头数据分配到定义好的结构体内存中
    eth_ii_hdr->type = ntohs(eth_ii_hdr->type);         // 
    return eth_ii_hdr;
}

// 打印解析出来的以太网帧头
void print_mac(const unsigned char *mac) {
    for (int i = 0; i < 6; ++i) {
        printf("%02x", mac[i]);
        if (i < 5) printf(":");
    }
}

void eth_ii_print(Eth_II_hdr *eth_ii_hdr){
    printf("Target MAC: ");
    print_mac(eth_ii_hdr->target_mac);
    printf("\nSource MAC: ");
    print_mac(eth_ii_hdr->source_mac);
    printf("\nType: 0x%04x\n", eth_ii_hdr->type);
}