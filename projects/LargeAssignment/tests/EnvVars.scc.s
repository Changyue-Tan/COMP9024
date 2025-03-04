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
                                                                        




# *****************************  printStrs(strs)  *****************************
                                                                        # Code Section
.text
.globl printStrs
printStrs:
                                                                        # Function Prologue
        pushq %rbp
        movq %rsp, %rbp
                                                                        # Frame size = 112
                                                                        # Number of Parameters/Locals/Temps = 1(6 registers), 2, 6
                                                                        # Frame size = (6 + 2 + 6) * 8 = 112
                                                                        # 16-byte-aligned frame size = 112
        subq $112, %rsp
                                                                        

                                                                        

                                                                        # Table of Function Parameters
                                                                        # ----------------------------
                                                                        #   AccessName        Name
                                                                        # ----------------------------
                                                                        #     -8(%rbp)        strs
                                                                        # ----------------------------
                                                                        

                                                                        # Table of Local Variables
                                                                        # ----------------------------
                                                                        #   AccessName        Name
                                                                        # ----------------------------
                                                                        #
                                                                        #    -56(%rbp)        i
                                                                        #    -64(%rbp)        s
                                                                        # ----------------------------
                                                                        

                                                                        # Simple policy for saving arguments passed in registers
        movq %rdi, -8(%rbp)
                                                                        

                                        # i = 0;
        movq $0, %rax
        movq %rax, -56(%rbp)
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -72(%rbp)        t0
                                                                        # ----------------------------
                                                                        

                                        # t0 = i * 8
        movq -56(%rbp), %rax
        imulq $8, %rax
        movq %rax, -72(%rbp)
                                                                        # Pass an argument: strs
        movq -8(%rbp), %rdi
                                                                        # Pass an argument: t0
        movq -72(%rbp), %rsi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t1 = SccRead64(strs,t0)
        call SccRead64
                                                                        # Copy the return value from SccRead64() to a temporary variable t1
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -80(%rbp)        t1
                                                                        # ----------------------------
                                                                        

        movq %rax, -80(%rbp)
                                        # s = t1;
        movq -80(%rbp), %rax
        movq %rax, -64(%rbp)
                                                                        

                                        # start of while (s) {}
Label_0:
                                        # if(!s) goto Label_1
        cmpq $0, -64(%rbp)
        je Label_1
                                                                        

                                                                        # Pass an argument: s
        movq -64(%rbp), %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t2 = puts(s)
        call puts
                                                                        # Copy the return value from puts() to a temporary variable t2
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -88(%rbp)        t2
                                                                        # ----------------------------
                                                                        

        movq %rax, -88(%rbp)
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -96(%rbp)        t3
                                                                        # ----------------------------
                                                                        

                                        # t3 = i + 1
        movq -56(%rbp), %rax
        addq $1, %rax
        movq %rax, -96(%rbp)
                                        # i = t3;
        movq -96(%rbp), %rax
        movq %rax, -56(%rbp)
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -104(%rbp)        t4
                                                                        # ----------------------------
                                                                        

                                        # t4 = i * 8
        movq -56(%rbp), %rax
        imulq $8, %rax
        movq %rax, -104(%rbp)
                                                                        # Pass an argument: strs
        movq -8(%rbp), %rdi
                                                                        # Pass an argument: t4
        movq -104(%rbp), %rsi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t5 = SccRead64(strs,t4)
        call SccRead64
                                                                        # Copy the return value from SccRead64() to a temporary variable t5
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #   -112(%rbp)        t5
                                                                        # ----------------------------
                                                                        

        movq %rax, -112(%rbp)
                                        # s = t5;
        movq -112(%rbp), %rax
        movq %rax, -64(%rbp)
                                                                        

                                        # goto Label_0
        jmp Label_0
                                                                        

                                        # end of while(s) do {}
Label_1:
                                                                        # Function Epilogue
        movq %rbp, %rsp
        popq %rbp
        ret
                                                                        

                                                                        




# *****************************  main(argc,argv,env)  *****************************
                                                                        # Code Section
.text
.globl main
main:
                                                                        # Function Prologue
        pushq %rbp
        movq %rsp, %rbp
                                                                        # Frame size = 72
                                                                        # Number of Parameters/Locals/Temps = 3(6 registers), 0, 3
                                                                        # Frame size = (6 + 0 + 3) * 8 = 72
                                                                        # 16-byte-aligned frame size = 80
        subq $80, %rsp
                                                                        

                                                                        

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
                                                                        # ----------------------------
                                                                        

                                                                        # Simple policy for saving arguments passed in registers
        movq %rdi, -8(%rbp)
        movq %rsi, -16(%rbp)
        movq %rdx, -24(%rbp)
                                                                        

                                        # output(argc);
        leaq .output_fmtstr, %rdi
        movq -8(%rbp), %rsi
        movq $0, %rax
        call printf
                                                                        # Pass an argument: argv
        movq -16(%rbp), %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t0 = printStrs(argv)
        call printStrs
                                                                        # Copy the return value from printStrs() to a temporary variable t0
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -56(%rbp)        t0
                                                                        # ----------------------------
                                                                        

        movq %rax, -56(%rbp)
                                                                        # Pass an argument: 10
        movq $10, %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t1 = putchar(10)
        call putchar
                                                                        # Copy the return value from putchar() to a temporary variable t1
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -64(%rbp)        t1
                                                                        # ----------------------------
                                                                        

        movq %rax, -64(%rbp)
                                                                        # Pass an argument: env
        movq -24(%rbp), %rdi
                                                                        # No floating-point numbers when calling a variadic function
        movq $0, %rax
                                        # t2 = printStrs(env)
        call printStrs
                                                                        # Copy the return value from printStrs() to a temporary variable t2
                                                                        

                                                                        # ----------------------------
                                                                        #   AccessName        Temp Var
                                                                        # ----------------------------
                                                                        #    -72(%rbp)        t2
                                                                        # ----------------------------
                                                                        

        movq %rax, -72(%rbp)
                                        # return 0;
                                                                        # Save current function's return value 0 in register rax
        movq $0, %rax
                                                                        # Function Epilogue
        movq %rbp, %rsp
        popq %rbp
        ret
                                                                        

        

   .section .note.GNU-stack,"",@progbits

