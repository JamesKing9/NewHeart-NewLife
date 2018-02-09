  




# Beginning Linux Programming, 4th Edition

Cover:

<img src="http://ouqfn1c6k.bkt.clouddn.com/cover.jpg" height="520px"> 



# About the Authors

**Neil Matthew** 

**Rick Stones**



---

# 1: Getting Started



#### 1.2.3  The C Compiler



######  Try It Out 'Your First Linux C Program'

In this example, you start developing for Linux using C by writing, compiling, and running your first Linux program. It might as well as be that most famous of all starting points, **Hello World**.

Here's the source code for the file `hello.c`:

```c++
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Hello world\n");
	exit(0);
}
```

Now compile, link, and run your program:

```shell
$ gcc -o hello hello.c
$./hello
```

It gives the following output:

```shell
Hello World
$
```
**How It Works**





# 2: Shell Programming

Having started this book on programming Linux using C, we now take a detour into writing shell programs. *Why?* Well, Linux isn't like systems where the command-line interface is an afterthought to the graphical interface.



# 4: The Linux Environment



## 4.2 Environment Variables

We discussed **environment variables** in Chapter 2. These are variables that can be used to control the behavior of **shell scripts** and other programs. You can also use them to configure the **user’s environment**. For example, each user has an environment variable, HOME, that defines his home directory, the default
starting place for his or her session. As you’ve seen, you can examine **environment variables** from the *shell prompt*:
```shell
$ echo $HOME
/home/neil
```
You can also use the shell’s set command to list all of the environment variables.

The UNIX specification defines many standard **environment variables** used for a variety of purposes, including terminal type, default editors, time zones, and so on. A C program may gain access to environment variables using the `putenv` and `getenv` functions.

**Syntax :**

```c
#include <stdlib.h>

char *getenv(const char *name);
int putenv(const char *string);
```

### [Case]  getenv and putenv

```c++
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *var, *value;

    if(argc == 1 || argc > 3) {
        fprintf(stderr,”usage: environ var [value]\n”);
        exit(1);
    }

    var = argv[1];
    value = getenv(var);
    if(value)
        printf(“Variable %s has value %s\n”, var, value);
    else
        printf(“Variable %s has no value\n”, var);
    if(argc == 3) {

        char *string;
        value = argv[2];

        string = malloc(strlen(var)+strlen(value)+2);
        if(!string) {
            fprintf(stderr,”out of memory\n”);
            exit(1);
        }
        strcpy(string,var);
        strcat(string,”=”);
        strcat(string,value);
        printf(“Calling putenv with: %s\n”,string);
        if(putenv(string) != 0) {
            fprintf(stderr,”putenv failed\n”);
            free(string);
            exit(1);
        // }
        value = getenv(var);
        if(value)
            printf(“New value of %s is %s\n”, var, value);
        else
            printf(“New value of %s is null??\n”, var);
    }
    exit(0);
}
```

When you run this program, you can see and set environment variables:
```shell
$ ./environ HOME
Variable HOME has value /home/neil
$ ./environ FRED
Variable FRED has no value
$ ./environ FRED hello
Variable FRED has no value
Calling putenv with: FRED=hello
New value of FRED is hello
$ ./environ FRED
Variable FRED has no value
```
Notice that the environment is local only to the program. Changes that you make within the program are not reflected outside it because variable values are not propagated from the child process (your program) to the parent (the shell).

# 5：Terminals



## 5.1 Reading from and Writing to the Terminal

In **Chapter 3**, you learned that when a program is invoked from the command prompt, the shell arranges for the standard input and output streams to be connected to your program. You should be able to interact with the user simply by using the `getchar` and `printf` routines to read and write these default streams.

In the following **Try It Out**, you try to rewrite the menu routines in C, using just those two routines, in a program called `menu1.c`.

###### Try It Out ‘Menu Routines in C’

```c++
// 1. Start with the following lines, which define the array to // be used as a menu, and prototype the `getchoice` function:
#include <stdio.h>
#include <stdlib.h>

char *menu[] = {
  "a - add new record",
  "d - delete record",
  "q - quit",
  NULL,
  
};

int getchoice(char *greet, char *choices[]);

// 2. The main function calls `getchoice` with the sample menu, // `menu`:
int main() {
  int choice = 0;
  
  do {
    choice = getchoice("Please select an action", menu);
    printf("You have chosen: %c\n", choice);
  } while (choice != 'q');
  exit(0);
}

// 3. Now for the important code — the function that both prints // the menu and reads the user’s input:
int getchoice(char *greet, char *choices[]) {
  int chosen =0;
  int selected;
  char **option;
  
  do {
    printf("Choice: %s\n", greet);
    option = choices;
    while (*option) {
      printf("%s\n", *option);
      option++;
    }
    selected = getchar();
    option = choices;
    
    while(*option) {
      if(selected == *option[0]) {
        chosen = 1;
        break;
      }
      option ++;
      
    }
    if (!chosen) {
      printf("Incorrect choice, select again\n");
    }
  } while (!chosen);
  return selected;
}

```








# 7:  Data Management

In earlier chapters, we touched on the subject of resource limits. In this chapter, we're going to look first at ways of managing your resource allocation, then at ways of dealing with files that are accessed by many users more or less simultaneously, and lastly at one tool provided in Linux systems for overcoming the limitations of flat files as a storage medium.

We can summarize these topics as three ways of managing data:

*   **Dynamic memory management**: what to do and what *Linux* won't let you do
*   **File locking**: cooperative locking, locking regions of shared files, and avoiding deadlocks
*   **The dbm database**: a basic, non-SQL-based database library featured in most Linux systems


### 7.1  Managing Memory





#### 7.1.1  Simple Memory Allocation

You allocate memory using the `malloc` call in the standard C library:

```c
#include <stdlib.h>
void *malloc(size_t size);
```



##### Try It Out:  "Simple Memory Allocation"

Type the following program, `memory1.c`:

```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define A_MEGABYTE (1024 * 1024)

int main() {
	char *some_memory;
  	int megabyte = A_MEGABYTE;
  	int exit_code = EXIT_FAILURE;
  	
  	some_memory = (char *)malloc(megabyte);
  	if (some_memory != NULL) {
  		sprintf(some_memory, "Hello World\n");
  		printf("%s", some_memory);
  		exit_code = EXIT_SUCCESS;
  	}
  	exit(exit_code);
}
```
Now compile, link, and run your program:

```mark
$ gcc -o memory1 memory.c
$./memory1
```

It gives the following output:

```mark
Hello World
$
```

**How it Works**

>   This program asks the malloc library to give it a pointer to a megabyte of memory. You check to ensure that `malloc` was successful and then use some of the memory to show that it exists. When you run the program, you should see *Hello World* printed out, showing that `malloc` did indeed return the megabyte of useable memory. We don't check that all of the megabyte is present; we have to put some trust in the `malloc` code!







# 11:  Processes and Signals





## Process Structure

Let's have a look at how a couple of processes might be arranged within the operating system. If two users, `neil` and `rick`, both run the `grep` program at the same time to look for different strings in different files, the processes being used might look like Figure 11-1.

<img src="http://ouqfn1c6k.bkt.clouddn.com/2.jpg"> 

​      

If you could run the `ps` command as in the following code quickly enough and before the searches had finished, the output might contain something like this:

```shell
$ ps -ef
UID     PID   PPID  C  STIME  TTY   TIME      CMD
rick    101   96    0  18:24  tty2  00:00:00  grep troi nextgen.doc
neil    102   92    0  18:24  tty4  00:00:00  grep kirk trek.txt
```

Each process is allocated a unique number, called a *process identifier* or PID. This is usually a positive integer between 2 and 32,768. When a process is started, the next unused number in sequence is chosen and the numbers restart at 2 so that they wrap around. The number 1 is typically reserved for the special `init `process, which manages other processes. We will come back to `init `shortly. Here you see that the two processes started by `neil `and `rick `have been allocated the identifiers 101 and 102  



# 14: Semaphores, Shared Memory, and Message Queues

In this chapter, we discuss a set of inter-process communication facilities that were originally
introduced in the AT&T System V.2 release of UNIX. Because all these facilities appeared in the
same release and have a similar programmatic interface, they are often referred to as the IPC
(Inter-Process Communication) facilities, or more commonly System V IPC. As you’ve already
seen, they are by no means the only way of communicating between processes, but the expression System V IPC is usually used to refer to these specific facilities.

We cover the following topics in this chapter:
❑ Semaphores, for managing access to resources
❑ Shared memory, for highly efficient data sharing between programs
❑ Messaging, for an easy way of passing data between programs



## Semaphores

When you write programs that use threads operating in multiuser systems, multiprocessing systems, or a combination of the two, you may often discover that you have critical sections of code, where you need to ensure that a single process (or a single thread of execution) has exclusive access to a resource.



## Semaphore Definition

The simplest semaphore is a variable that can take only the values 0 and 1, a binary semaphore. This is the most common form. Semaphores that can take many positive values are called general semaphores. For the remainder of this chapter, we concentrate on binary semaphores.



## Using Semaphores

As you can see from the previous section’s descriptions, semaphore operations can be rather complex. This is most unfortunate, because programming multiple processes or threads with critical sections is quite a difficult problem on its own and having a complex programming interface simply adds to the intellectual burden.



### Try It Out: Semaphores



```c
/*
(1) After the system #includes, you include a file `semun.h`. This defines the union semun, as required by X/OPEN, if the system include `sys/sem.h` doesn’t already define it. Then come the function prototypes, and the global variable, before you come to the main function. There the semaphore is created with a call to semget, which returns the semaphore ID. If the program is the first to be called (that is, it’s called with a parameter and argc > 1), a call is made to set_semvalue to initialize the semaphore and op_char is set to X:

 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include “semun.h”

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
static int sem_id;

int main(int argc, char *argv[]) {
    int i;
    int pause_time;
    char op_char = ‘O’;
    srand((unsigned int) getpid());
    sem_id = semget((key_t) 1234, 1, 0666 | IPC_CREAT);
    if (argc > 1) {
        if (!set_semvalue()) {
            fprintf(stderr, “Failed to initialize semaphore\n”);
            exit(EXIT_FAILURE);
        }
        op_char = ‘X’;
        sleep(2);
    }
    /*
  2. Then you have a loop that enters and leaves the critical section 10 times. There you first make a
  call to semaphore_p, which sets the semaphore to wait as this program is about to enter the
  critical section:
     */
    for (i = 0; i < 10; i++) {
        if (!semaphore_p()) exit(EXIT_FAILURE);
        printf(“ % c”, op_char);
        fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        printf(“ % c”, op_char);
        fflush(stdout);
        /*
      3. After the critical section, you call semaphore_v, setting the semaphore as available, before
      going through the for loop again after a random wait. After the loop, the call to del_semvalue
      is made to clean up the code:
         */
        if (!semaphore_v()) exit(EXIT_FAILURE);
        pause_time = rand() % 2;
        sleep(pause_time);
    }
    printf(“\n % d - finished\n”, getpid());
    if (argc > 1) {
        sleep(10);
        del_semvalue();
    }
    exit(EXIT_SUCCESS);
}

/*
4. The function set_semvalue initializes the semaphore using the SETVAL command in a semctl
call. You need to do this before you can use the semaphore:
 */
static int set_semvalue(void) {
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) return (0);
    return (1);
}

/*
5. The del_semvalue function has almost the same form, except that the call to semctl uses the command IPC_RMID to remove the semaphore’s ID:
 */
static void del_semvalue(void) {
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
        fprintf(stderr, “Failed to delete semaphore\n”);
}

/*
6. semaphore_p changes the semaphore by –1. This is the “wait” operation:
 */
static int semaphore_p(void) {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1; /* P() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, “semaphore_p failed\n”);
        return (0);
    }
    return (1);
}

/*
7. semaphore_v is similar except for setting the sem_op part of the sembuf structure to 1. This is the “release” operation, so that the semaphore becomes available:
 */
static int semaphore_v(void) {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1; /* V() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, “semaphore_v failed\n”);
        return (0);
    }
    return (1);
}
```

Notice that this simple program allows only a single binary semaphore per program, although you
could extend it to pass the semaphore variable if you need more semaphores. Normally, a single binary semaphore is sufficient.

You can test your program by invoking it several times. The first time, you pass a parameter to tell
the program that it’s responsible for creating and deleting the semaphore. The other invocations have no parameter.

Here’s some sample output, with two invocations of the program.
```shell
$ cc sem1.c -o sem1
$ ./sem1 1 &
[1] 1082
$ ./sem1
OOXXOOXXOOXXOOXXOOXXOOOOXXOOXXOOXXOOXXXX
1083 - finished
1082 - finished
$
```
Remember that “O” represents the first invocation of the program, and “X” the second invocation of the program. Because each program prints a character as it enters and again as it leaves the critical section, each character should only appear as part of a pair. As you can see, the Os and Xs are indeed properly paired, indicating that the critical section is being correctly processed. If this doesn’t work on your particular system, you may have to use the command stty –tostop before invoking the program to ensure that the background program generating tty output does not cause a signal to be generated.



#### How It Works

The program starts by obtaining a semaphore identity from the (arbitrary) key that you’ve chosen using the semget function. The IPC_CREAT flag causes the semaphore to be created if one is required.
If the program has a parameter, it’s responsible for initializing the semaphore, which it does with the function set_semvalue, a simplified interface to the more general semctl function. It also uses the presence of
the parameter to determine which character it should print out. The sleep simply allows you some time to
invoke other copies of the program before this copy gets to execute too many times around its loop. You
use srand and rand to introduce some pseudo-random timing into the program.
The program then loops 10 times, with pseudo-random waits in its critical and noncritical sections. The
critical section is guarded by calls to your semaphore_p and semaphore_v functions, which are simplified interfaces to the more general semop function.
Before it deletes the semaphore, the program that was invoked with a parameter then waits to allow
other invocations to complete. If the semaphore isn’t deleted, it will continue to exist in the system even
though no programs are using it. In real programs, it’s very important to ensure you don’t unintentionally leave semaphores around after execution. It may cause problems next time you run the program,
and semaphores are a limited resource that you must conserve.








# 15: Sockets



## What Is a Socket?

A socket is a communication mechanism that allows `client/server systems` to be developed either locally, on a single machine, or across networks. Linux functions such as printing, connecting to databases, and serving web pages as well as network utilities such as rlogin for remote login and ftp for file transfer usually use sockets to communicate.

Sockets are created and used differently from pipes because they make a clear distinction between client and server. The socket mechanism can implement multiple clients attached to a single server.



## Socket Connections



### Try It Out: A Simple Local Client

**client1.c**

```c
/* 
 * File:   client1.c
 * Author: james
 *
 * Created on January 17, 2018, 1:36 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';
    
    // (2)为客户创建一个套接字
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    // （3）根据服务器的情况给套接字命名
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);
    
    // (4)将我们的套接字连接到服务器的套接字
    result = connect(sockfd, (struct sockaddr *)&address, len);
    
    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }
    
    // (5)现在就可以通过sockfd进行读写操作了
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);
}
```



### Try It Out: A Simple Local Server

**server1.c**

```c
/* 
 * File:   server1.c
 * Here’s a very simple server program, `server1.c`, that accepts connections from the client. It creates the server socket, binds it to a name, creates a listen queue, and accepts connections.
 */
// 1. Make the necessary includes and set up the variables:
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
 
int main(int argc, char** argv) {

    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    // (2)删除以前的套接字， 为服务器创建一个未命名的套接字
    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    // (3)命名套接字
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof (server_address);
    bind(server_sockfd, (struct sockaddr *) & server_address, server_len);

    // (4)创建一个连接队列， 开始等待客户进行连接
    listen(server_sockfd, 5);
    while (1) {
        char ch;

        printf("server waiting\n");

        // (5)接受一个连接
        client_len = sizeof (client_address);
        client_sockfd = accept(server_sockfd,
                (struct sockaddr *) &client_address, &client_len);

        // (6)对client_sockfd套接字上的客户进行读写操作
        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}
```







# 16: GTK+

## 16.9

**cdapp_gnome.h**

```c
#include <gnome.h>
#include "app_mysql.h"
```





# The Filesystem Hierarchy Standard



| Directory | Required? | Use                                      |
| --------- | --------- | ---------------------------------------- |
|           |           |                                          |
|           |           |                                          |
| /mnt      | Y         | A convenient point to temporarily mount devices, such as CD-ROMs and flash memory sticks. |
|           |           |                                          |
|           |           |                                          |

 