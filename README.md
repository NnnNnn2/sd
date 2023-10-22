# sd
Linux program, it mimics basic behaviour of ls but is simpler and worse, I have no idea why would you even use it but hey

so basically you want to download it and run install.sh, to do it follow an instruction below

$ mkdir ~/sd

$ cd ~/sd

$ git clone https://github.com/NnnNnn2/sd.git

$ cd sd

$ chmod +x install.sh

$ ./install.sh


if it doesn't work you can compile the C file using gcc

$ gcc -o <path to sd.c> sd

and then manually install said file

$ sudo install ./sd /usr/bin
