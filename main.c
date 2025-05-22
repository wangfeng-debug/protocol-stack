# include <stdio.h>
# include "inc/device.h"
# include <pcap.h>
#include <stdlib.h>

# define NAME "eth0"

int main(){
    char errbuf[PCAP_ERRBUF_SIZE];
    // devices_info();     // 打印网卡信息
    pcap_if_t *device = device_find(NAME);      // 找到指定名字的网卡
    // printf("%s \n", *(device->addresses));

    // 打开网卡
    pcap_t *handle = pcap_open_live(device->name, BUFSIZ, 0, 1000, errbuf);
    if (!handle){
        fprintf(stderr, "Unable to open device: %s\n", errbuf);
        exit(-1);
    }

    // 使用pcap_loop()函数抓包
    pcap_loop(handle, 5, device_hander, NULL); // 抓取5个包  device_hander为回调函数

    pcap_close(handle);
    return 0;
}