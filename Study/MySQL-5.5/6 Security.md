[TOC]

---



### 6.2.3 Specifying Account Names

MySQL account names consist of a user name and a host name. This      enables creation of accounts for users with the same name who can      connect from different hosts. This section describes how to write      account names, including special values and wildcard rules.    

In SQL statements such as `CREATE USER`, `GRANT`, and `SET PASSWORD`, account names follow      these rules:

- Account name syntax is          `'*user_name*'@'*host_name*'`.        
- An account name consisting only of a user name is equivalent          to          `'*user_name*'@'%'`.          For example, `'me'` is equivalent to          `'me'@'%'`.     
- The user name and host name need not be quoted if they are          legal as unquoted identifiers. Quotes are necessary to specify  a *user_name* string containing          special characters (such as space or `-`), or  a *host_name* string containing   special characters or wildcard characters (such as `.` or `%`); for example, `'test-user'@'%.com'`.        
- Quote user names and host names as identifiers or as strings, using either backticks , single          quotation marks (`'`), or double quotation marks (`"`). For string-quoting and          identifier-quoting guidelines, see Section 9.1.1, “String Literals” , and Section 9.2, “Schema Object Names” .        
- The user name and host name parts, if quoted, must be quoted          separately. That is, write          `'me'@'localhost'`, not          `'me@localhost'`; the latter is actually          equivalent to `'me@localhost'@'%'`.        
- A reference to the `CURRENT_USER`         or `CURRENT_USER()` function is          equivalent to specifying the current client's user name and          host name literally.

MySQL stores account names in grant tables in the      `mysql` system database using separate columns      for the user name and host name parts:

- The `user` table contains one row for each          account. The `User` and          `Host` columns store the user name and host          name. This table also indicates which global privileges the          account has.        

- Other grant tables indicate privileges an account has for          databases and objects within databases. These tables have          `User` and `Host` columns to          store the account name. Each row in these tables associates          with the account in the `user` table that has          the same `User` and `Host`          values.        

- For access-checking purposes, comparisons of User values are          case sensitive. Comparisons of Host values are not case sensitive.



For additional detail about grant table structure, see      Section 6.2.2, “Grant Tables”.    
​      

User names and host names have certain special values or wildcard      conventions, as described following.    

​      

The user name part of an account name is either a nonblank value      that literally matches the user name for incoming connection      attempts, or a blank value (empty string) that matches any user      name. An account with a blank user name is an anonymous user. To      specify an anonymous user in SQL statements, use a quoted empty      user name part, such as `''@'localhost'`.    

The host name part of an account name can take many forms, and      wildcards are permitted:

- A host value can be a host name or an IP address (IPv4 or  IPv6). The name `'localhost'` indicates the          local host. The IP address `'127.0.0.1'`          indicates the IPv4 loopback interface. The IP address          `'::1'` indicates the IPv6 loopback          interface.        

- The `%` and `_` wildcard          characters are permitted in host name or IP address values.          These have the same meaning as for pattern-matching operations          performed with the [`LIKE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/functions.html#operator_like) operator.          For example, a host value of `'%'` matches          any host name, whereas a value of          `'%.mysql.com'` matches any host in the          `mysql.com` domain.          `'198.51.100.%'` matches any host in the          198.51.100 class C network.    <br>Because IP wildcard values are permitted in host values (for          example, `'198.51.100.%'` to match every host          on a subnet), someone could try to exploit this capability by          naming a host `198.51.100.somewhere.com`. To          foil such attempts, MySQL does not perform matching on host          names that start with digits and a dot. For example, if a host          is named `1.2.example.com`, its name never          matches the host part of account names. An IP wildcard value          can match only IP addresses, not host names.        

- For a host value specified as an IPv4 address, a netmask can          be given to indicate how many address bits to use for the          network number. Netmask notation cannot be used for IPv6          addresses.    <br>The syntax is          *host_ip*/*netmask*.          For example:             

  ```
  CREATE USER 'david'@'198.51.100.0/255.255.255.0';

  ```

  This enables `david` to connect from any          client host having an IP address          *client_ip* for which the following          condition is true:        

  ```
  client_ip & netmask = host_ip

  ```

  That is, for the [`CREATE USER`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#create-user)          statement just shown:        

  ```
  client_ip & 255.255.255.0 = 198.51.100.0
  ```

  IP addresses that satisfy this condition range from          `198.51.100.0` to          `198.51.100.255`.        

  A netmask typically begins with bits set to 1, followed by          bits set to 0. Examples:

  - `198.0.0.0/255.0.0.0`: Any host on the              198 class A network            
  - `198.51.100.0/255.255.0.0`: Any host on              the 198.51 class B network            
  - `198.51.100.0/255.255.255.0`: Any host on              the 198.51.100 class C network            
  - `198.51.100.1`: Only the host with this              specific IP address

​      

The server performs matching of host values in account names      against the client host using the value returned by the system DNS      resolver for the client host name or IP address. Except in the      case that the account host value is specified using netmask      notation, the server performs this comparison as a string match,      even for an account host value given as an IP address. This means      that you should specify account host values in the same format      used by DNS. Here are examples of problems to watch out for:

- Suppose that a host on the local network has a fully qualified          name of `host1.example.com`. If DNS returns  name lookups for this host as          `host1.example.com`, use that name in account  host values. If DNS returns just `host1`, use  `host1`  instead.        
- If DNS returns the IP address for a given host as          `198.51.100.2`, that will match an account          host value of `198.51.100.2` but not          `198.051.100.2`. Similarly, it will match an          account host pattern like `198.51.100.%` but not `198.051.100.%`.

​      

To avoid problems like these, it is advisable to check the format      in which your DNS returns host names and addresses. Use values in      the same format in MySQL account names.



### 6.2.4 Access Control, Stage 1: Connection Verification

​      When you attempt to connect to a MySQL server, the server accepts      or rejects the connection based on your identity and whether you      can verify your identity by supplying the correct password. If      not, the server denies access to you completely. Otherwise, the      server accepts the connection, and then enters Stage 2 and waits      for requests.    

​      Credential checking is performed using the three      `user` table scope columns      (`Host`, `User`, and      `Password`). The server accepts the connection      only if the `Host` and `User`      columns in some `user` table row match the client      host name and user name and the client supplies the password      specified in that row. The rules for permissible      `Host` and `User` values are      given in [Section 6.2.3, “Specifying Account Names”](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/security.html#account-names).    

​      Your identity is based on two pieces of information:

- ​          The client host from which you connect        
- ​          Your MySQL user name

​      If the `User` column value is nonblank, the user      name in an incoming connection must match exactly. If the      `User` value is blank, it matches any user name.      If the `user` table row that matches an incoming      connection has a blank user name, the user is considered to be an      anonymous user with no name, not a user with the name that the      client actually specified. This means that a blank user name is      used for all further access checking for the duration of the      connection (that is, during Stage 2).    

​      The `Password` column can be blank. This is not a      wildcard and does not mean that any password matches. It means      that the user must connect without specifying a password. If the      server authenticates a client using a plugin, the authentication      method that the plugin implements may or may not use the password      in the `Password` column. In this case, it is      possible that an external password is also used to authenticate to      the MySQL server.    

​      Nonblank `Password` values in the      `user` table represent encrypted passwords. MySQL      does not store passwords in cleartext form for anyone to see.      Rather, the password supplied by a user who is attempting to      connect is encrypted (using the      [`PASSWORD()`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/functions.html#function_password) function). The encrypted      password then is used during the connection process when checking      whether the password is correct. This is done without the      encrypted password ever traveling over the connection. See      [Section 6.3.1, “User Names and Passwords”](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/security.html#user-names).    

​      From MySQL's point of view, the encrypted password is the      *real* password, so you should never give      anyone access to it. In particular, *do not give      nonadministrative users read access to tables in the      mysql database*.    

​      The following table shows how various combinations of      `User` and `Host` values in the      `user` table apply to incoming connections.

| `User` Value | `Host` Value                   | Permissible Connections                  |
| ------------ | ------------------------------ | ---------------------------------------- |
| `'fred'`     | `'h1.example.net'`             | `fred`, connecting from              `h1.example.net` |
| `''`         | `'h1.example.net'`             | Any user, connecting from `h1.example.net` |
| `'fred'`     | `'%'`                          | `fred`, connecting from any host         |
| `''`         | `'%'`                          | Any user, connecting from any host       |
| `'fred'`     | `'%.example.net'`              | `fred`, connecting from any host in the              `example.net` domain |
| `'fred'`     | `'x.example.%'`                | `fred`, connecting from              `x.example.net`,              `x.example.com`,              `x.example.edu`, and so on; this is              probably not useful |
| `'fred'`     | `'198.51.100.177'`             | `fred`, connecting from the host with IP address              `198.51.100.177` |
| `'fred'`     | `'198.51.100.%'`               | `fred`, connecting from any host in the`198.51.100` class C subnet |
| `'fred'`     | `'198.51.100.0/255.255.255.0'` | Same as previous example                 |

​      It is possible for the client host name and user name of an      incoming connection to match more than one row in the      `user` table. The preceding set of examples      demonstrates this: Several of the entries shown match a connection      from `h1.example.net` by `fred`.    

​      When multiple matches are possible, the server must determine      which of them to use. It resolves this issue as follows:

- ​          Whenever the server reads the `user` table          into memory, it sorts the rows.        
- ​          When a client attempts to connect, the server looks through          the rows in sorted order.        
- ​          The server uses the first row that matches the client host          name and user name.

​      The server uses sorting rules that order rows with the      most-specific `Host` values first. Literal host      names and IP addresses are the most specific. (The specificity of      a literal IP address is not affected by whether it has a netmask,      so `198.51.100.13` and      `198.51.100.0/255.255.255.0` are considered      equally specific.) The pattern `'%'` means      “any host” and is least specific. The empty string      `''` also means “any host” but sorts      after `'%'`. Rows with the same      `Host` value are ordered with the most-specific      `User` values first (a blank      `User` value means “any user” and is      least specific). For rows with equally-specific      `Host` and `User` values, the      order is indeterminate.    

​      To see how this works, suppose that the `user`      table looks like this:    

```
+-----------+----------+-
| Host      | User     | ...
+-----------+----------+-
| %         | root     | ...
| %         | jeffrey  | ...
| localhost | root     | ...
| localhost |          | ...
+-----------+----------+-

```

​      When the server reads the table into memory, it sorts the rows      using the rules just described. The result after sorting looks      like this:    

```
+-----------+----------+-
| Host      | User     | ...
+-----------+----------+-
| localhost | root     | ...
| localhost |          | ...
| %         | jeffrey  | ...
| %         | root     | ...
+-----------+----------+-

```

​      When a client attempts to connect, the server looks through the      sorted rows and uses the first match found. For a connection from      `localhost` by `jeffrey`, two of      the rows from the table match: the one with      `Host` and `User` values of      `'localhost'` and `''`, and the      one with values of `'%'` and      `'jeffrey'`. The `'localhost'`      row appears first in sorted order, so that is the one the server      uses.    

​      Here is another example. Suppose that the `user`      table looks like this:    

```
+----------------+----------+-
| Host           | User     | ...
+----------------+----------+-
| %              | jeffrey  | ...
| h1.example.net |          | ...
+----------------+----------+-

```

​      The sorted table looks like this:    

```
+----------------+----------+-
| Host           | User     | ...
+----------------+----------+-
| h1.example.net |          | ...
| %              | jeffrey  | ...
+----------------+----------+-

```

​      A connection by `jeffrey` from      `h1.example.net` is matched by the first row,      whereas a connection by `jeffrey` from any host      is matched by the second.

Note

​        It is a common misconception to think that, for a given user        name, all rows that explicitly name that user are used first        when the server attempts to find a match for the connection.        This is not true. The preceding example illustrates this, where        a connection from `h1.example.net` by        `jeffrey` is first matched not by the row        containing `'jeffrey'` as the        `User` column value, but by the row with no        user name. As a result, `jeffrey` is        authenticated as an anonymous user, even though he specified a        user name when connecting.

​      If you are able to connect to the server, but your privileges are      not what you expect, you probably are being authenticated as some      other account. To find out what account the server used to      authenticate you, use the      [`CURRENT_USER()`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/functions.html#function_current-user) function. (See      [Section 12.14, “Information Functions”](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/functions.html#information-functions).) It returns a value in      `*user_name*@*host_name*`      format that indicates the `User` and      `Host` values from the matching      `user` table row. Suppose that      `jeffrey` connects and issues the following      query:    

```
mysql> SELECT CURRENT_USER();
+----------------+
| CURRENT_USER() |
+----------------+
| @localhost     |
+----------------+

```

​      The result shown here indicates that the matching      `user` table row had a blank      `User` column value. In other words, the server      is treating `jeffrey` as an anonymous user.    

​      Another way to diagnose authentication problems is to print out      the `user` table and sort it by hand to see where      the first match is being made.