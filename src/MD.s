# mark_description "Intel(R) C Intel(R) 64 Compiler for applications running on Intel(R) 64, Version 17.0.2.174 Build 20170213";
# mark_description "-S -o MD.s";
	.file "MD.c"
	.text
..TXTST0:
# -- Begin  evolve
	.text
# mark_begin;
       .align    16,0x90
	.globl evolve
# --- evolve(int, double)
evolve:
# parameter 1: %edi
# parameter 2: %xmm0
..B1.1:                         # Preds ..B1.0
                                # Execution count [1.00e+00]
	.cfi_startproc
..___tag_value_evolve.1:
..L2:
                                                          #11.1
        subq      $88, %rsp                                     #11.1
	.cfi_def_cfa_offset 96
        movl      $1, %esi                                      #20.7
        movaps    %xmm0, %xmm2                                  #11.1
        testl     %edi, %edi                                    #20.22
        jle       ..B1.49       # Prob 10%                      #20.22
                                # LOE rbx rbp r12 r13 r14 r15 esi edi xmm2
..B1.2:                         # Preds ..B1.1
                                # Execution count [9.00e-01]
        xorl      %edx, %edx                                    #46.14
        movsd     %xmm2, 24(%rsp)                               #105.36[spill]
        movq      %r13, 32(%rsp)                                #105.36[spill]
	.cfi_offset 13, -64
        movl      %edi, %r13d                                   #105.36
        movq      %r14, 40(%rsp)                                #105.36[spill]
        movq      %r15, 48(%rsp)                                #105.36[spill]
        movq      %rbx, 56(%rsp)                                #105.36[spill]
	.cfi_offset 3, -40
	.cfi_offset 14, -56
	.cfi_offset 15, -48
        movq      %rdx, %rbx                                    #105.36
        movq      %rbp, 64(%rsp)                                #105.36[spill]
	.cfi_offset 6, -32
        movl      %esi, %ebp                                    #105.36
                                # LOE rbx r12 ebp r13d
..B1.3:                         # Preds ..B1.47 ..B1.2
                                # Execution count [1.03e+00]
        movl      $.L_2__STRING.0, %edi                         #22.5
        movl      %ebp, %esi                                    #22.5
        xorl      %eax, %eax                                    #22.5
..___tag_value_evolve.9:
#       printf(const char *__restrict__, ...)
        call      printf                                        #22.5
..___tag_value_evolve.10:
                                # LOE rbx r12 ebp r13d
..B1.4:                         # Preds ..B1.3
                                # Execution count [1.03e+00]
        movl      $.L_2__STRING.1, %edi                         #23.5
        xorl      %eax, %eax                                    #23.5
        movl      collisions(%rip), %esi                        #23.5
..___tag_value_evolve.11:
#       printf(const char *__restrict__, ...)
        call      printf                                        #23.5
..___tag_value_evolve.12:
                                # LOE rbx r12 ebp r13d
..B1.5:                         # Preds ..B1.4
                                # Execution count [1.03e+00]
        movq      vis(%rip), %rcx                               #39.21
        movq      %rbx, %rax                                    #33.5
                                # LOE rax rcx rbx r12 ebp r13d
..B1.6:                         # Preds ..B1.8 ..B1.5
                                # Execution count [3.09e+00]
        xorl      %r8d, %r8d                                    #35.7
        .align    16,0x90
                                # LOE rax rcx rbx r12 ebp r8d r13d
..B1.7:                         # Preds ..B1.7 ..B1.6
                                # Execution count [6.32e+03]
        movq      velo(,%rax,8), %r10                           #39.31
        lea       (%r8,%r8), %r9d                               #39.21
        movsd     wind(,%rax,8), %xmm0                          #39.44
        incl      %r8d                                          #35.7
        movsd     (%rcx,%r9,8), %xmm1                           #39.21
        xorps     .L_2il0floatpacket.2(%rip), %xmm1             #39.21
        movq      f(,%rax,8), %r11                              #39.9
        addsd     (%r10,%r9,8), %xmm0                           #39.44
        mulsd     %xmm0, %xmm1                                  #39.44
        movsd     %xmm1, (%r11,%r9,8)                           #39.9
        movq      velo(,%rax,8), %r14                           #39.31
        movsd     wind(,%rax,8), %xmm2                          #39.44
        movsd     8(%rcx,%r9,8), %xmm3                          #39.21
        xorps     .L_2il0floatpacket.2(%rip), %xmm3             #39.21
        movq      f(,%rax,8), %r15                              #39.9
        addsd     8(%r14,%r9,8), %xmm2                          #39.44
        mulsd     %xmm2, %xmm3                                  #39.44
        movsd     %xmm3, 8(%r15,%r9,8)                          #39.9
        cmpl      $2048, %r8d                                   #35.7
        jb        ..B1.7        # Prob 99%                      #35.7
                                # LOE rax rcx rbx r12 ebp r8d r13d
..B1.8:                         # Preds ..B1.7
                                # Execution count [3.09e+00]
        incq      %rax                                          #33.5
        cmpq      $3, %rax                                      #33.5
        jb        ..B1.6        # Prob 66%                      #33.5
                                # LOE rax rcx rbx r12 ebp r13d
..B1.9:                         # Preds ..B1.8
                                # Execution count [1.03e+00]
        movq      r(%rip), %rax                                 #46.7
        movq      %rbx, %rcx                                    #44.5
        .align    16,0x90
                                # LOE rax rcx rbx r12 ebp r13d
..B1.10:                        # Preds ..B1.10 ..B1.9
                                # Execution count [4.21e+03]
        movq      %rbx, (%rax,%rcx,8)                           #46.7
        movq      pos(%rip), %r8                                #50.18
        movsd     (%r8,%rcx,8), %xmm2                           #50.30
        mulsd     %xmm2, %xmm2                                  #50.30
        movsd     %xmm2, (%rax,%rcx,8)                          #50.9
        movq      8+pos(%rip), %r9                              #50.18
        movsd     (%r9,%rcx,8), %xmm0                           #50.30
        mulsd     %xmm0, %xmm0                                  #50.30
        addsd     %xmm0, %xmm2                                  #50.9
        movsd     %xmm2, (%rax,%rcx,8)                          #50.9
        movq      16+pos(%rip), %r10                            #50.18
        movsd     (%r10,%rcx,8), %xmm1                          #50.30
        mulsd     %xmm1, %xmm1                                  #50.30
        addsd     %xmm1, %xmm2                                  #50.9
        sqrtsd    %xmm2, %xmm2                                  #53.14
        movsd     %xmm2, (%rax,%rcx,8)                          #53.7
        incq      %rcx                                          #44.5
        cmpq      $4096, %rcx                                   #44.5
        jb        ..B1.10       # Prob 99%                      #44.5
                                # LOE rax rcx rbx r12 ebp r13d
..B1.11:                        # Preds ..B1.10
                                # Execution count [1.03e+00]
        movq      %rbx, %r15                                    #57.9
                                # LOE rax rbx r12 r15 ebp r13d
..B1.12:                        # Preds ..B1.54 ..B1.11
                                # Execution count [3.09e+00]
        movq      %rbx, %r14                                    #59.11
                                # LOE rax rbx r12 r14 r15 ebp r13d
..B1.13:                        # Preds ..B1.55 ..B1.12
                                # Execution count [1.26e+04]
        movq      mass(%rip), %rcx                              #61.22
        movq      pos(,%r15,8), %r8                             #61.22
        movsd     (%rax,%r14,8), %xmm2                          #61.22
        movsd     (%rcx,%r14,8), %xmm0                          #61.22
        mulsd     .L_2il0floatpacket.0(%rip), %xmm0             #61.22
        movsd     (%r8,%r14,8), %xmm1                           #61.22
..___tag_value_evolve.13:
#       force(double, double, double)
        call      force                                         #61.22
..___tag_value_evolve.14:
                                # LOE rbx r12 r14 r15 ebp r13d xmm0
..B1.52:                        # Preds ..B1.13
                                # Execution count [1.26e+04]
        movaps    %xmm0, %xmm1                                  #61.22
                                # LOE rbx r12 r14 r15 ebp r13d xmm1
..B1.14:                        # Preds ..B1.52
                                # Execution count [1.26e+04]
        movq      f(,%r15,8), %rax                              #61.9
        movsd     (%rax,%r14,8), %xmm0                          #61.9
        subsd     %xmm1, %xmm0                                  #61.9
        movsd     %xmm0, (%rax,%r14,8)                          #61.9
        incq      %r14                                          #59.23
        cmpq      $4096, %r14                                   #59.17
        jge       ..B1.15       # Prob 0%                       #59.17
                                # LOE rbx r12 r14 r15 ebp r13d
..B1.55:                        # Preds ..B1.14
                                # Execution count [1.26e+04]
        movq      r(%rip), %rax                                 #46.7
        jmp       ..B1.13       # Prob 100%                     #46.7
                                # LOE rax rbx r12 r14 r15 ebp r13d
..B1.15:                        # Preds ..B1.14
                                # Execution count [3.09e+00]
        incq      %r15                                          #57.20
        cmpq      $3, %r15                                      #57.15
        jge       ..B1.16       # Prob 33%                      #57.15
                                # LOE rbx r12 r15 ebp r13d
..B1.54:                        # Preds ..B1.15
                                # Execution count [2.06e+00]
        movq      r(%rip), %rax                                 #46.7
        jmp       ..B1.12       # Prob 100%                     #46.7
                                # LOE rax rbx r12 r15 ebp r13d
..B1.16:                        # Preds ..B1.15
                                # Execution count [1.03e+00]
        movq      %rbx, %r9                                     #66.5
                                # LOE rbx r9 r12 ebp r13d
..B1.17:                        # Preds ..B1.26 ..B1.16
                                # Execution count [3.09e+00]
        xorl      %esi, %esi                                    #68.7
        movq      %rbx, %rax                                    #69.7
        xorl      %r10d, %r10d                                  #69.7
        xorl      %r11d, %r11d                                  #69.7
                                # LOE rax rbx r9 r12 ebp esi r10d r11d r13d
..B1.18:                        # Preds ..B1.25 ..B1.17
                                # Execution count [1.26e+04]
        movq      pos(,%r9,8), %rcx                             #71.28
        incl      %r10d                                         #72.13
        movl      %esi, %r8d                                    #71.28
        movsd     (%rcx,%rax,8), %xmm0                          #71.28
        cmpl      $4096, %r10d                                  #72.21
        jge       ..B1.25       # Prob 50%                      #72.21
                                # LOE rax rbx r9 r12 ebp esi r8d r10d r11d r13d xmm0
..B1.19:                        # Preds ..B1.18
                                # Execution count [1.26e+04]
        movl      $1, %r14d                                     #72.9
        lea       4095(%r11), %edi                              #72.9
        movl      %edi, %ecx                                    #72.9
        xorl      %edx, %edx                                    #72.9
        shrl      $31, %ecx                                     #72.9
        lea       4095(%rcx,%r11), %ecx                         #72.9
        sarl      $1, %ecx                                      #72.9
        testl     %ecx, %ecx                                    #72.9
        jbe       ..B1.23       # Prob 10%                      #72.9
                                # LOE rax rbx r9 r12 edx ecx ebp esi edi r8d r10d r11d r13d r14d xmm0
..B1.20:                        # Preds ..B1.19
                                # Execution count [1.14e+04]
        movslq    %esi, %r15                                    #74.11
        .align    16,0x90
                                # LOE rax rbx r9 r12 r15 edx ecx ebp edi r8d r10d r11d r13d xmm0
..B1.21:                        # Preds ..B1.21 ..B1.20
                                # Execution count [3.16e+04]
        movq      pos(,%r9,8), %rsi                             #74.41
        lea       (%rdx,%rdx), %r14d                            #74.41
        movslq    %r14d, %r14                                   #74.41
        movaps    %xmm0, %xmm1                                  #74.41
        movaps    %xmm0, %xmm2                                  #74.41
        lea       (%rsi,%rax,8), %rsi                           #74.41
        subsd     8(%rsi,%r14,8), %xmm1                         #74.41
        movq      delta_pos(,%r9,8), %rsi                       #74.11
        lea       (%rsi,%r15,8), %rsi                           #74.11
        movsd     %xmm1, (%rsi,%r14,8)                          #74.11
        movq      pos(,%r9,8), %rsi                             #74.41
        lea       (%rsi,%rax,8), %rsi                           #74.41
        subsd     16(%rsi,%r14,8), %xmm2                        #74.41
        movq      delta_pos(,%r9,8), %rsi                       #74.11
        lea       (%rsi,%r15,8), %rsi                           #74.11
        movsd     %xmm2, 8(%rsi,%r14,8)                         #74.11
        lea       2(%r8,%rdx,2), %esi                           #75.19
        incl      %edx                                          #72.9
        cmpl      %ecx, %edx                                    #72.9
        jb        ..B1.21       # Prob 64%                      #72.9
                                # LOE rax rbx r9 r12 r15 edx ecx ebp esi edi r8d r10d r11d r13d xmm0
..B1.22:                        # Preds ..B1.21
                                # Execution count [1.14e+04]
        lea       1(%rdx,%rdx), %r14d                           #74.11
                                # LOE rax rbx r9 r12 ebp esi edi r8d r10d r11d r13d r14d xmm0
..B1.23:                        # Preds ..B1.22 ..B1.19
                                # Execution count [1.26e+04]
        lea       -1(%r14), %ecx                                #72.9
        cmpl      %edi, %ecx                                    #72.9
        jae       ..B1.25       # Prob 10%                      #72.9
                                # LOE rax rbx r9 r12 ebp esi r8d r10d r11d r13d r14d xmm0
..B1.24:                        # Preds ..B1.23
                                # Execution count [1.14e+04]
        movslq    %r14d, %r14                                   #74.41
        movq      pos(,%r9,8), %rcx                             #74.41
        lea       (%r14,%r8), %esi                              #74.11
        lea       (%rax,%r14), %r15                             #74.41
        subsd     (%rcx,%r15,8), %xmm0                          #74.41
        movslq    %r8d, %r15                                    #74.11
        addq      %r14, %r15                                    #72.9
        movq      delta_pos(,%r9,8), %rcx                       #74.11
        movsd     %xmm0, -8(%rcx,%r15,8)                        #74.11
                                # LOE rax rbx r9 r12 ebp esi r10d r11d r13d
..B1.25:                        # Preds ..B1.24 ..B1.23 ..B1.18
                                # Execution count [1.26e+04]
        decl      %r11d                                         #72.13
        incq      %rax                                          #72.13
        cmpl      $4096, %r10d                                  #69.7
        jb        ..B1.18       # Prob 99%                      #69.7
                                # LOE rax rbx r9 r12 ebp esi r10d r11d r13d
..B1.26:                        # Preds ..B1.25
                                # Execution count [3.09e+00]
        .byte     15                                            #66.5
        .byte     31                                            #66.5
        .byte     128                                           #66.5
        .byte     0                                             #66.5
        .byte     0                                             #66.5
        .byte     0                                             #66.5
        .byte     0                                             #66.5
        incq      %r9                                           #66.5
        cmpq      $3, %r9                                       #66.5
        jb        ..B1.17       # Prob 66%                      #66.5
                                # LOE rbx r9 r12 ebp r13d
..B1.27:                        # Preds ..B1.26
                                # Execution count [1.25e-01]
        movq      delta_r(%rip), %rax                           #83.7
        movq      %rbx, %rdx                                    #81.5
        .align    16,0x90
                                # LOE rax rdx rbx r12 ebp r13d
..B1.28:                        # Preds ..B1.28 ..B1.27
                                # Execution count [1.03e+06]
        movq      %rbx, (%rax,%rdx,8)                           #83.7
        movq      delta_pos(%rip), %rcx                         #87.24
        movsd     (%rcx,%rdx,8), %xmm2                          #87.42
        mulsd     %xmm2, %xmm2                                  #87.42
        movsd     %xmm2, (%rax,%rdx,8)                          #87.9
        movq      8+delta_pos(%rip), %rdi                       #87.24
        movsd     (%rdi,%rdx,8), %xmm0                          #87.42
        mulsd     %xmm0, %xmm0                                  #87.42
        addsd     %xmm0, %xmm2                                  #87.9
        movsd     %xmm2, (%rax,%rdx,8)                          #87.9
        movq      16+delta_pos(%rip), %r8                       #87.24
        movsd     (%r8,%rdx,8), %xmm1                           #87.42
        mulsd     %xmm1, %xmm1                                  #87.42
        addsd     %xmm1, %xmm2                                  #87.9
        sqrtsd    %xmm2, %xmm2                                  #90.20
        movsd     %xmm2, (%rax,%rdx,8)                          #90.7
        incq      %rdx                                          #81.5
        cmpq      $8386560, %rdx                                #81.5
        jb        ..B1.28       # Prob 99%                      #81.5
                                # LOE rax rdx rbx r12 ebp r13d
..B1.29:                        # Preds ..B1.28
                                # Execution count [1.57e-01]
        movq      %rbx, %rcx                                    #97.9
        movq      %rbx, %rdx                                    #97.9
        movq      %rcx, %r14                                    #96.5
        movl      %ebp, 8(%rsp)                                 #97.9[spill]
        movq      %r14, %r15                                    #97.9
        movl      %r13d, (%rsp)                                 #97.9[spill]
        movq      %r12, 16(%rsp)                                #97.9[spill]
	.cfi_offset 12, -80
                                # LOE rax rdx rcx r14 r15
..B1.30:                        # Preds ..B1.42 ..B1.29
                                # Execution count [6.43e+02]
        lea       1(%rcx), %r12                                 #99.15
        lea       (,%r12,8), %rbx                               #99.11
        cmpq      $4096, %r12                                   #99.19
        jge       ..B1.42       # Prob 10%                      #99.19
                                # LOE rax rdx rcx rbx r12 r14 r15
..B1.31:                        # Preds ..B1.30
                                # Execution count [5.79e+02]
        movq      %rcx, 72(%rsp)                                #[spill]
                                # LOE rax rdx rbx r12 r14 r15
..B1.32:                        # Preds ..B1.40 ..B1.31
                                # Execution count [3.21e+03]
        movq      radius(%rip), %rcx                            #101.16
        xorb      %r13b, %r13b                                  #102.9
        movq      %rdx, %rbp                                    #103.13
        movsd     (%rcx,%r15), %xmm0                            #101.16
        addsd     (%rcx,%rbx), %xmm0                            #101.28
        movsd     %xmm0, 80(%rsp)                               #103.13[spill]
                                # LOE rax rbx rbp r12 r14 r15 r13b
..B1.33:                        # Preds ..B1.37 ..B1.35 ..B1.32
                                # Execution count [9.64e+03]
        movq      mass(%rip), %rdx                              #105.38
        movq      delta_pos(,%rbp,8), %rcx                      #105.30
        movsd     (%rax,%r14), %xmm2                            #105.30
        movsd     (%rdx,%r15), %xmm0                            #105.30
        mulsd     .L_2il0floatpacket.1(%rip), %xmm0             #105.30
        mulsd     (%rbx,%rdx), %xmm0                            #105.30
        movsd     (%rcx,%r14), %xmm1                            #105.30
..___tag_value_evolve.16:
#       force(double, double, double)
        call      force                                         #105.30
..___tag_value_evolve.17:
                                # LOE rbx rbp r12 r14 r15 r13b xmm0
..B1.53:                        # Preds ..B1.33
                                # Execution count [9.64e+03]
        movaps    %xmm0, %xmm2                                  #105.30
                                # LOE rbx rbp r12 r14 r15 r13b xmm2
..B1.34:                        # Preds ..B1.53
                                # Execution count [9.64e+03]
        movq      delta_r(%rip), %rax                           #107.15
        movq      f(,%rbp,8), %rdx                              #109.13
        movsd     (%rax,%r14), %xmm0                            #107.15
        comisd    80(%rsp), %xmm0                               #107.29[spill]
        jb        ..B1.37       # Prob 50%                      #107.29
                                # LOE rax rdx rbx rbp r12 r14 r15 r13b xmm2
..B1.35:                        # Preds ..B1.34
                                # Execution count [4.82e+03]
        movsd     (%rdx,%r15), %xmm0                            #109.13
        subsd     %xmm2, %xmm0                                  #109.13
        movsd     %xmm0, (%rdx,%r15)                            #109.13
        movq      f(,%rbp,8), %rdx                              #110.13
        incq      %rbp                                          #103.24
        movsd     (%rdx,%rbx), %xmm1                            #110.13
        addsd     %xmm2, %xmm1                                  #110.13
        movsd     %xmm1, (%rdx,%rbx)                            #110.13
        cmpq      $3, %rbp                                      #103.19
        jl        ..B1.33       # Prob 66%                      #103.19
                                # LOE rax rbx rbp r12 r14 r15 r13b
..B1.36:                        # Preds ..B1.35
                                # Execution count [1.61e+03]
        xorl      %edx, %edx                                    #
        cmpb      $1, %r13b                                     #119.25
        je        ..B1.39       # Prob 16%                      #119.25
        jmp       ..B1.40       # Prob 100%                     #119.25
                                # LOE rax rdx rbx r12 r14 r15
..B1.37:                        # Preds ..B1.34
                                # Execution count [4.82e+03]
        movsd     (%rdx,%r15), %xmm0                            #114.13
        movb      $1, %r13b                                     #116.13
        addsd     %xmm2, %xmm0                                  #114.13
        movsd     %xmm0, (%rdx,%r15)                            #114.13
        movq      f(,%rbp,8), %rdx                              #115.13
        incq      %rbp                                          #103.24
        movsd     (%rdx,%rbx), %xmm1                            #115.13
        subsd     %xmm2, %xmm1                                  #115.13
        movsd     %xmm1, (%rdx,%rbx)                            #115.13
        cmpq      $3, %rbp                                      #103.19
        jl        ..B1.33       # Prob 66%                      #103.19
                                # LOE rax rbx rbp r12 r14 r15 r13b
..B1.38:                        # Preds ..B1.37
                                # Execution count [1.61e+03]
        xorl      %edx, %edx                                    #
                                # LOE rax rdx rbx r12 r14 r15
..B1.39:                        # Preds ..B1.36 ..B1.38
                                # Execution count [5.14e+02]
        incl      collisions(%rip)                              #121.11
                                # LOE rax rdx rbx r12 r14 r15
..B1.40:                        # Preds ..B1.36 ..B1.39
                                # Execution count [3.21e+03]
        incq      %r12                                          #99.25
        addq      $8, %r14                                      #123.17
        addq      $8, %rbx                                      #99.25
        cmpq      $4096, %r12                                   #99.19
        jl        ..B1.32       # Prob 82%                      #99.19
                                # LOE rax rdx rbx r12 r14 r15
..B1.41:                        # Preds ..B1.40
                                # Execution count [5.79e+02]
        movq      72(%rsp), %rcx                                #[spill]
                                # LOE rax rdx rcx r14 r15
..B1.42:                        # Preds ..B1.41 ..B1.30
                                # Execution count [6.43e+02]
        incq      %rcx                                          #97.21
        addq      $8, %r15                                      #97.21
        cmpq      $4096, %rcx                                   #97.15
        jl        ..B1.30       # Prob 99%                      #97.15
                                # LOE rax rdx rcx r14 r15
..B1.43:                        # Preds ..B1.42
                                # Execution count [1.57e-01]
        movq      %rdx, %rbx                                    #
        movl      8(%rsp), %ebp                                 #[spill]
        movq      %rbx, %rax                                    #127.9
        movl      (%rsp), %r13d                                 #[spill]
        movq      16(%rsp), %r12                                #[spill]
	.cfi_restore 12
        movsd     24(%rsp), %xmm0                               #134.37[spill]
        movq      mass(%rip), %rdx                              #134.37
	.cfi_offset 12, -80
                                # LOE rax rdx rbx r12 ebp r13d xmm0
..B1.44:                        # Preds ..B1.46 ..B1.43
                                # Execution count [4.71e-01]
        movq      %rbx, %rcx                                    #129.11
        .align    16,0x90
                                # LOE rax rdx rcx rbx r12 ebp r13d xmm0
..B1.45:                        # Preds ..B1.45 ..B1.44
                                # Execution count [1.93e+03]
        movq      velo(,%rax,8), %rdi                           #132.27
        movq      pos(,%rax,8), %r8                             #132.9
        movsd     (%rdi,%rcx,8), %xmm1                          #132.27
        mulsd     %xmm0, %xmm1                                  #132.27
        addsd     (%r8,%rcx,8), %xmm1                           #132.9
        movsd     %xmm1, (%r8,%rcx,8)                           #132.9
        movq      f(,%rax,8), %r9                               #134.29
        movq      velo(,%rax,8), %r10                           #134.9
        movsd     (%r9,%rcx,8), %xmm2                           #134.29
        divsd     (%rdx,%rcx,8), %xmm2                          #134.37
        mulsd     %xmm0, %xmm2                                  #134.37
        addsd     (%r10,%rcx,8), %xmm2                          #134.9
        movsd     %xmm2, (%r10,%rcx,8)                          #134.9
        incq      %rcx                                          #129.23
        cmpq      $4096, %rcx                                   #129.17
        jl        ..B1.45       # Prob 99%                      #129.17
                                # LOE rax rdx rcx rbx r12 ebp r13d xmm0
..B1.46:                        # Preds ..B1.45
                                # Execution count [4.71e-01]
        incq      %rax                                          #127.20
        cmpq      $3, %rax                                      #127.15
        jl        ..B1.44       # Prob 66%                      #127.15
                                # LOE rax rdx rbx r12 ebp r13d xmm0
..B1.47:                        # Preds ..B1.46
                                # Execution count [1.57e-01]
        incl      %ebp                                          #20.28
        movsd     %xmm0, 24(%rsp)                               #[spill]
        cmpl      %r13d, %ebp                                   #20.22
        jle       ..B1.3        # Prob 82%                      #20.22
                                # LOE rbx r12 ebp r13d
..B1.48:                        # Preds ..B1.47
                                # Execution count [2.83e-02]
        movq      32(%rsp), %r13                                #[spill]
	.cfi_restore 13
        movq      40(%rsp), %r14                                #[spill]
	.cfi_restore 14
        movq      48(%rsp), %r15                                #[spill]
	.cfi_restore 15
        movq      56(%rsp), %rbx                                #[spill]
	.cfi_restore 3
        movq      64(%rsp), %rbp                                #[spill]
	.cfi_restore 6
	.cfi_restore 12
                                # LOE rbx rbp r12 r13 r14 r15
..B1.49:                        # Preds ..B1.48 ..B1.1
                                # Execution count [1.28e-01]
        addq      $88, %rsp                                     #140.1
	.cfi_def_cfa_offset 8
        ret                                                     #140.1
        .align    16,0x90
                                # LOE
	.cfi_endproc
# mark_end;
	.type	evolve,@function
	.size	evolve,.-evolve
	.data
# -- End  evolve
	.section .rodata, "a"
	.align 16
	.align 16
.L_2il0floatpacket.2:
	.long	0x00000000,0x80000000,0x00000000,0x00000000
	.type	.L_2il0floatpacket.2,@object
	.size	.L_2il0floatpacket.2,16
	.align 8
.L_2il0floatpacket.0:
	.long	0x00000000,0x409f4000
	.type	.L_2il0floatpacket.0,@object
	.size	.L_2il0floatpacket.0,8
	.align 8
.L_2il0floatpacket.1:
	.long	0x00000000,0x40000000
	.type	.L_2il0floatpacket.1,@object
	.size	.L_2il0floatpacket.1,8
	.section .rodata.str1.4, "aMS",@progbits,1
	.align 4
	.align 4
.L_2__STRING.0:
	.long	1701669236
	.long	1885697139
	.long	174335264
	.byte	0
	.type	.L_2__STRING.0,@object
	.size	.L_2__STRING.0,13
	.space 3, 0x00 	# pad
	.align 4
.L_2__STRING.1:
	.long	1819045731
	.long	1869181801
	.long	622883694
	.word	2660
	.byte	0
	.type	.L_2__STRING.1,@object
	.size	.L_2__STRING.1,15
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
# End
