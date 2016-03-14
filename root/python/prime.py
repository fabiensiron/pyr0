#!/bin/env python

def is_prime(n):
    if n < 2: return False
    for i in range(3, n):
        if n % i == 0:
            return False
    return True

def main():
    for i in range(0,100):
        if is_prime(i):
            print(i)

if __name__ == '__main__':
    main()
