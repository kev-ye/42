import sys


def handle_args(args):
    return True if len(args) == 2 else False


def capital_city(args):
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

        try:
            print(capital_cities[states[args[1]]])
        except KeyError:
            print("Unknown state")


if __name__ == '__main__':
    capital_city(sys.argv)
