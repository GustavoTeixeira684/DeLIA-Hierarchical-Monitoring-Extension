FT_PATH="$1"
FAULT_CODES=$FT_PATH/test/fault_codes
COMPLETION_CODES=$FT_PATH/test/completion_codes
DEFAULTCOLOR='\033[1;36m'
ERRORCOLOR='\033[1;31m'
HITCOLOR='\033[1;32m'
OUTPUT_FILE_COMPILE="output_compile.out"
OUTPUT_ERR_FILE_COMPILE="output_compile.err"

LIBRARY_TEST=$FT_PATH/test/A_Library

cd $LIBRARY_TEST;
sh $LIBRARY_TEST/compile_library.sh $FT_PATH >$OUTPUT_FILE_COMPILE 2>$OUTPUT_ERR_FILE_COMPILE &
sleep 10
if grep -Ff $FAULT_CODES $OUTPUT_ERR_FILE_COMPILE > /dev/null
then
    echo "${ERRORCOLOR}=> Compiled with erros" 1>&2
    0/0
    exit 1
else
    echo "${HITCOLOR}=> Compiled with sucess"
fi