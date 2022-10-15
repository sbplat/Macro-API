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
        print(path)
        result = subprocess.run(["clang-format", "-i", str(path)])
        if result.returncode != 0:
            print(f"clang-format failed on {path} with return code {result.returncode}")
