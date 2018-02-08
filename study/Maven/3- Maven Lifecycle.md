



## Specifying source encoding for platformindependent builds

Let us put our learning of properties to practical use. You will have observed the following
warning while building the simple project that we created in the **Building a simple project with**
**Maven recipe** in Chapter 1, Getting Started:
```shell
[WARNING] Using platform encoding (Cp1252 actually) to copy filtered
resources,
i.e. build is platform dependent!
```
Let us remove this **warning** if we really do not want the build to be platform dependent.

Let's specify the source encoding for platform-independent builds in our Maven project, by
performing the following steps:

1- Open the `pom` file we created previously.

2- Add the following code:
```xml
<properties>
	<project.build.sourceEncoding>
		UTF-8
	</project.build.sourceEncoding>
</properties>
```
3- Run the following command:
```shell
mvn package
```
4- Observe that the warning is no longer present.