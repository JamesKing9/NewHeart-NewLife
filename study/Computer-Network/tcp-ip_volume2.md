# 9 - IP Option Processing

## 9.1. Introduction

Recall from Chapter 8 that the IP input function (ipintr) processes options after it verifies the packet’s format (checksum, length, etc.) and before it determines whether the packet has reached its final destination. This implies that a packet’s options are processed by every router it encounters and by the final destination host.

RFCs 791 and 1122 specify the IP options and processing rules. This chapter describes the format and processing of most IP options. We’ll also show how a transport protocol can specify the IP options to be included in an IP datagram.

An IP packet can include optional fields that are processed before the packet is forwarded or accepted by a system. An IP implementation can handle options in any order; for Net/3, it is the order in which the options appear in the packet. Figure 9.1 shows that up to 40 bytes of options may follow the standard IP header.