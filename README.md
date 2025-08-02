gcc -fPIC -c print.c -o print.o  
gcc -shared -o libprint.so print.o
