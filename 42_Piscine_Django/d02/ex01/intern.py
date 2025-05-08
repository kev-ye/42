class Intern:
    def __init__(self, name="My name? I'm nobody, an intern, I have no name."):
        self.Name = name

    def __str__(self):
        return self.Name

    class Coffee:
        def __str__(self):
            return "This is the worst coffee you ever tasted."

    def work(self):
        raise Exception("I'm just an intern, I can't do that...")

    def make_coffee(self):
        return self.Coffee()


if __name__ == '__main__':
    no_name_intern = Intern()
    mark = Intern("Mark")

    print(no_name_intern)
    print(mark)

    coffee = mark.make_coffee()
    print(coffee)

    try:
        no_name_intern.work()
    except Exception as e:
        print(e)
