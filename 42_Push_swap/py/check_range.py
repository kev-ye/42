# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    check_range.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 19:05:14 by besellem          #+#    #+#              #
#    Updated: 2021/03/23 16:04:29 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from generate import ft_gen_numbers
import os
import sys
import subprocess


def	print_stats(operations_lst, stats):
	diff = int(sys.argv[2]) - int(sys.argv[1]) + 1
	average = sum(operations_lst) / len(operations_lst)

	print("\n######################################")
	print(f'push_swap has been executed \033[1;32m{stats["iterations_nb"]}\033[0m times:\n')
	print(f'The minimum was:       \033[1;32m{stats["min_op"]}\033[0m')
	print(f'The maximum was:       \033[1;32m{stats["max_op"]}\033[0m')
	print(f'Diff btwn min and max: \033[1;32m{stats["max_op"] - stats["min_op"]}\033[0m')
	print(f'Average:               \033[1;32m{average}\033[0m operations')

	if diff <= 500:
		print("")
		print("With the current average, the test seems ", end="")
		
		if diff <= 3:
			if average > 3:
				print("\033[1;31mKO :(\033[0m")
			else:
				print("\033[1;32mOK\033[0m")
		elif diff <= 5:
			if average > 12:
				print("\033[1;31mKO :(\033[0m")
			else:
				print("\033[1;32mOK\033[0m")
		elif diff <= 100:
			if average > 1500:
				print("\033[1;31mKO :(\033[0m")
			elif average > 1300:
				print("\033[1;32mOK with barem 1\033[0m")
			elif average > 1100:
				print("\033[1;32mOK with barem 2\033[0m")
			elif average > 900:
				print("\033[1;32mOK with barem 3\033[0m")
			elif average > 700:
				print("\033[1;32mOK with barem 4\033[0m")
			else:
				print("\033[1;32mOK with barem 5! Good job!\033[0m")
		else:
			if average > 11500:
				print("\033[1;31mKO :(\033[0m")
			elif average > 10000:
				print("\033[1;32mOK with barem 1\033[0m")
			elif average > 8500:
				print("\033[1;32mOK with barem 2\033[0m")
			elif average > 7000:
				print("\033[1;32mOK with barem 3\033[0m")
			elif average > 5500:
				print("\033[1;32mOK with barem 4\033[0m")
			else:
				print("\033[1;32mOK with barem 5! Good job!\033[0m")


if __name__ == "__main__":

	if len(sys.argv) == 3:
		
		if not os.path.isfile("./push_swap"):
			print("\033[1;31mError:\033[0m push_swap does not exist (create executable first)")
			exit(1)
		if not os.path.isfile("./checker"):
			print("\033[1;31mError:\033[0m checker does not exist (create executable first)")
			exit(1)

		operations_lst = []
		stats = {
			"iterations_nb": 50,
			"min_op":		 -1,
			"max_op":		 0
		}
		for i in range(1, stats["iterations_nb"] + 1):
			
			# Generate a list of numbers based on the arguments
			numbers_generated_lst = ft_gen_numbers(int(sys.argv[1]), int(sys.argv[2]))
			numbers_generated_str = ' '.join(map(str, numbers_generated_lst))
			
			# Get push_swap's number of operations for the current list of numbers
			push_swap_exec = subprocess.Popen(
				[f'./push_swap {numbers_generated_str} | wc -l | tr -d " "'],
				shell=True,
				stdout=subprocess.PIPE,
				stderr=subprocess.STDOUT
			)
			push_swap_stdout, push_swap_stderr = push_swap_exec.communicate()
			push_swap_operations_nb = int(push_swap_stdout.decode())

			# Append the list with the last result
			operations_lst.append(push_swap_operations_nb)

			# Print current state
			print(f'\033[1;36m# {i:2}\033[0m => {push_swap_operations_nb}')
			# print(numbers_generated_str)
			os.system(f"./push_swap {numbers_generated_str} | ./checker {numbers_generated_str}")
			
			# 2 4 1 3 5
			# 2 5 1 4 3
			
			# Replace stats if necessary
			if stats["max_op"] < max(operations_lst):
				stats["max_op"] = max(operations_lst)
			if stats["min_op"] == -1 or stats["min_op"] > min(operations_lst):
				stats["min_op"] = min(operations_lst)
		
		print_stats(operations_lst, stats)
		
	else:
		print("\033[1;31mError:\033[0m args")
