#!/bin/bash

FT_PATH="$1"
FAULT_CODES=$FT_PATH/test/fault_codes
COMPLETION_CODES=$FT_PATH/test/completion_codes
DEFAULTCOLOR='\033[1;36m'
ERRORCOLOR='\033[1;31m'
HITCOLOR='\033[1;32m'
OUTPUT_FILE_COMPILE="output_compile.out"
OUTPUT_ERR_FILE_COMPILE="output_compile.err"


## ====================================
##  CONFIGURATION TO SHARE DATA TESTS
## ====================================
PASSINGLIST_PATH=$FT_PATH/test/B_Checkpoint/project

# RUN BASIC TEST:
# WITHOUT THE LIBFT.A
# WITHOUT ANY FAILURE
OUTPUT_FILE="output_basic.out"
OUTPUT_ERR_FILE="output_basic.err"

echo "${DEFAULTCOLOR}=PASSING DATA WITHOUT FAILURE"
cd $PASSINGLIST_PATH;

sh $PASSINGLIST_PATH/01_basic.sh $FT_PATH $PASSINGLIST_PATH/$OUTPUT_FILE $PASSINGLIST_PATH/$OUTPUT_ERR_FILE >$OUTPUT_FILE_COMPILE 2>$OUTPUT_ERR_FILE_COMPILE &
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

if grep -Ff $FAULT_CODES $PASSINGLIST_PATH/$OUTPUT_ERR_FILE > /dev/null
then
    echo "${ERRORCOLOR}=> Basic test case failed" 1>&2
    killall -s 9 EXEC_TEST
    exit 125
fi

until grep -Ff $FAULT_CODES $PASSINGLIST_PATH/$OUTPUT_ERR_FILE -le /dev/null
do
    sleep 5    
    if grep -Ff $FAULT_CODES $PASSINGLIST_PATH/$OUTPUT_ERR_FILE > /dev/null
    then
        echo "${ERRORCOLOR}=> Basic test case failed" 0/0
        killall -s 9 EXEC_TEST
        exit 1
    fi

    if grep -Ff $COMPLETION_CODES $PASSINGLIST_PATH/$OUTPUT_FILE > /dev/null
    then
        echo "${HITCOLOR}=> Basic test case finalized with sucess"
        break
    fi
done

OUTPUT_FILE="output_withfailure.out"
OUTPUT_ERR_FILE="output_withfailure.err"
OUTPUT_FILE_COMPILE="output.out"
OUTPUT_ERR_FILE_COMPILE="output.err"

echo "${DEFAULTCOLOR}=PASSING DATA WITH FAILURE"
cd $PASSINGLIST_PATH;

sh $PASSINGLIST_PATH/02_recovery_data.sh $FT_PATH $PASSINGLIST_PATH/$OUTPUT_FILE $PASSINGLIST_PATH/$OUTPUT_ERR_FILE >$OUTPUT_FILE_COMPILE 2>$OUTPUT_ERR_FILE_COMPILE &
sleep 60

if grep -Ff $FAULT_CODES $PASSINGLIST_PATH/$OUTPUT_ERR_FILE_COMPILE > /dev/null
then
    echo "${ERRORCOLOR}=> Recovery Data test case failed" 1>&2
    echo "${ERRORCOLOR}ERROR:" 1>&2
    grep -Ff $FAULT_CODES $PASSINGLIST_PATH/$OUTPUT_ERR_FILE_COMPILE
    killall -s 9 EXEC_TEST >>$OUTPUT_FILE_COMPILE 2>>$OUTPUT_ERR_FILE_COMPILE
    exit 125
else
    echo "${HITCOLOR}=> Recovery Data test case finalized with sucess"
fi
