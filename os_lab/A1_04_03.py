#!/usr/bin/python3

"""
"" Section : A1
"" Team No: 4
"" Name : Aritra Sarkar; Roll no:002311001048
"" Name : Anish Das; Roll no: 00231101009 
"" Name : Dripta Patra; Roll no  : 002311001006
"" 
"" Emails: aritra sarkar2004nov@gmail.com, rkmvhs1344@gmail.com, patradripta@gmail.com
"" 
"" Usage: python3 script.py <dimension> <workers> <range_limit> <display_flag>
""
"" dimension: Size of square matrices (N x N)
"" workers: Number of parallel worker processes
"" range_limit: Maximum value for random matrix elements
"" display_flag: 1 to show matrices, 0 to hide them
""
"" Performs parallel matrix multiplication using multiprocessing
""
"" Sample Input/Output Sets:
"" Input:  python3 script.py 100 4 50 1
"" Output: Displays two 3000x3000 matrices and their product with timing
""                 
"" Input Details: Two randomly generated square matrices with elements in range [0, range_limit)
"" 
"" Output Details: Execution time and optionally the input matrices and result matrix
"" 
"" Time Taken ::: Tested on quad-core system with 3000x3000 matrices, ~3.2 seconds
"" 
"" CPU Utilization Commands:
"" 
"" # Monitor CPU usage during execution:
"" mpstat 1 10    # Shows CPU stats every 1 second for 10 intervals
"" sar -u 1 10    # Shows CPU utilization every 1 second for 10 intervals
"" 
"" # output
"" python3 A1_04_03.py 3000 4 1000 0
"" Time : 17.918602 seconds
"" mpstat 1 20
""Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	14/08/25 	_x86_64_	(12 CPU)
""
""12:59:48 PM IST  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
""12:59:49 PM IST  all   33.58    0.00    0.00    0.17    0.00    0.17    0.00    0.00    0.00   66.08
""12:59:50 PM IST  all   33.99    0.00    0.82    0.00    0.00    0.08    0.00    0.00    0.00   65.11
""12:59:51 PM IST  all   33.28    0.00    1.07    0.08    0.00    0.25    0.00    0.00    0.00   65.32
""12:59:52 PM IST  all   33.39    0.00    0.08    0.00    0.00    0.00    0.00    0.00    0.00   66.53
""12:59:53 PM IST  all   33.44    0.00    0.00    0.00    0.00    0.17    0.00    0.00    0.00   66.39
""12:59:54 PM IST  all   33.11    0.00    0.08    0.00    0.00    0.42    0.00    0.00    0.00   66.39
""12:59:55 PM IST  all   31.74    0.00    0.00    0.00    0.00    1.84    0.00    0.00    0.00   66.42
""12:59:56 PM IST  all   33.47    0.08    0.08    0.08    0.00    0.08    0.00    0.00    0.00   66.19
""12:59:57 PM IST  all   33.39    3.50    0.08    0.00    0.00    0.50    0.00    0.00    0.00   62.53
""12:59:58 PM IST  all   33.42    0.00    0.00    0.00    0.00    0.17    0.00    0.00    0.00   66.42
""12:59:59 PM IST  all    9.73    0.00    0.84    0.08    0.00    0.17    0.00    0.00    0.00   89.18
""01:00:00 PM IST  all    0.34    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.66
""01:00:01 PM IST  all    0.08    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.92
""01:00:02 PM IST  all    0.34    0.00    0.17    0.00    0.00    0.08    0.00    0.00    0.00   99.41
""01:00:03 PM IST  all    0.25    0.00    0.08    0.08    0.00    0.00    0.00    0.00    0.00   99.58
""01:00:04 PM IST  all    0.25    0.00    0.17    0.08    0.00    0.00    0.00    0.00    0.00   99.50
""01:00:05 PM IST  all    0.25    0.00    0.17    0.08    0.00    0.00    0.00    0.00    0.00   99.49
""01:00:06 PM IST  all    0.08    0.00    0.08    0.00    0.00    0.08    0.00    0.00    0.00   99.75
""01:00:07 PM IST  all    0.25    0.00    0.17    0.00    0.00    0.00    0.00    0.00    0.00   99.58
""01:00:08 PM IST  all    0.08    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.92
""
"""

import sys
import time
import numpy as np
from multiprocessing import Pool

def process_seg(params):
    """Process a segment of rows from first matrix with second matrix."""
    segment_data, second_matrix = params
    return np.dot(segment_data, second_matrix)

if __name__ == "__main__":
    # -------- Validate input parameters --------
    if len(sys.argv) != 5:
        print(f"Usage: {sys.argv[0]} <dimension> <workers> <range_limit> <display_flag>")
        sys.exit(1)
    
    dimension = int(sys.argv[1])
    workers = int(sys.argv[2])
    range_limit = int(sys.argv[3])
    display_flag = int(sys.argv[4])
    
    # -------- Generate random matrices (not timed) --------
    first_matrix = np.random.randint(0, range_limit, (dimension, dimension), dtype=np.uint32)
    second_matrix = np.random.randint(0, range_limit, (dimension, dimension), dtype=np.uint32)
    
    if display_flag:
        print("1st Matrix:")
        print(first_matrix)
        print("2nd Matrix:")
        print(second_matrix)
    
    # -------- Begin performance measurement --------
    begin_time = time.perf_counter()
    
    # Divide first matrix into segments for parallel processing
    segment_size = dimension // workers
    segments = [first_matrix[i*segment_size : (i+1)*segment_size] for i in range(workers)]
    
    with Pool(processes=workers) as pool:
        segment_results = pool.map(process_seg, [(segment, second_matrix) for segment in segments])
    
    # Merge segments into final output
    output_matrix = np.vstack(segment_results)
    
    # -------- End performance measurement --------
    finishT = time.perf_counter()
    totalT = finishT - begin_time
    
    # -------- Display results --------
    print(f"Time : {totalT:.6f} seconds")
    
    if display_flag:
        print("Output Matrix:")
        print(output_matrix)
