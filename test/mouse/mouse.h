TEST_CASE("[mouse] move absolute") {
    int expected_x = 300;
    int expected_y = 300;

    Macro::Mouse::MoveAbsolute(expected_x, expected_y);
    Macro::Mouse::Point actual = Macro::Mouse::GetPosition();

    INFO("Position x: ", actual.x);
    INFO("Position y: ", actual.y);

    REQUIRE(expected_x == doctest::Approx(actual.x).epsilon(0.01));
    REQUIRE(expected_y == doctest::Approx(actual.y).epsilon(0.01)); 
}
