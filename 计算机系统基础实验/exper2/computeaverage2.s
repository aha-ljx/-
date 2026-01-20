.section .text
.globl computeAverageScore
.type computeAverageScore, @function

# void computeAverageScore(student* s, int num)
# 参数：
#   [esp+4] = s    - 学生结构体数组首地址
#   [esp+8] = num  - 学生数量
computeAverageScore:
    pushl  %ebp       #保存栈基址
    movl   %esp, %ebp #使ebp成为栈基准点

    #保存被调用者保存寄存器（cdecl约定）
    pushl  %ebx
    pushl  %esi
    pushl  %edi

    #初始化变量
    movl  8(%ebp), %esi   #esi = 学生结构体数组首地址（4(%ebp) 是返回地址）
    movl  12(%ebp), %ecx  #ecx = 学生数量
    xorl  %ebx, %ebx      #初始化ebx=i=0

    #检查学生数量是否为0，避免无效循环
    testl %ecx, %ecx
    jz    .end_function   #若num=0，直接退出

.student_loop:
    #预计算当前学生scores数组首地址，减少重复运算
    leal  20(%esi), %edi
    xorl  %eax, %eax      #初始化总分为0
    movl  $7, %edx      #倒序计算，减少比较指令

.score_loop:
    #从8减到0，每次减1
    movzwl (%edi,%edx,2), %ecx
    addl %ecx, %eax
    # 检查是否遍历完所有课程（edx=0时，下一次就退出）
    cmpl  $0, %edx
    je    .calculate_average      # 若edx=0，退出循环

    decl  %edx
    jmp  .score_loop

.calculate_average:
    #用右移3位代替除法
    sarl  $3, %eax

    movw  %ax, 36(%esi)

    #移动到下一个学生
    addl  $38, %esi
    incl  %ebx
    cmpl  %ecx, %ebx
    jl    .student_loop

.end_function:
    #恢复寄存器
    popl  %edi
    popl  %esi
    popl  %ebx

    #函数返回
    movl  %ebp, %esp
    popl  %ebp
    ret

.section .note.GNU-stack,"",@progbits