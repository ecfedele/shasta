# The *Shasta* Microkernel Project
*Shasta* is a 64-bit experimental microkernel for x86 PCs designed primarily as a learning project and exploration into efficient implementation of microkernel principles. Named after [the mountain in Northern California](https://en.wikipedia.org/wiki/Mount_Shasta) my father and I have always dreamed of hiking, the *Shasta* kernel and associated operating system intend to implement a large subset of traditional Unix fundamentals while using modern techniques and concepts.

Shasta has a number of inspirations and influences. Much of the initial design inspiration for the Shasta microkernel comes from my own studies into the hybrid kernel architecture of Windows NT, with a greater emphasis on kernel encapsulation and user-mode relegation of services. The message-passing and IPC interfaces, on the other hand, are distinctly influenced by [seL4](https://github.com/seL4/seL4). Other major influences and inspirations may arise as the kernel development gets underway.

As opposed to construction *en bloc*, whereby each functional unit is built-up over the course of the first major version and finally integrated to form Shasta version 1.0, the development methodology used to implement the kernel very much emphasises rapid development, followed by refinement, of kernel features. Multiprocess scheduling and crude system call interfaces will appear as early as version 0.2 and progressively refined until version 1.0, which should represent a functional microkernel capable of operating modern workloads. While there isn't a current litmus test for the question of "what should qualify as 1.0?", my initial thoughts are that [hosting of GCC](https://wiki.osdev.org/Porting_GCC_to_your_OS) qualifies as sufficient standing for the first benchmark version.

## Design goals for the *Shasta* microkernel

Shasta has a number of design goals, many of which are influenced by my own experiences in computing:

1. __Unix-*inspired*, not Unix-*like*__. One of the primary goals of Shasta, beyond building my own operating system, is to study what works, what doesn't work, and what works *best*. In that spirit, my intention is to build Shasta on the core of the fundamentals which the Unix model does very well, while at the same time feeling free to deviate from the Unix tradition when better or more modern design choices exist.

## Roadmap

As mentioned above, the primary developmental goal is to construct Shasta *en bloc*, with a basic but full-featured microkernel implementation benchmarking the 1.0 version. While this may be subject to change, my general ideas for the versioning are as follows:

- `0.0.1`: __Basic UEFI bootloader complete__. 
- `0.0.2`: __Basic interrupt, APIC, and timer functionalities present__.
- `0.0.3`: __Basic paging and virtual memory management facilities in place__.
- `0.0.4`: __Interprocess communication (IPC) fundamentals present__.
- `0.0.4`: __Simplistic round-robin scheduling with ELF64 loading__.
- `0.0.5`: __AHCI driver and filesystem server implementation__.
- `0.0.6`: __Rudimentary USB support__.
