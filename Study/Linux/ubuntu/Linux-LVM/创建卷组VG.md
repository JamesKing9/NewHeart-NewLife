# Linux LVM学习总结——创建卷组VG

>   在Linux平台如何创建一个卷组（VG）呢？下面简单介绍一下卷组（VG）的创建步骤。
>
>   本文实验平台为Ubuntu 16.4.3 LTS



## 1： 查看当前卷组信息

查看服务器的卷组（VG）、物理卷（PV）、逻辑卷（LV）相关信息，在此之前，我们先来看看一些基本命令以及用法  

  

### **vgcan命令介绍** :  

​    查找系统中存在的LVM卷组，并显示找到的卷组列表。`vgscan`命令仅显示找到的卷组的名称和LVM元数据类型，要得到卷组的详细信息需要使用`vgdisplay`命令。  

**vgscan的参数：**

| Label                          | Describe                                 |
| ------------------------------ | ---------------------------------------- |
| [—cache]                       | Scan devices for LVM physical volumes and volume groups and instruct the lvmetad daemon to update its cached state accordingly |
| [--commandprofile ProfileName] |                                          |
| [-d\|--debug]                  | 调试模式                                     |
| [-h\|--help]                   | 查看帮助信息                                   |
| [--ignorelockingfailure]       | 忽略锁定失败的错误。                               |
| [--mknodes]                    | Also checks the LVM special files in /dev that are needed for active logical volumes and creates any missing ones and removes unused ones |
| [-P\|--partial]                | 部分模式。将处理不完整的逻辑卷                          |
| [-v\|--verbose]                | 显示输出详细信息                                 |
| [--version]                    | 查看命名版本信息                                 |

​                  

### **pvscan命令介绍：**  

扫描系统中连接的所有硬盘，列出找到的物理卷列表。  

**pvscan的参数:**   

| Label                                    | Desc                                 |
| ---------------------------------------- | ------------------------------------ |
| [-b\|—background]                        | 在后台运行这个命令                            |
| [--cache [-a\|--activate ay] [ DevicePath \| --major major --minor minor]...] |                                      |
| [--commandprofile ProfileName]           |                                      |
| [-d\|—debug]                             | 调试模式                                 |
| {-e\|--exported \| -n\|—novolumegroup}   | -e 仅显示属于输出卷组的物理卷; -n 仅显示不属于任何卷组的物理卷; |
| [-h\|-?\|--help]                         | 显示命令的帮助信息                            |
| [—ignorelockingfailure]                  | 忽略锁定失败的错误。                           |
| [-P\|—partial]                           | 部分模式. 将处理不完整的逻辑卷                     |
| [--readonly]                             |                                      |
| [-s\|—short]                             | 简短格式输出                               |
| [-u\|—uuid]                              | 显示输出UUID信息                           |
| [-v\|—verbose]                           | 显示输出详细信息                             |
| [—version]                               | 查看pvscan命令版本                         |

### **lvscan命令介绍 ：**  

扫描当前系统中存在的所有LVM的逻辑卷（lv)    

**lvscan的参数**： 

| Label                          | Desc             |
| ------------------------------ | ---------------- |
| [-a\|—all]                     | 输出所有的逻辑卷信息       |
| [-b\|--blockdevice]            | 显示逻辑卷的主设备号和次设备号  |
| [--cache]                      |                  |
| [--commandprofile ProfileName] |                  |
| [-d\|—debug]                   | 调试模式             |
| [-h\|-?\|--help]               | 查看命令的帮助信息        |
| [——ignorelockingfailure]       | 忽略锁定失败的错误。       |
| [-P\|—partial]                 | 部分模式. 将处理不完整的逻辑卷 |
| [--readonly]                   |                  |
| [-v\|—verbose]                 | 输出详细的结果          |
| [—version]                     | 查看lvscan命令版本     |

### 实际应用

```shell
[root@getlnx20 ~]# vgscan
  Reading all physical volumes.  This may take a while...
  Found volume group "VolGroup00" using metadata type lvm2

[root@getlnx20 ~]# pvscan
  PV /dev/sda2   VG VolGroup00   lvm2 [39.51 GiB / 0    free]
  Total: 1 [39.51 GiB] / in use: 1 [39.51 GiB] / in no VG: 0 [0   ]

[root@getlnx20 ~]# lvscan
  ACTIVE            '/dev/VolGroup00/lv_root' [31.51 GiB] inherit
  ACTIVE            '/dev/VolGroup00/lv_swap' [8.00 GiB] inherit

[root@getlnx20 ~]# df -h
Filesystem            Size  Used Avail Use% Mounted on
/dev/mapper/VolGroup00-lv_root	31G  2.5G   27G   9% /
tmpfs                 3.9G     0  3.9G   0% /dev/shm
/dev/sda1             477M   33M  419M   8% /boot

[root@getlnx20 ~]# 
```



新增一块硬盘后，使用fdisk -l命令，我们可以看到这块新增的硬盘被标记为`/dev/sdb`

```shell
[root@getlnx20 ~]# fdisk -l
Disk /dev/sda: 42.9 GB, 42949672960 bytes
64 heads, 32 sectors/track, 40960 cylinders
Units = cylinders of 2048 * 512 = 1048576 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x0006822c

   Device Boot      Start         End      Blocks   Id  System

/dev/sda1   *           2         501      512000   83  Linux

Partition 1 does not end on cylinder boundary.

/dev/sda2             502       40960    41430016   8e  Linux LVM

Partition 2 does not end on cylinder boundary.

Disk /dev/mapper/VolGroup00-lv_root: 33.8 GB, 33831256064 bytes
255 heads, 63 sectors/track, 4113 cylinders
Units = cylinders of 16065 * 512 = 8225280 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

Disk /dev/mapper/VolGroup00-lv_swap: 8589 MB, 8589934592 bytes
255 heads, 63 sectors/track, 1044 cylinders
Units = cylinders of 16065 * 512 = 8225280 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

Disk /dev/sdb: 85.9 GB, 85899345920 bytes
255 heads, 63 sectors/track, 10443 cylinders
Units = cylinders of 16065 * 512 = 8225280 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000
```

-   新增一个80G的硬盘，但是为什么使用fdisk 
    -l命令查看到的是85.9G？相信很多人看到这个都会有些疑惑。这个是因为计算时使用的单位有所差异所致, 85899345920/1024/1024/1024=80G，而85899345920/1000/1000/1000 ~= 85.899 ~=  85.9G 。



## 2： 新建一个分区（partition）

新建一个主分区（primary partition）或逻辑分区（logical partition）都OK

```shell
[root@getlnx20 ~]# fdisk /dev/sdb
Device contains neither a valid DOS partition table, nor Sun, SGI or OSF disklabel
Building a new DOS disklabel with disk identifier 0xaa12f277.
Changes will remain in memory only, until you decide to write them.
After that, of course, the previous content won't be recoverable.
Warning: invalid flag 0x0000 of partition table 4 will be corrected by w(rite)
WARNING: DOS-compatible mode is deprecated. It's strongly recommended to
         switch off the mode (command 'c') and change display units to
         sectors (command 'u').
Command (m for help): n
Command action
   e   extended
   p   primary partition (1-4)
p
Partition number (1-4): 1
First cylinder (1-10443, default 1): 1
Last cylinder, +cylinders or +size{K,M,G} (1-10443, default 10443): 
Using default value 10443

Command (m for help): w
The partition table has been altered!
Calling ioctl() to re-read partition table.
Syncing disks.
```



## 3：创建PV（物理卷）

```shell
[root@getlnx20 ~]# pvcreate /dev/sdb1

  Physical volume "/dev/sdb1" successfully created

[root@getlnx20 ~]# pvscan

  PV /dev/sda2   VG VolGroup00   lvm2 [39.51 GiB / 0    free]

  PV /dev/sdb1                   lvm2 [80.00 GiB]

  Total: 2 [119.51 GiB] / in use: 1 [39.51 GiB] / in no VG: 1 [80.00 GiB]
```



## 4：创建VG（卷组）

```shell
[root@getlnx20 ~]# vgcreate -s 32M VolGroup01 /dev/sdb1

  Volume group "VolGroup01" successfully created

[root@getlnx20 ~]# vgscan

  Reading all physical volumes.  This may take a while...

  Found volume group "VolGroup01" using metadata type lvm2

  Found volume group "VolGroup00" using metadata type lvm2
```



## 5：查看VG可用空间

```shell
[root@getlnx20 ~]# vgdisplay

  --- Volume group ---

  VG Name               VolGroup01

  System ID             

  Format                lvm2

  Metadata Areas        1

  Metadata Sequence No  1

  VG Access             read/write

  VG Status             resizable

  MAX LV                0

  Cur LV                0

  Open LV               0

  Max PV                0

  Cur PV                1

  Act PV                1

  VG Size               79.97 GiB

  PE Size               32.00 MiB

  Total PE              2559

  Alloc PE / Size       0 / 0   

  Free  PE / Size       2559 / 79.97 GiB

  VG UUID               FD5kEp-a9Cv-K181-Xb7e-i8k4-zV52-Dbuxc3

   

  --- Volume group ---

  VG Name               VolGroup00

  System ID             

  Format                lvm2

  Metadata Areas        1

  Metadata Sequence No  3

  VG Access             read/write

  VG Status             resizable

  MAX LV                0

  Cur LV                2

  Open LV               2

  Max PV                0

  Cur PV                1

  Act PV                1

  VG Size               39.51 GiB

  PE Size               4.00 MiB

  Total PE              10114

  Alloc PE / Size       10114 / 39.51 GiB

  Free  PE / Size       0 / 0   

  VG UUID               sWwXef-0AHf-66ZI-dZHh-JuJt-KMj7-YqIisW

   

[root@getlnx20 ~]# 
```



## 6：建立逻辑卷（LV）

```shell
[root@getlnx20 ~]# lvcreate -L79.97G -n LogVol00 VolGroup01

  Rounding up size to full physical extent 80.00 GiB

  Volume group "VolGroup01" has insufficient free space (2559 extents): 2560 required.

[root@getlnx20 ~]# lvcreate -L79.96G -n LogVol00 VolGroup01

  Rounding up size to full physical extent 79.97 GiB

  Logical volume "LogVol00" created

[root@getlnx20 ~]# lvscan

  ACTIVE            '/dev/VolGroup01/LogVol00' [79.97 GiB] inherit

  ACTIVE            '/dev/VolGroup00/lv_root' [31.51 GiB] inherit

  ACTIVE            '/dev/VolGroup00/lv_swap' [8.00 GiB] inherit
```



## 7：建立文件系统

```shell
[root@getlnx20 ~]# mkfs -t ext3 /dev/VolGroup01/LogVol00

mke2fs 1.41.12 (17-May-2010)

Filesystem label=

OS type: Linux

Block size=4096 (log=2)

Fragment size=4096 (log=2)

Stride=0 blocks, Stripe width=0 blocks

5242880 inodes, 20963328 blocks

1048166 blocks (5.00%) reserved for the super user

First data block=0

Maximum filesystem blocks=4294967296

640 block groups

32768 blocks per group, 32768 fragments per group

8192 inodes per group

Superblock backups stored on blocks: 

        32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632, 2654208, 

        4096000, 7962624, 11239424, 20480000

 

Writing inode tables: done                            

Creating journal (32768 blocks): done

Writing superblocks and filesystem accounting information: done

 

This filesystem will be automatically checked every 24 mounts or

180 days, whichever comes first.  Use tune2fs -c or -i to override.
```



## 8：建立挂载点

```shell
[root@getlnx20 ~]# mkdir /home/当前用户/文件夹
```



## 9：挂载存储

```shell
[root@getlnx20 ~]# mount /dev/VolGroup01/LogVol00 /home/当前用户/文件夹

[root@getlnx20 ~]# df -h
Filesystem            Size  Used Avail Use% Mounted on
/dev/mapper/VolGroup00-lv_root  31G  2.5G   27G   9% /
tmpfs                 3.9G     0  3.9G   0% /dev/shm
/dev/sda1             477M   33M  419M   8% /boot
/dev/mapper/VolGroup01-LogVol00 79G  184M   75G   1% /mysqldata

[root@getlnx20 ~]# 
```



## 10：修改fstab配置文件实现自动挂载

```shell
[root@getlnx20 ~]# more /etc/fstab
#
# /etc/fstab
# Created by anaconda on Sat Jun 13 10:29:07 2015
#
# Accessible filesystems, by reference, are maintained under '/dev/disk'
# See man pages fstab(5), findfs(8), mount(8) and/or blkid(8) for more info
#
/dev/mapper/VolGroup00-lv_root /                       ext4    defaults        1 1
UUID=5486634e-ec6a-42d5-bbb9-dcd92537c294 /boot                   ext4    defaults        1 2
/dev/mapper/VolGroup00-lv_swap swap                    swap    defaults        0 0
/dev/VolGroup01/LogVol00                                /mysqldata  ext3 defaults 1 1
tmpfs                   /dev/shm                tmpfs   defaults        0 0
devpts                  /dev/pts                devpts  gid=5,mode=620  0 0
sysfs                   /sys                    sysfs   defaults        0 0
proc                    /proc                   proc    defaults        0 0

[root@getlnx20 ~]# 
```

