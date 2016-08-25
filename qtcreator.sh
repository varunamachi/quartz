#/bin/bash

exec &> logfile.txt

SCRIPT_DIR=$(dirname $0)
QUARTZ_ROOT=`readlink -f .`
echo "Using root $QUARTZ_ROOT"
export QUARTZ_ROOT
if [[ -e ~/bin/qtcreator ]] 
then
    echo "Launching ~/bin/qtcreator"
    ~/bin/qtcreator &
elif [[ -e ~/Bin/qtcreator ]] 
then
    echo "Launching ~/Bin/qtcreator"
    ~/Bin/qtcreator &
else
    echo "Launching `which qtcreator`"
    qtcreator &
fi
    





