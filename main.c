# include <stdio.h>
# include "inc/device.h"
# include <pcap.h>

# define name "eth0"

int main(){
    // devices_info();
    pcap_if_t *device = device_find(name);
    // printf("%p \n", device);
    return 0;
}