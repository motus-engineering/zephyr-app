#!/bin/bash

west twister -cv --coverage --gcov-tool gcovr --coverage-tool gcovr --coverage-formats txt -T tests/ -O ${WORKDIR}/build/twister
gcovr -f app --txt ${WORKDIR}/build/twister/coverage/coverage.txt --xml ${WORKDIR}/build/twister/coverage/coverage.xml ..
cat ${WORKDIR}/build/twister/coverage/coverage.txt
