# Building CeanOS

This document provides instructions on how to build the CeanOS operating system from source.
> **Warning!** If any step fails, do NOT proceed... Start over (double checking your dependencies) and if the issue persists, create an issue reporting it. Remember, the project is still in development!

## Prerequisites
- **GCC**
- **NASM**
- **Make**
- **QEMU**
- **Git**

### Installation

- On **Arch Linux**, you can install the necessary packages using:

  ```bash
  sudo pacman -S base-devel qemu git gcc nasm make
  ```

- On **Ubuntu**, you can install the necessary packages using:

  ```bash
  sudo apt install base-devel qemu git gcc nasm make
  ```
- On **Windows**, use WSL to compile

- I didn't test on **macOS** yet, but if you _are_ a macOS user, try compiling it and dm me on discord if it works .

### Building

# - Clone the repo

```bash
git clone https://github.com/asdasda3456/CeanOS
cd CeanOS
```

# - Compile

```bash
make
```

# - Debugging
 
To debug CeanOS, do:
```bash
make debug
```
This will open Qemu and dump registers every time you do something.

# - Other

If you encounter a bug, create a new issue on the github page, or if you know how to fix it, create a pull request.

# - Contribuiting

If you are interseted in contribuiting to the development of CeanOS, dm me on discord: `asdasda123_` . 

### License
This project is licensed under GPL v3 (GNU General Public License v3.0). For more information go to the [LICENSE](LICENSE) file.