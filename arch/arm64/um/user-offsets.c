// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <poll.h>
#include <sys/mman.h>
#include <sys/user.h>
#define __FRAME_OFFSETS
#include <linux/ptrace.h>
#include <asm/types.h>
#include <linux/kbuild.h>

#define DEFINE_LONGS(sym, val)	\
	COMMENT(#val " / sizeof(unsigned long)");	\
	DEFINE(sym, val / sizeof(unsigned long))

void foo(void)
{
    DEFINE(HOST_FP_SIZE, 4096 / sizeof(unsigned long));
#if 0
    DEFINE_LONGS(HOST_BX, RBX);
    DEFINE_LONGS(HOST_CX, RCX);
    DEFINE_LONGS(HOST_DI, RDI);
    DEFINE_LONGS(HOST_SI, RSI);
    DEFINE_LONGS(HOST_DX, RDX);
    DEFINE_LONGS(HOST_BP, RBP);
    DEFINE_LONGS(HOST_AX, RAX);
    DEFINE_LONGS(HOST_R8, R8);
    DEFINE_LONGS(HOST_R9, R9);
    DEFINE_LONGS(HOST_R10, R10);
    DEFINE_LONGS(HOST_R11, R11);
    DEFINE_LONGS(HOST_R12, R12);
    DEFINE_LONGS(HOST_R13, R13);
    DEFINE_LONGS(HOST_R14, R14);
    DEFINE_LONGS(HOST_R15, R15);
    DEFINE_LONGS(HOST_ORIG_AX, ORIG_RAX);
    DEFINE_LONGS(HOST_CS, CS);
    DEFINE_LONGS(HOST_SS, SS);
    DEFINE_LONGS(HOST_EFLAGS, EFLAGS);
    DEFINE_LONGS(HOST_IP, RIP);
    DEFINE_LONGS(HOST_SP, RSP);
#endif
	DEFINE(UM_FRAME_SIZE, sizeof(struct user_regs_struct));
	DEFINE(UM_POLLIN, POLLIN);
	DEFINE(UM_POLLPRI, POLLPRI);
	DEFINE(UM_POLLOUT, POLLOUT);

	DEFINE(UM_PROT_READ, PROT_READ);
	DEFINE(UM_PROT_WRITE, PROT_WRITE);
	DEFINE(UM_PROT_EXEC, PROT_EXEC);
}
