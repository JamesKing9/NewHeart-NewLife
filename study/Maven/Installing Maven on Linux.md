#  install Maven on Linux

While there are many ﬂavors of Linux (Ubuntu, Fedora, RHEL, SUSE, CentOS, and so on), the
steps to set up Maven are similar.

## install JDK

Maven needs Java, specifcally the Java Development Kit (JDK). Using the following steps, let
us check if it is installed in your Linux system, which is a bit tricky:

Open a terminal and run the following command:

```shell
java -version
```

See if you get an output similar to the following:
```shell
java version "1.7.0_65"
OpenJDK Runtime Environment (rhel-2.5.1.2.el6_5-x86_64 u65-b17)
```
The preceding output will still not tell you where your Java is installed, which is
required to set `JAVA_HOME`. You can get this information by performing the next set
of steps.

Check if `javac` works; it does only if JDK is installed, not JRE:
`$ javac -version`
The output for the preceding command is shown as:
`javac 1.7.0_65`

Find the location of the javac command:
`$ which javac`
The output for the preceding command is shown as:
`/usr/bin/javac`





## To set up Maven on Linux, perform the following steps:

1- Go to http://maven.apache.org/ and click on the **Download** link. The links to
latest stable versions of Maven will be displayed.

2- The binaries are available in both `.zip` and `.tar.gz` formats. For Mac OS X and
Linux, the preferred download format is `.tar.gz`.

3- Extract the downloaded binary to a folder you want Maven to reside in. The typical
location in Linux is the `/usr/local` folder.

	> You will need a `super user (su)` or administrator access to place
	> contents in the `/usr/local` folder. If you do not have access, you
	> can place this in a subfolder of your `HOME` folder.

4- Execute the following command, and ensure the contents of the `apachemaven-3.2.5` folder are similar to the following output:
`/usr/local/apache-maven-3.2.5$ ls -l`
The output for the preceding command is shown as:
```shell
total 27
-rw-r--r-- 1 root root 17464 Aug 12 02:29 LICENSE
-rw-r--r-- 1 root root 182 Aug 12 02:29 NOTICE
-rw-r--r-- 1 root root 2508 Aug 12 02:26 README.txt
drwxr-xr-x 8 root root 4096 Aug 19 13:41 bin
drwxr-xr-x 3 root root 0 Aug 19 13:41 boot
drwxr-xr-x 4 root root 0 Oct 14 17:39 conf
drwxr-xr-x 67 root root 28672 Aug 19 13:41 lib
```

5- Set the `M2_HOME` variable as follows:
`export M2_HOME=/usr/local/apache-maven-3.2.5`

6- Update `PATH` to include Maven's `bin` folder:
`export PATH=$PATH:$M2_HOME/bin`

Like `JAVA_HOME`, the preceding settings can be persisted by updating `.bash_profile`.