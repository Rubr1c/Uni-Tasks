import array
import subprocess
import sys
import tkinter as tk
import time
from typing import List, Tuple

try:
    __import__("tkinter")
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "tkinter"])

def read_file(filename: str) -> Tuple[List[Tuple[int, str, str]], int]:
    moves = []
    disks = set()
    with open(filename, "r") as f:
        for line in f:
            line_split = line.replace("\n", "").split(" ")
            moves.append((int(line_split[2]), line_split[4], line_split[6]))
            disks.add(int(line_split[2]))
    return moves, len(disks)


class TowerOfHanoiGUI:
    def __init__(self, root, moves: List[Tuple[int, str, str]], num_disks: int):
        self.root = root
        self.moves = moves
        self.canvas = tk.Canvas(root, width=600, height=400, bg="white")
        self.canvas.pack()
        
        self.move_count_label = tk.Label(root, text="Move Count: 0", font=("Arial", 14))
        self.move_count_label.pack()
        
        self.move_count = 0

        self.peg_positions = {
            'A': 100,
            'B': 300,
            'C': 500
        }
        self.peg_height = 300
        self.disk_width = 120
        self.disk_height = 20

        self.create_pegs()

        self.disks = {}
        self.pegs = {'A': [], 'B': [], 'C': []}
        self.initialize_disks(num_disks)

    def create_pegs(self) -> None:
        for peg, x in self.peg_positions.items():
            self.canvas.create_line(x, self.peg_height, x, self.peg_height - 200, width=5)
            self.canvas.create_text(x, self.peg_height + 20, text=peg, font=("Arial", 14))

    def initialize_disks(self, num_disks: int) -> None:
        for i in range(num_disks, 0, -1):
            width = self.disk_width - (num_disks - i) * 20
            x_start = self.peg_positions['A'] - width // 2
            x_end = self.peg_positions['A'] + width // 2
            y = self.peg_height - ((num_disks - i + 1) * self.disk_height)

            disk = self.canvas.create_rectangle(x_start, y, x_end, y + self.disk_height, fill="blue", outline="black")

            self.disks[i] = disk
            self.pegs['A'].append(i)

    def move_disk(self, disk: int, from_peg: str, to_peg: str) -> None:
        self.pegs[from_peg].remove(disk)
        
        self.move_count += 1
        self.move_count_label.config(text=f"Move Count: {self.move_count}")

        x_start, y_start, x_end, _ = self.canvas.coords(self.disks[disk])
        disk_width = x_end - x_start

        new_x_start = self.peg_positions[to_peg] - disk_width // 2
        new_y = self.peg_height - len(self.pegs[to_peg]) * self.disk_height - self.disk_height

        dx = (new_x_start - x_start) / 10
        dy = (new_y - y_start) / 10
        for _ in range(10):
            self.canvas.move(self.disks[disk], dx, dy)
            self.root.update()
            time.sleep(0.05)

        self.pegs[to_peg].append(disk)

        time.sleep(0.5)

    def play_moves(self) -> None:
        for move in self.moves:
            disk, from_peg, to_peg = move
            self.move_disk(disk, from_peg, to_peg)

if __name__ == "__main__":
    moves, num_disks = read_file("output.txt")
    root = tk.Tk()
    root.title("Tower of Hanoi")
    app = TowerOfHanoiGUI(root, moves, num_disks)
    app.play_moves()
    root.mainloop()
