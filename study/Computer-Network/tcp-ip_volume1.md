## 1.5. Designing Applications

The network concepts we have touched upon so far provide a fairly simple service model `[RFC6250]`: moving bytes between programs running on different (or, occasionally, the same) computers. To do anything useful with this capability, we need **networked applications** that use the network for providing services or performing computations. **Networked applications** are typically structured according to a small number of design patterns. The most common of these are `client/server` and `peer-to-peer`.

### 1.5.1. Client/Server

Most **network applications** are designed so that one side is the **client** and the other side is the **server**. The server provides some type of service to clients, such as access to files on the server host. We can categorize servers into two classes: **iterative** and **concurrent**. 

An **iterative** server iterates through the following steps:

- I1. Wait for a client request to arrive.
- I2. Process the client request.
- I3. Send the response back to the client that sent the request.
- I4. Go back to step **I1**.

The problem with an iterative server occurs when **step I2** takes a long time. During this time no other clients are serviced. A **concurrent** server, on the other hand, performs the following steps:

- C1. Wait for a client request to arrive.
- C2. Start a new **server** instance to handle this **client’s** request. This may involve creating a new process, task, or thread, depending on what **the underlying operating system** supports. This new **server** handles one **client’s** entire request. When the requested task is complete, the new server terminates. Meanwhile, the original server instance continues to **C3**.
- C3. Go back to step **C1**.

The advantage of a **concurrent** server is that the server just spawns other server instances to handle the **client** requests. Each client has, in essence, its own server. Assuming that the operating system allows multiprogramming (essentially all do today), multiple clients are serviced concurrently. **The reason we categorize servers, and not clients**, is that a client normally cannot tell whether it is talking to an iterative server or a concurrent server. As a general rule, most servers are **concurrent**.

Note that we use the terms client and server to refer to applications and not to the particular computer
systems on which they run. The very same terms are sometimes used to refer to the pieces of hardware
that are most often used to execute either client or server applications. Although the terminology is thus
somewhat imprecise, it works well enough in practice. As a result, it is common to find a server (in the
hardware sense) running more than one server (in the application sense).





## 13.2. TCP Connection Establishment and Termination

A TCP `connection` is defined to be a 4-tuple consisting of two IP addresses and two port numbers. More precisely, it is a pair of *endpoints* or *sockets* where each endpoint is identified by an (IP address, port number) pair.