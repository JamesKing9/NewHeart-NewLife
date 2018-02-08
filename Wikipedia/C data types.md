# C data types

From Wikipedia, the free encyclopedia

In the [C programming language](https://en.wikipedia.org/wiki/C_(programming_language)), **data types** are declarations for [memory locations](https://en.wikipedia.org/wiki/Memory_address) or [variables](https://en.wikipedia.org/wiki/Variable_(computer_science)) that determine the characteristics of the data that may be stored and the methods (operations) of processing that are permitted involving them.

The C language provides basic arithmetic types, such as [integer](https://en.wikipedia.org/wiki/Integer) and [real number](https://en.wikipedia.org/wiki/Real_number) types, and syntax to build array and compound types. Several [headers](https://en.wikipedia.org/wiki/Include_directive) in the [C standard library](https://en.wikipedia.org/wiki/C_standard_library) contain definitions of support types, that have additional properties, such as providing storage with an exact size, independent of the implementation.[[1\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-1)[[2\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99-2)



## Basic types

The C language provides the four basic arithmetic type specifiers *char*, *int*, *float* and *double*, and the modifiers *signed*, *unsigned*, *short* and *long*. The following table lists the permissible combinations to specify a large set of storage size-specific declarations.

| Type                                     | Explanation                              | Format Specifier                         |
| ---------------------------------------- | ---------------------------------------- | ---------------------------------------- |
| char                                     | Smallest addressable unit of the machine that can contain basic character set. It is an [integer](https://en.wikipedia.org/wiki/Integer_(computer_science)) type. Actual type can be either signed or unsigned. It contains `CHAR_BIT` bits.[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3) | %c                                       |
| signed char                              | Of the same size as `char`, but guaranteed to be signed. Capable of containing **at least** the [−127, +127] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) | %c (or %hhi for numerical output)        |
| unsigned char                            | Of the same size as `char`, but guaranteed to be unsigned. Contains **at least** the [0, 255] range.[[5\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99generalrepr-5) | %c (or %hhu for numerical output)        |
| shortshort intsigned shortsigned short int | *Short* signed integer type. Capable of containing **at least** the [−32,767, +32,767] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) thus, it is at least 16 bits in size. The negative value is −32767 (not −32768) due to the one's-complement and sign-magnitude representations allowed by the standard, though the two's-complement representation is much more common.[[6\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-6) | %hi                                      |
| unsigned shortunsigned short int         | *Short* unsigned integer type. Contains **at least** the [0, 65535] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) | %hu                                      |
| intsignedsigned int                      | Basic signed integer type. Capable of containing **at least** the [−32,767, +32,767] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) thus, it is at least 16 bits in size. | %i or %d                                 |
| unsignedunsigned int                     | Basic unsigned integer type. Contains **at least** the [0, 65535] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) | %u                                       |
| longlong intsigned longsigned long int   | *Long* signed integer type. Capable of containing **at least** the [−2,147,483,647, +2,147,483,647] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) thus, it is at least 32 bits in size. | %li                                      |
| unsigned longunsigned long int           | *Long* unsigned integer type. Capable of containing **at least** the [0, 4,294,967,295] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) | %lu                                      |
| long longlong long intsigned long longsigned long long int | *Long long* signed integer type. Capable of containing **at least** the [−9,223,372,036,854,775,807, +9,223,372,036,854,775,807] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) thus, it is at least 64 bits in size. Specified since the [C99](https://en.wikipedia.org/wiki/C99) version of the standard. | %lli                                     |
| unsigned long longunsigned long long int | *Long long* unsigned integer type. Contains **at least** the [0, +18,446,744,073,709,551,615] range;[[3\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99sizes-3)[[4\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-restr-4) Specified since the [C99](https://en.wikipedia.org/wiki/C99) version of the standard. | %llu                                     |
| float                                    | Real floating-point type, usually referred to as a single-precision floating-point type. Actual properties unspecified (except minimum limits), however on most systems this is the [IEEE 754 single-precision binary floating-point format](https://en.wikipedia.org/wiki/Single-precision_floating-point_format). This format is required by the optional Annex F "IEC 60559 floating-point arithmetic". | for formatted input:%f %F for digital notation, or%g %G, or%e %E%a %Afor [scientific notation](https://en.wikipedia.org/wiki/Scientific_notation)[[7\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-uplowcase-7) |
| double                                   | Real floating-point type, usually referred to as a double-precision floating-point type. Actual properties unspecified (except minimum limits), however on most systems this is the [IEEE 754 double-precision binary floating-point format](https://en.wikipedia.org/wiki/Double-precision_floating-point_format). This format is required by the optional Annex F "IEC 60559 floating-point arithmetic". | %lf %lF%lg  %lG%le  %lE%la %lA;[[7\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-uplowcase-7) for formatted output, the length modifier l is optional. |
| long double                              | Real floating-point type, usually mapped to an [extended precision](https://en.wikipedia.org/wiki/Extended_precision) floating-point number format. Actual properties unspecified. Unlike types float and double, it can be either [80-bit floating point format](https://en.wikipedia.org/wiki/80-bit_floating_point_format), the non-IEEE "[double-double](https://en.wikipedia.org/wiki/Double-double_arithmetic)" or [IEEE 754 quadruple-precision floating-point format](https://en.wikipedia.org/wiki/IEEE_754_quadruple-precision_floating-point_format) if a higher precision format is provided, otherwise it is the same as double. See [the article on long double](https://en.wikipedia.org/wiki/Long_double) for details. | %Lf %LF%Lg %LG%Le %LE%La %LA[[7\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-uplowcase-7) |

The actual size of the [integer](https://en.wikipedia.org/wiki/Integer_(computer_science)) types varies by implementation. The standard only requires size relations between the data types and minimum sizes for each data type:

The relation requirements are that the `long long` is not smaller than `long`, which is not smaller than `int`, which is not smaller than `short`. As `char`'s size is always the minimum supported data type, no other data types (except bit-fields) can be smaller.

The minimum size for `char` is 8 bits, the minimum size for `short` and `int` is 16 bits, for `long` it is 32 bits and `long long` must contain at least 64 bits.

The type `int` should be the integer type that the target processor is most efficiently working with. This allows great flexibility: for example, all types can be 64-bit. However, several different integer width schemes (data models) are popular. Because the data model defines how different programs communicate, a uniform data model is used within a given operating system application interface.[[8\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-8)

In practice, `char` is usually eight bits in size and `short` is usually 16 bits in size (as are their unsigned counterparts). This holds true for platforms as diverse as 1990s [SunOS](https://en.wikipedia.org/wiki/SunOS) 4 Unix, Microsoft [MS-DOS](https://en.wikipedia.org/wiki/MS-DOS), modern [Linux](https://en.wikipedia.org/wiki/Linux), and Microchip MCC18 for embedded 8-bit PIC [microcontrollers](https://en.wikipedia.org/wiki/Microcontroller). [POSIX](https://en.wikipedia.org/wiki/POSIX) requires `char` to be exactly eight bits in size.

Various rules in the C standard make `unsigned char` the basic type used for arrays suitable to store arbitrary non-bit-field objects: its lack of padding bits and trap representations, the definition of *object representation*,[[5\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99generalrepr-5) and the possibility of aliasing.[[9\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-9)

The actual size and behavior of floating-point types also vary by implementation. The only guarantee is that `long double` is not smaller than `double`, which is not smaller than `float`. Usually, the 32-bit and 64-bit [IEEE 754](https://en.wikipedia.org/wiki/IEEE_floating_point) binary floating-point formats are used, if supported by hardware.

The [C99](https://en.wikipedia.org/wiki/C99) standard includes new real floating-point types `float_t` and `double_t`, defined in `<math.h>`. They correspond to the types used for the intermediate results of floating-point expressions when `FLT_EVAL_METHOD` is 0, 1, or 2. These types may be wider than `long double`.

C99 also added [complex](https://en.wikipedia.org/wiki/Complex_number) types: `float _Complex`, `double _Complex`, `long double _Complex`.

### Boolean type

[C99](https://en.wikipedia.org/wiki/C99) added a boolean (true/false) type `_Bool`. Additionally, the new `<stdbool.h>` header defines `bool` as a convenient alias for this type, and also provides macros for `true` and `false`. `_Bool` functions similarly to a normal integral type, with one exception: any assignments to a `_Bool` that are not 0 (false) are stored as 1 (true). This behavior exists to avoid [integer overflows](https://en.wikipedia.org/wiki/Integer_overflow) in implicit narrowing conversions. For example, in the following code:

```
unsigned char b = 256;

if (b) {
   /* do something */
}

```

`b` evaluates to false if `unsigned char` is 8 bits wide. This is because 256 does not fit in the data type, which results in the lower 8 bits of it being used, resulting in a zero value. However, changing the type causes the previous code to behave normally:

```
_Bool b = 256;

if (b) {
   /* do something */
}

```

### Size and pointer difference types

The C language specification includes the typedefs `size_t` and `ptrdiff_t` to represent memory-related quantities. Their size is defined according to the target processor's arithmetic capabilities, not the memory capabilities, such as available address space. Both of these types are defined in the `<stddef.h>` header (`cstddef` header in C++).

`size_t` is an unsigned integer type used to represent the size of any object (including arrays) in the particular implementation. The `sizeof` operator yields a value of the type `size_t`. The maximum size of `size_t` is provided via `SIZE_MAX`, a macro constant which is defined in the `<stdint.h>` header (`cstdint` header in C++). `size_t` is guaranteed to be at least 16 bits wide. Additionally, POSIX includes `ssize_t`, which is a signed integral type of the same width as `size_t`.

`ptrdiff_t` is a signed integral type used to represent the difference between pointers. It is only guaranteed to be valid against pointers of the same type; subtraction of pointers consisting of different types is implementation-defined.

### Interface to the properties of the basic types

Information about the actual properties, such as size, of the basic arithmetic types, is provided via macro constants in two headers: `<limits.h>` header (`climits` header in C++) defines macros for integer types and `<float.h>` header (`cfloat` header in C++) defines macros for floating-point types. The actual values depend on the implementation.

- Properties of integer types


- `CHAR_BIT` – size of the char type in bits (at least 8 bits)
- `SCHAR_MIN`, `SHRT_MIN`, `INT_MIN`, `LONG_MIN`, `LLONG_MIN`(C99) – minimum possible value of signed integer types: signed char, signed short, signed int, signed long, signed long long
- `SCHAR_MAX`, `SHRT_MAX`, `INT_MAX`, `LONG_MAX`, `LLONG_MAX`(C99) – maximum possible value of signed integer types: signed char, signed short, signed int, signed long, signed long long
- `UCHAR_MAX`, `USHRT_MAX`, `UINT_MAX`, `ULONG_MAX`, `ULLONG_MAX`(C99) – maximum possible value of unsigned integer types: unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long
- `CHAR_MIN` – minimum possible value of char
- `CHAR_MAX` – maximum possible value of char
- `MB_LEN_MAX` – maximum number of bytes in a multibyte character


- Properties of floating-point types


- `FLT_MIN`, `DBL_MIN`, `LDBL_MIN` – minimum normalized positive value of float, double, long double respectively
- `FLT_TRUE_MIN`, `DBL_TRUE_MIN`, `LDBL_TRUE_MIN` (C11) – minimum positive value of float, double, long double respectively
- `FLT_MAX`, `DBL_MAX`, `LDBL_MAX` – maximum finite value of float, double, long double, respectively
- `FLT_ROUNDS` – rounding mode for floating-point operations
- `FLT_EVAL_METHOD` (C99) – evaluation method of expressions involving different floating-point types
- `FLT_RADIX` – radix of the exponent in the floating-point types
- `FLT_DIG`, `DBL_DIG`, `LDBL_DIG` – number of decimal digits that can be represented without losing precision by float, double, long double, respectively
- `FLT_EPSILON`, `DBL_EPSILON`, `LDBL_EPSILON` – [difference between 1.0 and the next representable value](https://en.wikipedia.org/wiki/Machine_epsilon) of float, double, long double, respectively
- `FLT_MANT_DIG`, `DBL_MANT_DIG`, `LDBL_MANT_DIG` – number of `FLT_RADIX`-base digits in the floating-point significand for types float, double, long double, respectively
- `FLT_MIN_EXP`, `DBL_MIN_EXP`, `LDBL_MIN_EXP` – minimum negative integer such that `FLT_RADIX` raised to a power one less than that number is a normalized float, double, long double, respectively
- `FLT_MIN_10_EXP`, `DBL_MIN_10_EXP`, `LDBL_MIN_10_EXP` – minimum negative integer such that 10 raised to that power is a normalized float, double, long double, respectively
- `FLT_MAX_EXP`, `DBL_MAX_EXP`, `LDBL_MAX_EXP` – maximum positive integer such that `FLT_RADIX` raised to a power one less than that number is a normalized float, double, long double, respectively
- `FLT_MAX_10_EXP`, `DBL_MAX_10_EXP`, `LDBL_MAX_10_EXP` – maximum positive integer such that 10 raised to that power is a normalized float, double, long double, respectively
- `DECIMAL_DIG` (C99) – minimum number of decimal digits such that any number of the widest supported floating-point type can be represented in decimal with a precision of `DECIMAL_DIG` digits and read back in the original floating-point type without changing its value. `DECIMAL_DIG` is at least 10.

## Fixed-width integer types

The [C99](https://en.wikipedia.org/wiki/C99) standard includes definitions of several new integer types to enhance the portability of programs.[[2\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-c99-2) The already available basic integer types were deemed insufficient, because their actual sizes are implementation defined and may vary across different systems. The new types are especially useful in [embedded environments](https://en.wikipedia.org/wiki/Embedded_system) where hardware usually supports only several types and that support varies between different environments. All new types are defined in `<inttypes.h>` header (`cinttypes` header in C++) and also are available at `<stdint.h>` header (`cstdint` header in C++). The types can be grouped into the following categories:

- Exact-width integer types which are guaranteed to have the same number **N** of bits across all implementations. Included only if it is available in the implementation.
- Least-width integer types which are guaranteed to be the smallest type available in the implementation, that has at least specified number **N** of bits. Guaranteed to be specified for at least N=8,16,32,64.
- Fastest integer types which are guaranteed to be the fastest integer type available in the implementation, that has at least specified number **N** of bits. Guaranteed to be specified for at least N=8,16,32,64.
- Pointer integer types which are guaranteed to be able to hold a pointer. Included only if it is available in the implementation.
- Maximum-width integer types which are guaranteed to be the largest integer type in the implementation.

The following table summarizes the types and the interface to acquire the implementation details (**N** refers to the number of bits):

| Type category | Signed types       | Unsigned types       |                      |                     |               |                       |
| ------------- | ------------------ | -------------------- | -------------------- | ------------------- | ------------- | --------------------- |
| Type          | Minimum value      | Maximum value        | Type                 | Minimum value       | Maximum value |                       |
| Exact width   | `int**N**_t`       | `INT**N**_MIN`       | `INT**N**_MAX`       | `uint**N**_t`       | 0             | `UINT**N**_MAX`       |
| Least width   | `int_least**N**_t` | `INT_LEAST**N**_MIN` | `INT_LEAST**N**_MAX` | `uint_least**N**_t` | 0             | `UINT_LEAST**N**_MAX` |
| Fastest       | `int_fast**N**_t`  | `INT_FAST**N**_MIN`  | `INT_FAST**N**_MAX`  | `uint_fast**N**_t`  | 0             | `UINT_FAST**N**_MAX`  |
| Pointer       | `intptr_t`         | `INTPTR_MIN`         | `INTPTR_MAX`         | `uintptr_t`         | 0             | `UINTPTR_MAX`         |
| Maximum width | `intmax_t`         | `INTMAX_MIN`         | `INTMAX_MAX`         | `uintmax_t`         | 0             | `UINTMAX_MAX`         |

### Printf and scanf format specifiers

Main article: [printf format string](https://en.wikipedia.org/wiki/Printf_format_string)

The `<inttypes.h>` header (`cinttypes` header in C++) provides features that enhance the functionality of the types defined in `<stdint.h>` header. Included are macros that define [printf format string](https://en.wikipedia.org/wiki/Printf_format_string) and [scanf format string](https://en.wikipedia.org/wiki/Scanf_format_string) specifiers corresponding to the `<stdint.h>` types and several functions for working with `intmax_t` and `uintmax_t` types. This header was added in [C99](https://en.wikipedia.org/wiki/C99).

- Printf format string

The macros are in the format `PRI*{fmt}{type}*`. Here *{fmt}* defines the output formatting and is one of `d` (decimal), `x` (hexadecimal), `o` (octal), `u` (unsigned) and `i` (integer). *{type}* defines the type of the argument and is one of `**N**`, `FAST**N**`, `LEAST**N**`, `PTR`, `MAX`, where `**N**` corresponds to the number of bits in the argument.

- Scanf format string

The macros are in the format `SCN*{fmt}{type}*`. Here *{fmt}* defines the output formatting and is one of `d` (decimal), `x` (hexadecimal), `o` (octal), `u` (unsigned) and `i` (integer). *{type}* defines the type of the argument and is one of `**N**`, `FAST**N**`, `LEAST**N**`, `PTR`, `MAX`, where `**N**` corresponds to the number of bits in the argument.

- Functions

| [![[icon\]](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1c/Wiki_letter_w_cropped.svg/20px-Wiki_letter_w_cropped.svg.png)](https://en.wikipedia.org/wiki/File:Wiki_letter_w_cropped.svg) | **This section needs expansion**. You can help by [adding to it](https://en.wikipedia.org/w/index.php?title=C_data_types&action=edit&section=). *(October 2011)* |
| ---------------------------------------- | ---------------------------------------- |
|                                          |                                          |

## Structures

Structures aggregate the storage of multiple data items, of potentially differing data types, into one memory block referenced by a single variable. The following example declares the data type *struct birthday* which contains the name and birthday of a person. The structure definition is followed by a declaration of the variable *John* that allocates the needed storage.

```
struct birthday {
    char name[20];
    int day;
    int month;
    int year;
};

struct birthday John;

```

The memory layout of a structure is a language implementation issue for each platform, with a with few restrictions. The memory address of the first member must be the same as the address of structure itself. Structures may be [initialized](https://en.wikipedia.org/wiki/C_syntax#Initialization) or assigned to using compound literals. A function may directly return a structure, although this is often not efficient at run-time. Since [C99](https://en.wikipedia.org/wiki/C99), a structure may also end with a [flexible array member](https://en.wikipedia.org/wiki/Flexible_array_member).

A structure containing a pointer to a structure of its own type is commonly used to build [linked data structures](https://en.wikipedia.org/wiki/Linked_data_structure):

```
struct node {
	int val;
	struct node *next;
};

```

## Arrays

For every type *T*, except void and function types, there exist the types "array of *N* elements of type *T*". An array is a collection of values, all of the same type, stored contiguously in memory. An array of size *N* is indexed by integers from *0* up to and including *N-1*. There are also "arrays of unspecified size" where the number of elements is not known by the compiler. Here is a brief example:

```
int cat[10];  // array of 10 elements, each of type int
int bob[];    // array of an unspecified number of 'int' elements

```

Arrays can be initialized with a compound initializer, but not assigned. Arrays are passed to functions by passing a pointer to the first element. Multidimensional arrays are defined as "array of array …", and all except the outermost dimension must have compile-time constant size:

```
int a[10][8];  // array of 10 elements, each of type 'array of 8 int elements'
float f[][32]; // array of unspecified number of 'array of 32 float elements'

```

## Pointers

Every data type *T* has a corresponding type *pointer to T*. A [pointer](https://en.wikipedia.org/wiki/Pointer_(computer_programming)) is a data type that contains the address of a storage location of a variable of a particular type. They are declared with the asterisk (***) type declarator following the basic storage type and preceding the variable name. White space before or after the asterisk is optional.

```
char * square;
long* circle;
int *oval;

```

Pointers may also be declared for pointer data types, thus creating multiple indirect pointers, such as *char\*** and *int\****, including pointers to array types. The latter are less common than an array of pointers, and their syntax may be confusing:

```
char *pc[10]; // array of 10 elements of 'pointer to char'
char (*pa)[10]; // pointer to a 10-element array of char

```

The element *pc* consumes ten blocks of memory of the size of *pointer to char* (usually 40 or 80 bytes on common platforms), but element *pa* is only one pointer—*sizeof pa* is usually 4 or 8—and the data it refers to is an array of ten bytes (sizeof *pa == 10).

## Unions

A union type is a special construct that permits access to the same memory block by using a choice of differing type descriptions. For example, a union of data types may be declared to permit reading the same data either as an integer, a float, or any other user declared type:

```
union {
    int i;
    float f;
    struct {
        unsigned int u;
        double d;
    } s;
} u;

```

The total size of *u* is the size of *u.s*—which happens to be the sum of the sizes of *u.s.u* and *u.s.d*—since *s* is larger than both *i* and *f*. When assigning something to *u.i*, some parts of *u.f* may be preserved if *u.i* is smaller than *u.f*.

Reading from a union member is not the same as casting since the value of the member is not converted, but merely read.

## Function pointers

Function pointers allow referencing functions with a particular signature. For example, to store the address of the standard function `abs` in the variable `my_int_f`:

```
int (*my_int_f)(int) = &abs;
// the & operator can be omitted, but makes clear that the "address of" abs is used here

```

Function pointers are invoked by name just like normal function calls. Function pointers are separate from pointers and [void pointers](https://en.wikipedia.org/wiki/Void_pointer).

## Type qualifiers

Main article: [Type qualifier](https://en.wikipedia.org/wiki/Type_qualifier)

The aforementioned types can be characterized further by [type qualifiers](https://en.wikipedia.org/wiki/Type_qualifier), yielding a *qualified type*. As of 2014 and [C11](https://en.wikipedia.org/wiki/C11_(C_standard_revision)), there are four type qualifiers in standard C: `const` ([C89](https://en.wikipedia.org/wiki/ANSI_C)), `volatile` ([C89](https://en.wikipedia.org/wiki/ANSI_C)), `restrict` ([C99](https://en.wikipedia.org/wiki/C99)) and `_Atomic` ([C11](https://en.wikipedia.org/wiki/C11_(C_standard_revision))) –  the latter has a private name to avoid clashing with user names,[[10\]](https://en.wikipedia.org/wiki/C_data_types#cite_note-10) but the more ordinary name `atomic` can be used if the `<stdatomic.h>` header is included. Of these, `const` is by far the best-known and most used, appearing in the [standard library](https://en.wikipedia.org/wiki/Standard_library) and encountered in any significant use of the C language, which must satisfy [const-correctness](https://en.wikipedia.org/wiki/Const-correctness). The other qualifiers are used for low-level programming, and while widely used there, are rarely used by typical programmers.[*citation needed*]

