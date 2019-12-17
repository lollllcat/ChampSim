import glob, os
from multiprocessing import Pool
import pandas as pd
import math

lst = pd.read_csv('instruction_count.csv')
lst = lst.values.tolist()

def f(x):
    if math.isnan(x[2]):
        return
    else:
        os.system("sh run_tracer.sh " + x[0] + " " + str(int(x[1])) + " " + str(int(x[3])))
cpu_num = 12

p = Pool(cpu_num)

p.map(f, lst)
