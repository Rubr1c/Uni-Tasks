import subprocess
import sys

def install(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

required_packages = ["matplotlib", "numpy"]

for package in required_packages:
    try:
        __import__(package)
    except ImportError:
        print(f"{package} not found. Installing...")
        install(package)
        
import matplotlib.pyplot as plt
import numpy as np

matrix = []
moves = []

foundPath = False

with open("maze_output.txt", "r") as f:
    for line in f:
        if line == "Path: \n":
            foundPath = True
            continue
        
        if not foundPath:
            matrix.append(line.split())
            continue
    
        for move in line.split(','):
            moves.append(tuple(move.strip().split(' ')))
        
        
matrix = np.array(matrix)

matrix = matrix.astype(int)


plt.figure(figsize=(8, 8))
ax = plt.gca()


from matplotlib import colors
cmap = colors.ListedColormap(['black', 'white', 'red', 'green', 'yellow'])
norm = colors.BoundaryNorm([0, 1, 2, 3, 4, 5], cmap.N)


plt.imshow(matrix, cmap=cmap, norm=norm, interpolation='none')
ax.axis('off')
plt.ion()  
plt.show()
plt.pause(0.1)  

# Color the path with delay
for i, move in enumerate(moves):
    row, col = int(move[0]), int(move[1])
    # Use yellow (4) for the path
    matrix[row, col] = 4
    plt.imshow(matrix, cmap=cmap, norm=norm, interpolation='none')
    plt.draw()
    plt.pause(0.5)  # Add delay between each step

input("Press Enter to close the window...")
