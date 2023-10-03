import numpy as np
import pandas as pd


def print_results(path):
    data = pd.read_csv(path)

    print(f"Algo={data.iloc[0].iloc[0]}")
    print(f"N={data.iloc[0].iloc[1]}")
    print(f"Mean {data.loc[:, 'ms'].mean()}")
    print(f"Min {data.loc[:, 'ms'].min()}")
    print(f"Max {data.loc[:, 'ms'].max()}")


print_results("./results_qh_1000.csv")
print_results("./results_qh_10000.csv")
print_results("./results_qh_100000.csv")
print_results("./results_qh_250000.csv")
print_results("./results_qh_500000.csv")
print_results("./results_qh_1000000.csv")
print_results("./results_qh_10000000.csv")