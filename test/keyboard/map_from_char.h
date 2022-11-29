#include <map>

#define CHECK_KEY_COMBO(ch, expected_key, expected_shift, expected_ctrl, expected_alt)             \
    {                                                                                              \
        INFO("Char: ", ch);                                                                        \
        Macro::Keyboard::Combo combo = Macro::Keyboard::MapFromChar(ch);                           \
        CHECK_EQ(combo.key, expected_key);                                                         \
        CHECK_EQ(combo.shift, expected_shift);                                                     \
        CHECK_EQ(combo.ctrl, expected_ctrl);                                                       \
        CHECK_EQ(combo.alt, expected_alt);                                                         \
    }

TEST_CASE("[keyboard] map from char") {
    INFO("Lowercase");
    for (char c = 'a'; c <= 'z'; ++c) {
        CHECK_KEY_COMBO(c, c - 'a' + Macro::Keyboard::Key::A, false, false, false);
    }

    INFO("Uppercase");
    for (char c = 'A'; c <= 'Z'; ++c) {
        CHECK_KEY_COMBO(c, c - 'A' + Macro::Keyboard::Key::A, true, false, false);
    }

    INFO("Numbers");
    for (char c = '0'; c <= '9'; ++c) {
        CHECK_KEY_COMBO(c, c - '0' + Macro::Keyboard::Key::ZERO, false, false, false);
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
        CHECK_KEY_COMBO(c, key, false, false, false);
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
        CHECK_KEY_COMBO(c, key, true, false, false);
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
        CHECK_KEY_COMBO(c, key, false, false, false);
    }
}

#undef CHECK_KEY_COMBO
