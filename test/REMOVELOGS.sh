#!/bin/bash

PATH_PROJECT="$1"
echo $PATH_PROJECT
cd $PATH_PROJECT/test;
ls
rm -rv $PATH_PROJECT/test/*/*.out
rm -rv $PATH_PROJECT/test/*/*/*.out
rm -rv $PATH_PROJECT/test/*/*.bin
rm -rv $PATH_PROJECT/test/*/*/*.bin
rm -rv $PATH_PROJECT/test/*/*.err
rm -rv $PATH_PROJECT/test/*/*/*.err