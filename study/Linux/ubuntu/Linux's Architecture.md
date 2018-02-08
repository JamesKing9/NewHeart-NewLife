#  Filesystem Hierarchy Standard(FHS)

The top-level structure is defined by FHS to have several mandatory subdirectories and a small number of optional directories; the main ones are shown in the following table.

| Directory | Required? | Use                                      |
| --------- | --------- | ---------------------------------------- |
| /bin      | Y         | Important system binary files.           |
| /boot     | Y         | Files required to boot the system.       |
| /dev      | Y         | Devices.                                 |
| /etc      | Y         | System configuration files.              |
| /home     | N         | Directories for user files.              |
| /lib      | Y         | Standard libraries.                      |
| /media    | Y         | A place for removable media to be mounted, with separate subdirectories for each media type supported by the system. |
| /mnt      | Y         | A convenient point to temporarily mount devices, such as CD-ROMs and flash memory sticks. |
| /opt      | Y         | Additional application software.         |
| /root     | N         | Files for the root user.                 |
| /sbin     | Y         | Important system binary files that are required during system startup. |
| /srv      | Y         | Read-only data for services provided by this system. |
| /tmp      | Y         | Temporary files.                         |
| /usr      | Y         | A secondary hierarchy. Traditionally user files were also stored here, but that is now considered bad practice, and `/usr` should not be writable by ordinary users. |
| /var      | Y         | Variable data, such as log files.        |