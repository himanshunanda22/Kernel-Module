# Kernel-Module
A simple kernel module to print any string into a file using echo and cat for printing on the terminal.
How to run this Kermel Module:A simple kernel module to print anything into a file which is logged into a file:
First you need to be a root user to access al dev files provided in your kernel.
Save your code-file, in my case it is “osproject.c”
Create a Makefile as shown above
Now run the following commands one at a time
  1.	sudo apt-get install linux-headers-$(uname -r)
  2.	make -C /lib/modules/$(uname -r)/build M=$(pwd) modules -v
  3.	sudo insmod osproject.ko
  4.	sudo su
  5.	echo "hello" > /dev/osproject (instead of hello input whatever you wish to enter into the file)
  6.	cat /dev/osproject
  7.	For example, to change the permissions of /dev/mydev to allow all users to write to it, you can run the following command as the root user:
      chmod a+w /dev/mydev

 
 
