# Code Analyzer

A simple C++ code analyzer that reads a source file, performs a few basic checks, and displays the analysis in a GLUT-based GUI window.

## Features

- Counts total, blank, comment, and code lines
- Checks for possible missing semicolons on common statements
- Verifies whether braces are balanced
- Reports style issues such as long lines and `goto`
- Gives simple performance tips for `endl` and raw `new`
- Counts `for` and `while` loops
- Detects whether `main()` exists
- Counts functions using a basic pattern check

## Files

- `code_analyzer.cpp` - main analyzer program
- `example1.cpp` - sample file you can use for testing

## How It Works

The program:

1. asks for a filename,
2. reads the file line by line,
3. runs several analysis checks,
4. shows the output inside an OpenGL/GLUT window.

## Requirements

- C++ compiler with standard library support
- OpenGL
- GLUT or FreeGLUT

## Compile

Example command with `g++`:

```bash
g++ code_analyzer.cpp -o code_analyzer -lglut -lglu32 -lopengl32
```

If your system uses different library names or paths, adjust the command accordingly.

## Run

After compiling:

```bash
./code_analyzer
```

Then enter a file name such as:

```bash
example1.cpp
```

## Sample Checks Performed

The analyzer currently looks for:

- line statistics
- comment and blank line counts
- brace balance
- possible missing semicolons
- long lines over 80 characters
- use of `goto`
- use of `endl`
- raw pointer allocation with `new`
- loop counts
- presence of `main()`
- approximate function count

## Limitations

This is a basic educational project, so the checks are simple text-based checks rather than full compiler-level parsing. Some warnings may be approximate.

## Purpose

This project is useful for learning:

- file handling in C++
- string processing
- simple static analysis ideas
- OpenGL/GLUT text output

## Author

Jeet Patel
