#include "model.hxx"

// Create three grids : the starting grid, the grid that the player can edit
// and the solution grid
Model::Model(Grid const& puzzle, Grid const& solution)
        : initial_grid_(puzzle)
        , editing_grid_(puzzle)
        , solution_grid_(solution)
{

}

// gives the digit at the specified position
Digit Model::get_digit(ge211::Position position) const
{
    return editing_grid_[position.x][position.y];
}

// the player is able to enter/remove a digit in a position that is
// originally zero
void Model::play_move(Digit digit, ge211::Position position)
{
    if (is_modifiable(position)) {
        editing_grid_[position.x][position.y] = digit;
    }
}


// determines whether a position's digit is one already given, if so false
bool Model::is_modifiable(ge211::Position position) const
{
    return initial_grid_[position.x][position.y] == 0;
}

// determines whether a position's digit conflicts with another positions
// digit in the row, column, or grid, if so returns true
bool Model::is_conflicted(ge211::Position position) const
{
    for (int i = 0; i < 9; i++) {
        if (i != position.y &&
            editing_grid_[position.x][i] == get_digit(position)) {
            return true;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (i != position.x &&
            editing_grid_[i][position.y] == get_digit(position)) {
            return true;
        }
    }
    for (int i = 0; i < 9; i++) {
        int xpos = (position.x / 3) * 3 + (i / 3);
        int ypos = (position.y / 3) * 3 + ((i+3) % 3);
        if ((editing_grid_[xpos][ypos] == get_digit(position)) &&
            (xpos != position.x || ypos != position.y)){
            return true;
        }
    }
    return false;
}
bool Model::is_complete() const
{
    return editing_grid_ == solution_grid_;
}

