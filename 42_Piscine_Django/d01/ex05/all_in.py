import sys


def handle_args(args):
    return True if len(args) == 2 else False


def all_in(args):
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

        mapped_c_s = dict(zip(capital_cities.values(), states.keys()))
        mapped_s_c = dict(zip(states.keys(), capital_cities.values()))

        for data in [new_d for d in args[1].split(',') if (new_d := d.strip())]:
            title = data.title()
            if title in mapped_c_s.keys():
                print(f"{title} is the capital of {mapped_c_s[title]}")
            elif title in mapped_s_c.keys():
                print(f"{mapped_s_c[title]} is the capital of {title}")
            else:
                print(f"{data} is neither a capital city nor a state")


if __name__ == '__main__':
    all_in(sys.argv)
