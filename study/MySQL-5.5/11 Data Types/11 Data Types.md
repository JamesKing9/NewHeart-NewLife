# Chapter 11 Data Types

MySQL supports a number of SQL data types in several categories: 
* numeric types, 
* date and time types, 
* string (character and byte) types, 
* and spatial types. 

This chapter provides an overview of these data types, a more detailed description of the properties of the types in each category, and a summary of the data type storage requirements. The initial overview is intentionally brief. The more detailed descriptions later in the chapter should be consulted for additional information about particular data types, such as the permissible formats in which you can specify values.

 Data type descriptions use these conventions:

-    *M* indicates the maximum display width for integer types. For floating-point and fixed-point types, *M* is the total number of digits that can be stored (the precision). For string types, *M* is the maximum length. The maximum permissible value of *M* depends on the data type.
-    *D* applies to floating-point and fixed-point types and indicates the number of digits following the decimal point (the scale). The maximum possible value is 30, but should be no greater than *M*−2.
-    Square brackets (`[` and `]`) indicate optional parts of type definitions.