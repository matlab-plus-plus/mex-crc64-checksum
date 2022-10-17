Matlab Mex Facilities for Calculating CRC64 Checksums
=====================================================

This project provides a small, fast library for calculating CRC64 checksums of text, files, and directories in Matlab code.

> **_Disclaimer:_**  Checksums are not [cryptographically secure](https://en.wikipedia.org/wiki/Cryptographic_hash_function). Use a crytpo hash like [sha256](https://en.wikipedia.org/wiki/SHA-2) if you require high security.
> See the [use-cases](#use-case) section for appropriate applications of crc64 checksums.

# Features
- The `+crc64` package containing the Matlab library functions
    - FileChecksum: Computes the checksum of a file
    - FolderChecksum: Computes the checksum of a directory
    - TextChecksum: Computes the checksum of input text (string or char array)
- The `crc64.mexw64` mex function, abstracted-away through the above Matlab functions.
    - This is written in C++, so it is very fast. Heavyweight operations like file reading and directory iteration are handled on the mex side, and only extremely minimal data is passed into and out of the Matlab <-> mex interface.
    - Both data type and semantic constraints are validated in the Matlab code wrappers, so you don't have to worry about debugging crytpic errors. You shouldn't ever have to actually look at the C++ code if you don't want to.
- The `crc64.exe` program is also provided as a convenient command line tool for calculating checksums outside of Matlab.

# Algorithm
[CRC64](https://en.wikipedia.org/wiki/Cyclic_redundancy_check) stands for Cyclic Redundancy Check [using a 64-bit Linear Feedback Shift Register ([LFSR](https://en.wikipedia.org/wiki/Linear-feedback_shift_register)). This project uses the same CRC64 specification as 7-zip: [CRC-64/XZ](https://reveng.sourceforge.io/crc-catalogue/all.htm#crc.cat.crc-64-xz)[1^] (also called CRC-64/GO-ECMA). This decision, made in the early stages of development, was born out of two requirements:
1. Trivial verification of checksums calculated on files.
2. Seamless integration into an existing project which used 7-zip as the (slow)[^2] method of calculating file checksums.
Most people already have [7-zip](https://www.7-zip.org/) installed on their computer, so it is very straightforward for any library user to verify the correctness themselves by calculating the checksum of any file using both methods. Also, it goes without saying, but 7-zip is such a ubiquitous tool in the software development field, algorithms selected by the library have a fair bit of ethos backing them and will help will adoption.

[~1]: 7-zip's documentation gets this wrong and claims it's _ECMA_. However, the [crc-catalog](https://reveng.sourceforge.io/crc-catalogue/all.htm#crc.cat.crc-64-xz) link above explains this is a common misidentification. You can verify it yourself by creating a file with the exact string "123456789" using a UTF-8 encoding. 7-zip should return the hex value `0x995dc9bbdf1939fa`, indicating it used CRC-64/XZ.
[^2]: It's important to note that 7-zip itself is extremely fast, but the system call required to reach-out from Matlab is painfully slow (on the order of 500 ms).

# Use Cases
_TODO_

# Upcomming FEX Availability
The plan is to add this library to the [Mathworks File Exchange](https://www.mathworks.com/matlabcentral/fileexchange/) once this project reaches a stable development point.
This will most likely happen at release 1.0.0.