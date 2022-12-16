```
mkdir -p arch/arm64/um/{shared/sysdep,asm}
cp arch/x86/Makefile.um arch/arm64
cp arch/x86/um/Makefile arch/arm64/um/
cp arch/x86/um/user-offsets.c arch/arm64/um/
cp arch/x86/um/Kconfig arch/arm64/um/
cp arch/x86/um/shared/sysdep/* arch/arm64/um/shared/sysdep/
cp arch/x86/um/asm/* arch/arm64/um/asm
```

### Minor Modifications / Comment Outs

* Create `cpufeatures.h` which is included by a bunch of stuff in the main UM port.
    * `touch arch/arm64/include/asm/cpufeatures.h`

### Replace the contents of `arch/arm64/Makefile.um` with the following:

```sh
core-y += arch/arm64/crypto/

START := 0x60000000

KBUILD_CFLAGS += -fno-builtin

CHECKFLAGS  += -D__ARM64__
KBUILD_AFLAGS +=
KBUILD_LDFLAGS += -m aarch64elf
KBUILD_CPPFLAGS += 

ELF_ARCH := aarch64
ELF_FORMAT := elf64-littleaarch64

# Not on all 64-bit distros /lib is a symlink to /lib64. PLD is an example.

LINK-$(CONFIG_LD_SCRIPT_DYN_RPATH) += -Wl,-rpath,/lib64
LINK-y +=

# The archprepare rule is called by the main kernel Makefile.
# This is a script that generates some header files for arm64
# port.
archprepare:
    $(Q)$(MAKE) $(build)=arch/arm64/tools kapi
                      
```
**A note for the curious:**
The `ELF_ARCH` and `ELF_FORMAT` symbols tell the linker script what `OUTPUT_ARCH` and `OUTPUT_FORMAT` to use in the linker script. You can learn more about the available options in the [GNU `ld` Documentation](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_node/ld_30.html#SEC30)

## Modify `arch/arm64/um/user-offsets.c` to the following.

* DONE

* This gets rid of x86-specific register definitions. The `struct sigcontext` for AARCH64 lives in `arch/arm64/include/uapi/asm/sigcontext.h`

```c
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

#define DEFINE_LONGS(sym, val)  
    COMMENT(#val " / sizeof(unsigned long)");   
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
```


## Comment Out x86-Specific Things in `arch/arm64/um/shared/sysdep/ptrace.h`


```c
/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __SYSDEP_X86_PTRACE_H
#define __SYSDEP_X86_PTRACE_H

#include <generated/user_constants.h>
#include <sysdep/faultinfo.h>

#define MAX_REG_OFFSET (UM_FRAME_SIZE)
#define MAX_REG_NR ((MAX_REG_OFFSET) / sizeof(unsigned long))
#if 0
#define REGS_IP(r) ((r)[HOST_IP])
#define REGS_SP(r) ((r)[HOST_SP])
#define REGS_EFLAGS(r) ((r)[HOST_EFLAGS])
#define REGS_AX(r) ((r)[HOST_AX])
#define REGS_BX(r) ((r)[HOST_BX])
#define REGS_CX(r) ((r)[HOST_CX])
#define REGS_DX(r) ((r)[HOST_DX])
#define REGS_SI(r) ((r)[HOST_SI])
#define REGS_DI(r) ((r)[HOST_DI])
#define REGS_BP(r) ((r)[HOST_BP])
#define REGS_CS(r) ((r)[HOST_CS])
#define REGS_SS(r) ((r)[HOST_SS])
#define REGS_DS(r) ((r)[HOST_DS])
#define REGS_ES(r) ((r)[HOST_ES])

#define UPT_IP(r) REGS_IP((r)->gp)
#define UPT_SP(r) REGS_SP((r)->gp)
#define UPT_EFLAGS(r) REGS_EFLAGS((r)->gp)
#define UPT_AX(r) REGS_AX((r)->gp)
#define UPT_BX(r) REGS_BX((r)->gp)
#define UPT_CX(r) REGS_CX((r)->gp)
#define UPT_DX(r) REGS_DX((r)->gp)
#define UPT_SI(r) REGS_SI((r)->gp)
#define UPT_DI(r) REGS_DI((r)->gp)
#define UPT_BP(r) REGS_BP((r)->gp)
#define UPT_CS(r) REGS_CS((r)->gp)
#define UPT_SS(r) REGS_SS((r)->gp)
#define UPT_DS(r) REGS_DS((r)->gp)
#define UPT_ES(r) REGS_ES((r)->gp)
#endif

#ifdef __i386__
#include "ptrace_32.h"
#else
#include "ptrace_64.h"
#endif

struct syscall_args {
    unsigned long args[6];
};
```

(file contents continue.)

## Comment Out x86-Specific Things in `arch/arm64/um/asm/ptrace.h`

* DONE:

```c
/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __UM_X86_PTRACE_H
#define __UM_X86_PTRACE_H

#include <linux/compiler.h>
#ifndef CONFIG_X86_32
#define __FRAME_OFFSETS /* Needed to get the R* macros */
#endif
#include <asm/ptrace-generic.h>

#define user_mode(r) UPT_IS_USER(&(r)->regs)

#if 0
#define PT_REGS_AX(r) UPT_AX(&(r)->regs)
#define PT_REGS_BX(r) UPT_BX(&(r)->regs)
#define PT_REGS_CX(r) UPT_CX(&(r)->regs)
#define PT_REGS_DX(r) UPT_DX(&(r)->regs)

#define PT_REGS_SI(r) UPT_SI(&(r)->regs)
#define PT_REGS_DI(r) UPT_DI(&(r)->regs)
#define PT_REGS_BP(r) UPT_BP(&(r)->regs)
#define PT_REGS_EFLAGS(r) UPT_EFLAGS(&(r)->regs)

#define PT_REGS_CS(r) UPT_CS(&(r)->regs)
#define PT_REGS_SS(r) UPT_SS(&(r)->regs)
#define PT_REGS_DS(r) UPT_DS(&(r)->regs)
#define PT_REGS_ES(r) UPT_ES(&(r)->regs)
#endif

#define PT_REGS_ORIG_SYSCALL(r) PT_REGS_AX(r)
#define PT_REGS_SYSCALL_RET(r) PT_REGS_AX(r)

#define PT_FIX_EXEC_STACK(sp) do ; while(0)

#define profile_pc(regs) PT_REGS_IP(regs)

#define UPT_RESTART_SYSCALL(r) (UPT_IP(r) -= 2)
#define PT_REGS_SET_SYSCALL_RETURN(r, res) (PT_REGS_AX(r) = (res))

static inline long regs_return_value(struct pt_regs *regs)
{   
    return regs->regs.gp[0];  // MODIFIED!!
} 
```

(file contents continue.)

Be sure to modify the function `regs_return_value` to return general-purpose register 0 instead of using the x86-specific `PT_REGS_AX` macro.

### Compile

    `make SUBARCH=arm64 ARCH=um`

Or if cross compiling:

    `CROSS_COMPILE=aarch64-linux-gnu- make SUBARCH=arm64 ARCH=um`
    
---

# Nick Changes

* On cross compile

## A Missing File?

```
CROSS_COMPILE=aarch64-linux-gnu- make SUBARCH=arm64 ARCH=um
arch/um/Makefile:118: warning: overriding recipe for target 'archprepare'
arch/arm64/Makefile.um:24: warning: ignoring old recipe for target 'archprepare'
make[1]: Nothing to be done for 'archheaders'.
  UPD     include/config/kernel.release
  UPD     include/generated/utsrelease.h
  CC      kernel/bounds.s
In file included from ./arch/arm64/include/asm/alternative.h:5,
                 from ./arch/arm64/um/asm/barrier.h:6,
                 from ./include/asm-generic/bitops/generic-non-atomic.h:7,
                 from ./include/linux/bitops.h:34,
                 from ./include/linux/log2.h:12,
                 from kernel/bounds.c:13:
./arch/arm64/include/asm/alternative-macros.h:5:10: fatal error: asm/cpucaps.h: No such file or directory
    5 | #include <asm/cpucaps.h>
      |          ^~~~~~~~~~~~~~~
compilation terminated.
make[1]: *** [scripts/Makefile.build:117: kernel/bounds.s] Error 1
make: *** [Makefile:1205: prepare0] Error 2
```

* Our version of the kernel is literally missing asm/cpucaps.h??? Not sure why it was missing
* Added copy from [here](https://elixir.bootlin.com/linux/v4.19/source/arch/arm64/include/asm/cpucaps.h)

## x86_capability Array

* Stores info about the x86 processor on which the kernel is running
> Rhere is an equivalent for the arm64 architecture. The Linux kernel uses the elf_hwcap and elf_hwcap2 arrays to store information about the capabilities of the arm64 processor. These arrays are populated during the boot process, using information provided by the processor itself. Like the x86_capability array, the elf_hwcap and elf_hwcap2 arrays are used by the kernel and other system software to make decisions about how to use the processor and its features.
