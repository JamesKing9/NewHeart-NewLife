ubuntu 的 deb 文件可以通过系统自带的 `Ubuntu Software Centre` 来安装， 但是会出现“安装好了，打不开” 的情况。

因此，推荐下述方法：

```shell
sudo dpkg -i <filename>.deb
```

- “dpkg ”是“Debian Packager ”的简写。为 “Debian” 专门开发的套件管理系统，方便软件的安装、更新及移除。所有源自“Debian”的“Linux ”发行版都使用 “dpkg”，例如 “Ubuntu”、“Knoppix ”等。 

