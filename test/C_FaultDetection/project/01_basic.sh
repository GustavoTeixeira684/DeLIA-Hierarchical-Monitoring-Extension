
#!/bin/bash

FT_PATH="$1"
PASSINGINTERFACESGL_PATH=$FT_PATH/test/C_FaultDetection/project

FILE_OUTPUT="$2"
FILE_ERROUTPUT="$3"
TYPE_TEST="$4"

cd $PASSINGINTERFACESGL_PATH
if [ -e $PASSINGINTERFACESGL_PATH/build ]; then
    rm -rv ./build/*; wait    
    rm -r build
    echo "DELETING BUILD"
fi

if [ -e $PASSINGINTERFACESGL_PATH/data ]; then
    rm -rv ./data/*; wait
    rm -r data
    echo "DELETING Data"
fi

if [ -e $PASSINGINTERFACESGL_PATH/DeLIA_lib ]; then
    rm -rv ./DeLIA_lib/*; wait
    rm -r DeLIA_lib
    echo "DELETING DeLIA_lib"
fi

mkdir DeLIA_lib
cp -r $FT_PATH/DeLIA_lib/ $PASSINGINTERFACESGL_PATH/

mkdir build
cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=$PASSINGINTERFACESGL_PATH -DDELIA=ON;
make -j; 
make install;
cd $PASSINGINTERFACESGL_PATH
mkdir data
TEST_LOCAL="TEST_LOCAL"
echo $TYPE_TEST
if [ "$TYPE_TEST" = "$TEST_LOCAL" ]; then
    echo "LOCAL TEST"
    mpirun -n 4 $PASSINGINTERFACESGL_PATH/bin/EXEC_TEST 10 "wo_trigger.json" >$FILE_OUTPUT 2>$FILE_ERROUTPUT
else
    echo "CI TEST"
    mpirun --allow-run-as-root -n 4 $PASSINGINTERFACESGL_PATH/bin/EXEC_TEST 10 "wo_trigger.json" >$FILE_OUTPUT 2>$FILE_ERROUTPUT
fi