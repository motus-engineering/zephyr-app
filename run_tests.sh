#!/bin/bash

west twister -cv --coverage --gcov-tool gcovr --coverage-tool gcovr --coverage-formats txt -T app/tests/ -O build/twister
gcovr -f app --txt build/twister/coverage/coverage.txt --xml build/twister/coverage/coverage.xml ..
cat build/twister/coverage/coverage.txt
