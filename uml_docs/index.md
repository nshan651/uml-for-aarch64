# UML Docs Index

[Changelog](changelog)
[ChatGPT Recommendation](chatgpt-rec)
[UML to AARCH64](uml-to-aarch64.md)
[Resources](resources)

## Presentation order

* John: 
    1. Project vision
    2. road map
    3. meet the team 
    4. Why are we doing this
    5. Missing header files
    6. Conclusion
* Nick
    * 5. Intro to uml 
        * It's important to understand the distinction, because for our purposes we basically need to use virtualization in order to achieve native containerization
        * UML currently only works on the x86 architecture. But, basically all mobile chips are arm-based
    * 7. Compiling
        * Here are the instructions for cross-compiling the kernel with uml
        * Note the cflags, the subarchitecture is set to arm64 and the arch is um (user-mode)
        * We can then use make with the ARCH=um cflag and menuconfig to pull up menuconfig, which is basically a graphical interface for configuring the user-mode kernel
    * 8. menuconfig
        * Here's what it looks like
        * We can see this graphic of the directory structure. This highlighted part are the flags that we need to add
        * Ideally we would make it completely cpu agnostic and support the several dozen architectures the main kernel runs on, but we just focused on this for now
    * 9. and 10. user-mode for arm64
    * 10. Modification summary
    * 11. Holy macros!
    * 12. Navigating the kernel
