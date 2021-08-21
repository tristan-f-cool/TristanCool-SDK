#!/bin/bash

set -e
echo
# Tristan Cool - SDK Raspsberry Pi API updater
# repos must be cloned in '/home/pi/repos/TristanCool-SDK'
echo Tristan Cool - SDK Raspsberry Pi API updater
echo
date
echo
echo use 'Ctrl + c' to terminate script
echo
cd ~
cd /home/pi/repos/TristanCool-SDK
read -p "Select branch: 1-master : 2-RASPBERRYPI-API : 3-RASPBERRYPI-API_dev : q- Quit " branch
echo 

if [ $branch == '1' ]
then
    branch=master
    echo master
    git checkout master
elif [ $branch == '2'  ]
then
    branch=RASPBERRYPI-API
    echo RASPBERRYPI-API
    git checkout RASPBERRYPI-API
elif [ $branch == '3'  ]
then
    branch=RASPBERRYPI-API_dev
    echo RASPBERRYPI-API_dev
    git checkout RASPBERRYPI-API_dev
elif [ $branch == 'q'  ]
then
    echo quit
else
    echo invalid selection
fi

git status
echo 

read -p "Update repos? y/n : " update

if [ $update == 'y' ]
then
    echo updating...
    echo $branch
    git pull origin $branch
elif [ $update == 'n'  ]
then
    echo not updating...
else
    echo invalid selection
fi
