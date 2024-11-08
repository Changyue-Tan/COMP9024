#include "expr.h"
#include "emit.h"
#include "error.h"
#include "func.h"
#include "lex.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_VAR_NAME_FMT "t%d"

//#define ADD_RIGHT_ASSOCIATIVITY
//#define MUL_RIGHT_ASSOCIATIVITY

/////////////////////////////////////////////////////////////////////

// the offset in the function frame
static int offset;
// the number of temporary variables
static int tmpNo;

// The first token of an expression in SCC
static TokenKind prefixOfExpr[] = {TK_ID, TK_LPAREN, TK_NUM};
/////////////////////////////////////////////////////////////////////

/*
    Check whether tk is the first token of an expression.
 */
static int isPrefixOfExpression(TokenKind tk) {
    int i = 0;
    for (i = 0; i < sizeof(prefixOfExpr) / sizeof(prefixOfExpr[0]); i++) {
        if (tk == prefixOfExpr[i]) {
            return 1;
        }
    }
    return 0;
}

// The stack space SCC allocates for the current function definition
int GetFrameSize(void) { return -offset; }

int GetTmpVarNum(void) { return tmpNo; }

// To be simple, always reserve stack space for the six registers
// (rdi, rsi, rdx, rcx, r8, r9)
void ResetFrameSize(void) {
    offset = -(CPU_WORD_SIZE_IN_BYTES * NUM_OF_ARGS_IN_REGS);
    tmpNo = 0;
}

// Temporary variables are named as "t0", "t1", "t2", .... for debugging.
// They are generated by arithmetic operations like a+b, a-b, a*b, a/b.
static int NewTemp(void) { return tmpNo++; }

/*
    Allocate stack space for a local/temporary variable.
    We need to calculate its offset relative to the frame pointer (rbp).
    
    A temporary variable is introduced by scc (e.g.,  when processing "a + b"), 
    not named by programmers. 
  
    Note that a function parameter' offset has been calculated in FunctionDefinition().
 */
int AllocFrameOffset(void) {
    offset -= CPU_WORD_SIZE_IN_BYTES;
    return offset;
}

/*
    Create an Ast node for an expression.
 */
AstExprNodePtr CreateAstExprNode(TokenKind tk, Value *pVal, AstExprNodePtr left,
                                 AstExprNodePtr right) {
    AstExprNodePtr pNode = (AstExprNodePtr)malloc(sizeof(struct astExprNode));
    assert(pNode != NULL && pVal != NULL);

    memset(pNode, 0, sizeof(*pNode));
    pNode->op = tk;
    pNode->value = *pVal;
    pNode->kids[0] = left;
    pNode->kids[1] = right;
    return pNode;
}

/*
    We expect that the current token in the input stream is tk.
  
    If it is as expected
      get the next token
    else
      report an error  
 */
void DoExpect(char *sccFile, int sccLine, TokenKind tk) {
    if (curToken.kind == tk) {
        NEXT_TOKEN;
    } else {
        Error(sccFile, sccLine, "\"%s\" expected", GetTokenName(tk));
    }
}

/*
    FunctionCallExpression:

        ID (Expression, Expression, ..., Expression)
 */
AstExprNodePtr FunctionCallExpression(Token savedToken) {
    AstExprNodePtr expr = NULL;

    assert(savedToken.kind == TK_ID);
    assert(curToken.kind == TK_LPAREN);

    expr = CreateAstExprNode(TK_CALL, &savedToken.value, NULL, NULL);
    NEXT_TOKEN;
    // Analyzing "expr, expr, ..., expr" in a function call
    //    function call:  ID (expr, expr, ..., expr)
    int arg_cnt = 0;
    while (isPrefixOfExpression(curToken.kind)) {
        expr->args[arg_cnt] = Expression();
        arg_cnt++;
        if (arg_cnt > MAX_ARG_CNT) {
            Error(__FILE__, __LINE__, "only %d arguments allowed", MAX_ARG_CNT);
        }
        if (curToken.kind == TK_COMMA) {
            NEXT_TOKEN;
            if (!isPrefixOfExpression(curToken.kind)) {
                Error(__FILE__, __LINE__, "',' redundant");
            }
        } else if (curToken.kind == TK_RPAREN) {
            break;
        } else {
            Error(__FILE__, __LINE__, "illegal tokens");
        }
    }
    Expect(TK_RPAREN);
    expr->arg_cnt = arg_cnt;
    // allocate a temp for storing the return value
    expr->offset = AllocFrameOffset();
    snprintf(expr->retValTmp, MAX_ID_LEN, TEMP_VAR_NAME_FMT, NewTemp());
    return expr;
}

/*
    PrimaryExpression:
        ID (Expression, Expression, ..., Expression)
        ID
        NUM
        (Expression)
 */
static AstExprNodePtr PrimaryExpression(void) {
    AstExprNodePtr expr = NULL;
    if (curToken.kind == TK_ID) {
        Token savedToken = curToken;
        NEXT_TOKEN;
        if (curToken.kind == TK_LPAREN) { // function call
            expr = FunctionCallExpression(savedToken);
        } else { // id
            expr = CreateAstExprNode(savedToken.kind, &savedToken.value, NULL,
                                     NULL);
        }
    } else if (curToken.kind == TK_NUM) {
        expr = CreateAstExprNode(curToken.kind, &curToken.value, NULL, NULL);

        NEXT_TOKEN;
    } else if (curToken.kind == TK_LPAREN) {
        NEXT_TOKEN;
        expr = Expression();
        Expect(TK_RPAREN);
    } else {
        Error(__FILE__, __LINE__, "id, number or '(' expected");
    }
    return expr;
}

/*
    mop:
                  *  
                  /
    
    MultiplicativeExpression:
              PrimaryExpression mop PrimaryExpression  ...  mop PrimaryExpression

    -------------------------------------------------------------------------------
  
    (1)  Left Associativity
  
    MultiplicativeExpression:
        MultiplicativeExpression * PrimaryExpression
        MultiplicativeExpression / PrimaryExpression
        PrimaryExpression
  
    (2)  Right Associativity
  
    MultiplicativeExpression:
        PrimaryExpression * MultiplicativeExpression
        PrimaryExpression / MultiplicativeExpression
        PrimaryExpression
 */
static AstExprNodePtr MultiplicativeExpression(void) {
#ifndef MUL_RIGHT_ASSOCIATIVITY
    AstExprNodePtr left;
    left = PrimaryExpression();
    while (curToken.kind == TK_MUL || curToken.kind == TK_DIV) {
        Value value;
        AstExprNodePtr expr;
        memset(&value, 0, sizeof(value));
        snprintf(value.name, MAX_ID_LEN, TEMP_VAR_NAME_FMT, NewTemp());
        expr = CreateAstExprNode(curToken.kind, &value, NULL, NULL);
        expr->offset = AllocFrameOffset();
        NEXT_TOKEN;
        expr->kids[0] = left;
        expr->kids[1] = PrimaryExpression();
        left = expr;
    }
    return left;
#else
    AstExprNodePtr left;
    left = PrimaryExpression();
    if (curToken.kind == TK_MUL || curToken.kind == TK_DIV) {
        Value value;
        AstExprNodePtr expr;
        memset(&value, 0, sizeof(value));
        snprintf(value.name, MAX_ID_LEN, TEMP_VAR_NAME_FMT, NewTemp());
        expr = CreateAstExprNode(curToken.kind, &value, NULL, NULL);
        expr->offset = AllocFrameOffset();
        NEXT_TOKEN;
        expr->kids[0] = left;
        expr->kids[1] = MultiplicativeExpression();
        return expr;
    } else {
        return left;
    }
#endif
}

/*
    aop:
                *  
                /
  
    AdditiveExpression:
          MultiplicativeExpression aop MultiplicativeExpression  ...  aop MultiplicativeExpression 
  
    -------------------------------------------------------------------------------             
  
    (1)  Left Associativity
  
    AdditiveExpression:
        MultiplicativeExpression
        AdditiveExpression + MultiplicativeExpression
        AdditiveExpression - MultiplicativeExpression
  
    (2)  Right Associativity
  
    AdditiveExpression:
        MultiplicativeExpression
        MultiplicativeExpression + AdditiveExpression
        MultiplicativeExpression - AdditiveExpression
 */
static AstExprNodePtr AdditiveExpression(void) {
#ifndef ADD_RIGHT_ASSOCIATIVITY
    AstExprNodePtr left;
    left = MultiplicativeExpression();
    while (curToken.kind == TK_SUB || curToken.kind == TK_ADD) {
        Value value;
        AstExprNodePtr expr;
        memset(&value, 0, sizeof(value));
        snprintf(value.name, MAX_ID_LEN, TEMP_VAR_NAME_FMT, NewTemp());
        expr = CreateAstExprNode(curToken.kind, &value, NULL, NULL);
        expr->offset = AllocFrameOffset();
        NEXT_TOKEN;
        expr->kids[0] = left;
        expr->kids[1] = MultiplicativeExpression();
        left = expr;
    }
    return left;
#else
    AstExprNodePtr left;
    left = MultiplicativeExpression();
    if (curToken.kind == TK_SUB || curToken.kind == TK_ADD) {
        Value value;
        AstExprNodePtr expr;
        memset(&value, 0, sizeof(value));
        snprintf(value.name, MAX_ID_LEN, TEMP_VAR_NAME_FMT, NewTemp());
        expr = CreateAstExprNode(curToken.kind, &value, NULL, NULL);
        expr->offset = AllocFrameOffset();
        NEXT_TOKEN;
        expr->kids[0] = left;
        expr->kids[1] = AdditiveExpression();
        return expr;
    } else {
        return left;
    }
#endif
}

/*
    Expression:
        AdditiveExpression
  */
AstExprNodePtr Expression(void) { return AdditiveExpression(); }

static int IsArithmeticNode(AstExprNodePtr pNode) {
    return pNode->op == TK_SUB || pNode->op == TK_ADD || pNode->op == TK_MUL ||
           pNode->op == TK_DIV;
}

/*
    Find a symbol @id in the local symbol table @symTable. 
    The parameter @size is the size of the local symbol table. 
  
    If found,
      return its offset relative to the frame pointer (negative or positive)
    else
      return 0
 */
static int SearchInSymbolTable(struct astExprNode *symTable, int size,
                               char *id) {
    for (int i = 0; i < size; i++) {
        int len = strlen(id);
        int len2 = strlen(symTable[i].value.name);
        if (strncmp(symTable[i].value.name, id, len) == 0 &&
            len == len2) { // equal
            return symTable[i].offset;
        }
    }
    return 0;
}

/*
    Searching in our local symbol table in the function definition
    (paras[] and local_vars[] in struct astFuncDefNode in func.h)
  
    According to the stack layout in func.c,
    the offset of local variables and parameters are either negative or positive.
    So we can use 0 as a special return value when we can't find a local variable or a parameter 
    whose name is equal to id in the current function.
    If the return value is 0, we will assume id is a global variable (Please refer to GetNodeNameInAssembly()).
 */
static int GetLocalVarOrParameterOffset(char *id) {
    AstFuncDefNodePtr func = GetCurFuncDef();
    assert(func);
    // check function formal parameters first
    int offset = SearchInSymbolTable(func->paras, func->para_cnt, id);
    if (offset == 0) {
        // then check local variables
        offset =
            SearchInSymbolTable(func->local_vars, func->local_vars_cnt, id);
    }
    return offset;
}

/* 
    Get the access name of an AST node.
    An access name is a string that represents the AST node in the assembly code.
  
    (1) Global variable
  
        It is allocated in the global/static memory area.
  
           Its name (e.g., 'year') is used as its string represention in the assembly code.
           Finally, the name will be replaced with an absolute/relative address by the linker.
  
    (2) Local variable, function parameter, and temporary varaible
  
        It is allocated on the call stack at runtime. 
        We only calculate its offset at compiling time.
  
        Its access name in the assembly code are as follows:
  
           offset (%rbp)
  
        where rbp is the frame (base) pointer register for a function, and offset is an integer constant (e.g., 16).
  
        See the stack memory layout in func.c.
        The callee's rbp will be set in EmitPrologue(int frameSize) in emit.c.
  
        When the callee is returning, its caller's frame pointer will be restored in EmitEpilogue(void).
  
    (3) Integer constant 
  
        For example, 15 is represented as $15 (AT&T Assembly Syntax)       
  
          $15 
  
        Please refer to 
  
          movl $1, 0x604892         # direct (address is constant value)
  
          https://web.stanford.edu/class/cs107/guide/x86-64.html         
         
 */
char *GetNodeNameInAssembly(AstExprNodePtr pNode) {
    if (pNode) {
        if (pNode->op == TK_ID) {
            int offset = GetLocalVarOrParameterOffset(pNode->value.name);
            if (offset != 0) {
                // FIXME:
                // function parameters: offset > 0;
                // local variables: offset < 0
                snprintf(pNode->accessName, MAX_ID_LEN + 1, "%d(%%rbp)",
                         offset);
            } else { // global variables, 'year'
                snprintf(pNode->accessName, MAX_ID_LEN + 1, "%s",
                         pNode->value.name);
            }
        } else if (pNode->op == TK_NUM) { // integer constant, such as 15
            snprintf(pNode->accessName, MAX_ID_LEN + 1, "$%ld",
                     pNode->value.numVal);
        } else { // temporary variables, a+b
            snprintf(pNode->accessName, MAX_ID_LEN + 1, "%d(%%rbp)",
                     pNode->offset);
        }
        return pNode->accessName;
    } else {
        return "";
    }
}

/*
    We add some comments in the assembly file to make the assembly code more readable.
  
    1. For a temporary variable, 
  
       its node name in the comments is like t0, t1, ...
  
    2. For a global/local variable,
     
       its id name is used.
    
    3. For a number, 300, 
       
       its string representation ("300") is used.
    
    4. For a function call (TK_CALL), say, t5 = f()
  
       we use the name ("t5") of the temporary variable for representing the return value.

 */
char *GetNodeNameInIR(AstExprNodePtr pNode) {
    if (!pNode)
        return "";
    if (pNode->op == TK_CALL)
        return pNode->retValTmp;
    else
        return pNode->value.name;
}

static void OutputTmpVarInfo(AstExprNodePtr tmpVar) {
#define SYMBOL_TABLE_OUTPUT_FMT "# %12s        %s"
    EmitComments("\n");
    EmitComments("# ----------------------------");
    EmitComments(SYMBOL_TABLE_OUTPUT_FMT, "AccessName", "Temp Var");
    EmitComments("# ----------------------------");

    EmitComments(SYMBOL_TABLE_OUTPUT_FMT, GetNodeNameInAssembly(tmpVar),
                 GetNodeNameInIR(tmpVar));
    EmitComments("# ----------------------------");
#undef SYMBOL_TABLE_OUTPUT_FMT
    EmitComments("\n");
}

/*
    Generate assembly code for expressions (including +, -, *, / and functions calls)
 */
void EmitAstExprNode(AstExprNodePtr pNode) {
    // https://en.wikipedia.org/wiki/X86_calling_conventions
    static char *x64ArgRegs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    if (pNode == NULL) {
        return;
    }

    if (pNode->op ==
        TK_CALL) { // function call can be seen as an expression, say, f(n) + 30
        int cnt = 0;
        // argNamesInComments is used in comments in assembly code
        char argNamesInComments[MAX_ARG_CNT * (MAX_ID_LEN + 1)];
        memset(argNamesInComments, 0, sizeof(argNamesInComments));
        // evaluate arguments (as expressions) from left to right
        while (cnt < pNode->arg_cnt) {
            EmitAstExprNode(pNode->args[cnt]);
            strcat(argNamesInComments, GetNodeNameInIR(pNode->args[cnt]));
            if (cnt < pNode->arg_cnt - 1) {
                strcat(argNamesInComments, ",");
            }
            cnt++;
        }
        int numOfRegs = (pNode->arg_cnt >= NUM_OF_ARGS_IN_REGS)
                            ? NUM_OF_ARGS_IN_REGS
                            : pNode->arg_cnt;
        // move arguments to registers as required by SysV ABI
        for (cnt = 0; cnt < numOfRegs; ++cnt) {
            /**********************************************************************
             The format string %%%s consists of two parts.
            
                 %% is escaped as '%'
                 %s corresponds to a register name like 'rdi'
                 
                 Put them together(i.e., %%%s), we can have %rdi in the output. (AT&T Assembly Syntax)      
             **********************************************************************/
            EmitComments("# Pass an argument: %s",
                         GetNodeNameInIR(pNode->args[cnt]));
            EmitAssembly("movq %s, %%%s",
                         GetNodeNameInAssembly(pNode->args[cnt]),
                         x64ArgRegs[cnt]);
        }
        // push the other arguments from right to left
        if (pNode->arg_cnt > NUM_OF_ARGS_IN_REGS) {
            if (pNode->arg_cnt % 2 != 0) {
                /*
                    Adjust the stack pointer rsp of CPU,
                    such that it is 16-byte aligned (required by the SysV ABI).
                    The stack pointer should be aligned to 16 bytes before a function is called.
         
                    Simply speaking, 
                    If the number of arguments is odd (e.g., 7, 9, 11, ...),
                    emit 'subq	$8, %rsp` for a 16-byte aligned rsp.
                    AS the call stack grows from high to low addresses,
                    a 'push' will decrease the stack pointer rsp.
                 */
                EmitComments("# Make the stack pointer rsp 16-byte aligned");
                EmitAssembly("subq $%ld, %%rsp", CPU_WORD_SIZE_IN_BYTES);
            }
            cnt = pNode->arg_cnt;
            while (cnt > NUM_OF_ARGS_IN_REGS) {
                EmitComments("# Push an argument %s onto the call stack",
                             GetNodeNameInIR(pNode->args[cnt - 1]));
                EmitAssembly("pushq %s",
                             GetNodeNameInAssembly(pNode->args[cnt - 1]));
                cnt--;
            }
        }
        // call the function
        // FIXME:
        // "rax == 0" means no floating-point numbers when calling a variadic function.
        // Conservatively set rax to be 0 for every called function (even it is not variadic).
        EmitComments(
            "# No floating-point numbers when calling a variadic function");
        EmitAssembly("movq $0, %%rax");
        EmitIR("# %s = %s(%s)", GetNodeNameInIR(pNode), pNode->value.name,
               argNamesInComments);
        EmitAssembly("call %s", pNode->value.name);
        /*
            See the comments before we emit the "call" instruction.
            When the callee function (called), the caller function need to restore the stack pointer.
         */
        if (pNode->arg_cnt > NUM_OF_ARGS_IN_REGS) {
            int rspAdjust =
                CPU_WORD_SIZE_IN_BYTES * (pNode->arg_cnt - NUM_OF_ARGS_IN_REGS);
            // If the number of arguments is odd (7, 9, 11, ...).
            if (pNode->arg_cnt % 2 != 0) {
                rspAdjust += CPU_WORD_SIZE_IN_BYTES;
            }
            EmitComments("# Pop the arguments on the call stack");
            EmitAssembly("addq $%d, %%rsp", rspAdjust);
        }
        // move the return value (saved in register %rax) to a temporary variable.
        // Now a function call is finished.
        EmitComments(
            "# Copy the return value from %s() to a temporary variable %s",
            pNode->value.name, GetNodeNameInIR(pNode));
        OutputTmpVarInfo(pNode);
        EmitAssembly("movq %%rax, %s", GetNodeNameInAssembly(pNode));
    } else if (IsArithmeticNode(pNode)) { // arithmetic expressions
        // recursively generate assembly code for the left and right operands
        EmitAstExprNode(pNode->kids[0]);
        EmitAstExprNode(pNode->kids[1]);
        if (pNode->kids[0] && pNode->kids[1]) { // +, -, *, /
            switch (pNode->op) {
            case TK_ADD: // left + right
                /*************************************************************
                    Expression:
           
                               +                 
                         left     right
           
                    Description:
                    
                         pNode->kids[0] is the left operand
                         pNode->kids[1] is the right operand
                         pNode is the operator  
                    
                    Example:
                         movq  left, %rax                # move the 64-bit left operand to register %rax
                                                         # the 'q' in 'movq' means it is a 64-bit operation.
           
                         addq  right, %rax               # do the addition
                                                         # %rax = %rax + right
           
                         movq  %rax, -64(%rbp)           # Save the result to a temporary variable,
                                                         # -64(%rbp) is its access name
                *************************************************************/
                OutputTmpVarInfo(pNode);
                EmitIR("# %s = %s + %s", GetNodeNameInIR(pNode),
                       GetNodeNameInIR(pNode->kids[0]),
                       GetNodeNameInIR(pNode->kids[1]));
                EmitAssembly("movq %s, %%rax",
                             GetNodeNameInAssembly(pNode->kids[0]));
                EmitAssembly("addq %s, %%rax",
                             GetNodeNameInAssembly(pNode->kids[1]));
                EmitAssembly("movq %%rax, %s", GetNodeNameInAssembly(pNode));
                break;
            case TK_SUB: // left - right
                OutputTmpVarInfo(pNode);
                EmitIR("# %s = %s - %s", GetNodeNameInIR(pNode),
                       GetNodeNameInIR(pNode->kids[0]),
                       GetNodeNameInIR(pNode->kids[1]));
                EmitAssembly("movq %s, %%rax",
                             GetNodeNameInAssembly(pNode->kids[0]));
                EmitAssembly("subq %s, %%rax",
                             GetNodeNameInAssembly(pNode->kids[1]));
                EmitAssembly("movq %%rax, %s", GetNodeNameInAssembly(pNode));
                break;
            case TK_MUL: // left * right
                OutputTmpVarInfo(pNode);
                EmitIR("# %s = %s * %s", GetNodeNameInIR(pNode),
                       GetNodeNameInIR(pNode->kids[0]),
                       GetNodeNameInIR(pNode->kids[1]));
                EmitAssembly("movq %s, %%rax",
                             GetNodeNameInAssembly(pNode->kids[0]));
                EmitAssembly("imulq %s, %%rax",
                             GetNodeNameInAssembly(pNode->kids[1]));
                EmitAssembly("movq %%rax, %s", GetNodeNameInAssembly(pNode));
                break;
            case TK_DIV: // left / right, i.e., dividend / divisor
                /***************************************************************************
                    Generating the assembly code for division.
           
                     Example:  left/right
           
                           movq  left, %rax
                           cqto                
                           movq  right, %rdi
                           idivq  %rdi
                           movq  %rax, -64(%rbp)           # -64(%rbp) is the access name of a temporary variable.
           
                     --------------------------------------------------------------------
                    movq  left, %rax
                         Put the dividend in the register rax
           
                    cqto
                         The 64-bit dividend (in rax) is sign-extended to be 128-bit.
           
                             rax  --->  rdx  rax
           
                         Then, (rdx, rax) becomes a 128-bit dividend.
           
                    movq  right, %rdi
           
                         Then we put the divisor in the register rdi.
           
                    idivq
                         Signed Divide in x86_64
           
                         When it is done, 
                           the quotient is put in rax, and 
                           the remainder is put in rdx.
           
                         quotient = dividend / divisor
                         remainder = dividend % divisor
           
                     movq  %rax, -64(%rbp)
           
                         move the result to a temporary variable whose access name is -64(%rbp)
           
                    If you are interested in computer systems, you can have a brief look at the following link.        
                    
                         https://www.cs.cmu.edu/~fp/courses/15213-s07/misc/asm64-handout.pdf
           
           
                ****************************************************************************/
                OutputTmpVarInfo(pNode);
                EmitIR("# %s = %s / %s", GetNodeNameInIR(pNode),
                       GetNodeNameInIR(pNode->kids[0]),
                       GetNodeNameInIR(pNode->kids[1]));
                EmitAssembly("movq %s, %%rax",
                             GetNodeNameInAssembly(pNode->kids[0]));
                EmitAssembly("cqto");
                EmitAssembly("movq %s, %%rdi",
                             GetNodeNameInAssembly(pNode->kids[1]));
                EmitAssembly("idivq %%rdi");
                EmitAssembly("movq %%rax, %s", GetNodeNameInAssembly(pNode));
                break;
            }
        }
    }
}

