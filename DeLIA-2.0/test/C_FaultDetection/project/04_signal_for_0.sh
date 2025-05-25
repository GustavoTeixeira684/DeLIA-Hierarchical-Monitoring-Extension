
#!/bin/bash

FT_PATH="$1"
PASSINGINTERFACESGL_PATH=$FT_PATH/test/C_FaultDetection/project

FILE_OUTPUT="$2"
FILE_ERROUTPUT="$3"
TYPE_TEST="$4"

cd $PASSINGINTERFACESGL_PATH

if [ -e $PASSINGINTERFACESGL_PATH/data ]; then
    rm -rv ./data/*; wait
    rm -r data
    echo "DELETING Data"
fi

cd $PASSINGINTERFACESGL_PATH
mkdir data
TEST_LOCAL="TEST_LOCAL"

if [ "$TYPE_TEST" = "$TEST_LOCAL" ]; then
    echo "LOCAL TEST WITH FAIL"
    mpirun -n 5 $PASSINGINTERFACESGL_PATH/bin/EXEC_TEST 100 "w_trigger.json" >$FILE_OUTPUT 2>$FILE_ERROUTPUT &
else
    echo "CI TEST"
    mpirun --allow-run-as-root -n 5 $PASSINGINTERFACESGL_PATH/bin/EXEC_TEST 100 "w_trigger.json" >$FILE_OUTPUT 2>$FILE_ERROUTPUT &
fi

sleep 25;
STATERUN=$(ps -C EXEC_TEST)
echo $STATERUN
echo "aqui"
JOB_ID=$(echo $STATERUN | grep -o -E '[0-9]+' | head -n 1 | tail -6 | sed -e 's/^0\+//')
echo $JOB_ID
SIGTERM=15
SIGKILL=9
echo "matando o processo"
echo $JOB_ID
kill -$SIGTERM $JOB_ID
sleep 20
echo "matando o processo pela segunda vez"
echo $JOB_ID
kill -$SIGTERM $JOB_ID
sleep 20
DETECT_NODE="SIGNAL_RECEIVED_15_IN_RANK_0"
if $(grep -q $DETECT_NODE $FILE_ERROUTPUT)
then
    echo "${HITCOLOR}RANK_0_RECEIVED_SIGNAL"
else
    echo "${ERRORCOLOR}}RANK_0_NOT_RECEIVED_SIGNAL" 1>&2
    exit 125
fi
DETECT_NODE="MSG_RECEIVED_1_:_-1"
if $(grep -q $DETECT_NODE $FILE_ERROUTPUT)
then
    echo "${HITCOLOR}RANK_1_RECEIVED_SIGNAL"
else
    echo "${ERRORCOLOR}}RANK_1_NOT_RECEIVED_SIGNAL" 1>&2
    exit 125
fi
DETECT_NODE="MSG_RECEIVED_2_:_-1"
if $(grep -q $DETECT_NODE $FILE_ERROUTPUT)
then
    echo "${HITCOLOR}RANK_2_RECEIVED_SIGNAL"
else
    echo "${ERRORCOLOR}}RANK_2_NOT_RECEIVED_SIGNAL" 1>&2
    exit 125
fi
DETECT_NODE="MSG_RECEIVED_3_:_-1"
if $(grep -q $DETECT_NODE $FILE_ERROUTPUT)
then
    echo "${HITCOLOR}RANK_3_RECEIVED_SIGNAL"
else
    echo "${ERRORCOLOR}}RANK_3_NOT_RECEIVED_SIGNAL" 1>&2
    exit 125
fi


killall -s $SIGKILL EXEC_TEST