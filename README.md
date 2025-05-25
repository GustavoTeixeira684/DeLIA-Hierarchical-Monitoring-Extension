# Developer overview

This code refers to the fault tolerance library DeLIA [`(check the user documentation)`](https://lappsufrn.gitlab.io/delia/index.html) and is implemented in C++.
The folder organization is:
* include: the necessary headers to use in an application.
* libs: the external libs used in the code
* src: the source code
* test: usability test with the testing of the main features.

## Generated the library

```sh
$ git clone git@gitlab.com:lappsufrn/delia.git
$ export DELIA=<PATH TO DELIA FOLDER>
$ cd $DELIA
$ mkdir build 
$ cd build
$ make clear
$ cmake ../ -DCMAKE_INSTALL_PREFIX=$DELIA -DVERBOSE=ON -DTEST=OFF -DDEBUG=OFF;
$ make -j; 
$ make install;
```
## Run the tests
```sh
$ cd $DELIA
$ sh $DELIA/test/ALLTESTS.sh $DELIA
```
After running the tests, the output message should be:

<p align="center">
  <img src="./assets/test_result.png" width="300" title="" />
</p>

If you have any problem, you can check the log files in the test folder. Otherwise, you can remove all logs with the command:

```sh
$ cd $DELIA
$ sh $DELIA/test/REMOVELOGS.sh $DELIA
```

## Credits

This project is based on the original [DeLIA fault tolerance library](https://gitlab.com/lappsufrn/delia.git), developed by the LApps research group at UFRN.

We would like to thank the original authors for their contribution to fault-tolerant systems in distributed computing. For more information, refer to the official documentation: [https://lappsufrn.gitlab.io/delia/index.html](https://lappsufrn.gitlab.io/delia/index.html).

