TEST_CASE("[keyboard] key conversions") {
    for (Macro::Keyboard::Key key = Macro::Keyboard::Key::BACKSPACE; key <= Macro::Keyboard::Key::OEM_102;
         key = static_cast<Macro::Keyboard::Key>(key + 1)) {
        int osKey = Macro::Keyboard::MapToOSKey(key);
        Macro::Keyboard::Key key2 = Macro::Keyboard::MapFromOSKey(osKey);
        INFO("Key: ", Macro::Keyboard::GetKeyName(key));
        CHECK_EQ(key, key2);
    }
}
