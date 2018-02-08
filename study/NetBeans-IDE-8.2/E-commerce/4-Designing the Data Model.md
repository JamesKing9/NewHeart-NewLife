[TOC]
# 4-Designing the Data Model

This tutorial unit focuses on data modeling, or the process of creating a conceptual model of your storage system by identifying and defining the entities that your system requires, and their relationships to one another. The data model should contain all the logical and physical design parameters required to generate a script using the Data Definition Language (DDL), which can then be used to create a database.

In this unit, you work primarily with [MySQL Workbench](), a graphical tool that enables you to create data models, reverse-engineer SQL scripts into visual representations, forward-engineer data models into database schemata, and synchronize models with a running MySQL database server.

You begin by creating an entity-relationship diagram to represent the data model for the AffableBean application. When you have completed identifying and defining all entities and the relationships that bind them, you use Workbench to forward-engineer and run a DDL script that converts the data model into a database schema. Finally, you connect to the new schema from the NetBeans IDE.

You can view a live demo of the application that you build in this tutorial: NetBeans E-commerce Tutorial Demo Application.

[affablebean_schema_creation.sql](./affablebean_schema_creation.sql) 



## Identifying Entities for the Data Model

In the real world, you may not have the luxury of designing the data model for your application. For example, your task may be to develop an application on top of an existing database system. Provided you do not have a data model to base your application on, creating one should be one of the first design steps you take before embarking on development. Creating a data model involves identifying the objects, or entities, required by your system and defining the relationships between them.

To begin identifying the entities we need for the data model, re-examine the use-case presented in Designing the Application. Search for commonly-occurring nouns. For example:

> Use-Case
>
> Customer visits the welcome page and selects a product category. Customer browses products within the selected category page, then adds a product to his or her shopping cart. Customer continues shopping and selects a different category. Customer adds several products from this category to shopping cart. Customer selects 'view cart' option and updates quantities for cart products in the cart page. Customer verifies shopping cart contents and proceeds to checkout. In the checkout page, customer views the cost of the order and other information, fills in personal data, then submits his or her details. The order is processed and customer is taken to a confirmation page. The confirmation page provides a unique reference number for tracking the customer order, as well as a summary of the order.


The text highlighted above in bold indicates the candidates that we can consider for the data model. Upon closer inspection, you may deduce that the shopping cart does not need to be included, since the data it provides (i.e., products and their quantities) is equally offered by a customer order once it is processed. In fact, as will be demonstrated in Unit 8, Managing Sessions, the shopping cart merely serves as a mechanism that retains a user session temporarily while the customer shops online. We can therefore settle on the following list:

- customer
- category
- product
- order

With these four entities, we can begin constructing an entity-relationship diagram (ERD).

> Note: In this tutorial, we create a database schema from the ERD, then use the IDE's EclipseLink support to generate JPA entity classes from the existing database. (EclipseLink and the Java Persistence API (JPA) are covered in Unit 7, Adding Entity Classes and Session Beans.) This approach is described as bottom up development. An equally viable alternative is the top down approach.
>
> - Top down: In top down development, you start with an existing Java implementation of the domain model, and have complete freedom with respect to the design of the database schema. You must create mapping metadata (i.e., annotations used in JPA entity classes), and can optionally use a persistence tool to automatically generate the schema.
> - Bottom up: Bottom up development begins with an existing database schema. In this case, the easiest way to proceed is to use forward-engineering tools to extract metadata from the schema and generate annotated Java source code (JPA entity classes).

For more information on top down and bottom up design strategies, see Data modeling: Modeling methodologies [Wikipedia].

