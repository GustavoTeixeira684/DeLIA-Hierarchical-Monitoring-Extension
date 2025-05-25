
#!/bin/bash

FT_PATH="$1"
PASSINGLIST_PATH=$FT_PATH/test/B_Checkpoint/project

FILE_OUTPUT="$2"
FILE_ERROUTPUT="$3"

cd $PASSINGLIST_PATH
if [ -e $PASSINGLIST_PATH/build ]; then
    rm -rv ./build/*; wait    
    rm -r build
    echo "DELETING BUILD"
fi

if [ -e $PASSINGLIST_PATH/data ]; then
    rm -rv ./data/*; wait
    rm -r data
    echo "DELETING Data"
fi

if [ -e $PASSINGLIST_PATH/DeLIA_lib ]; then
    rm -rv ./DeLIA_lib/*; wait
    rm -r DeLIA_lib
    echo "DELETING DeLIA_lib"
fi

mkdir DeLIA_lib
cp -r $FT_PATH/DeLIA_lib/ $PASSINGLIST_PATH/

mkdir build
cd build
# cmake ../ -DCMAKE_INSTALL_PREFIX=$PASSINGLIST_PATH -DDELIA=ON -DDEBUG=ON;
cmake ../ -DCMAKE_INSTALL_PREFIX=$PASSINGLIST_PATH -DDELIA=ON -DDEBUG=ON -DCMAKE_CXX_FLAGS=-pg -DCMAKE_EXE_LINKER_FLAGS=-pg -DCMAKE_SHARED_LINKER_FLAGS=-pg;
make -j; 
make install;
cd $PASSINGLIST_PATH
mkdir data
$PASSINGLIST_PATH/bin/EXEC_TEST 10 wofailures.out >$FILE_OUTPUT 2>$FILE_ERROUTPUT