TEST_CASE("[mouse] move absolute") {
    int expected_x = 300;
    int expected_y = 300;

    Macro::Mouse::MoveAbsolute(expected_x, expected_y);
    Macro::Mouse::Point actual = Macro::Mouse::GetPosition();

    INFO("Position x: ", actual.x);
    INFO("Position y: ", actual.y);

    CHECK_EQ(expected_x, actual.x);
    CHECK_EQ(expected_y, actual.y);
}
