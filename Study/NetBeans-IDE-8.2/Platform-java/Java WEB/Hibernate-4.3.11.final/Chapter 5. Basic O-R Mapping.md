# Chapter 5. Basic O/R Mapping
[TOC]
---

## 5.1. Mapping declaration

Object/relational mappings can be defined in three approaches:

* using Java 5 annotations (via the Java Persistence 2 annotations)
* using JPA 2 XML deployment descriptors (described in chapter XXX)
* using the Hibernate legacy XML files approach known as hbm.xml

Annotations are split in two categories, the logical mapping annotations (describing the object model, the association between two entities etc.) and the physical mapping annotations (describing the physical schema, tables, columns, indexes, etc). We will mix annotations from both categories in the following code examples.

JPA annotations are in the `javax.persistence.*` package. Hibernate specific extensions are in `org.hibernate.annotations.*`. You favorite IDE can auto-complete annotations and their attributes for you (even without a specific "JPA" plugin, since JPA annotations are plain Java 5 annotations).

Here is an example of mapping:
```java
package eg;

@Entity
@Table(name = "cats")
@Inheritance(strategy = SINGLE_TABLE)
@DiscriminatorValue("C")
@DiscriminatorColumn(name = "subclass", discriminatorType = CHAR)
public class Cat {

    @Id
    @GeneratedValue
    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    private Integer id;

    public BigDecimal getWeight() {
        return weight;
    }

    public void setWeight(BigDecimal weight) {
        this.weight = weight;
    }

    private BigDecimal weight;

    @Temporal(DATE)
    @NotNull
    @Column(updatable = false)
    public Date getBirthdate() {
        return birthdate;
    }

    public void setBirthdate(Date birthdate) {
        this.birthdate = birthdate;
    }

    private Date birthdate;

    @org.hibernate.annotations.Type(type = "eg.types.ColorUserType")
    @NotNull
    @Column(updatable = false)
    public ColorType getColor() {
        return color;
    }

    public void setColor(ColorType color) {
        this.color = color;
    }

    private ColorType color;

    @NotNull
    @Column(updatable = false)
    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    private String sex;

    @NotNull
    @Column(updatable = false)
    public Integer getLitterId() {
        return litterId;
    }

    public void setLitterId(Integer litterId) {
        this.litterId = litterId;
    }

    private Integer litterId;

    @ManyToOne
    @JoinColumn(name = "mother_id", updatable = false)
    public Cat getMother() {
        return mother;
    }

    public void setMother(Cat mother) {
        this.mother = mother;
    }

    private Cat mother;

    @OneToMany(mappedBy = "mother")
    @OrderBy("litterId")
    public Set<Cat> getKittens() {
        return kittens;
    }

    public void setKittens(Set<Cat> kittens) {
        this.kittens = kittens;
    }

    private Set<Cat> kittens = new HashSet<Cat>();
}

@Entity
@DiscriminatorValue("D")
public class DomesticCat extends Cat {

    public String getName() {
        return name;
    }

  public void setName(String name) { this.name = name }

    private String name;
}

@Entity
public class Dog { ... }
```

The legacy hbm.xml approach uses an XML schema designed to be readable and hand-editable. The mapping language is Java-centric, meaning that mappings are constructed around persistent class declarations and not table declarations.

Please note that even though many Hibernate users choose to write the XML by hand, a number of tools exist to generate the mapping document. These include XDoclet, Middlegen and AndroMDA.

Here is an example mapping:
```xml
<?xml version="1.0"?>
<!DOCTYPE hibernate-mapping PUBLIC
      "-//Hibernate/Hibernate Mapping DTD 3.0//EN"
          "http://www.hibernate.org/dtd/hibernate-mapping-3.0.dtd">

<hibernate-mapping package="eg">

        <class name="Cat"
            table="cats"
            discriminator-value="C">

                <id name="id">
                        <generator class="native"/>
                </id>

                <discriminator column="subclass"
                    type="character"/>

                <property name="weight"/>

                <property name="birthdate"
                    type="date"
                    not-null="true"
                    update="false"/>

                <property name="color"
                    type="eg.types.ColorUserType"
                    not-null="true"
                    update="false"/>

                <property name="sex"
                    not-null="true"
                    update="false"/>

                <property name="litterId"
                    column="litterId"
                    update="false"/>

                <many-to-one name="mother"
                    column="mother_id"
                    update="false"/>

                <set name="kittens"
                    inverse="true"
                    order-by="litter_id">
                        <key column="mother_id"/>
                        <one-to-many class="Cat"/>
                </set>

                <subclass name="DomesticCat"
                    discriminator-value="D">

                        <property name="name"
                            type="string"/>

                </subclass>

        </class>

        <class name="Dog">
                <!-- mapping for Dog could go here -->
        </class>

</hibernate-mapping>
```
We will now discuss the concepts of the mapping documents (both annotations and XML). We will only describe, however, the document elements and attributes that are used by Hibernate at runtime. The mapping document also contains some extra optional attributes and elements that affect the database schemas exported by the schema export tool (for example, the not-null attribute).



### 5.1.1. Entity

An entity is a regular Java object (aka POJO) which will be persisted by Hibernate.

To mark an object as an entity in annotations, use the `@Entity `annotation.
```java
@Entity
public class Flight implements Serializable {
    Long id;

    @Id
    public Long getId() { return id; }
    
    public void setId(Long id) { this.id = id; }
}         
```
That's pretty much it, the rest is optional. There are however any options to tweak your entity mapping, let's explore them.

`@Table` lets you define the table the entity will be persisted into. If undefined, the table name is the unqualified class name of the entity. You can also optionally define the catalog, the schema as well as unique constraints on the table.

```java
@Entity
@Table(name="TBL_FLIGHT", 
       schema="AIR_COMMAND", 
       uniqueConstraints=
           @UniqueConstraint(
               name="flight_number", 
               columnNames={"comp_prefix", "flight_number"} ) )
public class Flight implements Serializable {
    @Column(name="comp_prefix")
    public String getCompagnyPrefix() { return companyPrefix; }

    @Column(name="flight_number")
    public String getNumber() { return number; }
}
```

The constraint name is optional (generated if left undefined). The column names composing the constraint correspond to the column names as defined before the Hibernate `NamingStrategyDelegator` is applied.

> **Tip :**
>
> Be sure to use the database-level column names for the `columnNames` property of a `@UniqueConstraint`. For example, whilst for simple types the database-level column name may be the same as the entity-level property name, this is often not the case for relational properties. 



`@Entity.name` lets you define the shortcut name of the entity you can use in JP-QL and HQL queries. It defaults to the unqualified class name of the class.

Hibernate goes beyond the JPA specification and provide additional configurations. Some of them are hosted on `@org.hibernate.annotations.Entity`:



### 5.1.2. Identifiers

Mapped classes must declare the primary key column of the database table. Most classes will also have a JavaBeans-style property holding the unique identifier of an instance.



Mark the identifier property with `@Id`.

```java
@Entity
public class Person {
   @Id Integer getId() { ... }
   ...
}
```



In `hbm.xml`, use the `<id>` element which defines the mapping from that property to the primary key column.

```xml
<id
        name="propertyName"                              
        type="typename"                       
        column="column_name"                             
        unsaved-value="null|any|none|undefined|id_value"   
        access="field|property|ClassName">                 
        node="element-name|@attribute-name|element/@attribute|."

        <generator class="generatorClass"/>
</id>
```

`name` (optional): the name of the identifier property.

`type` (optional): a name that indicates the Hibernate type.

`column` (optional - defaults to the property name): the name of the primary key column.

`unsaved-value` (optional - defaults to a "sensible" value): an identifier property value that indicates an instance is newly instantiated (unsaved), distinguishing it from detached instances that were saved or loaded in a previous session.

`access` (optional - defaults to `property`): the strategy Hibernate should use for accessing the property value.

If the `name` attribute is missing, it is assumed that the class has no identifier property.

The `unsaved-value` attribute is almost never needed in Hibernate and indeed has no corresponding element in annotations.

You can also declare the identifier as a composite identifier. This allows access to legacy data with composite keys. Its use is strongly discouraged for anything else.