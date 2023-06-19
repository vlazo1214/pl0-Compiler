# pl0-Compiler

This project is a compiler that reads in a sample PL/0 program, parses through it creating abstract syntax trees (ASTs), and generates 3-letter assembly mnemonic instructions based on those ASTs. The rule behind creating tokens that comprise the ASTs is the following context-free grammar, lexical grammar, and abstract syntax:

```⟨program⟩ ::= ⟨block⟩ . 
⟨block⟩ ::= ⟨const-decls⟩ ⟨var-decls⟩ ⟨proc-decls⟩ ⟨stmt⟩
⟨const-decls⟩ ::= {⟨const-decl⟩}
⟨const-decl⟩ ::= const ⟨const-def⟩ {⟨comma-const-def⟩} ;
⟨const-def⟩ ::= ⟨ident⟩ = ⟨number⟩
⟨comma-const-def⟩ ::= , ⟨const-def⟩
⟨var-decls⟩ ::= {⟨var-decl⟩}
⟨var-decl⟩ ::= var ⟨idents⟩ ;
⟨idents⟩ ::= ⟨ident⟩ {⟨comma-ident⟩}
⟨comma-ident⟩ ::= , ⟨ident⟩

⟨proc-decls⟩ ::= {⟨proc-decl⟩}
⟨proc-decl⟩ ::= procedure ⟨ident⟩ ; ⟨block⟩ ;

⟨stmt⟩ ::= ⟨ident⟩ := ⟨expr⟩
    | call ⟨ident⟩
    | begin ⟨stmt⟩ {⟨semi-stmt⟩} end
    | if ⟨condition⟩ then ⟨stmt⟩ else ⟨stmt⟩
    | while ⟨condition⟩ do ⟨stmt⟩
    | read ⟨ident⟩
    | write ⟨expr⟩
    | skip

⟨semi-stmt⟩ ::= ; ⟨stmt⟩
⟨empty⟩ ::=

⟨condition⟩ ::= odd ⟨expr⟩
    | ⟨expr⟩ ⟨rel-op⟩ ⟨expr⟩

⟨rel-op⟩ ::= = | <> | < | <= | > | >=
⟨expr⟩ ::= ⟨term⟩ {⟨add-sub-term⟩}
⟨add-sub-term⟩ ::= ⟨add-sub⟩ ⟨term⟩
⟨add-sub⟩ ::= ⟨plus⟩ | ⟨minus⟩
⟨term⟩ ::= ⟨factor⟩ {⟨mult-div-factor⟩}
⟨mult-div-factor⟩ ::= ⟨mult-div⟩ ⟨factor⟩
⟨mult-div⟩ ::= ⟨mult⟩ | ⟨div⟩
⟨factor⟩ ::= ⟨ident⟩ | ⟨sign⟩ ⟨number⟩ | ( ⟨expr⟩ )
⟨sign⟩ ::= ⟨plus⟩ | ⟨minus⟩ | ⟨empty⟩```

```⟨ident⟩ ::= ⟨letter⟩ {⟨letter-or-digit⟩}
⟨letter⟩ ::= a | b | . . . | y | z | A | B | . . . | Y | Z
⟨number⟩ ::= ⟨digit⟩ {⟨digit⟩}
⟨digit⟩ ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
⟨letter-or-digit⟩ ::= ⟨letter⟩ | ⟨digit⟩
⟨plus⟩ ::= +
⟨minus⟩ ::= -
⟨mult⟩ ::= *
⟨div⟩ ::= /
⟨ignored⟩ ::= ⟨blank⟩ | ⟨tab⟩ | ⟨vt⟩ | ⟨formfeed⟩ | ⟨eol⟩ | ⟨comment⟩
⟨blank⟩ ::= “A space character (ASCII 32)”
⟨tab⟩ ::= “A horizontal tab character (ASCII 9)”
⟨vt⟩ ::= “A vertical tab character (ASCII 11)”
⟨formfeed⟩ ::= “A formfeed character (ASCII 12)”
⟨newline⟩ ::= “A newline character (ASCII 10)”
⟨cr⟩ ::= “A carriage return character (ASCII 13)”
⟨eol⟩ ::= ⟨newline⟩ | ⟨cr⟩ ⟨newline⟩
⟨comment⟩ ::= ⟨pound-sign⟩ {⟨non-nl⟩} ⟨newline⟩
⟨pound-sign⟩ ::= #
⟨non-nl⟩ ::= “Any character except a newline”``

``⟨program⟩ ::= {⟨const-decl⟩} {⟨var-decl⟩} {⟨proc-decl⟩} ⟨stmt⟩
⟨const-decl⟩ ::= const ⟨name⟩ = ⟨number⟩
⟨var-decl⟩ ::= var ⟨name⟩
⟨proc-decl⟩ ::= procedure ⟨name⟩ ⟨program⟩
⟨stmt⟩ ::= ⟨ident⟩ := ⟨expr⟩
| call ⟨ident⟩
| begin ⟨stmt⟩ {⟨stmt⟩}
| if ⟨condition⟩ then ⟨stmt⟩ else ⟨stmt⟩
| while ⟨condition⟩ do ⟨stmt⟩
| read ⟨ident⟩
| write ⟨expr⟩
| skip
⟨ident⟩ ::= ⟨name⟩ ⟨id-use⟩
⟨id-use⟩ ::= ⟨attrs⟩ ⟨levelsOutward⟩
⟨attrs⟩ ::= ⟨file-location⟩ ⟨kind⟩ ⟨loc-offset⟩ ⟨label⟩
⟨kind⟩ ::= constant | variable | procedure
⟨label⟩ ::= ⟨unset-label⟩ | ⟨set-label⟩
⟨unset-label⟩ ::= unset-label false
⟨set-label⟩ ::= set-label ⟨address⟩
⟨condition⟩ ::= odd ⟨expr⟩ | ⟨expr⟩ ⟨rel-op⟩ ⟨expr⟩
⟨rel-op⟩ ::= = | <> | < | <= | > | >=
⟨expr⟩ ::= ⟨expr⟩ ⟨bin-arith-op⟩ ⟨expr⟩ | ⟨ident⟩ | ⟨number⟩
⟨bin-arith-op⟩ ::= + | - | * | /```
