# retro-matrix

![Project screencast](doc/screencast.gif)

**retro-matrix** is an independent program to show a digital rain animation on your screen.

**retro-matrix** is so independent that it does not need any operating system to work. It just works on bare x86 machines. **retro-matrix** is also a 16-bit program, which is primitive, and, indeed retro.

**retro-matrix** is also a submission for one of assignments in **IF2230 Operating System course**.

## Getting Started

### Requirements

To get started with this project, you need these tools.

- [`bin86` and `dev86`](http://v3.sk/~lkundrak/dev86) for program compilation.
- [`nasm`](https://nasm.us) for bootloader compilation.
- [GNU Make](https://gnu.org/software/make) as the build system.
- [Bochs](http://bochs.sourceforge.net), [QEMU](https://qemu.org) or other virtual machine to run.

### Compilation

To compile:

```
$ make
```

This command will generate a floppy image on `bin/floppy.img`.

### Running

**Bochs** can be used for testing.

```
$ bochs -f opsys.bxrc
```

Then, press `c` to continue.

You can use another virtual machine other than **Bochs**, like **QEMU**, **VirtualBox**, etc. Just boot `bin/floppy.img` as a RAW floppy image.

## Architecture Overview

The original assignment specification can be seen [here](doc/SpesifikasiTugasBesar-BeneathTheSkin-Milestone-1.pdf) in Indonesian.

The first component to be executed is [the bootloader](src/_ctrl/loader.asm), which loads the kernel from the disk, then executes the top of it.

The first component of the kernel to be executed must be [the entry point](src/_ctrl/main.s), so it is [passed as the first parameter](Makefile#L64) to the linker, so it is placed on the top of the kernel.

The entry point executes [`kernel_main`](src/main.c#L10) routine which is written in C language, which also initializes several things:

- [The digital rain animation](src/anim.c) itself.
- [Timer interrupt](src/timer.c) to advance the animation in defined period.
- [Keyboard interrupt](src/kbd.c) to listen for keyboard events.

## Contributors

**retro-matrix** is bought to you by:

- **13515035 Oktavianus Handika** ([handikao29](https://github.com/handikao29)) for the assets.
- **13515071 Daniel Pintara** ([nieltg](https://github.com/nieltg)) for the main program.
- **13515080 Muhammad Treza Nolandra** ([rezardes](https://github.com/rezardes)) for compile script for the submission.

## License

[MIT](LICENSE)
