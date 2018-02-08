# Chapter 6. Types
[TOC]
---

As an Object/Relational Mapping solution, Hibernate deals with both the Java and JDBC representations of application data. An online catalog application, for example, most likely has Product object with a number of attributes such as a sku, name, etc. For these individual attributes, Hibernate must be able to read the values out of the database and write them back. This 'marshalling' is the function of a Hibernate type, which is an implementation of the `org.hibernate.type.Type` interface. In addition, a Hibernate type describes various aspects of behavior of the Java type such as "how is equality checked?" or "how are values cloned?".

> **Important : **
> A Hibernate type is neither a Java type nor a SQL datatype; it provides a information about both.<br> When you encounter the term type in regards to Hibernate be aware that usage might refer to the Java type, the SQL/JDBC type or the Hibernate type.



**Hibernate categorizes types into two high-level groups: value types and entity types.** 



## 6.1. Value types

The main distinguishing characteristic of a value type is the fact that they do not define their own lifecycle. We say that they are "owned" by something else (specifically an entity, as we will see later) which defines their lifecycle. 

Value types are further classified into 3 sub-categories: basic types (see *Section 6.1.1, “Basic value types”*), composite types (see *Section 6.1.2, “Composite types”*) amd collection types (see *Section 6.1.3, “Collection types”*).

### 6.1.1. Basic value types

The norm for basic value types is that they map a single database value (column) to a single, non-aggregated Java type. Hibernate provides a number of built-in basic types, which we will present in the following sections by the Java type. Mainly these follow the natural mappings recommended in the JDBC specification. We will later cover how to override these mapping and how to provide and use alternative type mappings.

#### 6.1.1.1. java.lang.String

`org.hibernate.type.StringType`
Maps a string to the JDBC `VARCHAR`  type. This is the standard mapping for a string if no Hibernate type is specified.

Registered under string and java.lang.String in the type registry (see *Section 6.5, “Type registry”*).



`org.hibernate.type.MaterializedClob`
Maps a string to a JDBC CLOB type

Registered under materialized_clob in the type registry (see Section 6.5, “Type registry”).



`org.hibernate.type.TextType`
Maps a string to a JDBC LONGVARCHAR type

Registered under text in the type registry (see Section 6.5, “Type registry”).



#### 6.1.1.2. java.lang.Character (or char primitive)

`org.hibernate.type.CharacterType`

Maps a char or java.lang.Character to a JDBC CHAR

Registered under char and java.lang.Character in the type registry (see Section 6.5, “Type registry”).

#### 6.1.1.3. java.lang.Boolean (or boolean primitive)

`org.hibernate.type.BooleanType`

Maps a boolean to a JDBC BIT type

Registered under boolean and java.lang.Boolean in the type registry (see Section 6.5, “Type registry”).



`org.hibernate.type.NumericBooleanType`
Maps a boolean to a JDBC INTEGER type as 0 = false, 1 = true

Registered under numeric_boolean in the type registry (see Section 6.5, “Type registry”).

`org.hibernate.type.YesNoType`

Maps a boolean to a JDBC CHAR type as ('N' | 'n') = false, ( 'Y' | 'y' ) = true

Registered under yes_no in the type registry (see Section 6.5, “Type registry”).

`org.hibernate.type.TrueFalseType`

Maps a boolean to a JDBC CHAR type as ('F' | 'f') = false, ( 'T' | 't' ) = true

Registered under true_false in the type registry (see Section 6.5, “Type registry”).


#### 6.1.1.4. java.lang.Byte (or byte primitive)

org.hibernate.type.ByteType

Maps a byte or java.lang.Byte to a JDBC TINYINT
Registered under byte and java.lang.Byte in the type registry (see Section 6.5, “Type registry”).

#### 6.1.1.5. java.lang.Short (or short primitive)

`org.hibernate.type.ShortType`
Maps a short or java.lang.Short to a JDBC SMALLINT
Registered under short and java.lang.Short in the type registry (see Section 6.5, “Type registry”).


#### 6.1.1.6. java.lang.Integer (or int primitive)

`org.hibernate.type.IntegerTypes`
Maps an `int` or `java.lang.Integer` to a JDBC `INTEGER`
Registered under `int` and `java.lang.Integer` in the type registry (see Section 6.5, “Type registry”).


#### 6.1.1.7. java.lang.Long (or long primitive)

org.hibernate.type.LongType

    Maps a long or java.lang.Long to a JDBC BIGINT

    Registered under long and java.lang.Long in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.8. java.lang.Float (or float primitive)

org.hibernate.type.FloatType

    Maps a float or java.lang.Float to a JDBC FLOAT

    Registered under float and java.lang.Float in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.9. java.lang.Double (or double primitive)

org.hibernate.type.DoubleType

    Maps a double or java.lang.Double to a JDBC DOUBLE

    Registered under double and java.lang.Double in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.10. java.math.BigInteger

org.hibernate.type.BigIntegerType

    Maps a java.math.BigInteger to a JDBC NUMERIC

    Registered under big_integer and java.math.BigInteger in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.11. java.math.BigDecimal

org.hibernate.type.BigDecimalType

    Maps a java.math.BigDecimal to a JDBC NUMERIC

    Registered under big_decimal and java.math.BigDecimal in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.12. java.util.Date or java.sql.Timestamp

org.hibernate.type.TimestampType

    Maps a java.sql.Timestamp to a JDBC TIMESTAMP

    Registered under timestamp, java.sql.Timestamp and java.util.Date in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.13. java.sql.Time

org.hibernate.type.TimeType

    Maps a java.sql.Time to a JDBC TIME

    Registered under time and java.sql.Time in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.14. java.sql.Date

org.hibernate.type.DateType

    Maps a java.sql.Date to a JDBC DATE

    Registered under date and java.sql.Date in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.15. java.util.Calendar

org.hibernate.type.CalendarType

    Maps a java.util.Calendar to a JDBC TIMESTAMP

    Registered under calendar, java.util.Calendar and java.util.GregorianCalendar in the type registry (see Section 6.5, “Type registry”).
org.hibernate.type.CalendarDateType

    Maps a java.util.Calendar to a JDBC DATE

    Registered under calendar_date in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.16. java.util.Currency

org.hibernate.type.CurrencyType

    Maps a java.util.Currency to a JDBC VARCHAR (using the Currency code)

    Registered under currency and java.util.Currency in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.17. java.util.Locale

org.hibernate.type.LocaleType

    Maps a java.util.Locale to a JDBC VARCHAR (using the Locale code)

    Registered under locale and java.util.Locale in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.18. java.util.TimeZone

org.hibernate.type.TimeZoneType

    Maps a java.util.TimeZone to a JDBC VARCHAR (using the TimeZone ID)

    Registered under timezone and java.util.TimeZone in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.19. java.net.URL

org.hibernate.type.UrlType

    Maps a java.net.URL to a JDBC VARCHAR (using the external form)

    Registered under url and java.net.URL in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.20. java.lang.Class

org.hibernate.type.ClassType

    Maps a java.lang.Class to a JDBC VARCHAR (using the Class name)

    Registered under class and java.lang.Class in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.21. java.sql.Blob

org.hibernate.type.BlobType

    Maps a java.sql.Blob to a JDBC BLOB

    Registered under blob and java.sql.Blob in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.22. java.sql.Clob

org.hibernate.type.ClobType

    Maps a java.sql.Clob to a JDBC CLOB

    Registered under clob and java.sql.Clob in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.23. byte[]

org.hibernate.type.BinaryType

    Maps a primitive byte[] to a JDBC VARBINARY

    Registered under binary and byte[] in the type registry (see Section 6.5, “Type registry”).
org.hibernate.type.MaterializedBlobType

    Maps a primitive byte[] to a JDBC BLOB

    Registered under materialized_blob in the type registry (see Section 6.5, “Type registry”).
org.hibernate.type.ImageType

    Maps a primitive byte[] to a JDBC LONGVARBINARY

    Registered under image in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.24. Byte[]

org.hibernate.type.BinaryType

    Maps a java.lang.Byte[] to a JDBC VARBINARY

    Registered under wrapper-binary, Byte[] and java.lang.Byte[] in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.25. char[]

org.hibernate.type.CharArrayType

    Maps a char[] to a JDBC VARCHAR

    Registered under characters and char[] in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.26. Character[]

org.hibernate.type.CharacterArrayType

    Maps a java.lang.Character[] to a JDBC VARCHAR

    Registered under wrapper-characters, Character[] and java.lang.Character[] in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.27. java.util.UUID

org.hibernate.type.UUIDBinaryType

    Maps a java.util.UUID to a JDBC BINARY

    Registered under uuid-binary and java.util.UUID in the type registry (see Section 6.5, “Type registry”).
org.hibernate.type.UUIDCharType

    Maps a java.util.UUID to a JDBC CHAR (though VARCHAR is fine too for existing schemas)

    Registered under uuid-char in the type registry (see Section 6.5, “Type registry”).
org.hibernate.type.PostgresUUIDType

    Maps a java.util.UUID to the PostgreSQL UUID data type (through Types#OTHER which is how the PostgreSQL JDBC driver defines it).

    Registered under pg-uuid in the type registry (see Section 6.5, “Type registry”).
#### 6.1.1.28. java.io.Serializable

org.hibernate.type.SerializableType

    Maps implementors of java.lang.Serializable to a JDBC VARBINARY

    Unlike the other value types, there are multiple instances of this type. It gets registered once under java.io.Serializable. Additionally it gets registered under the specific java.io.Serializable implementation class names.
### 6.1.2. Composite types

> **Note:**
>
> The Java Persistence API calls these embedded types, while Hibernate traditionally called them components. Just be aware that both terms are used and mean the same thing in the scope of discussing Hibernate.

Components represent aggregations of values into a single Java type. For example, you might have an Address class that aggregates street, city, state, etc information or a Name class that aggregates the parts of a person's Name. In many ways a component looks exactly like an entity. They are both (generally speaking) classes written specifically for the application. They both might have references to other application-specific classes, as well as to collections and simple JDK types. As discussed before, the only distinguishing factory is the fact that a component does not own its own lifecycle nor does it define an identifier.

### 6.1.3. Collection types

> **Important**: 
>
> It is critical understand that we mean the collection itself, not its contents. The contents of the collection can in turn be basic, component or entity types (though not collections), but the collection itself is owned.

Collections are covered in *Chapter 7, Collection mapping*.



## 6.2. Entity types

The definition of entities is covered in detail in Chapter 4, Persistent Classes. For the purpose of this discussion, it is enough to say that entities are (generally application-specific) classes which correlate to rows in a table. Specifically they correlate to the row by means of a unique identifier. Because of this unique identifier, entities exist independently and define their own lifecycle. As an example, when we delete a Membership, both the User and Group entities remain.

> **Note**:
>
> This notion of entity independence can be modified by the application developer using the concept of cascades. Cascades allow certain operations to continue (or "cascade") across an association from one entity to another. Cascades are covered in detail in *Chapter 8, Association Mappings* .