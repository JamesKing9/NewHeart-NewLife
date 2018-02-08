#!/usr/bin/python
# -*-coding: UTF-8-*-
'''
需求：
'''

def palin(n):
    next = 0
    if n <= 1:
        next = input()
        print
        print next
    else:
        next = input()
        palin(n-1)
        print next
        i = 5
        palin(i)
        print
