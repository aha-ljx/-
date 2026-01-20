.section .rodata

lpfmt:
    .string "%s %s %d %d\n\0"
lpfmt_string:
    .string "%s  \0"
lpfmt_num:
    .string "%d  \0"
lpfmt_newline:
    .string "\n"

.text
.globl display
.type display, @function

# void display(student* sptr, int num)
# 参数：
#   [esp+4] = sptr  - 学生结构体数组首地址
#   [esp+8] = num   - 学生数量
display:
    pushl   %ebp
    movl    %esp, %ebp          # 建立栈帧

    # 保存被调用者保存寄存器（cdecl约定）
    pushl   %ebx
    pushl   %esi
    pushl   %edi

    # 初始化：获取参数
    movl    8(%ebp), %esi       # esi = sptr（当前学生指针）
    movl    12(%ebp), %ecx      # ecx = num（循环计数器，控制学生数量）

    # 检查学生数量是否为0，避免无效循环
    testl   %ecx, %ecx
    jz      .end_loop           # 若num=0，直接退出

.loop_start:
    # 打印当前学生的姓名（sname，偏移0）
    pushl   %esi                # 参数2：sname地址
    pushl   $lpfmt_string       # 参数1：格式字符串
    call    printf
    addl    $8, %esp            # 清理栈上的两个参数

    # 打印学号（sid，偏移8字节）
    leal    8(%esi), %eax       # eax = &sid（sname占8字节）
    pushl   %eax
    pushl   $lpfmt_string
    call    printf
    addl    $8, %esp

    # 打印scores[0]（偏移20字节）
    movzwl  20(%esi), %eax      # 读取short类型的scores[0]，零扩展为32位
    pushl   %eax
    pushl   $lpfmt_num
    call    printf
    addl    $8, %esp

    # 打印scores[2]（偏移24字节：20 + 2*2）
    movzwl  24(%esi), %eax
    pushl   %eax
    pushl   $lpfmt_num
    call    printf
    addl    $8, %esp

    # 每个学生信息后打印换行
    pushl   $lpfmt_newline
    call    printf
    addl    $4, %esp

    # 移动到下一个学生（结构体大小根据实际情况调整，这里假设为40字节）
    addl    $40, %esi           # esi指向数组中的下一个student

    decl    %ecx                # 学生计数器减1
    jnz     .loop_start         # 若计数器不为0，继续循环

.end_loop:
    # 恢复寄存器
    popl    %edi
    popl    %esi
    popl    %ebx

    # 函数返回
    movl    %ebp, %esp
    popl    %ebp
    ret

.section .note.GNU-stack,"",@progbits
