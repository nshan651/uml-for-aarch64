# UML to AARCH64

## Compiling

* `CROSS_COMPILE=aarch64-linux-gnu- make ARCH=um`
* `make ARCH=um menuconfig`
* Search for flags where we've changed things:
    * `rg "FJCK" .`

## Resources on UML

* [UML how-to](https://www.landley.net/code/UML.html)
* [kernel.org full UML guide](https://www.kernel.org/doc/Documentation/virtual/uml/UserModeLinux-HOWTO.txt)
* [UML on Ubuntu](https://xeiaso.net/blog/howto-usermode-linux-2019-07-07)
 
## PT_REGS

* pt_regs is at the high end of kernel stack, is mainly used for saving user registers in user-kernel mode switching. Therefore, after returning to user space, the first instruction get executed is at pt_regs->pc 
* Stores user registers `u_regs[16]`
* PT_REGS_AX -> UPT_REGS_AX -> REGS_AX

## Menuconfig

* Make notes of the errors that pop up, mark with "FJCK"
* Try to add custom kernel options to menuconfig
* Find and isolate x84_64 specific architecture lines of code in it

