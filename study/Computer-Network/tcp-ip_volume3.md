## 10.6 tcp_close Function

```c++
if (SEQ_LT(tp->iss + so->so_snd.sb_hiwat * 16, tp->snd_max) &&
	(
```





# 17  Unix Domain Protocols: Implementation



## 17.1 Introduction

The source code to implement the Unix domain protocols consists of 16 functions in the file `uipc_usrreq.c`. This totals about 1000 lines of C code, which is similar in size to the 800 lines required to implement UDP in **Volume 2**, but far less than the 4500 lines required to implement TCP.

We divide our presentation of the Unix domain protocol implementation into two chapters. 



## 17.3 Unix domain and protosw Structures


```

```