#!/bin/bash

clear

rm -rf LoremToHello.log
rm -rf forbiddenLocation.log

make re

valgrind --leak-check=full --track-fds=yes --log-file=forbiddenLocation.log ./Sed_is_for_losers nonexistent Lorem hello

valgrind --leak-check=full --track-fds=yes --log-file=LoremToHello.log ./Sed_is_for_losers text Lorem hello