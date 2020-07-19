# DFK
Dylan's Free Kernel

## Overview
This is my experiment at making a kernel. We'll see where this goes. It's in C++ but I lean heavily into C-Style programming with some oop dropped in where it is useful. (No TEMPLATES)

Requires lld-10, clang++-10, and GNU Make


## The Kernel
The DFK Kernel is an extreme microkernel. Its functions are designed to be very minimal such that the user of the kernel can assemble (put together, not `nasm`) the things they need to run their application. Do I need a File System?, do I need networking?, do I need USB?, do I need VGA, do I need process-management(multitasking), do I need threads?, do I need virtual memory/paging? among otherthings. This process should be facilitated by a simple build tool. You will build your project, and the build tool will fetch the appropriate kernel modules and make an image of your program and kernel. 

This modularized approach is exemplified by the `modules/` directory. In the modules directory are the basic modules that come with the kernel.


## Images
The makefile in the root directory has the following usefule rules: `image`, `kernel`, `modules`, `clean`, and `all`. `all` builds `image`, `kernel`, and `modules`. `clean` erases all object and image files. `kernel` builds the most basic kernel, and `modules` all of the necessary functionality. `image` is the tricky one. It generates a disk image for the kernel and the modules you specify. All of the modules are placed into the image in a filesystem agnostic manner. 



## Resources
### AMD64
AMD64 Manuals:
- [Volume 1: Application Programming](https://www.amd.com/system/files/TechDocs/24592.pdf)
- [Volume 2: Systems Programming](https://www.amd.com/system/files/TechDocs/24593.pdf)
- [Volume 3: Instructions](https://www.amd.com/system/files/TechDocs/24594.pdf)


### ARM64