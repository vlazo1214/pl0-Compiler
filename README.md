# pl0-Compiler

This project is a compiler that reads in a sample PL/0 program, parses through it creating abstract syntax trees (ASTs), and generates 3-letter assembly mnemonic instructions based on those ASTs. The rule behind creating tokens that comprise the ASTs is the following context-free grammar, lexical grammar, and abstract syntax:

![alt text](https://github.com/vlazo1214/pl0-Compiler/blob/main/cfg1.jpg?raw=true)
![alt text](https://github.com/vlazo1214/pl0-Compiler/blob/main/cfg2.jpg?raw=true)

![alt text](https://github.com/vlazo1214/pl0-Compiler/blob/main/lg.jpg?raw=true)

![alt text](https://github.com/vlazo1214/pl0-Compiler/blob/main/as.jpg?raw=true)
