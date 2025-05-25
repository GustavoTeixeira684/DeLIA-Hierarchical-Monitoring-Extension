
diretorio=$(pwd)

export DELIA=$diretorio
export CC=mpicc
export CXX=mpic++
export OMPI_MCA_btl=^openib 

cd $DELIA
mkdir -p build
cd build
make clean
cmake ../ -DCMAKE_INSTALL_PREFIX=$DELIA -DVERBOSE=ON -DTEST=ON -DDEBUG=OFF
make -j
make install
cd $DELIA
sh $DELIA/test/ALLTESTS.sh $DELIA
