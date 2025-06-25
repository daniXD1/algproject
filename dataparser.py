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

def main():
    parser = argparse.ArgumentParser(description='Process a data file.')
    parser.add_argument('directory', type=str, help='Path to the data file')
    parser.add_argument('-i', '--interpolate', type=int, default=0, help='Interpolate the data with n points')
    parser.add_argument('-if', '--interpolate_function', type=str, default='nlogn', help='Interpolation function to use [default nlog(n)]')
    parser.add_argument('-ls', '--logscale', action='store_true', help='Use log scale for the x-axis')
    args = parser.parse_args()

    if not os.path.exists(args.directory):
        print(f"Dir {args.directory} does not exist.")
        return

    files = os.listdir(args.directory)
    files.sort()
    if not files:
        print("No files found in the directory.")
        return
    
    params = []
    times = []

    for file in files:
        file_path = os.path.join(args.directory, file)
        if not os.path.isfile(file_path) or not file.endswith('.txt'):
            print(f"{file} is not a file.")
            continue
        
        with open(file_path, 'r') as f:
            b, batch_size, batch_parameter, gen_function = parse_file(f)
            params.append(batch_parameter)
            times.append(b.average())
    
    print(params)
    print(times)

    if args.interpolate > 0:
        x = np.array(params)
        y = np.array(times)

        if args.interpolate_function == 'nlogn':
            func = nlogn_func
        elif args.interpolate_function == 'lin':
            func = linear_func
        elif args.interpolate_function == 'sqr':
            func = square_func
        elif args.interpolate_function == 'log':
            func = logn_func
        else:
            print(f"Unknown interpolation function: {args.interpolate_function}")
            return

        popt, _ = curve_fit(func, x, y)
        x_fit = np.geomspace(min(x), max(x), args.interpolate)
        y_fit = func(x_fit, *popt)

        plt.plot(x_fit, y_fit, marker='x', label=f'Fit: {args.interpolate_function}')

    if args.logscale:
        plt.xscale('log')
        plt.yscale('log')
    else:
        plt.xscale('linear')
        plt.yscale('linear')

    plt.plot(params, times, marker='o')
    plt.xlabel('Batch Parameter')
    plt.ylabel('Average Time')
    plt.title('Batch Parameter vs Average Time')
    plt.grid(True)
    plt.show()
if __name__ == "__main__":
    main()