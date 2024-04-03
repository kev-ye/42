# 42 projet : Push_swap

## Index

* [Presentation](#Presentation)
* [To_do_list](#To_do_list)
* [How_to_run](#How_to_run)
* [Method_and_work_time](#Method_and_work_time)
* [Documentation](#Documentation)
* [Notes](#Notes)

## Presentation

This project will make you sort data on a stack, with a limited set of instructions, using
the lowest possible number of actions. To succeed you’ll have to manipulate various types of algorithms and choose the one (of many) most appropriate solution for an optimized data sorting.

## To_do_list

- [x] parser
- [x] checker
- [x] push_swap
- [x] norme

## How_to_run

Compilation :  

	make

Tester python (by Besellem) :  
[@Besellem_github](https://github.com/besellem)

	python3 py/check_range.py [min] [max] : Various random sorts within the test range
	python3 py/generate.py [min] [max] : generate random range value

Checker :  

	./checker [value] : simple run  
	./checker -v [value] : run with debug mode  
	./checker -b [valuer] : run with color bar mode  
	use ctrl + d to end the command (EOF)

push_swap :  

	./push_swap [value] : simple run  
	./push_swap -v [value] : run with debug mode  
	./push_swap -b [value] : run with color bar mode

## Method_and_work_time

	Sorting method used: Quick sort
	Work time : about a week

## Documentation

[Sorting_algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm)

## Notes

	✅ 100