This tutorial unit focuses on communication between the database and the application. You begin by adding sample data to the database and explore some of the features provided by the IDE's SQL editor. You set up a data source and connection pool on the GlassFish server, and proceed by creating a JSP page that tests the data source by performing a simple query on the database.

This unit also addresses how the application retrieves and displays images necessary for web presentation, and how to set context parameters and retrieve their values from web pages. Once you are certain the data source is working correctly, you apply JSTL's core and sql tag libraries to retrieve and display category and product images for the `index and category pages`.



## Adding Sample Data to the Database

## Creating a Connection Pool and Data Source

## Testing the Connection Pool and Data Source

## Setting Context Parameters

## Working with JSTL

In this final section, you combine these achievements to plug the product and category images into the application. In order to do so effectively, you need to begin taking advantage of the JavaServer Pages Standard Tag Library (JSTL).

Note that you do not have to worry about adding the JSTL JAR file (jstl-impl.jar) to your project's classpath because it already exists. When you created the AffableBean project and selected GlassFish as your development server, the libraries contained in the server were automatically added to your project's classpath. You can verify this in the Projects window by expanding the AffableBean project's Libraries > GlassFish Server 3 node to view all of the libraries provided by the server. 



## Troubleshooting