# mysql-connector-demo
This is a demonstration of how to use mysql-connector library in C++

## Requires
- MySQL Connector for C++ (development) files (>= 1.1.12)
- MySQL Connector for C++ (library) (>= 1.1.12)
- C++ compiler with C++17 support

## To compile

Make sure you change the connection information in **test.hpp** before compiling

```
cd ~/path/to/repo/src
make
```

## To test

```
cd ~/path/to/repo/src
./test.exe
```

### Sample output

```
Query: SELECT * FROM SEQUENCE_TABLE (100) AS SEQ LIMIT 0, 10
0
1
2
3
4
5
6
7
8
9
Query: SELECT * FROM SEQUENCE_TABLE (100) AS SEQ LIMIT ?, ?
Values used: 10, 10
10
11
12
13
14
15
16
17
18
19
```

## Testing with valgrind

```
cd ~/path/to/repo/src
valgrind ./test.exe
```

### Sample output

```
==41129== Memcheck, a memory error detector
==41129== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==41129== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==41129== Command: ./test.exe
==41129==
Query: SELECT * FROM SEQUENCE_TABLE (100) AS SEQ LIMIT 0, 10
0
1
2
3
4
5
6
7
8
9
Query: SELECT * FROM SEQUENCE_TABLE (100) AS SEQ LIMIT ?, ?
Values used for ?, ?: 10, 10
10
11
12
13
14
15
16
17
18
19
==41129== 
==41129== HEAP SUMMARY:
==41129==     in use at exit: 0 bytes in 0 blocks
==41129==   total heap usage: 6,311 allocs, 6,311 frees, 651,579 bytes allocated
==41129== 
==41129== All heap blocks were freed -- no leaks are possible
==41129== 
==41129== For lists of detected and suppressed errors, rerun with: -s
==41129== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## References

- [MySQL Connector/C++ 1.1 Developer Guide](https://dev.mysql.com/doc/connector-cpp/1.1/en/)
- [MySQL Connector/C++ 8.0 Developer Guide](https://dev.mysql.com/doc/connector-cpp/8.0/en/)