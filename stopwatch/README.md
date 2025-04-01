# A CLI based Stopwatch in C
<br>

## What is this?
- A CLI based Stopwatch, written entirely in C.

<br>

## What it does?
- Show the time elapsed since the execution of the program.
- Stops the program when user types any character
- Executes the program in non-canonical mode.
    - Thus no need to press enter when typing the character.
- Uses 'read()' syscall in order to read the character.
    - read() is a low-level syscall.
    - It allows finer control over user-input and output.

<br>

## Potential bugs and missing features:

- Missing features:
    - Only compiles on POSIX Compliant operating systems (Unix, Linux and MacOs)

<br>

## What I learned from this project?
- Low-level terminal interface and it's manipulation.
    - Learned about canonical and non-canonical terminal modes.
    - Learned about the 'read()' syscall.
    - Learned about 'File streams and file descriptors' and how they differ.
    - Learned about 'bit-flags, bit-manipulation and bit-masking'.