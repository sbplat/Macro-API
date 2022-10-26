TEST_CASE("[mouse] mouse movement absolute") {
    int expected_x = 300;
    int expected_y = 300;

    Macro::Mouse::MoveAbsolute(expected_x, expected_y);
    Macro::Mouse::Point actual = Macro::Mouse::GetPosition();

    INFO("Position x: ", actual.x);
    INFO("Position y: ", actual.y);

    CHECK(expected_x == actual.x);
    CHECK(expected_y == actual.y);
}
