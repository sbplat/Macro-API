TEST_CASE("[mouse] move absolute") {
    int expected_x = 120;
    int expected_y = 160;

    Macro::Mouse::MoveAbsolute(expected_x, expected_y);
    Macro::Mouse::Point actual = Macro::Mouse::GetPosition();

    INFO("Expected: " << expected_x << ", " << expected_y);
    INFO("Actual: " << actual.x << ", " << actual.y);

    // Allow for a 1% margin of error due to rounding.
    CHECK_EQ(expected_x, doctest::Approx(actual.x).epsilon(0.01));
    CHECK_EQ(expected_y, doctest::Approx(actual.y).epsilon(0.01));
}
