# Chapter 4. Persistent Classes

[TOC]
---

 Persistent classes are classes in an application that implement the entities of the business problem (e.g. Customer and Order in an E-commerce application). The term "persistent" here means that the classes are able to be persisted, not that they are in the persistent state (see Section 11.1, “Hibernate object states” for discussion).

Hibernate works best if these classes follow some simple rules, also known as the Plain Old Java Object (POJO) programming model. However, none of these rules are hard requirements. Indeed, Hibernate assumes very little about the nature of your persistent objects. You can express a domain model in other ways (using trees of java.util.Map instances, for example). 



## 4.1. A simple POJO example

Example 4.1. Simple POJO representing a cat
```java
package eg;
import java.util.Set;
import java.util.Date;

public class Cat {
	private Long id; // identifier

	private Date birthdate;
	private Color color;
	private char sex;
	private float weight;
    private int litterId;

    private Cat mother;
    private Set kittens = new HashSet();
    
    private void setId(Long id) {
        this.xml:id=id;
    }
    public Long getId() {
        return id;
    }
    
    void setBirthdate(Date date) {
        birthdate = date;
    }
    public Date getBirthdate() {
        return birthdate;
    }
    
    void setWeight(float weight) {
        this.weight = weight;
    }
    public float getWeight() {
        return weight;
    }
    
    public Color getColor() {
        return color;
    }
    void setColor(Color color) {
        this.color = color;
    }
    
    void setSex(char sex) {
        this.sex=sex;
    }
    public char getSex() {
        return sex;
    }
    
    void setLitterId(int id) {
        this.litterId = id;
    }
    public int getLitterId() {
        return litterId;
    }
    
    void setMother(Cat mother) {
        this.mother = mother;
    }
    public Cat getMother() {
        return mother;
    }
    void setKittens(Set kittens) {
        this.kittens = kittens;
    }
    public Set getKittens() {
        return kittens;
    }
    
    // addKitten not needed by Hibernate
    public void addKitten(Cat kitten) {
        kitten.setMother(this);
    kitten.setLitterId( kittens.size() );
        kittens.add(kitten);
    }
}
```

The four main rules of persistent classes are explored in more detail in the following sections.



### 4.1.1. Implement a no-argument constructor

`Cat` has a no-argument constructor. All persistent classes must have a default constructor (which can be non-public) so that Hibernate can instantiate them using `java.lang.reflect.Constructor.newInstance()`. It is recommended that this constructor be defined with at least package visibility in order for runtime proxy generation to work properly.



### 4.1.2. Provide an identifier property

> **Note**
>
> Historically this was considered option. While still not (yet) enforced, this should be considered a deprecated feature as it will be completely required to provide an identifier property in an upcoming release.

`Cat` has a property named `id`. This property maps to the primary key column(s) of the underlying database table. The type of the identifier property can be any "basic" type.

> **Note**
>
> Identifiers do not necessarily need to identify column(s) in the database physically defined as a primary key. They should just identify columns that can be used to uniquely identify rows in the underlying table.

We recommend that you declare consistently-named identifier properties on persistent classes and that you use a `nullable` (i.e., non-primitive) type. 



### 4.1.3. Prefer non-final classes (semi-optional)

A central feature of Hibernate, proxies (lazy loading), depends upon the persistent class being either non-final, or the implementation of an interface that declares all public methods. You can persist final classes that do not implement an interface with Hibernate; you will not, however, be able to use proxies for lazy association fetching which will ultimately limit your options for performance tuning. To persist a final class which does not implement a "full" interface you must disable proxy generation. See Example 4.2, “Disabling proxies in hbm.xml” and Example 4.3, “Disabling proxies in annotations”. 



### 4.1.4. Declare accessors and mutators for persistent fields (optional)

`Cat` declares accessor methods for all its persistent fields. Many other ORM tools directly persist instance variables. It is better to provide an indirection between the relational schema and internal data structures of the class. By default, Hibernate persists JavaBeans style properties and recognizes method names of the form `getFoo`, `isFoo` and `setFoo`. If required, you can switch to direct field access for particular properties.

Properties need not be declared public. Hibernate can persist a property declared with `package`, `protected` or `private` visibility as well.



## 4.2. Implementing inheritance

A subclass must also observe the first and second rules. It inherits its identifier property from the superclass, Cat. For example:
```java
package eg;

public class DomesticCat extends Cat {
        private String name;

        public String getName() {
                return name;
        }
        protected void setName(String name) {
                this.name=name;
        }
}
```



## 4.3. Implementing equals() and hashCode()

You have to override the `equals()` and `hashCode()` methods if you:

* intend to put instances of persistent classes in a `Set` (the recommended way to represent many-valued associations); 
* intend to use reattachment of detached instances


Hibernate guarantees equivalence of persistent identity (database row) and Java identity only inside a particular session scope. When you mix instances retrieved in different sessions, you must implement equals() and hashCode() if you wish to have meaningful semantics for Sets.

The most obvious way is to implement equals()/hashCode() by comparing the identifier value of both objects. If the value is the same, both must be the same database row, because they are equal. If both are added to a Set, you will only have one element in the Set). Unfortunately, you cannot use that approach with generated identifiers. Hibernate will only assign identifier values to objects that are persistent; a newly created instance will not have any identifier value. Furthermore, if an instance is unsaved and currently in a Set, saving it will assign an identifier value to the object. If equals() and hashCode() are based on the identifier value, the hash code would change, breaking the contract of the Set. See the Hibernate website for a full discussion of this problem. This is not a Hibernate issue, but normal Java semantics of object identity and equality.

It is recommended that you implement `equals()` and `hashCode()` using *Business key equality*. *Business key equality* means that the `equals()` method compares only the properties that form the *business key*. It is a key that would identify our instance in the real world (a natural candidate key):

```java
public class Cat {

    ...
    public boolean equals(Object other) {
        if (this == other) return true;
        if ( !(other instanceof Cat) ) return false;

        final Cat cat = (Cat) other;

        if ( !cat.getLitterId().equals( getLitterId() ) ) return false;
        if ( !cat.getMother().equals( getMother() ) ) return false;

        return true;
    }

    public int hashCode() {
        int result;
        result = getMother().hashCode();
        result = 29 * result + getLitterId();
        return result;
    }

}
```




