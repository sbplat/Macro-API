import re

extract_enum_names_re = re.compile(
    "enum Key {\n"
    "    // clang-format off\n"
    "((?:    [A-Z0-9_ ,]+\n)+)"
    "    // clang-format on\n"
    "};"
)

keyboard_h_data = ""
with open("../include/macro/keyboard.h", "r") as f:
    keyboard_h_data = f.read()

enum_names = extract_enum_names_re.findall(keyboard_h_data)[0]

values = [
    value
    for value in enum_names.replace("\n", "").replace(" ", "").split(",")
    if len(value) > 0
]

code = """\
#include <macro/keyboard.h>

#include <stdexcept>

namespace Macro {
namespace Keyboard {

std::string GetKeyName(Key key) {
    // clang-format off
    switch (key) {
"""

for i, value in enumerate(values):
    code += f'        case Key::{value}: return "{value}";\n'

code += """\
        default: throw std::runtime_error("Unknown key (GetKeyName): " + std::to_string(key));
    }
    // clang-format on
}

}  // namespace Keyboard
}  // namespace Macro
"""

with open("../src/common/keyboard_key_to_string.cpp", "w") as f:
    f.write(code)
