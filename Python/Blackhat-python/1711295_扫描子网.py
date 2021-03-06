import threading
import time
from netaddr import IPNetwork,IPAddress
import socket
import os
import struct
from ctypes import *
import datetime

class IP(Structure):
    _fields_ =[
        ("ihl", c_ubyte, 4),
        ("version", c_ubyte,4),
        ("tos", c_ubyte),
        ("len", c_ushort),
        ("id", c_ushort),
        ("offset", c_ushort),
        ("ttl", c_ubyte),
        ("protocol_num", c_ubyte),
        ("sum", c_ushort),
        ("src", c_uint),
        ("dst", c_uint)
    ]

    def __new__(self,socket_buffer = None):
        return self.from_buffer_copy(socket_buffer)

    def __init__(self,socket_buffer = None):
        #协议字段与协议名称对应
        self.protocol_map = {1:"ICMP", 6:"TCP", 17:"UDP"}
        #可读性更强的IP地址
        self.src_address = socket.inet_ntoa(struct.pack("<L",self.src))
        self.dst_address = socket.inet_ntoa(struct.pack("<L",self.dst))
        #协议类型
        try:
            self.protocol = self.protocol_map[self.protocol_num]
        except:
            self.protocol = str(self.protocol_num)

class ICMP(Structure):
    _fields_ =[
        ("type", c_ubyte),
        ("code", c_ubyte),
        ("checksum", c_ushort),
        ("unused", c_ushort),
        ("next_hop_mtu", c_ushort),
    ]

    def __new__(self, socket_buffer):
        return self.from_buffer_copy(socket_buffer)

    def __init__(self,socket_buffer):
        pass

host = "192.168.1.112"
subnet = "192.168.1.0/24"

magic_message = "Congratulatons!"

#批量发送udp数据包
def udp_sender(subnet,magic_message):
    time.sleep(1)
    sender = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    for index,ip in enumerate(IPNetwork(subnet)):
        try:
            sender.sendto(bytes(magic_message,'utf-8'),("%s" % ip,65212))
            #print("%s" % ip,"已经发送")
        except:
            # print("%s" % ip,"没有发出")
            pass



socket_protocol = socket.IPPROTO_ICMP
sniffer = socket.socket(socket.AF_INET,socket.SOCK_RAW,socket_protocol)
sniffer.bind((host,0))
sniffer.setsockopt(socket.IPPROTO_IP,socket.IP_HDRINCL,1)
#1大概表示1个数据包



# #开始发送数据包
t = threading.Thread(target=udp_sender,args=(subnet,magic_message))
i = datetime.datetime.now()
print ("发送数据包的时间 %s:%s:%s" %(i.hour,i.minute,i.second))
t.start()

try:
    while True:
        raw_buffer = sniffer.recvfrom(65565)[0]
        ip_header = IP(raw_buffer[0:20])
        i = datetime.datetime.now()
        #print("* %s:%s:%s Protocol: %s %s -> %s" % (i.hour,i.minute,i.second,\
            # ip_header.protocol,ip_header.src_address,ip_header.dst_address))
        #如果为ICMP,进行处理
        if ip_header.protocol == "ICMP":
            offset = ip_header.ihl*4
            buf = raw_buffer[offset:offset + sizeof(ICMP)]

            #解析ICMP数据
            icmp_header = ICMP(buf)
            # print("ICMP -> Type: %d Code: %d" % (icmp_header.type, icmp_header.code))

            if icmp_header.code == 3 and icmp_header.type == 3:
                if IPAddress(ip_header.src_address) in IPNetwork(subnet):
                    # if raw_buffer[len(raw_buffer) - len(magic_message):] == \
                    #      magic_message:
                    # print("* %s:%s:%s Protocol: %s %s -> %s" % (i.hour,i.minute,i.second,\
                    # ip_header.protocol,ip_header.src_address,ip_header.dst_address))
                    # name = socket.gethostbyaddr(ip_header.src_address)
                    print("Host Up:%s" %(ip_header.src_address))
                    # os.system('nmap {}'.format(ip_header.src_address))


except KeyboardInterrupt:
    pass
