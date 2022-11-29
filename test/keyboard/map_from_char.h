#include <map>
#include <string>

TEST_CASE("[keyboard] map from char") {
    INFO("Lowercase");
    for (char c = 'a'; c <= 'z'; ++c) {
        INFO("Char: ", c);
        Macro::Keyboard::Combo combo = Macro::Keyboard::MapFromChar(c);
        CHECK_EQ(Macro::Keyboard::GetKeyName(combo.key), std::string(1, c - 'a' + 'A'));
        CHECK_EQ(combo.shift, false);
        CHECK_EQ(combo.ctrl, false);
        CHECK_EQ(combo.alt, false);
    }

    INFO("Uppercase");
    for (char c = 'A'; c <= 'Z'; ++c) {
        INFO("Char: ", c);
        Macro::Keyboard::Combo combo = Macro::Keyboard::MapFromChar(c);
        CHECK_EQ(Macro::Keyboard::GetKeyName(combo.key), std::string(1, c));
        CHECK_EQ(combo.shift, true);
        CHECK_EQ(combo.ctrl, false);
        CHECK_EQ(combo.alt, false);
    }

    INFO("Numbers");
    for (char c = '0'; c <= '9'; ++c) {
        INFO("Char: ", c);
        Macro::Keyboard::Combo combo = Macro::Keyboard::MapFromChar(c);
        CHECK_EQ(combo.key - Macro::Keyboard::Key::ZERO, c - '0');
        CHECK_EQ(combo.shift, false);
        CHECK_EQ(combo.ctrl, false);
        CHECK_EQ(combo.alt, false);
    }

    INFO("Symbols (unshifted)");
    std::map<char, Macro::Keyboard::Key> unshifted_symbols = {
        // clang-format off
        {';', Macro::Keyboard::Key::COLON},
        {'=', Macro::Keyboard::Key::PLUS},
        {',', Macro::Keyboard::Key::COMMA},
        {'-', Macro::Keyboard::Key::MINUS},
        {'.', Macro::Keyboard::Key::PERIOD},
        {'/', Macro::Keyboard::Key::SLASH},
        {'`', Macro::Keyboard::Key::TILDE},
        {'[', Macro::Keyboard::Key::LEFT_BRACKET},
        {'\\', Macro::Keyboard::Key::BACKSLASH},
        {']', Macro::Keyboard::Key::RIGHT_BRACKET},
        {'\'', Macro::Keyboard::Key::QUOTE},
        // clang-format on
    };
    for (auto &pair : unshifted_symbols) {
        char c = pair.first;
        Macro::Keyboard::Key key = pair.second;
        INFO("Char: ", c);
        Macro::Keyboard::Combo combo = Macro::Keyboard::MapFromChar(c);
        CHECK_EQ(combo.key, key);
        CHECK_EQ(combo.shift, false);
        CHECK_EQ(combo.ctrl, false);
        CHECK_EQ(combo.alt, false);
    }

    INFO("Symbols (shifted)");
    std::map<char, Macro::Keyboard::Key> shifted_symbols = {
        // clang-format off
        {'!', Macro::Keyboard::Key::ONE},
        {'@', Macro::Keyboard::Key::TWO},
        {'#', Macro::Keyboard::Key::THREE},
        {'$', Macro::Keyboard::Key::FOUR},
        {'%', Macro::Keyboard::Key::FIVE},
        {'^', Macro::Keyboard::Key::SIX},
        {'&', Macro::Keyboard::Key::SEVEN},
        {'*', Macro::Keyboard::Key::EIGHT},
        {'(', Macro::Keyboard::Key::NINE},
        {')', Macro::Keyboard::Key::ZERO},
        {':', Macro::Keyboard::Key::COLON},
        {'+', Macro::Keyboard::Key::PLUS},
        {'<', Macro::Keyboard::Key::COMMA},
        {'_', Macro::Keyboard::Key::MINUS},
        {'>', Macro::Keyboard::Key::PERIOD},
        {'?', Macro::Keyboard::Key::SLASH},
        {'~', Macro::Keyboard::Key::TILDE},
        {'{', Macro::Keyboard::Key::LEFT_BRACKET},
        {'|', Macro::Keyboard::Key::BACKSLASH},
        {'}', Macro::Keyboard::Key::RIGHT_BRACKET},
        {'"', Macro::Keyboard::Key::QUOTE},
        // clang-format on
    };
    for (auto &pair : shifted_symbols) {
        char c = pair.first;
        Macro::Keyboard::Key key = pair.second;
        INFO("Char: ", c);
        Macro::Keyboard::Combo combo = Macro::Keyboard::MapFromChar(c);
        CHECK_EQ(combo.key, key);
        CHECK_EQ(combo.shift, true);
        CHECK_EQ(combo.ctrl, false);
        CHECK_EQ(combo.alt, false);
    }

    INFO("Special keys");
    std::map<char, Macro::Keyboard::Key> special_keys = {
        // clang-format off
        {'\b', Macro::Keyboard::Key::BACKSPACE},
        {'\t', Macro::Keyboard::Key::TAB},
        {'\r', Macro::Keyboard::Key::ENTER},
        {' ', Macro::Keyboard::Key::SPACE},
        {'\e', Macro::Keyboard::Key::ESCAPE},
        // clang-format on
    };
    for (auto &pair : special_keys) {
        char c = pair.first;
        Macro::Keyboard::Key key = pair.second;
        INFO("Char: ", c);
        Macro::Keyboard::Combo combo = Macro::Keyboard::MapFromChar(c);
        CHECK_EQ(combo.key, key);
        CHECK_EQ(combo.shift, false);
        CHECK_EQ(combo.ctrl, false);
        CHECK_EQ(combo.alt, false);
    }
}
