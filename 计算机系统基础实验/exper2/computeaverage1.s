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
    #内层循环计算总分
    xorl  %eax, %eax      #初始化总分为0
    xorl  %edx, %edx      #edx = j = 0

.score_loop:
    #检查是否处理完8门课程
    cmpl  $8, %edx
    jge   .calculate_average  #若j>=8,计算平均分

    #获取score[j]的值
    movzwl 20(%esi,%edx,2), %edi  #读取short类型的scores，零扩展为32位
    addl  %edi, %eax       #累加总分

    incl  %edx
    jmp   .score_loop

.calculate_average:
    #计算平均分
    movl  $8, %edi
    xorl  %edx, %edx
    divl  %edi

    #保存平均分到average
    movw  %ax, 36(%esi)

    #移动到下一个学生
    addl  $38, %esi

    incl  %ebx
    cmpl  %ecx, %ebx
    jl    .student_loop   #i<num 时，跳转

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

