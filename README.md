# rotN
Simple binary to do Caesar cipher

Created in C

## Compiling
Compile using `gcc` or `clang`, doesn't need any compiler flags since this is a very simple program.

For example: `gcc rotn.c -o rotN`

## Usage
`./rotN -r <rot amount> -i <input (optional)> -v (for verbose)`

The rotation amount will wrap around if it's greater than 25. If ran without input, it'll just read from `stdin`
