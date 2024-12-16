# CeanOS 

![GitHub top language](https://img.shields.io/github/languages/top/ceanvalds/CeanOS)
![Contributors](https://img.shields.io/github/contributors/ceanvalds/CeanOS)
![Commits](https://img.shields.io/github/commit-activity/m/ceanvalds/CeanOS)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/ceanvalds/CeanOS)
![GitHub Release](https://img.shields.io/github/v/release/ceanvalds/CeanOS?include_prereleases)
![GitHub repo size](https://img.shields.io/github/repo-size/ceanvalds/CeanOS)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/ceanvalds/ceanos/latest?include_prereleases)
![License](https://img.shields.io/badge/License-GPL--v3-blue)

  > CeanOS is a UNIX-like operating system . The goal is to create a lightweight, efficient OS with a non-bloated kernel and a user-friendly interface. This project is built with C and assembly using no standard libraries . 

<br>

![image](res/screenshot.png)

#### warning -> i took `rc` versioning instead of `alpha` and `beta` because it sounds more professional and cooler <img src="res/cool.png" alt="cool" style="width: 5%;"/>


## Kernel Status
The CeanOS kernel is a monolithic x86 one. I am also planning to port it to x86_64 and arm after im done with x86 .

## Userland Status

There is no userland yet lol.

## Other Information
The file `vga_types.h` includes macros from the Linux source code. You can find the original file [here](https://github.com/torvalds/linux/blob/42f7652d3eb527d03665b09edac47f85fb600924/include/video/vga.h).

The files `ata.c` and `ata.h` are taken from [this](https://github.com/malwarepad/cavOS/blob/2ad71233123bf610188cc6d4d3cda30d8e275909/src/kernel/drivers/) location(malwarepad/cavOS) with some modifications to integrate into CeanOS . 

## Kernel archive

[CeanOS Kernel Site](https://ceanvalds.github.io/ceanos-kernel-site/)

## Goals

Here’s what I’m working on:

### **Kernel**
- [x] Basic kernel initialization
- [x] Simple memory management (GDT, IDT, ISRs)
- [x] Advanced memory management (paging, virtual memory, heap)
- [ ] Multitasking and process scheduling
- [ ] Inter-process communication (IPC)
- [ ] Dynamic module loading/unloading

### **Architecture**
- [x] x86 (Work in Progress)
- [ ] x86_64 (planned)
- [ ] ARM (planned)

### **Filesystems**
- [ ] FAT32 boot sector support
- [ ] FAT32 read/write operations
- [ ] ext2 read/write operations
- [ ] Advanced filesystem features (journaling, metadata management)
- [x] VFS 
- [x] tmpfs 

### **Device Drivers**
- **Input/Output:**
  - [x] Keyboard
  - [ ] Mouse
  - [ ] USB devices
- **Graphics:**
  - [x] VGA text mode
  - [ ] Framebuffer
  - [ ] GPU acceleration
  - [ ] CWM (Cean Window Manager)
- **Storage:**
  - [x] Basic ATA/IDE driver
  - [ ] AHCI driver
  - [ ] SSD/HDD/USB device support
- **Networking:**
  - [ ] Basic NIC driver
  - [ ] TCP/IP stack implementation
  - [ ] DHCP and DNS support
  - [ ] HTTP support
- **Power Management:**
  - [ ] ACPI implementation
  - [ ] Power states (sleep, hibernate)
  - [ ] Battery management for portable devices
- **Other:**
  - [x] PCI (work in progress)
### **Userland**
- [ ] Minimal shell (interactive terminal)
- [ ] Core utilities
- [ ] Package manager (eventually)
- [ ] Multitasking user applications
- [ ] System services (e.g., logging, daemon management)

### **Networking**
- [ ] Packet handling
- [ ] Basic firewall support
- [ ] DNS resolution
- [ ] HTTP/HTTPS client
- [ ] SSH support (long-term)

### **Security**
- [ ] User authentication system
- [ ] Multi-user environment support
- [ ] Permissions and access control
- [ ] Encrypted filesystem support
- [ ] Kernel-level security features (ASLR, DEP)

### **Graphics**
- [x] VGA text mode (for kernel debugging)
- [ ] Framebuffer driver
- [ ] Basic GUI support
- [ ] cwm (Cean Window Manager)
- [ ] Theme and UI customization options

### **System Utilities**
- [ ] Logging system (syslog)
- [ ] Debugger for kernel and userland
- [ ] Performance monitoring tools (CPU, memory usage)
- [ ] Disk partitioning and formatting tools

### **Development Tools**
- [ ] In-system compiler for C (eventually)
- [ ] Debugging tools for applications and kernel
- [ ] Cross-compilation support

### **Long-Term Vision**
- [ ] Support for virtualized environments
- [ ] Distributed computing capabilities
- [ ] Experimental features
- [ ] Self-hosting

## Compiling
Everything about it can be found in `Documentation/build.md` or [here](Documentation/build.md)

## Contributing

Read [this](Documentation/CONTRIBUTING.md) 

## Screenshots

> No good ones yet ):

## License
This project is licensed under GPL v3 (GNU General Public License v3.0). For more information, see the [LICENSE](LICENSE).
