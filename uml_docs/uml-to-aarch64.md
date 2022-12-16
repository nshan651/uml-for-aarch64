# UML to AARCH64

MR. DIKE'S EMAIL: jdike@linux.intel.com

## Compiling

* `CROSS_COMPILE=aarch64-linux-gnu- make SUBARCH=arm64 ARCH=um`
* `make ARCH=um menuconfig`
* Search for flags where we've changed things:
    * `rg "FJCK" .`
 
## PT_REGS

* pt_regs is at the high end of kernel stack, is mainly used for saving user registers in user-kernel mode switching. Therefore, after returning to user space, the first instruction get executed is at pt_regs->pc 
* Stores user registers `u_regs[16]`
* PT_REGS_AX -> UPT_REGS_AX -> REGS_AX

## Menuconfig

* Make notes of the errors that pop up, mark with "FJCK"
* Try to add custom kernel options to menuconfig
* Find and isolate x84_64 specific architecture lines of code in it

## Architecture Macros

* The arm64 macro is `__aarch64__`
* The x86 macro is `__x86_64`

## arch/um vs arch/x86/um

> The "arch/x86/um" directory in a Linux operating system refers to the User Mode version of the Linux kernel that has been compiled to run on the x86 architecture. This directory would contain the kernel files and other resources that are specific to the x86 architecture.

> On the other hand, the "arch/um" directory would contain the generic User Mode kernel files that are not specific to any one architecture. This directory would contain files that are common to all architectures, or that can be used by multiple architectures.

> It's worth noting that the exact structure and naming of directories in a Linux operating system can vary depending on the distribution and version. Some distributions may not have a separate "arch/um" directory, and instead include the generic User Mode files in the "arch/x86/um" directory or a similar directory for a specific architecture.
