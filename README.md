# DataLite
Simple database written in C, based off of SQLite

In order to create a database similar SQLite, we need to understand the internals of SQLite itself:

## How does SQLite work?
- SQL statements are compiled into bytecode which is then run in a VM
- interfaces (such as `sqlite3_prepare_v2()`) act as a compiler for converting SQL text into bytecode
- Objects (such as `sqlite3_stmt`) act as a container for a single bytecode program that implements a single SQL statement.
- The interface (`sqlite3_step()`) then psses a bytecode program into the VM and runs the program until: 

  a - the program completes 
  
  b - forms row of result to be returned 
  
  c - hit a fatal error or is interrupted

## Flow of data in SQLite

Tokenizer -> Parser -> Code Generator -> VM -> B-Tree -> Page Cache -> OS Interface

**Tokenizer** 
- breaks SQL statements into tokens

**Parser** 
- assigns meaning to tokens based on context (SQLite uses Lemon)

**Code Generator** 
- generates bytecode
- AI chooses one of millions of algorithms to compute answer for each statement 

**Byte Engine / VM** 
- runs the bytecode program created by code generator

**B-Tree** 
- separate B-trees are used for each table & each index in the database
- all B-trees are stored in same file 

**Page Cache** 
- B-tree requests information from disks in fixed-size pages
- the default page size = 4096 bytes
- cab be any power of 2 between 512 and 65536
- responsible for licking of database
- responsible for handling of all requests and making sure they're handled quickly and efficiently

**OS Interface**
- provides portability across all operating systems 
- provides methods for opening, reading, writing, and closing files on disk
- In terms of this project, we are not supporting multiple operating systems

Resource: https://www.sqlite.org/arch.html
