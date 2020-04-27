# -*- coding: utf-8 -*-

import math


def poww(number):
    return math.pow(number, 2)


def array(number):
    # генерация списка
    data = [i for i in range(0, number)]
    return tuple(data)
