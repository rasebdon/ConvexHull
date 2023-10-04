import numpy as np
import pandas as pd
from os import listdir
from os.path import isfile, join

def print_results(path):
    data = pd.read_csv(path)

    print(f"Algo={data.iloc[0].iloc[0]}")
    print(f"N={data.iloc[0].iloc[1]}")
    print(f"Mean {data.loc[:, 'ms'].mean() / 1000}".replace(".", ","))
    print(f"Max {data.loc[:, 'ms'].max() / 1000}".replace(".", ","))
    print(f"Min {data.loc[:, 'ms'].min() / 1000}".replace(".", ","))
    print("----------------------------------------------")

dirName = "./line"
files = [f for f in listdir(dirName) if isfile(join(dirName, f))]

for file in files:
    print_results(f"{dirName}/{file}")
