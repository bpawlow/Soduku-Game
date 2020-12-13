#include "model.hxx"
#include <catch.hxx>

const Grid puzzle1 { {{ 3, 1, 6, 5, 7, 8, 4, 9, 2 },
                             { 5, 2, 9, 1, 3, 4, 7, 6, 8 },
                             { 4, 8, 7, 6, 2, 9, 5, 3, 1 },
                             { 2, 6, 3, 0, 1, 5, 9, 8, 7 },
                             { 9, 7, 4, 8, 6, 0, 1, 2, 5 },
                             { 8, 5, 1, 7, 9, 2, 6, 4, 3 },
                             { 1, 3, 8, 0, 4, 7, 2, 0, 6 },
                             { 6, 9, 2, 3, 5, 1, 8, 7, 4 },
                             { 7, 4, 5, 0, 8, 6, 3, 1, 0 } }};

const Grid solution1 { {{3, 1, 6, 5, 7, 8, 4, 9, 2},
                               {5, 2, 9, 1, 3, 4, 7, 6, 8},
                               {4, 8, 7, 6, 2, 9, 5, 3, 1},
                               {2, 6, 3, 4, 1, 5, 9, 8, 7},
                               {9, 7, 4, 8, 6, 3, 1, 2, 5},
                               {8, 5, 1, 7, 9, 2, 6, 4, 3},
                               {1, 3, 8, 9, 4, 7, 2, 5, 6},
                               {6, 9, 2, 3, 5, 1, 8, 7, 4},
                               {7, 4, 5, 2, 8, 6, 3, 1, 9} }};

TEST_CASE("Playing a move")
{
    Model model(puzzle1, solution1);
    model.play_move(2, {8, 8});
    CHECK(model.get_digit({8, 8}) == 2 );
}

TEST_CASE("What is modifiable?")
{
    Model model(puzzle1, solution1);

    CHECK(model.is_modifiable({8, 3}) );
    CHECK_FALSE(model.is_modifiable({9, 9}) );
    CHECK_FALSE(model.is_modifiable({0, 2}) );

    model.play_move(6, {8, 8});

    CHECK(model.is_modifiable({8, 8}) );
}

TEST_CASE("detects conflicts")
{
    Model model(puzzle1, solution1);
    CHECK_FALSE(model.is_conflicted({0, 1}) );
    CHECK_FALSE(model.is_conflicted({0, 2}) );

    model.play_move(5, {8, 8});
    CHECK(model.is_conflicted({8, 2}) );
    CHECK(model.is_conflicted({6, 7}) );
    CHECK_FALSE(model.is_conflicted({2, 1}) );

    model.play_move(3, {6, 3});
    CHECK_FALSE(model.is_conflicted({0, 1}) );
    CHECK(model.is_conflicted({7, 3}) );
    CHECK(model.is_conflicted({6, 1}) );

    model.play_move(2, {4, 5});
    CHECK(model.is_conflicted({5, 5}) );
    CHECK_FALSE(model.is_conflicted({0, 4}) );
    CHECK_FALSE(model.is_conflicted({2, 1}) );
}

TEST_CASE("Is the game complete?")
{
    Model model(puzzle1, solution1);
    CHECK_FALSE(model.is_complete());
    model.play_move(9, {8, 8});
    CHECK_FALSE(model.is_complete());
    model.play_move(5, {6, 7});
    CHECK_FALSE(model.is_complete());
    model.play_move(3, {4, 5});
    CHECK_FALSE(model.is_complete());
    model.play_move(4, {3, 3});
    CHECK_FALSE(model.is_complete());
    model.play_move(2, {8, 3});
    CHECK_FALSE(model.is_complete());
    model.play_move(9, {6, 3});
    CHECK(model.is_complete());
}