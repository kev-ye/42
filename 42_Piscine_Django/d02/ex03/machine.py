import random
from beverages import HotBeverage


class CoffeeMachine:
    def __init__(self):
        self.drinks_served = 0
        self.is_broken = False

    class EmptyCup(HotBeverage):
        def __init__(self):
            super().__init__()
            self.name = "empty cup"
            self.price = 0.90

        def description(self):
            return "An empty cup?! Gimme my money back!"

    class BrokenMachineException(Exception):
        def __init__(self):
            super().__init__("This coffee machine has to be repaired.")

    def repair(self):
        self.is_broken = False
        self.drinks_served = 0

    def serve(self, beverage_class):
        if self.is_broken:
            raise self.BrokenMachineException()

        self.drinks_served += 1
        if self.drinks_served > 10:
            self.is_broken = True
            raise self.BrokenMachineException()

        if random.random() < 0.5:
            return beverage_class()
        return self.EmptyCup()


if __name__ == '__main__':
    from beverages import Coffee, Tea, Chocolate, Cappuccino

    machine = CoffeeMachine()
    beverages = [Coffee, Tea, Chocolate, Cappuccino]

    print("=== First test cycle ===")
    try:
        for i in range(12):
            beverage = machine.serve(random.choice(beverages))
            print(f'{i + 1}: {beverage}')
            print()
    except CoffeeMachine.BrokenMachineException as e:
        print(f"Machine broke: {e}")
        print()

    print("=== Repairing machine ===")
    machine.repair()
    print()

    print("=== Second test cycle ===")
    try:
        for i in range(12):
            beverage = machine.serve(random.choice(beverages))
            print(f'{i + 1}: {beverage}')
            print()
    except CoffeeMachine.BrokenMachineException as e:
        print(f"Machine broke: {e}")
