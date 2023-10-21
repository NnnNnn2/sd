#!/bin/bash

if [ -z /usr/bin ]; then
	echo "no /usr/bin directory!"
else
	sudo install ./sd /usr/bin/
	echo "success!"
fi

if [ -z /usr/local/share/man/man1 ]; then
	echo "couldn't copy the manual"
else
	sudo cp ./sd.1 /usr/local/share/man/man1
	sudo gzip /usr/local/share/man/man1/sd.1
	sudo mandb
	echo "manual copied"
fi
