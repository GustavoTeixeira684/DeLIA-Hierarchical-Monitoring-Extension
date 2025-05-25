#!/bin/bash

PATH_PROJECT="$1"
TYPE_TEST="$2"

N=""
if [ "$TYPE_TEST" = "$N" ]; then
    TYPE_TEST="TEST_LOCAL"
fi

LIBRARYDATA_PATH=$PATH_PROJECT/test/A_Library
GLOBALDATA_PATH=$PATH_PROJECT/test/B_Checkpoint
HM_PATH=$PATH_PROJECT/test/C_FaultDetection
SHAREDATA_PATH=$PATH_PROJECT/test/D_ShareData
DEFAULTCOLOR='\033[1;36m'

echo "${DEFAULTCOLOR}============================================"
echo "${DEFAULTCOLOR}                 DELIA TESTS"
echo "${DEFAULTCOLOR}============================================"
echo "${DEFAULTCOLOR}           LIBRARY COMPILE TESTS"
if (! sh $LIBRARYDATA_PATH/alltests.sh $PATH_PROJECT); then
  exit 1                                 
fi
echo "${DEFAULTCOLOR}============================================"
echo "${DEFAULTCOLOR}           CHECKPOINT DATA TESTS"
if (! sh $GLOBALDATA_PATH/alltests.sh $PATH_PROJECT); then
  exit 1                                 
fi
echo "${DEFAULTCOLOR}============================================"
echo "${DEFAULTCOLOR}           INTERRUPTION DETECTION TESTS"
if (! sh $HM_PATH/alltests.sh $PATH_PROJECT); then
  exit 1                                 
fi
echo "${DEFAULTCOLOR}============================================"