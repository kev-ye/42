#!/bin/bash

## ANSI COLOR CODES

BLACK="\033[1;30m"
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
CYAN="\033[1;36m"
NONE="\033[0m"
CLR_SCREEN="\033[2J\033[H"

## Var: folder

CONTAINERS_FOLDER=../containers

## Var: compilation

CC=clang++
FLAGS=-Wall -Wextra -Werror -std=c++98

## Var: tester utils

containers=('vector' 'stack' 'map' 'set')
folders=('deepthought' 'log')
namespace=('std' 'ft')

## Utils

printHeader() {
echo -e "$CLR_SCREEN$CYAN\
 _______                                        _                   
(_______)_                            _        (_)                  
 _____ _| |_         ____ ___  ____ _| |_ _____ _ ____  _____  ____ 
|  ___|_   _)       / ___) _ \|  _ (_   _|____ | |  _ \| ___ |/ ___)
| |     | |_ ______( (__| |_| | | | || |_/ ___ | | | | | ____| |    
|_|      \__|_______)____)___/|_| |_| \__)_____|_|_| |_|_____)_|    
                                                                    
$BLUE"Ft_containers tester"
Credits to kaye"$NONE"
$NONE"
}

printUsage() {
echo -e "usage: ./test.sh [${GREEN}agrs${NONE}]
args:	${GREEN}all${NONE}: launch all test
	${GREEN}clean${NONE}: clear deepthought/log directory and file
	${GREEN}containers${NONE}: vector/stack/map/set (diff + log)
Tips: ${PURPLE}Changer the path in test.sh with 'CONTAINERS_FOLDER'${NONE}
Tips2: ${PURPLE}You can use the execute std/ft{containersNames} (after tester launch) to compare one by one${NONE}"
}

createDeepthoughtDirectory() {
	for DL in ${folders[@]}
	do
		if [ ! -d "./$DL" ] ; then
			mkdir $DL
		fi
	done
}

cleanAll() {
	for DL in ${folders[@]}
	do
		if [ -d "./$DL" ] ; then
			rm -rf $DL
		fi
	done

	for EN in ${containers[@]}
	do
		for NS in ${namespace[@]}
		do
			if [ -f "./$NS$EN" ] ; then
				rm $NS$EN
			fi
		done
	done
}

remake() {
	cleanAll
	createDeepthoughtDirectory
}

## Run

clear
cleanAll
printHeader

if [ $# -eq 1 ] && [ $1 = 'all' ] ; then
	containersArray=('vector' 'stack' 'map' 'set')

else
	if [ $# -lt 1 ] ; then
		printUsage
		exit
	fi
	containersArray=($*)
fi

remake

if [ $# -eq 1 ] && [ $1 = 'clean' ] ; then
	cleanAll

	echo -e ""$PURPLE"clean all file"$NONE""
	exit
fi

functionArray=('constructTest' 'iteratorTest' 'emptyTest' 'sizeTest' 'resizeTest' 'elementAccessTest' 'assignTest' 'pbTest' 'insertTest' 'eraseTest' 'swapTest' 'clearTest' 'keyCompTest' 'valueCompTest' 'findTest' 'countTest' 'boundTest' 'equalRangeTest')

for CONT in ${containersArray[@]}
do
	if [ ! -f "./srcs/${CONT}Test.cpp" ] || [ ! -f "$CONTAINERS_FOLDER/$CONT.hpp" ] ; then
		echo -e "${RED}Unknow test file or containers file not exist!${NONE}"
		cleanAll
		exit
	fi

	echo -e "$PURPLE""$CONT""$NONE"

	$CC $FLAGS -I./inc -I$CONTAINERS_FOLDER ./srcs/$CONT"Test.cpp" -D __NS__=std -o std$CONT
	$CC $FLAGS -I./inc -I$CONTAINERS_FOLDER ./srcs/$CONT"Test.cpp" -D __NS__=ft -o ft$CONT

	printf "%-20s  %s | %s |  %s\n" "" "Diff" "  STD  " " FT  "
	for TEST in ${functionArray[@]}
	do
		if [ -d "./log" ] && [ -f "./std$CONT" ] && [ -f "./ft$CONT" ]; then
			stdStart=$(python -c "import time; print(int(time.time() * 1000))")
			./std$CONT $TEST > ./log/std_${CONT}_${TEST}.log
			stdEnd=$(python -c "import time; print(int(time.time() * 1000))")

			stdruntime=$( echo "$stdEnd - $stdStart" | bc -l )
			if [ ! -s "./log/std_${CONT}_${TEST}.log" ] ; then
				rm ./log/std_${CONT}_${TEST}.log
			fi

			ftStart=$(python -c "import time; print(int(time.time() * 1000))")
			./ft$CONT $TEST > ./log/ft_${CONT}_${TEST}.log
			ftEnd=$(python -c "import time; print(int(time.time() * 1000))")

			ftruntime=$( echo "$ftEnd - $ftStart" | bc -l )
			if [ ! -s "./log/ft_${CONT}_${TEST}.log" ] ; then
				rm ./log/ft_${CONT}_${TEST}.log
			fi

			if [ -d "./deepthought" ] && [ -f "./log/std_${CONT}_${TEST}.log" ] && [ -f "./log/ft_${CONT}_${TEST}.log" ] ; then
				diff ./log/std_${CONT}_${TEST}.log ./log/ft_${CONT}_${TEST}.log > ./deepthought/${CONT}_${TEST}.diff

				stdRunTime=$(echo "$stdEnd - $stdStart" | bc -l)
				ftRunTime=$(echo "$ftEnd - $ftStart" | bc -l)
				if [ ! -s "./deepthought/${CONT}_${TEST}.diff" ] ; then
					printf "%-20s: $GREEN%s$NONE | $CYAN[%s]$NONE ms | $CYAN[%s]$NONE ms\n" $TEST "[ok]" $stdRunTime $ftRunTime
					rm ./deepthought/${CONT}_${TEST}.diff

				else
					printf "%-20s: $RED%s$NONE\n" $TEST "[ko]" 
					
				fi
			fi

		else
			echo -e "\033[1;31mlog folder or execute file not found!${NONE}"
			exit
		fi
	done

	if [ $CONT != ${containersArray[@]:(-1)} ] ; then
		echo ""
	fi
done
