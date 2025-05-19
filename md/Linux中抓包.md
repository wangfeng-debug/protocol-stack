

## 1. Linux中抓取包

监听`example.com`

第一个终端中使用    `sudo tcpdump -nn host example.com -w web.pcap`

```bash
wangfeng@WF-LOPTOP:~/protocol/protocol-stack/prap$ sudo tcpdump -nn host example.com -w web.pcap
tcpdump: listening on eth0, link-type EN10MB (Ethernet), snapshot length 262144 bytes

```

第二个终端使用  `curl example.com`访问



但是结束第一个终端后，并没有抓到包`0 packets received by filter`

```bash
wangfeng@WF-LOPTOP:~/protocol/protocol-stack/prap$ sudo tcpdump -nn host example.com -w web.pcap
tcpdump: listening on eth0, link-type EN10MB (Ethernet), snapshot length 262144 bytes
^C0 packets captured
0 packets received by filter      
0 packets dropped by kernel
```

查看使用  `curl -v example.com`是否真正直访问到了

```bash
wangfeng@WF-LOPTOP:~/protocol/protocol-stack$ curl -v example.com
* Uses proxy env variable no_proxy == '192.168.*,172.31.*,172.30.*,172.29.*,172.28.*,172.27.*,172.26.*,172.25.*,172.24.*,172.23.*,172.22.*,172.21.*,172.20.*,172.19.*,172.18.*,172.17.*,172.16.*,10.*,127.*,localhost'
* Uses proxy env variable http_proxy == 'http://127.0.0.1:10986'
*   Trying 127.0.0.1:10986...
* Connected to (nil) (127.0.0.1) port 10986 (#0)
> GET http://example.com/ HTTP/1.1
> Host: example.com
> User-Agent: curl/7.81.0
> Accept: */*
> Proxy-Connection: Keep-Alive
```

```bash

* Uses proxy env variable http_proxy == 'http://127.0.0.1:10986'
*   Trying 127.0.0.1:10986...

```

`curl` 命令 **没有直接访问目标网站**，而是系统中设置的 HTTP 代理（本地端口 `127.0.0.1:10986`）访问目标网站

抓不到包，是因为：

* 设置了代理后，`curl` 只是发包到本地 `127.0.0.1`，**实际由本地代理程序转发**到目标网站；

* 而 `tcpdump` 抓的是某个网卡（如 `eth0`）上的包，而本地代理的流量走 `lo`（回环网卡）或可能根本不经过外网；

* 所以你看不到与 `39.156.66.10` 的真正通信。



在 `curl` 命令中加上 `--noproxy` 或清除代理环境变量：

`curl -v --noproxy '*' http://39.156.66.10`

正常抓取到包写入到`web.pcap`

<img src="file:///C:/Users/86182/Pictures/Typedown/717bd772-5cb6-41d3-9acc-878b1fa054fd.png" title="" alt="717bd772-5cb6-41d3-9acc-878b1fa054fd" style="zoom:80%;">



## 2. 使用wireshark分析包

移动`web.pcap`到指定windows文件夹下，在使用wireshark打开该文件

```bash
sudo mv web.pcap /mnt/f/network/pcap
```

![8765f8ea-d756-45f4-ae09-21888b9d3aaa](file:///C:/Users/86182/Pictures/Typedown/8765f8ea-d756-45f4-ae09-21888b9d3aaa.png)


