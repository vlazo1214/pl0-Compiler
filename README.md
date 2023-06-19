# pl0-Compiler

This project is a compiler that reads in a sample PL/0 program, parses through it creating abstract syntax trees (ASTs), and generates 3-letter assembly mnemonic instructions based on those ASTs. The rule behind creating tokens that comprise the ASTs is the following context-free grammar, lexical grammar, and abstract syntax:

⟨program⟩ ::= ⟨block⟩ .
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
⟨sign⟩ ::= ⟨plus⟩ | ⟨minus⟩ | ⟨empty⟩
