// 打印网卡信息
# include <stdio.h>
# include <pcap.h>

void devices_info()
{
    pcap_if_t *alldevs;     // 所有设备列表
    pcap_if_t *device;      // 当前设备
    char errbuf[PCAP_ERRBUF_SIZE];  // 错误信息缓冲区

    // 获取设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1){          // 函数会把设备链表头指针赋给alldevs
        fprintf(stderr, "Error in pcap_findalldevices: %s\n", errbuf);      //将错误信息输出到 stderr，而不是 stdout
        return;
    }

    printf("Network devices found: \n");
    int i = 0;
    for (device = alldevs; device != NULL; device = device->next){      // 遍历所有设备列表
        printf("\n id: %d, Device name: %s\n", ++i ,device->name);

        if (device->description){
            printf("Description: %s\n", device->description);
        }
        else
            printf("No description available. \n");

        for (pcap_addr_t *addr = device->addresses; addr != NULL; addr = addr->next){
        if (addr->addr && addr->addr->sa_family == AF_INET){        // 检查这个地址节点是否有地址值， 该地址类型是否是IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)addr->addr;
            struct sockaddr_in *mask = (struct sockaddr_in *)addr->netmask;
            
            printf("IP address: %s\n", inet_ntoa(ipv4->sin_addr));            //inet_ntoa() 是 C 标准函数，用来把 in_addr（一个整数形式的 IP 地址）转换为 点分十进制字符串（如 "192.168.0.1"）。
            if (mask){
                printf("Subnet Mask: %s\n", inet_ntoa(mask->sin_addr));
            }
        }
    }
    }

    
    pcap_freealldevs(alldevs);
}
