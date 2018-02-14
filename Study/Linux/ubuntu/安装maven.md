# download tar.gz
`apache-maven-3.5.2-bin.tar.gz`
then **Extract Here**.

# move to opt
```shell
$ sudo mv apache-maven-3.5.2 /opt

```

# add to PATH
```shell
export PATH="/opt/apache-maven-3.5.2/bin:$PATH"
```

# verify
```shell
$ mvn -version
Apache Maven 3.5.2 (138edd61fd100ec658bfa2d307c43b76940a5d7d; 2017-10-18T15:58:13+08:00)
Maven home: /opt/apache-maven-3.5.2
Java version: 1.8.0_162, vendor: Oracle Corporation
Java home: /opt/jdk1.8.0_162/jre
Default locale: en_US, platform encoding: UTF-8
OS name: "linux", version: "4.13.0-26-generic", arch: "amd64", family: "unix"
$

```

# modify the repority

## local
at line 55:
```xml
<localRepository>/home/james/Documents/maven/repo</localRepository>
```


## remote
behind line 158:
```xml
    <mirror>
      <id>alimaven</id>
      <mirrorOf>central</mirrorOf>
      <name>aliyun maven</name>
      <url>http://maven.aliyun.com/nexus/content/repositories/central/</url>
    </mirror>
  </mirrors>
```

It's OK!