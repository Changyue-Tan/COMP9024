# **************************** Auto-Generated by scc  *******************************#
#                                                                                    #
# 1. For better understanding of C, recursion, call stack, tree and linked list.     #
#                                                                                    #
# 2. No code optimization.                                                           #
#                                                                                    #
# 3. Three columns in the assembly file: assembly code, IR, and comments             #
#                                                                                    #
#                                                           COMP9024                 #
# ***********************************************************************************#



                                                                        # Data Section
.data
        .input_fmtstr: .string "%ld"
        .output_fmtstr: .string "%ld\012"
                                                                        




# *****************************  main(argc,argv,env)  *****************************
                                                                        # Code Section
.text
.globl main
main:
                                                                        # Function Prologue
        pushq %rbp
        movq %rsp, %rbp
                                                                        # Frame size = 224
                                                                        # Number of Parameters/Locals/Temps = 3(6 registers), 4, 18
                                                                        # Frame size = (6 + 4 + 18) * 8 = 224
                                                                        # 16-byte-aligned frame size = 224
        subq $224, %rsp
                                                                        

                                                                        

                                                                        # Table of Function Parameters
                                                                        # ----------------------------
                                                                        #   AccessName        Name
                                                                        # ----------------------------
                                                                        #     -8(%rbp)        argc
                                                                        #    -16(%rbp)        argv
                                                                        #    -24(%rbp)        env
                                                                        # ----------------------------
                                                                        

                                                                        # Table of Local Variables
                                                                        # ----------------------------
                                                                        #   AccessName        Name
                                                                        # ----------------------------
                                                                        #
                                                                        #    -56(%rbp)        base
                                                                        #    -64(%rbp)        i
                                                                        #    -72(%rbp)        val
                                                                        #    -80(%rbp)        tmp
                                                                        # ----------------------------
                                                                        

                                                                        # Simple policy for saving arguments passed in registers
        movq %rdi, -8(%rbp)
        movq %rsi, -16(%rbp)
        movq %rdx, -24(%rbp)
                                                                        

                                                                        # Pass an argument: 2024
        movq $2024, %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t0 = SccMalloc(2024)
        call SccMalloc
                                                                        # Copy the return value from SccMalloc() to a temporary variable t0
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -88(%rbp)        t0
                                                                        # ----------------------------
                                                                        

        movq %rax, -88(%rbp)
                                        # base = t0;
        movq -88(%rbp), %rax
        movq %rax, -56(%rbp)
                                        # val = 97;
        movq $97, %rax
        movq %rax, -72(%rbp)
                                        # i = 0;
        movq $0, %rax
        movq %rax, -64(%rbp)
                                                                        

                                        # start of while (t1) {}
Label_0:
                                                                        # Pass an argument: i
        movq -64(%rbp), %rdi
                                                                        # Pass an argument: 26
        movq $26, %rsi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t1 = SccLess(i,26)
        call SccLess
                                                                        # Copy the return value from SccLess() to a temporary variable t1
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -96(%rbp)        t1
                                                                        # ----------------------------
                                                                        

        movq %rax, -96(%rbp)
                                        # if(!t1) goto Label_1
        cmpq $0, -96(%rbp)
        je Label_1
                                                                        

                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -104(%rbp)        t2
                                                                        # ----------------------------
                                                                        

                                        # t2 = val + i
        movq -72(%rbp), %rax
        addq -64(%rbp), %rax
        movq %rax, -104(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: i
        movq -64(%rbp), %rsi
                                                                        # Pass an argument: t2
        movq -104(%rbp), %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t3 = SccWrite8(base,i,t2)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t3
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -112(%rbp)        t3
                                                                        # ----------------------------
                                                                        

        movq %rax, -112(%rbp)
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -120(%rbp)        t4
                                                                        # ----------------------------
                                                                        

                                        # t4 = i + 1
        movq -64(%rbp), %rax
        addq $1, %rax
        movq %rax, -120(%rbp)
                                        # i = t4;
        movq -120(%rbp), %rax
        movq %rax, -64(%rbp)
                                                                        

                                        # goto Label_0
        jmp Label_0
                                                                        

                                        # end of while(t1) do {}
Label_1:
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 26
        movq $26, %rsi
                                                                        # Pass an argument: 0
        movq $0, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t5 = SccWrite8(base,26,0)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t5
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -128(%rbp)        t5
                                                                        # ----------------------------
                                                                        

        movq %rax, -128(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t6 = puts(base)
        call puts
                                                                        # Copy the return value from puts() to a temporary variable t6
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -136(%rbp)        t6
                                                                        # ----------------------------
                                                                        

        movq %rax, -136(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 0
        movq $0, %rsi
                                                                        # Pass an argument: 112
        movq $112, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t7 = SccWrite8(base,0,112)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t7
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -144(%rbp)        t7
                                                                        # ----------------------------
                                                                        

        movq %rax, -144(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 1
        movq $1, %rsi
                                                                        # Pass an argument: 121
        movq $121, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t8 = SccWrite8(base,1,121)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t8
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -152(%rbp)        t8
                                                                        # ----------------------------
                                                                        

        movq %rax, -152(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 2
        movq $2, %rsi
                                                                        # Pass an argument: 116
        movq $116, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t9 = SccWrite8(base,2,116)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t9
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -160(%rbp)        t9
                                                                        # ----------------------------
                                                                        

        movq %rax, -160(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 3
        movq $3, %rsi
                                                                        # Pass an argument: 104
        movq $104, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t10 = SccWrite8(base,3,104)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t10
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -168(%rbp)        t10
                                                                        # ----------------------------
                                                                        

        movq %rax, -168(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 4
        movq $4, %rsi
                                                                        # Pass an argument: 111
        movq $111, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t11 = SccWrite8(base,4,111)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t11
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -176(%rbp)        t11
                                                                        # ----------------------------
                                                                        

        movq %rax, -176(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 5
        movq $5, %rsi
                                                                        # Pass an argument: 110
        movq $110, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t12 = SccWrite8(base,5,110)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t12
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -184(%rbp)        t12
                                                                        # ----------------------------
                                                                        

        movq %rax, -184(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 6
        movq $6, %rsi
                                                                        # Pass an argument: 51
        movq $51, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t13 = SccWrite8(base,6,51)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t13
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -192(%rbp)        t13
                                                                        # ----------------------------
                                                                        

        movq %rax, -192(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # Pass an argument: 7
        movq $7, %rsi
                                                                        # Pass an argument: 0
        movq $0, %rdx
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t14 = SccWrite8(base,7,0)
        call SccWrite8
                                                                        # Copy the return value from SccWrite8() to a temporary variable t14
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -200(%rbp)        t14
                                                                        # ----------------------------
                                                                        

        movq %rax, -200(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t15 = puts(base)
        call puts
                                                                        # Copy the return value from puts() to a temporary variable t15
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -208(%rbp)        t15
                                                                        # ----------------------------
                                                                        

        movq %rax, -208(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t16 = system(base)
        call system
                                                                        # Copy the return value from system() to a temporary variable t16
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -216(%rbp)        t16
                                                                        # ----------------------------
                                                                        

        movq %rax, -216(%rbp)
                                                                        # Pass an argument: base
        movq -56(%rbp), %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t17 = SccFree(base)
        call SccFree
                                                                        # Copy the return value from SccFree() to a temporary variable t17
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -224(%rbp)        t17
                                                                        # ----------------------------
                                                                        

        movq %rax, -224(%rbp)
                                        # return 0;
                                                                        # Save current function's return value 0 in register rax
        movq $0, %rax
                                                                        # Function Epilogue
        movq %rbp, %rsp
        popq %rbp
        ret
                                                                        

        

   .section .note.GNU-stack,"",@progbits

