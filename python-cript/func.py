# -*- coding: utf-8 -*-
"""
Created on Thu Apr  9 01:47:19 2020

@author: man
"""
import statistics

a = 11
b = 22
c = 33


def get_value(x):
    return x


def mean(*args):
    # print(dat + 1000)
    # return statistics.mean(dat)
    return statistics.median(args)

# print(mean((3.4, 4.1, 5.5, 6.3, 7.4 )))