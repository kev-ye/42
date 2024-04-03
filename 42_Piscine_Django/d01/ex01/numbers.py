def show_file_number():
    with open('numbers.txt', 'r') as f:
        numbers = f.read().split(',')
        for number in numbers:
            print(number)


if __name__ == '__main__':
    show_file_number()
