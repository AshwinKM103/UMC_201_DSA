import ctypes
import time
from typing import List

# Load the shared library
lib = ctypes.CDLL('./liblargeinteger.so')
lib.count_pairs_from_file.argtypes = [ctypes.c_char_p]
lib.count_pairs_from_file.restype = ctypes.c_int

def count_pairs(data: List[str], target: str) -> int:
    """Count the number of pairs with difference equal to target (Python implementation)."""
    result = 0
    target_int = int(target)
    data_int = [int(x) for x in data]

    for i in range(len(data_int) - 1):
        for j in range(i + 1, len(data_int)):
            if data_int[i] - data_int[j] == target_int:
                result += 1

    return result

def read_file(filename):
    """Read the target and data from the file."""
    with open(filename) as file:
        target = file.readline().strip()
        n = int(file.readline())
        data = [file.readline().strip() for _ in range(n)]
    return data, target

def count_pairs_file(filename: str) -> int:
    """Count pairs using both C++ and Python implementations and compare timings."""
    # Convert filename to ctypes
    filename_c = filename.encode('utf-8')

    # Measure time for C++ implementation
    start_c = time.time()
    result = lib.count_pairs_from_file(filename_c)
    end_c = time.time()

    # Read data and target from file
    data, target = read_file(filename)

    # Measure time for Python implementation
    start_python = time.time()
    res = count_pairs(data, target)
    end_python = time.time()

    # Print results
    print("\nC++ implementation time:", end_c - start_c)
    print("Result from C++:", result, '\n\n')

    print("Python implementation time:", end_python - start_python)
    print("Result from Python:", res, '\n\n')

    print("T_python - T_c++ =", (end_python - start_python) - (end_c - start_c))

    return result


