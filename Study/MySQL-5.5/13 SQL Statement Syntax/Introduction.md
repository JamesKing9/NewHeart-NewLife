[TOC]

## Introduction

>   **SQL**
>
>   The Structured Query Language that is standard for performing        database operations. Often divided into the categories        **DDL**,        **DML**, and        **queries**. 
>
>   MySQL includes some        additional statement categories such as        **replication**. See        [Chapter 9, *Language Structure*](file:///E:/github/refman-5.5-en.html-chapter/language-structure.html) for the building blocks of        SQL syntax, [Chapter 11, *Data Types*](file:///E:/github/refman-5.5-en.html-chapter/data-types.html) for the data types to        use for MySQL table columns, [Chapter 13, *SQL Statement Syntax*](file:///E:/github/refman-5.5-en.html-chapter/sql-syntax.html) for        details about SQL statements and their associated categories,        and [Chapter 12, *Functions and Operators*](file:///E:/github/refman-5.5-en.html-chapter/functions.html) for standard and MySQL-specific        functions to use in queries.      

> **DDL**
>
> *Data definition language*, a set of        **SQL** statements for manipulating        the database itself rather than individual table rows. Includes        all forms of the `CREATE`,        `ALTER`, and `DROP`        statements. Also includes the `TRUNCATE`        statement, because it works differently than a `DELETE        FROM *table_name*` statement,        even though the ultimate effect is similar.      
>
> DDL statements automatically        **commit** the current        **transaction**; they cannot be        **rolled back**.      
>
> ​        The `InnoDB`        [online DDL](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/glossary.html#glos_online_ddl) feature        enhances performance for [`CREATE        INDEX`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#create-index), [`DROP INDEX`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#drop-index), and        many types of [`ALTER TABLE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#alter-table)        operations. See [InnoDB and Online DDL](http://dev.mysql.com/doc/refman/5.6/en/innodb-online-ddl.html) for more        information. Also, the `InnoDB`        [file-per-table](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/glossary.html#glos_file_per_table)        setting can affect the behavior of [`DROP        TABLE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#drop-table) and [`TRUNCATE        TABLE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#truncate-table) operations.      
>
> ​        Contrast with **DML** and        **DCL**.      

> DML
>
> ​        Data manipulation language, a set of        **SQL** statements for performing        [`INSERT`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#insert),        [`UPDATE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#update), and        [`DELETE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#delete) operations. The        [`SELECT`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#select) statement is sometimes        considered as a DML statement, because the `SELECT ...        FOR UPDATE` form is subject to the same considerations        for **locking** as        [`INSERT`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#insert),        [`UPDATE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#update), and        [`DELETE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#delete).      
>
> ​        DML statements for an `InnoDB` table operate in        the context of a **transaction**,        so their effects can be        **committed** or        **rolled back** as a single unit.      
>
> ​        Contrast with **DDL** and        **DCL**.      



> DCL
>
> ​        Data control language, a set of        **SQL** statements for managing        privileges. In MySQL, consists of the        [`GRANT`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#grant) and        [`REVOKE`](file:///F:/Tech_doc/Mysql/refman-5.5-en.html-chapter/sql-syntax.html#revoke) statements. Contrast with        **DDL** and        **DML**.    