import pathlib
import subprocess

clang_format = "clang-format"
exclude = ["../build", "../test/doctest.h"]
extensions = [".cpp", ".hpp", ".h", ".c", ".cc", ".hh", ".cxx", ".hxx"]


def is_excluded(path):
    for e in exclude:
        if path.is_relative_to(e):
            return True
    return False


for path in pathlib.Path("..").rglob("*"):
    if path.is_file() and path.suffix in extensions and not is_excluded(path):
        ouput = subprocess.check_output(
            [clang_format, "-i", str(path)],
            stderr=subprocess.PIPE,
        )
        if ouput:
            print(f"Error formatting {path}:\n{ouput.decode()}")
        else:
            print(f"Formatted {path}")
