#!/bin/bash

FT_PATH="$1"
TYPE_TEST="$2"
FAULT_CODES=$FT_PATH/test/fault_codes
COMPLETION_CODES=$FT_PATH/test/completion_codes
DEFAULTCOLOR='\033[1;36m'
ERRORCOLOR='\033[1;31m'
HITCOLOR='\033[1;32m'

## ====================================
##              BASIC TEST
## ====================================

echo "${DEFAULTCOLOR}=HEARTBEAT BASIC CASE"
HM_PATH=$FT_PATH/test/C_FaultDetection/project

OUTPUT_FILE_COMPILE="output_compile.out"
OUTPUT_ERR_FILE_COMPILE="output_compile.err"
OUTPUT_FILE="output_basic.out"
OUTPUT_ERR_FILE="output_basic.err"
cd $HM_PATH;

sh $HM_PATH/01_basic.sh $FT_PATH $HM_PATH/$OUTPUT_FILE $HM_PATH/$OUTPUT_ERR_FILE $TYPE_TEST >$OUTPUT_FILE_COMPILE 2>$OUTPUT_ERR_FILE_COMPILE &
sleep 10
if grep -Ff $FAULT_CODES $OUTPUT_ERR_FILE_COMPILE > /dev/null
then
    echo "${ERRORCOLOR}=> Compiled with errors" 1>&2
    killall -s 9 EXEC_TEST
    exit 125
else
    echo "${HITCOLOR}=> Compiled with sucess"
fi
sleep 5

if grep -Ff $FAULT_CODES $HM_PATH/$OUTPUT_ERR_FILE > /dev/null
then
    echo "${ERRORCOLOR}=> Basic test case failed" 1>&2
    killall -s 9 EXEC_TEST
    exit 125
fi

until grep -Ff $FAULT_CODES $HM_PATH/$OUTPUT_ERR_FILE -le /dev/null
do
    sleep 5    
    if grep -Ff $FAULT_CODES $HM_PATH/$OUTPUT_ERR_FILE > /dev/null
    then
        echo "${ERRORCOLOR}=> Basic test case failed" 0/0
        killall -s 9 EXEC_TEST
        exit 1
    fi

    if grep -Ff $COMPLETION_CODES $HM_PATH/$OUTPUT_FILE > /dev/null
    then
        echo "${HITCOLOR}=> Basic test case finalized with sucess"
        break
    fi
done

## ====================================
##         WITH FAILURES TEST
## ====================================

echo "${DEFAULTCOLOR}=HEARTBEAT WITH FAILURES"
HM_PATH=$FT_PATH/test/C_FaultDetection/project


OUTPUT_FILE="output_wf.out"
OUTPUT_ERR_FILE="output_wf.err"
OUTPUT_FILE_COMPILE="outputall_wf.out"
OUTPUT_ERR_FILE_COMPILE="outputall_wf.err"
cd $HM_PATH;

sh $HM_PATH/02_with_failures.sh $FT_PATH $HM_PATH/$OUTPUT_FILE $HM_PATH/$OUTPUT_ERR_FILE $TYPE_TEST >$OUTPUT_FILE_COMPILE 2>$OUTPUT_ERR_FILE_COMPILE &

sleep 40

DETECT_NODE="LEADER_DETECT"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Leader Node detects failure of node 1"
else
    echo "${ERRORCOLOR}=> Leader Node does not detect failure of node 1" 1>&2
    exit 125
fi
sleep 10

TRIGGER_RECEIVED="NODE_2_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 2 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 2 does not receive trigger" 1>&2
    exit 125
fi

TRIGGER_RECEIVED="NODE_3_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 3 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 3 does not receive trigger" 1>&2
    exit 125
fi

TRIGGER_RECEIVED="NODE_4_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 4 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 4 does not receive trigger" 1>&2
    exit 125
fi
TRIGGER_RECEIVED="NODE_5_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 5 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 5 does not receive trigger" 1>&2
    exit 125
fi
TRIGGER_RECEIVED="NODE_6_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 6 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 6 does not receive trigger" 1>&2
    exit 125
fi
TRIGGER_RECEIVED="NODE_7_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 7 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 7 does not receive trigger" 1>&2
    exit 125
fi
TRIGGER_RECEIVED="NODE_8_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 8 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 8 does not receive trigger" 1>&2
    exit 125
fi
TRIGGER_RECEIVED="NODE_9_OK"
if $(grep -q $TRIGGER_RECEIVED $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Node 9 receives trigger"
else
    echo "${ERRORCOLOR}=> Node 9 does not receive trigger" 1>&2
    exit 125
fi

## ====================================
##    WITH TRIGGER SIGNAL TEST ALL
## ====================================

echo "${DEFAULTCOLOR}=TRIGGER SIGNAL IN ALL NODES"
HM_PATH=$FT_PATH/test/C_FaultDetection/project


OUTPUT_FILE="output_trigger_all.out"
OUTPUT_ERR_FILE="output_trigger_all.err"
OUTPUT_FILE_COMPILE="output_trigger_all_comp.out"
OUTPUT_ERR_FILE_COMPILE="output_trigger_all_comp.err"
cd $HM_PATH;

sh $HM_PATH/03_signal_for_all.sh $FT_PATH $HM_PATH/$OUTPUT_FILE $HM_PATH/$OUTPUT_ERR_FILE $TYPE_TEST >$OUTPUT_FILE_COMPILE 2>$OUTPUT_ERR_FILE_COMPILE &

sleep 40

DETECT_NODE="RANK_0_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 0 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 0 does not receive SIGTERM" 1>&2
    exit 125
fi
DETECT_NODE="RANK_1_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 1 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 1 does not receive SIGTERM" 1>&2
    exit 125
fi
DETECT_NODE="RANK_2_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 2 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 2 does not receive SIGTERM" 1>&2
    exit 125
fi
DETECT_NODE="RANK_3_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 3 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 3 does not receive SIGTERM" 1>&2
    exit 125
fi

DETECT_NODE="RANK_4_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 4 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 4 does not receive SIGTERM" 1>&2
    exit 125
fi

DETECT_NODE="RANK_5_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 5 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 5 does not receive SIGTERM" 1>&2
    exit 125
fi

DETECT_NODE="RANK_6_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 6 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 6 does not receive SIGTERM" 1>&2
    exit 125
fi

DETECT_NODE="RANK_7_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 7 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 7 does not receive SIGTERM" 1>&2
    exit 125
fi

DETECT_NODE="RANK_8_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 8 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 8 does not receive SIGTERM" 1>&2
    exit 125
fi

DETECT_NODE="RANK_9_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 9 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 9 does not receive SIGTERM" 1>&2
    exit 125
fi

## ====================================
##   WITH TRIGGER SIGNAL TEST FOR 0
## ====================================

echo "${DEFAULTCOLOR}=TRIGGER SIGNAL JUST NODE 0"
HM_PATH=$FT_PATH/test/C_FaultDetection/project


OUTPUT_FILE="output_trigger_0.out"
OUTPUT_ERR_FILE="output_trigger_0.err"
OUTPUT_FILE_COMPILE="output_trigger_0_comp.out"
OUTPUT_ERR_FILE_COMPILE="output_trigger_0_comp.err"
cd $HM_PATH;

sh $HM_PATH/04_signal_for_0.sh $FT_PATH $HM_PATH/$OUTPUT_FILE $HM_PATH/$OUTPUT_ERR_FILE $TYPE_TEST >$OUTPUT_FILE_COMPILE 2>$OUTPUT_ERR_FILE_COMPILE &

sleep 120

DETECT_NODE="RANK_0_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 0 receives SIGTERM"
else
    echo "${ERRORCOLOR}=> Rank 0 does not receive SIGTERM" 1>&2
    exit 125
fi
DETECT_NODE="RANK_1_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 1 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 1 does not receive trigger from node 0" 1>&2
    exit 125
fi
DETECT_NODE="RANK_2_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 2 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 2 does not receive trigger from node 0" 1>&2
    exit 125
fi
DETECT_NODE="RANK_3_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 3 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 3 does not receive trigger from node 0" 1>&2
    exit 125
fi

DETECT_NODE="RANK_4_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 4 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 4 does not receive trigger from node 0" 1>&2
    exit 125
fi

DETECT_NODE="RANK_5_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 5 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 5 does not receive trigger from node 0" 1>&2
    exit 125
fi

DETECT_NODE="RANK_6_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 6 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 6 does not receive trigger from node 0" 1>&2
    exit 125
fi

DETECT_NODE="RANK_7_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 7 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 7 does not receive trigger from node 0" 1>&2
    exit 125
fi

DETECT_NODE="RANK_8_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 8 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 8 does not receive trigger from node 0" 1>&2
    exit 125
fi

DETECT_NODE="RANK_9_RECEIVED_SIGNAL"
if $(grep -q $DETECT_NODE $OUTPUT_FILE_COMPILE)
then
    echo "${HITCOLOR}=> Rank 9 receives trigger from node 0"
else
    echo "${ERRORCOLOR}=> Rank 9 does not receive trigger from node 0" 1>&2
    exit 125
fi