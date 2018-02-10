[TOC]

# 1-Introduction

## What about

Welcome to the NetBeans `E-commerce` Tutorial. In this multi-part tutorial, you learn how to create a simple yet effective e-commerce application that demonstrates various important features of `Java web` and `EE` development.



## What will acquire



Taking the time to master the IDE will ultimately lead you to become more efficient and versatile as a developer. While you work through the tutorial units, you'll learn how to make best use of the IDE's facilities and tools. These include:

- Editor support for different languages: syntax highlighting, code completion, API documentation support, keyboard shortcuts, refactoring capabilities, and code templates
- Window system: Projects, Files and Services windows, the Tasks window, Javadoc window, HTTP Monitor, Navigator and Palette
- Integration with other services: automatic deployment to a registered server, database connectivity, browser interoperability
- Development tools: Debugger, Profiler, HTTP Server Monitor, Local History support, and a graphical Diff Viewer


## Who this Tutorial is for

The content of this tutorial caters to four demographics:

- Java developers interested in expanding their skill set to include Java EE technologies
- Newcomers to the NetBeans IDE wanting to try out its development environment
- Web developers wanting to see how Java compares to other web-based technologies
- Students wanting to understand the nuts and bolts a simple e-commerce application, and how its development could apply to a real-world use-case

If you fall into any of these categories, this tutorial will be helpful to you. Depending on your background, you may find that certain tutorial units are more difficult to grasp than others. Understanding how technologies work is key to leveraging the IDE for your purposes. Therefore, if you are really interested in learning the technologies involved, you may find that this tutorial works best as a companion to the Java EE Tutorial. For each tutorial unit, make best use of the provided links to relevant areas in the Java EE Tutorial, as well as to other useful resources.

## What this Tutorial Covers

The application that you develop in this tutorial involves numerous concepts, technologies, and tooling components:

- Concepts
  - Front-end development
  - Web application project structure
  - Data modeling
  - Database connectivity
  - Object-relational mapping
  - Session management
  - Transactional business logic
  - Client and server-side validation
  - Localization
  - Web application security
  - Design patterns, including Model-View-Controller (MVC) and Session Facade
- Technologies
  - HTML, CSS, and JavaScript technologies
  - Servlet and JavaServer Pages (JSP) technologies
  - Enterprise JavaBeans (EJB) technology
  - Java Persistence API (JPA)
  - The JavaServer Pages Standard Tag Library (JSTL)
  - Java Database Connectivity (JDBC)
- Development Tools
  - NetBeans IDE
  - GlassFish, a Java EE application server
  - MySQL, a relational database management server (RDBMS)
  - MySQL WorkBench, a visual database design tool


## What is an E-commerce Application?

The term e-commerce, as we think of it today, refers to the buying and selling of goods or services over the Internet. For example, you may think of Amazon, which provides online shopping for various product categories, such as books, music, and electronics. This form of e-commerce is known as electronic retailing, or e-tailing, and usually involves the transportation of physical items. It is also referred to as business-to-customer, or B2C. Other well-known forms include:

  - **Consumer-to-consumer (C2C)**: Transactions taking place between individuals, usually through a third-party site such as an online auction. A typical example of C2C commerce is eBay.
  - **Business-to-business (B2B)**: Trade occurring between businesses, e.g., between a retailer and wholesaler, or between a wholesaler and manufacturer.
  - **Business-to-government (B2G):** Trade occurring between businesses and government agencies.

This tutorial focuses on business-to-customer (B2C) e-commerce, and applies the typical scenario of a small retail store seeking to create a website enabling customers to shop online. Software that accommodates a B2C scenario generally consists of two components:

- **Store Front:** The website that is accessed by customers, enabling them to purchase goods over the Internet. Data from the store catalog is typically maintained in a database, and pages requiring this data are generated dynamically.
- **Administration Console:** A password-protected area that is accessed over a secure connection by store staff for purposes of online management. This typically involves CRUD (create read update delete) access to the store catalog, management of discounts, shipping and payment options, and review of customer orders.

