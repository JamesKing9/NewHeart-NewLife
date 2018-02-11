# 删除卷组VG

origin from: [Linux LVM学习总结——删除卷组VG](http://www.cnblogs.com/kerrycode/p/4569515.html) 

在Linux系统中，如何删除一个卷组（VG）呢？ 下面我总结了一下如何删除卷组（VG）的具体步骤，仅供参考，如有不足，敬请指出。谢谢！在下面的例子中，我想删除卷组VolGroup05。

## 步骤1： 查看卷组（VG）相关信息

```shell
[root@getlnx01uat ~]# df -h

Filesystem            Size  Used Avail Use% Mounted on

/dev/mapper/VolGroup00-LogVol00

                       97G   36G   57G  39% /

/dev/mapper/VolGroup01-LogVol00

                       79G   33G   43G  44% /u01

/dev/mapper/VolGroup02-LogVol00

                      197G  182G  5.4G  98% /u02

/dev/mapper/VolGroup03-LogVol00

                      197G   57G  130G  31% /u03

/dev/mapper/VolGroup04-LogVol00

                      138G  118G   14G  90% /u04

/dev/mapper/VolGroup05-LogVol00

                      178G   48G  121G  29% /u05

/dev/sda1              99M   23M   71M  25% /boot

tmpfs                 2.0G     0  2.0G   0% /dev/shm

[root@getlnx01uat ~]# vgscan

  Reading all physical volumes.  This may take a while...

  Found volume group "VolGroup05" using metadata type lvm2

  Found volume group "VolGroup04" using metadata type lvm2

  Found volume group "VolGroup03" using metadata type lvm2

  Found volume group "VolGroup02" using metadata type lvm2

  Found volume group "VolGroup01" using metadata type lvm2

  Found volume group "VolGroup00" using metadata type lvm2

[root@getlnx01uat ~]# 
```



查看卷组VolGroup05包含的PV、LV信息。

```shell
[root@getlnx01uat ~]# vgdisplay -v VolGroup05

    Using volume group(s) on command line

    Finding volume group "VolGroup05"

  --- Volume group ---

  VG Name               VolGroup05

  System ID             

  Format                lvm2

  Metadata Areas        1

  Metadata Sequence No  2

  VG Access             read/write

  VG Status             resizable

  MAX LV                0

  Cur LV                1

  Open LV               1

  Max PV                0

  Cur PV                1

  Act PV                1

  VG Size               179.97 GB

  PE Size               32.00 MB

  Total PE              5759

  Alloc PE / Size       5759 / 179.97 GB

  Free  PE / Size       0 / 0   

  VG UUID               UNFxZH-lAGM-vqF3-jtNK-yuKT-enUX-WwL7FQ

   

  --- Logical volume ---

  LV Name                /dev/VolGroup05/LogVol00

  VG Name                VolGroup05

  LV UUID                kCTJnc-D3zQ-QiJp-TfPh-ivWs-WKyW-VvGTod

  LV Write Access        read/write

  LV Status              available

  # open                 1

  LV Size                179.97 GB

  Current LE             5759

  Segments               1

  Allocation             inherit

  Read ahead sectors     auto

  - currently set to     256

  Block device           253:2

   

  --- Physical volumes ---

  PV Name               /dev/sdg5     

  PV UUID               VbSwjS-9ckQ-ZfWf-bl8g-oPWQ-TMBi-H6oMWv

  PV Status             allocatable

  Total PE / Free PE    5759 / 0
```



## **2：卸载卷组的逻辑卷LV** 

要卸载对应卷组VG的所有逻辑卷LV。从上面的信息可以看出对应的卷组VolGroup05只有/dev/VolGroup05/LogVol00这个逻辑卷LV

```
[root@getlnx01uat ~]# umount /dev/VolGroup05/LogVol00
```

使用下面命令亦可

```
[root@getlnx01uat ~]# umount /u05
```

如果还用进程在使用对应逻辑卷的文件，就必须强制卸载挂接点。 



3：删除逻辑卷LV
```shell

[root@getlnx01uat ~]# lvremove /dev/VolGroup05/LogVol00

Do you really want to remove active logical volume LogVol00? [y/n]: y

  Logical volume "LogVol00" successfully removed

[root@getlnx01uat ~]# 
```

验证LV是否删除
```shell
[root@getlnx01uat ~]# lvdisplay | grep "dev/VolGroup05/LogVol00" 
```

## 4：删除卷组VG


```shell
[root@getlnx01uat ~]# vgremove VolGroup05 

  Volume group "VolGroup05" successfully removed

[root@getlnx01uat ~]# 
```
如果采用安全的方式删除卷组VG，则必须使用vgchange -a n VolGroup05关闭了vg_name，然后才可以删除它。
```shell
[root@getlnx01uat ~]# vgchange -a n VolGroup05

  0 logical volume(s) in volume group "VolGroup05" now active

[root@getlnx01uat ~]# vgremove VolGroup05 

  Volume group "VolGroup05" successfully removed
```
验证卷组（VG）是否删除
```shell
[root@getlnx01uat ~]# vgscan

 

Reading all physical volumes. This may take a while...

 

Found volume group "VolGroup04" using metadata type lvm2

 

Found volume group "VolGroup03" using metadata type lvm2

 

Found volume group "VolGroup02" using metadata type lvm2

 

Found volume group "VolGroup01" using metadata type lvm2

 

Found volume group "VolGroup00" using metadata type lvm2

 

[root@getlnx01uat ~]# 
```



## 5：删除物理卷PV

```
[root@getlnx01uat ~]# pvremove /dev/sdg5  

  Labels on physical volume "/dev/sdg5" successfully wiped

[root@getlnx01uat ~]# pvscan

  PV /dev/sde5   VG VolGroup04   lvm2 [139.97 GB / 0    free]

  PV /dev/sdd5   VG VolGroup03   lvm2 [199.97 GB / 0    free]

  PV /dev/sdc5   VG VolGroup02   lvm2 [199.97 GB / 0    free]

  PV /dev/sdb5   VG VolGroup01   lvm2 [79.97 GB / 0    free]

  PV /dev/sda2   VG VolGroup00   lvm2 [51.88 GB / 0    free]

  PV /dev/sdf5   VG VolGroup00   lvm2 [59.97 GB / 0    free]

  Total: 6 [731.72 GB] / in use: 6 [731.72 GB] / in no VG: 0 [0   ]
```



## **6：编辑/etc/fstab，删除对应挂载信息** 

如果这一步不处理，则系统重启过程中会遇到如下错误信息： 

[![clip_image002](https://images0.cnblogs.com/blog/73542/201506/111640554889379.png)](http://images0.cnblogs.com/blog/73542/201506/111659171137460.png) 

在修复模式下（Repair filesystem），文件是被保护的，不能被修改 。编辑vi /etc/fstab后并不能保存。 

[![clip_image003](https://images0.cnblogs.com/blog/73542/201506/111640582544933.png)](http://images0.cnblogs.com/blog/73542/201506/111659187852917.png) 

可以运行下面命令，把系统文件权限修改为可读写（rw）,然后编辑/etc/fstab,删除挂载点信息，重启服务器即可解决问题。 

```
mount -o remount, rw / 
```

