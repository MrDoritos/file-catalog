#!/bin/bash
#I have no fucking idea why I wasted my time making this file
echo PWD: $(pwd)
file="main.cpp"
include="-Icataloging/database/ -IMoorepp/crypto/ -IMoorepp/encoding/base64/ -IMoorepp/console/ -IMoorepp/socket/ -IMoorepp/socket/tcp/ -IMoorepp/ -IMoorepp/http/ -IMoorepp/conversions/ -IMoorepp/data/ -Icataloging/ -Imisc/"
opts="-fpermissive -w"

config1="-march=native -ggdb"
config1n="debug"

config2="-march=native -O2"
config2n="personal-release"

config3="-O2 -s"
config3n="fcat"

cnfg="3"
echo Compiling for $cnfg configuration\(s\)

echo BUILDING $file...
g++ $file $include $opts $config1 -o $config1n
if [ $? == 0 ]
then
echo ...END -\> $config1n
else
echo ...FAIL
fi

exit

echo BUILDING $file...
g++ $file $include $opts $config2 -o $config2n
if [ $? == 0 ]
then
echo ...END -\> $config2n
else
echo ...FAIL
fi

echo BUILDING $file...
g++ $file $include $opts $config3 -o $config3n
if [ $? == 0 ]
then
echo ...END -\> $config3n
else
echo ...FAIL
fi

