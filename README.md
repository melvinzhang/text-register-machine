# Text Register Machine Emulator

A Text Register Machine emulator written in C++ 11

## Building the binary

You'll need Make and g++ to compile the source code. Running

```
make
```

will produce the binary `trm`

## Command line options

The program takes two optional arguments. 

The first is the maximum number of steps to execute the machine.

The second the frames per second of the animation. A setting of zero means there is no animation.

The default is 1000 steps with no animation.

## Running the self progam, a quine

```
make self
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
