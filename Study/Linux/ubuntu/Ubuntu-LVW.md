```shell
root@james-B85M-D3H:/home/james# df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            3.9G     0  3.9G   0% /dev
tmpfs           787M  9.6M  777M   2% /run
/dev/sdb6        49G   43G  4.0G  92% /
tmpfs           3.9G   25M  3.9G   1% /dev/shm
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           3.9G     0  3.9G   0% /sys/fs/cgroup
/dev/loop0       82M   82M     0 100% /snap/core/3887
/dev/loop1      160M  160M     0 100% /snap/spotify/5
tmpfs           787M   60K  787M   1% /run/user/1000
root@james-B85M-D3H:/home/james# fdisk -l
Disk /dev/loop0: 81.3 MiB, 85291008 bytes, 166584 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes


Disk /dev/loop1: 159.5 MiB, 167231488 bytes, 326624 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes


Disk /dev/sda: 931.5 GiB, 1000204886016 bytes, 1953525168 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 4096 bytes
I/O size (minimum/optimal): 4096 bytes / 4096 bytes
Disklabel type: dos
Disk identifier: 0xc5135a60

Device     Boot Start        End    Sectors   Size Id Type
/dev/sda1        2048 1953523711 1953521664 931.5G 8e Linux LVM


Disk /dev/sdb: 111.8 GiB, 120034123776 bytes, 234441648 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0xde96de96

Device     Boot     Start       End   Sectors  Size Id Type
/dev/sdb1  *         2048 114003603 114001556 54.4G 83 Linux
/dev/sdb2       114003966 234440703 120436738 57.4G  5 Extended
/dev/sdb5       217905152 234440703  16535552  7.9G 82 Linux swap / Solaris
/dev/sdb6       114003968 217905151 103901184 49.6G 83 Linux

Partition table entries are not in disk order.


root@james-B85M-D3H:/home/james# 

```

