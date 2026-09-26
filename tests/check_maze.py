"""Check maze properties independently from the C implementation."""
from collections import deque
from pathlib import Path
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def check_maze(executable, width, height, seed):
    args = [str(executable), str(width), str(height), str(seed)]
    plain = subprocess.check_output(args, text=True)
    assert plain == subprocess.check_output(args, text=True), "Seed is not reproducible"
    solved = subprocess.check_output(args + ["--solve"], text=True)
    grid = plain.splitlines()[2:2 + 2 * height + 1]
    solution = solved.splitlines()[2:2 + 2 * height + 1]
    assert len(grid) == 2 * height + 1
    assert all(len(row) == 2 * width + 1 for row in grid)
    assert set(grid[0] + grid[-1]) == {"#"}
    assert all(row[0] == row[-1] == "#" for row in grid)
    open_cells = {(x, y) for y, row in enumerate(grid)
                  for x, cell in enumerate(row) if cell != "#"}
    assert all((2 * x + 1, 2 * y + 1) in open_cells
               for y in range(height) for x in range(width))
    start = (1, 1)
    treasures = [(x, y) for x, y in open_cells if grid[y][x] == "T"]
    assert grid[1][1] == "S" and len(treasures) == 1
    treasure = treasures[0]
    parents, distances = {start: None}, {start: 0}
    queue = deque([start])
    edges = 0
    while queue:
        x, y = queue.popleft()
        for neighbor in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
            if neighbor not in open_cells:
                continue
            edges += 1
            if neighbor not in parents:
                parents[neighbor] = (x, y)
                distances[neighbor] = distances[(x, y)] + 1
                queue.append(neighbor)
    assert len(parents) == len(open_cells), "Disconnected maze"
    assert edges // 2 == len(open_cells) - 1, "Maze contains cycles"
    assert distances[treasure] == max(distances.values())
    reported = int(re.search(r"Treasure is (\d+) room steps", plain)[1])
    assert reported * 2 == distances[treasure]
    path, current = set(), treasure
    while current is not None:
        path.add(current)
        current = parents[current]
    for y, row in enumerate(solution):
        for x, cell in enumerate(row):
            expected = "." if (x, y) in path - {start, treasure} else grid[y][x]
            assert cell == expected, "Incorrect solution overlay"


def main():
    with tempfile.TemporaryDirectory(prefix="maze-check-") as directory:
        executable = Path(directory) / "maze.exe"
        subprocess.run(["gcc", "-std=c11", "-Wall", "-Wextra", "-Wpedantic",
                        "-Werror", str(ROOT / "maze_cartographer.c"),
                        "-o", str(executable)], check=True)
        for width, height in [(2, 2), (2, 30), (30, 2), (12, 8), (30, 30)]:
            for seed in [0, 1, 42, 4294967295]:
                check_maze(executable, width, height, seed)
        invalid = [["1", "8", "0"], ["31", "8", "0"], ["12", "0", "0"],
                   ["12", "31", "0"], ["12", "8", "4294967296"],
                   ["12", "8", "-1"], ["12", "8", "1x"],
                   ["", "8", "0"], ["12"], ["12", "8"],
                   ["12", "8", "0", "--unknown"],
                   ["12", "8", "0", "--solve", "extra"],
                   ["9" * 1000, "8", "0"]]
        for args in invalid:
            result = subprocess.run([str(executable)] + args, capture_output=True)
            assert result.returncode != 0 and b"Usage:" in result.stderr
        subprocess.run([str(executable), "--help"], check=True, capture_output=True)
        subprocess.run([str(executable)], check=True, capture_output=True)
    print("Passed: 20 maze cases, 13 invalid inputs, help, and default invocation.")


if __name__ == "__main__":
    main()
