import pathlib
import subprocess

cmake_format = "cmake-format"
exclude = ["../build"]
names = ["CMakeLists.txt"]


def is_excluded(path):
    for e in exclude:
        if path.is_relative_to(e):
            return True
    return False


for path in pathlib.Path("..").rglob("*"):
    if path.is_file() and path.name in names and not is_excluded(path):
        ouput = subprocess.check_output(
            [cmake_format, "-i", str(path)],
            stderr=subprocess.PIPE,
        )
        if ouput:
            print(f"Error formatting {path}:\n{ouput.decode()}")
        else:
            print(f"Formatted {path}")
