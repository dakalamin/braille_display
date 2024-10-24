cd "$(dirname "$0")/.."

if [ -f src/main.cpp ];
then
	echo Changing to ArduinoIDE project structure

	mv src main
	cd main
	mv main.cpp main.ino

elif [ -f main/main.ino ];
then
	echo Changing to PlatformIO project structure

	mv main src
	cd src
	mv main.ino main.cpp
	
else
	echo Project structure is not recognized
	echo Please consider reseting it

	exit 1
fi
