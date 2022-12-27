# Description
C program to return a list of palindromes in file: it's only 56 lines of ASM and the UTF-8 version is only 138 lines of ASM!

It can sort through a list of 300 million words case insensitively and write them to a file in under 7s. The UTF-8 version is ~1s slower for every 300 million words.

# Install & Usage
```
# UTF-8 version
wget https://github.com/i34/palindrome/raw/master/palindrome-utf8.c
gcc -O3 -opalindrome-utf8 palindrome-utf8.c
./palindrome-utf8 /path/to/wordfile

# Non UTF-8 version
wget https://github.com/i34/palindrome/raw/master/palindrome.c
gcc -O3 -opalindrome palindrome.c
./palindrome /path/to/wordfile
it is my addition
to this readme file 
