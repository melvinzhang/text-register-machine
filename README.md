# Text Register Machine Emulator

A Text Register Machine emulator written in C++ 11. It is based on the 1# language introduced in [Introduction to Computability Theory by Lawrence S. Moss](http://www.indiana.edu/~iulg/trm/)

## Building the binary

You'll need Make and g++ to compile the source code. Running

```
make
```

will produce the binary `trm`

## Command line options

The program takes two optional arguments. 

The first is the maximum number of steps to execute the machine.

The second is the frames per second of the animation. A setting of zero means there is no animation. A negative number disables the animation.

The default is 1000 steps with no animation.

## Generating the self progam, a quine

```
make self.trm
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
