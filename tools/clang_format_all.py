import pathlib
import subprocess

exclude = ["../build", "../test/doctest.h"]
extensions = [".cpp", ".hpp", ".h", ".c", ".cc", ".hh", ".cxx", ".hxx"]


def is_excluded(path):
    for e in exclude:
        if path.is_relative_to(e):
            return True
    return False


for path in pathlib.Path("..").rglob("*"):
    if path.is_file() and path.suffix in extensions and not is_excluded(path):
        result = subprocess.Popen(["clang-format", "-i", str(path)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = result.communicate()
        if err:
            print(f"Error formatting {path}:\n{err.decode('utf-8')}")
        else:
            print(f"Formatted {path}")
