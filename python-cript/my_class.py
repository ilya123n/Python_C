# -*- coding: utf-8 -*-
"""
Created on Wed Apr 22 13:47:39 2020

@author: man
"""
import statistics


class MathStat(object):
    def __init__(self, dat):
        self.dat = dat
        pass

    def mean(self):
        return statistics.mean(self.dat)

    def variance(self):
        return statistics.variance(self.dat)

    def all(self):
        return [self.mean(), self.variance()]


#def square(number):
 #   return number * number


#def generarray(number):
 #   return [i for i in range(0, number)]
