import statistics


class MathStat(object):
    def __init__(self, *args):
        self.dat = args

    def variance(self):
        return statistics.variance(self.dat)

    def mean(self):
        return statistics.mean(self.dat)

    def all(self):
        res = (self.mean(), self.variance())
        return res