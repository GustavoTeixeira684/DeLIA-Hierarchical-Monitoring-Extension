DELIA="$1"

cd $DELIA
wait;
if [ -e $DELIA/build ]; then
    rm -rv ./build/*; wait  
    rm -r build
    echo "DELETING BUILD"
fi

if [ -e $DELIA/DeLIA_lib ]; then
    rm -rv ./DeLIA_lib/*; wait  
    rm -r DeLIA_lib
    echo "DELETING DeLIA_lib"
fi

mkdir build 
cd build
make clear
cmake ../ -DCMAKE_INSTALL_PREFIX=$DELIA -DVERBOSE=ON -DTEST=ON -DDEBUG=OFF;
make -j; 
make install;