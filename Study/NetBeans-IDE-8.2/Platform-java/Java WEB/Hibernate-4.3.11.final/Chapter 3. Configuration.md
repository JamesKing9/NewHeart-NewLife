# Chapter 3. Configuration
[TOC]
---

Hibernate is designed to operate in many different environments and, as such, there is a broad range of configuration parameters. Fortunately, most have sensible default values and Hibernate is distributed with an example hibernate.properties file in etc/ that displays the various options. Simply put the example file in your classpath and customize it to suit your needs.

## 3.1. Programmatic configuration

An instance of `org.hibernate.cfg.Configuration` represents an entire set of mappings of an application's Java types to an SQL database. The `org.hibernate.cfg.Configuration` is used to build an immutable `org.hibernate.SessionFactory`. The mappings are compiled from various XML mapping files.

You can obtain a `org.hibernate.cfg.Configuration` instance by instantiating it directly and specifying XML mapping documents. If the mapping files are in the classpath, use `addResource()`. For example:
```java
Configuration cfg = new Configuration()
    .addResource("Item.hbm.xml")
    .addResource("Bid.hbm.xml");
```
An alternative way is to specify the mapped class and allow Hibernate to find the mapping document for you:
```java
Configuration cfg = new Configuration()
    .addClass(org.hibernate.auction.Item.class)
    .addClass(org.hibernate.auction.Bid.class);
```
Hibernate will then search for mapping files named `/org/hibernate/auction/Item.hbm.xml` and `/org/hibernate/auction/Bid.hbm.xml` in the classpath. This approach eliminates any hardcoded filenames.

A `org.hibernate.cfg.Configuration` also allows you to specify configuration properties. For example:
```java
Configuration cfg = new Configuration()
    .addClass(org.hibernate.auction.Item.class)
    .addClass(org.hibernate.auction.Bid.class)
    .setProperty("hibernate.dialect", "org.hibernate.dialect.MySQLInnoDBDialect")
    .setProperty("hibernate.connection.datasource", "java:comp/env/jdbc/test")
    .setProperty("hibernate.order_updates", "true");
```

This is not the only way to pass configuration properties to Hibernate. Some alternative options include:
1. Pass an instance of `java.util.Properties` to `Configuration.setProperties()`.
2. Place a file named `hibernate.properties` in a root directory of the classpath.
3. Set System properties using `java -Dproperty=value`.
4. Include `<property>` elements in `hibernate.cfg.xml` (this is discussed later).

If you want to get started quickly `hibernate.properties` is the easiest approach.

The `org.hibernate.cfg.Configuration` is intended as a startup-time object that will be discarded once a `SessionFactory` is created.

## 3.2. Obtaining a SessionFactory

When all mappings have been parsed by the `org.hibernate.cfg.Configuration`, the application must obtain a factory for `org.hibernate.Session` instances. This factory is intended to be shared by all application threads:
```java
SessionFactory sessions = cfg.buildSessionFactory();
```
Hibernate does allow your application to instantiate more than one `org.hibernate.SessionFactory`. This is useful if you are using more than one database.

## 3.3. JDBC connections

It is advisable to have the `org.hibernate.SessionFactory` create and pool JDBC connections for you. If you take this approach, opening a `org.hibernate.Session` is as simple as:
```java
Session session = sessions.openSession(); // open a new Session
```
Once you start a task that requires access to the database, a JDBC connection will be obtained from the pool.

Before you can do this, you first need to pass some JDBC connection properties to Hibernate. All Hibernate property names and semantics are defined on the class `org.hibernate.cfg.Environment`. The most important settings for JDBC connection configuration are outlined below.

Hibernate will obtain and pool connections using `java.sql.DriverManager` if you set the following properties:

**Table 3.1. Hibernate JDBC Properties**
| Property name                     | Purpose                              |
| --------------------------------- | ------------------------------------ |
| hibernate.connection.driver_class | JDBC driver class                    |
| hibernate.connection.url          | JDBC URL                             |
| hibernate.connection.username     | database user                        |
| hibernate.connection.password     | database user password               |
| hibernate.connection.pool_size    | maximum number of pooled connections |

Hibernate's own connection pooling algorithm is, however, quite rudimentary. It is intended to help you get started and is not intended for use in a production system, or even for performance testing. You should use a third party pool for best performance and stability. Just replace the `hibernate.connection.pool_size` property with connection pool specific settings. This will turn off Hibernate's internal pool. For example, you might like to use `c3p0`.

`C3P0` is an open source JDBC connection pool distributed along with Hibernate in the lib directory. Hibernate will use its `org.hibernate.connection.C3P0ConnectionProvider` for connection pooling if you set `hibernate.c3p0.* properties`. If you would like to use `Proxool`, refer to the packaged `hibernate.properties` and the Hibernate web site for more information.

The following is an example hibernate.properties file for `c3p0`:
```
hibernate.connection.driver_class = org.postgresql.Driver
hibernate.connection.url = jdbc:postgresql://localhost/mydatabase
hibernate.connection.username = myuser
hibernate.connection.password = secret
hibernate.c3p0.min_size=5
hibernate.c3p0.max_size=20
hibernate.c3p0.timeout=1800
hibernate.c3p0.max_statements=50
hibernate.dialect = org.hibernate.dialect.PostgreSQL82Dialect
```

For use inside an application server, you should almost always configure Hibernate to obtain connections from an application server `javax.sql.Datasource` registered in JNDI. You will need to set at least one of the following properties:

**Table 3.2. Hibernate Datasource Properties**
| Property name                   | Purpose                                  |
| ------------------------------- | ---------------------------------------- |
| hibernate.connection.datasource | datasource JNDI name                     |
| hibernate.jndi.url              | URL of the JNDI provider (optional)      |
| hibernate.jndi.class            | class of the JNDI `InitialContextFactory` (optional) |
| hibernate.connection.username   | database user (optional)                 |
| hibernate.connection.password   | database user password (optional)        |

Here is an example `hibernate.properties` file for an application server provided JNDI datasource:
```
hibernate.connection.datasource = java:/comp/env/jdbc/test
hibernate.transaction.factory_class = \
    org.hibernate.transaction.JTATransactionFactory
hibernate.transaction.manager_lookup_class = \
    org.hibernate.transaction.JBossTransactionManagerLookup
hibernate.dialect = org.hibernate.dialect.PostgreSQL82Dialect
```
JDBC connections obtained from a JNDI datasource will automatically participate in the container-managed transactions of the application server.

Arbitrary connection properties can be given by prepending "hibernate.connection" to the connection property name. For example, you can specify a charSet connection property using `hibernate.connection.charSet`.

You can define your own plugin strategy for obtaining JDBC connections by implementing the interface `org.hibernate.connection.ConnectionProvider`, and specifying your custom implementation via the `hibernate.connection.provider_class` property.
