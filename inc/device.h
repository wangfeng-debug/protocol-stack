// device.h
#ifndef DEVICE_H
#define DEVICE_H
# include <pcap.h>

void devices_info();
pcap_if_t *device_find();
void device_hander();

#endif