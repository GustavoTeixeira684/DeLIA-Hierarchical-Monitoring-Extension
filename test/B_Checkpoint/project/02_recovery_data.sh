
#!/bin/bash

FT_PATH="$1"
PASSINGLIST_PATH=$FT_PATH/test/B_Checkpoint/project

FILE_OUTPUT="$2"
FILE_ERROUTPUT="$3"

cd $PASSINGLIST_PATH

if [ -e $PASSINGLIST_PATH/data ]; then
    rm -rv ./data/*; wait
    rm -r data
    echo "DELETING Data"
fi

mkdir data
$PASSINGLIST_PATH/bin/EXEC_TEST 10 wofailures.out >$FILE_OUTPUT 2>$FILE_ERROUTPUT

if [ -e $PASSINGLIST_PATH/data ]; then
    rm -rv ./data/*; wait
    rm -r data
    echo "DELETING Data"
fi
mkdir data
$PASSINGLIST_PATH/bin/EXEC_TEST 10 wfailures.out >>$FILE_OUTPUT 2>>$FILE_ERROUTPUT &

# SIGKILL=5
SIGKILL=9
sleep 5
killall -s $SIGKILL EXEC_TEST

$PASSINGLIST_PATH/bin/EXEC_TEST 10 wfailures.out >>$FILE_OUTPUT 2>>$FILE_ERROUTPUT

# diff wofailures.bin wfailures.bin > diferance

if cmp -s wofailures.out wfailures.out; then
    echo "FILE EQUAL";
else
    echo "FILE DIFFERENT" 1>&2;
fi