# ece362_try2_hw2

These 3 programs are for Portland State University ECE362 HW#2
By Seth Rohrbach, Last modified Feb 2 2020.

Please find the 3 program descriptions below. Note these are largely just copied from the program headers and I have included them here simply because the assignment requires it.


******************


twist.c - this program reverses the order of bytes input, and outputs the bytes in reverse order.

For Portland State University ECE362 Winter 2020
Author: Seth Rohrbach
Last Modified: Feb 2, 2020

----------------------------
expected arguments:
-i <filename> : input file name. default is stdin
-o <filename> : output file name. default is stdout
-b <num>      : number of characters in a block to reverse. default is 10


*****************


xor.c - this program reads a sequence of bytes and logically bitwise XORs it with a mask.
this program should be reversable i.e. if the output is returned as input with the same mask, the original input is returned.
For Portland State University ECE362 Winter 2020
Author: Seth Rohrbach
Last Modified: Feb 2, 2020

----------------------------
expected arguments:
-i <filename> : input file name. default is stdin
-o <filename> : output file name. default is stdout
<string>      : mask used. must be less than 10 chars. this argument is mandatory and there is no default.


*************************


tx.c - this program will fork two processes to run xor and twist programs, also written with this assignment,
such that the output of twist is sent through a unix pipe to xor
For Portland State University ECE362 Winter 2020
Author: Seth Rohrbach
Last Modified: Feb 2, 2020

----------------------------
expected arguments:
-i <filename> : input file name. default is stdin. this argument will be sent to twist.
-o <filename> : output file name. default is stdout. this argument will be sent to xor.
-b <num>      : number of characters in a block to reverse. default is 10. this argument will be sent to twist.
<string>      : mask used. must be less than 10 chars. this argument is mandatory and there is no default. this program will be sent to xor.
