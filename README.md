# Huffman File Compressor

A simple and efficient file compression tool using Huffman coding algorithm. This program can compress and decompress files using Huffman encoding to reduce file size while ensuring lossless compression.

## Features

- Lossless file compression
- Command-line interface
- Supports any file type
- Simple to use
- Error handling and validation

## Project Structure

```
file-compressor/
├── build/
│   ├── bin/         # Compiled binary
│   └── obj/         # Object files
├── src/
│   ├── app/
│   │   ├── main.c           # Entry point
│   │   ├── huffman.c        # Huffman coding implementation
│   │   ├── compress.c       # Compression logic
│   │   └── decompress.c     # Decompression logic
│   └── include/
│       └── huffman.h        # Header file
├── Makefile         # Build configuration
├── LICENSE          # License file
└── README.md        # This file
```

## Prerequisites

- GCC compiler
- Make build system
- Unix-like environment (Linux, macOS)

## Building

1. Clone the repository:
```bash
git clone [repository-url]
cd file-compressor
```

2. Build the project:
```bash
make clean  # Clean any previous builds
make        # Build the project
```

The executable will be created at `build/bin/compressor`

## Usage

### Compressing a File

```bash
./build/bin/compressor comp <filename>
```

This will create a compressed file with `.huf` extension.

### Decompressing a File

```bash
./build/bin/compressor decomp <filename.huf>
```

This will restore the original file from the compressed `.huf` file.

## Examples

```bash
# Compress a text file
./build/bin/compressor comp example.txt
# Creates example.txt.huf

# Decompress the file
./build/bin/compressor decomp example.txt.huf
# Restores original example.txt
```

## Error Handling

The program includes error checking for:
- File open/read/write operations
- Memory allocation
- Invalid input files
- Corrupt compressed files
- Empty files

## Memory Usage

The program uses dynamic memory allocation for:
- File buffers
- Huffman tree nodes
- Frequency tables
- Compressed data storage

All memory is properly freed after use.

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Algorithm Overview

The compression uses Huffman coding which:
1. Counts frequency of bytes in the input file
2. Builds a Huffman tree based on these frequencies
3. Generates variable-length codes for each byte
4. Replaces each byte with its corresponding code

The compressed file format:
1. File size (8 bytes)
2. Number of unique characters (1 byte)
3. Frequency table
4. Compressed data

## Future Improvements

- [ ] Add multi-threading support
- [ ] Implement progress indicator
- [ ] Add compression ratio display
- [ ] Support for directory compression
- [ ] Add integrity checking