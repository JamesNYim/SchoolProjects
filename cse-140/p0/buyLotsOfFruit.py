#!/usr/bin/env python3

"""
Based off of: http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

To run this script, type:

  python3 buyLotsOfFruit.py

Once you have correctly implemented the buyLotsOfFruit function,
the script should produce the output:

Cost of [('apples', 2.0), ('pears', 3.0), ('limes', 4.0)] is 12.25
"""

FRUIT_PRICES = {
    'apples': 2.00,
    'oranges': 1.50,
    'pears': 1.75,
    'limes': 0.75,
    'strawberries': 1.00
}

def isBuyable(fruitList, fruit):
    for item in fruitList:
        if (fruit == item):
            return True
    return False
    
def weightedPrice(fruitPrices, item, fruitWeight):
    cost = 0.0
    for fruit, price in fruitPrices.items():
        if (fruit == item):
            cost = price * fruitWeight
    
    return cost
        
def buyLotsOfFruit(orderList):
    """
    orderList: List of (fruit, weight) tuples

    Returns cost of order
    """

    # *** Your Code Here ***
    totalCost = 0.0
    for item, weight in orderList:
        if (isBuyable(FRUIT_PRICES, item)): # Item is buyable
            totalCost += weightedPrice(FRUIT_PRICES, item, weight)
        else: # Item is not buyable
            return None
    return totalCost

def main():
    orderList = [
        ('apples', 2.0),
        ('pears', 3.0),
        ('limes', 4.0)
    ]

    print("Cost of %s is %s." % (orderList, buyLotsOfFruit(orderList)))

if __name__ == '__main__':
    main()
