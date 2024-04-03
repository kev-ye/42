import sys


def handle_args(args):
    return True if len(args) == 2 else False


def state(args):
    if handle_args(args):
        states = {
            "Oregon" : "OR",
            "Alabama" : "AL",
            "New Jersey": "NJ",
            "Colorado" : "CO"
        }
        capital_cities = {
            "OR": "Salem",
            "AL": "Montgomery",
            "NJ": "Trenton",
            "CO": "Denver"
        }

        mapped = dict(zip(capital_cities.values(), states.keys()))
        try:
            print(mapped[args[1]])
        except KeyError:
            print("Unknown capital city")


if __name__ == '__main__':
    state(sys.argv)
