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
                                                                        # Frame size = 96
                                                                        # Number of Parameters/Locals/Temps = 1(6 registers), 2, 4
                                                                        # Frame size = (6 + 2 + 4) * 8 = 96
                                                                        # 16-byte-aligned frame size = 96
        subq $96, %rsp
                                                                        

                                                                        

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

