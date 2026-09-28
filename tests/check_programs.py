"""Compile every example and check numeric limits and input-ending behavior."""

from pathlib import Path
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parents[1]
CASES = [
    ("temperature_converter", "100 C\n", 0,
     ["Celsius: 100.00 C", "Fahrenheit: 212.00 F", "Kelvin: 373.15 K"]),
    ("temperature_converter", "32 f\n", 0,
     ["Celsius: 0.00 C", "Fahrenheit: 32.00 F", "Kelvin: 273.15 K"]),
    ("temperature_converter", "0 K\n", 0,
     ["Celsius: -273.15 C", "Fahrenheit: -459.67 F", "Kelvin: 0.00 K"]),
    ("temperature_converter", "-273.15 C\n", 0, ["Kelvin: 0.00 K"]),
    ("temperature_converter", "-459.67 F\n", 0, ["Kelvin: 0.00 K"]),
    ("temperature_converter", "-274 C\n", 1, ["below absolute zero"]),
    ("temperature_converter", "-460 F\n", 1, ["below absolute zero"]),
    ("temperature_converter", "-1 K\n", 1, ["below absolute zero"]),
    ("temperature_converter", "nan C\n", 1, ["finite number"]),
    ("temperature_converter", "inf K\n", 1, ["finite number"]),
    ("temperature_converter", "hello\n", 1, ["finite number"]),
    ("temperature_converter", "25\n", 1, ["Unknown unit"]),
    ("temperature_converter", "25 X\n", 1, ["Unknown unit"]),
    ("temperature_converter", "25 C extra\n", 1, ["Unexpected text"]),
    ("temperature_converter", "1.7e308 C\n", 1, ["outside the supported"]),
    ("temperature_converter", "", 1, ["complete temperature"]),
    ("temperature_converter", "1" * 200 + " C\n", 1, ["complete temperature"]),
    ("temperature_converter", "  25 c  ", 0, ["Kelvin: 298.15 K"]),
    ("pointer_array_stats", "4\n3 1 4 2\n", 0,
     ["Average: 2.50", "Median: 2.50", "descending order: 4 3 2 1"]),
    ("pointer_array_stats", "3\n9 -2 4\n", 0,
     ["Minimum: -2", "Maximum: 9", "Median: 4.00"]),
    ("pointer_array_stats", "2\n2147483647 2147483647\n", 0,
     ["Average: 2147483647.00", "Median: 2147483647.00"]),
    ("pointer_array_stats", "2\n-2147483648 -2147483648\n", 0,
     ["Average: -2147483648.00", "Median: -2147483648.00"]),
    ("pointer_array_stats", "1\n7\n", 0, ["Median: 7.00"]),
    ("pointer_array_stats", "0\n", 1, ["positive number"]),
    ("pointer_array_stats", "2\n1 nope\n", 1, ["Invalid input"]),
    ("stm", "1\nAda\nLovelace\n1\n", 1, ["Input ended"]),
    ("stm", "1\nAda\nLovelace\n1\ninvalid", 1, ["Input ended"]),
    ("stm", "1\nAda\nLovelace\n1\n101", 1, ["Input ended"]),
    ("stm", "1\nAda\nLovelace\n1\ninvalid\n90\n80\n70\n", 0,
     ["Ada Lovelace", "80.00%"]),
    ("calculator", "6\n2\n/\n", 0, ["Result: 3.00"]),
    ("calculator", "6\n0\n/\n", 1, ["Division by zero"]),
    ("calculator", "nan\n", 1, ["Invalid number"]),
    ("calculator", "inf\n", 1, ["Invalid number"]),
    ("calculator", "1e308\n1e308\n*\n", 1, ["outside the supported"]),
]


def main():
    with tempfile.TemporaryDirectory(prefix="c-examples-") as directory:
        build = Path(directory)
        sources = sorted(ROOT.glob("*.c"))
        for source in sources:
            subprocess.run(
                ["gcc", "-std=c11", "-Wall", "-Wextra", "-Wpedantic",
                 "-Werror", str(source), "-o", str(build / (source.stem + ".exe"))],
                check=True, capture_output=True, text=True,
            )
        for program, data, expected_status, expected_text in CASES:
            result = subprocess.run(
                [str(build / (program + ".exe"))], input=data,
                capture_output=True, text=True, timeout=5,
            )
            if result.returncode != expected_status or any(
                text not in result.stdout for text in expected_text
            ):
                raise AssertionError(
                    f"{program} failed for {data!r}: "
                    f"exit={result.returncode}, output={result.stdout!r}, "
                    f"stderr={result.stderr!r}"
                )
        print(f"Compiled {len(sources)} programs; passed {len(CASES)} regression cases.")


if __name__ == "__main__":
    main()
