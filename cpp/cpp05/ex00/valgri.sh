#!/usr/bin/env bash

clear
make val
valgrind --leak-check=full --show-leak-kinds=all ./buildValgrind