#!/bin/env python3

import argparse
import os
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

class batch:
    def __init__(self, batch_size, parameter):
        self.batch_size = batch_size
        self.parameter = parameter
        self.data = []

    def add_data(self, data):
        self.data.append(data)
    
    
    def average(self):
        if not self.data:
            return 0
        
        s=0
        for d in self.data:
            if d > 0:
                s += d
        assert s >= 0
        s=s/self.batch_size
        
        return s


def parse_file(f):
    batch_size=int(f.readline().split(':')[1].strip())
    batch_parameter=int(f.readline().split(':')[1].strip())
    gen_function=f.readline().split(':')[1].strip()

    b = batch(batch_size, batch_parameter)
    l = f.readline().strip()
    while l:
        b.add_data(float(l))
        l = f.readline().strip()
    
    return b, batch_size, batch_parameter, gen_function

def nlogn_func(n, a, b):
    return a * n * np.log(n) + b

def linear_func(n, a, b):
    return a * n + b

def square_func(n, a, b):
    return a * n**2 + b

def logn_func(n, a, b):
    return a * np.log(n) + b

def read_data(dir, alg):
    files = os.listdir(dir)
    files.sort()
    if not files:
        print("No files found in the directory.")
        return
    
    params = []
    times = []

    for file in files:
        file_path = os.path.join(dir, file)
        if not os.path.isfile(file_path) or not file.endswith('.txt') or not file.startswith(f'log-{alg}-'):
            continue
        
        with open(file_path, 'r') as f:
            b, batch_size, batch_parameter, gen_function = parse_file(f)
            params.append(batch_parameter)
            times.append(b.average())
    
    print(params)
    print(times)
    return params, times

def plot_data(params, times, name=None, interp:int=0, interpf:str=None):
    if interp>0:
        x = np.array(params)
        y = np.array(times)

        if interpf == 'nlogn':
            func = nlogn_func
        elif interpf == 'lin':
            func = linear_func
        elif interpf == 'sqr':
            func = square_func
        elif interpf == 'log':
            func = logn_func
        else:
            print(f"Unknown interpolation function: {interpf}")
            return

        popt, _ = curve_fit(func, x, y)
        x_fit = np.geomspace(min(x), max(x), interp)
        y_fit = func(x_fit, *popt)

        plt.plot(x_fit, y_fit, marker='x', label=f'Fit: {interpf}')
    
    plt.plot(params, times, label=name)


def main():
    parser = argparse.ArgumentParser(description='Process a data file.')
    parser.add_argument('directory', type=str, help='Path to the data file')
    parser.add_argument('-i', '--interpolate', type=int, default=0, help='Interpolate the data with n points')
    parser.add_argument('-if', '--interpolate_function', type=str, default='nlogn', help='Interpolation function to use [default nlog(n)]')
    parser.add_argument('-ls', '--logscale', action='store_true', help='Use log scale for the x-axis')
    parser.add_argument('--cmp', type=str, default='', help='Se log di vari algoritmi sono presenti seleziona quali parsare (in base al nome del logfile), se piu di uno viene specificato verranno messi sullo stesso grarfico in comparison\nFormato: --cmp insertionSort,mergeSort,quickSort')
    parser.add_argument('--title', type=str, default='Parameter vs Average Time', help='Titolo del grafico')
    args = parser.parse_args()

    if args.logscale:
        plt.xscale('log')
        plt.yscale('log')
    else:
        plt.xscale('linear')
        plt.yscale('linear')
    

    if not os.path.exists(args.directory):
        print(f"Dir {args.directory} does not exist.")
        return

    if len(args.cmp)==0:
        params, times = read_data(args.directory, args.cmp)
        plot_data(params, times)
    else:
        for alg in args.cmp.split(','):
            params,times=read_data(args.directory, alg)
            plot_data(params, times, name=alg)


    plt.legend()
    plt.xlabel('Array Length')
    plt.ylabel('Average Time')
    plt.title(args.title)
    plt.grid(True)
    plt.show()
if __name__ == "__main__":
    main()
