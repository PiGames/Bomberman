#!/bin/sh
​
ELFNAME="BombermanX86_64"
​
# silent check if libsfml is installed
ldconfig -p | grep libsfml > /dev/null
if [ `echo $?` -ne 0 ]; then
	echo "SFML is not installed!"
	echo "Downloading SFML..."
	sudo apt-get install libsfml-dev
fi

# compile
make && make clean 
​
# privileges
chmod 744 "$ELFNAME"
