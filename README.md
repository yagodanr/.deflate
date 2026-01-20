# Deflate Compression Tool

## Overview

This is a student project implementing a custom deflate compression and decompression tool in C++. The project demonstrates understanding of data compression algorithms, including Huffman coding and LZ77, and provides a practical implementation for compressing and decompressing files. This work showcases skills in algorithm design, C++ programming, binary file handling, and performance optimization.

## Features

- **Compression**: Implements deflate-like compression using LZ77 and Huffman coding.
- **Decompression**: Efficiently decompresses files compressed with the tool.
- **Binary File Handling**: Custom utilities for reading and writing binary data.
- **Test Files**: Includes various test cases (bigfile, lz_test1, lz_test2, lz_test3) to validate compression ratios and correctness.
- **Command-Line Interface**: Simple CLI for encoding and decoding files.

## Algorithms Implemented

1. **LZ77 (Lempel-Ziv 1977)**: Sliding window compression technique for finding repeated sequences in data.
2. **Huffman Coding**: Entropy encoding for variable-length codes based on frequency analysis.
3. **Deflate Combination**: Integrates LZ77 and Huffman to achieve high compression ratios.

The implementation focuses on educational purposes, demonstrating core concepts of lossless compression while maintaining reasonable performance.

## Requirements

- **C++ Compiler**: GCC or similar (tested with g++)
- **Build System**: Makefile or direct compilation
- **Operating System**: Linux (tested on Linux)

## Installation

1. Clone or download the project repository.
2. Navigate to the project directory.
3. Compile the source files:

   ```bash
   g++ -o encode encode.cpp rw_binary.cpp
   g++ -o decode decode.cpp rw_binary.cpp
   ```

## Usage

### Compression

To compress a file (e.g., `bigfile.txt`):

```bash
./encode bigfile.txt bigfile.deflate
```

### Decompression

To decompress a file (e.g., `bigfile.deflate`):

```bash
./decode bigfile.deflate bigfile_decoded.txt
```

### Testing

The project includes several test files:

- `lz_test1.txt` / `lz_test1.deflate`
- `lz_test2.txt` / `lz_test2.deflate`
- `lz_test3.txt` / `lz_test3.deflate`
- `bigfile.txt` / `bigfile.deflate`

Run compression and decompression on these to verify functionality:

```bash
./encode lz_test1.txt lz_test1.deflate
./decode lz_test1.deflate lz_test1_decoded.txt
diff lz_test1.txt lz_test1_decoded.txt  # Should show no differences
```

## Project Structure

```
.
├── encode.cpp              # Main compression program
├── decode.cpp              # Main decompression program
├── rw_binary.cpp           # Binary read/write utilities
├── rw_binary.h             # Header for binary utilities
├── write_binary_dict.cpp   # Dictionary writing utility
├── write_binary_obj.cpp    # Object writing utility
├── write_binary_obj.h      # Header for object utilities
├── bigfile.txt             # Large test file
├── bigfile.deflate         # Compressed version
├── bigfile_decoded.txt     # Decompressed output
├── lz_test1.txt            # Test file 1
├── lz_test1.deflate        # Compressed test 1
├── lz_test2.txt            # Test file 2
├── lz_test2.deflate        # Compressed test 2
├── lz_test3.txt            # Test file 3
├── lz_test3.deflate        # Compressed test 3
├── text.txt                # Additional text file
├── image.deflate           # Compressed image
├── writing_binary.deflate  # Binary writing test
├── LICENSE                 # Project license
├── build/                  # Build directory
│   └── Debug/
│       └── outDebug        # Compiled executable
└── README.md               # This file
```

## Performance Notes

- Compression ratios vary based on input data entropy.
- Optimized for educational clarity rather than maximum speed.
- Handles both text and binary files.

## Learning Outcomes

This project demonstrates:

- Implementation of classic compression algorithms
- Binary data manipulation in C++
- Memory management and efficiency
- Testing and validation of compression tools
- Command-line application development
