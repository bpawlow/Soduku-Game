#include "ui.hxx"
#include "model.hxx"
#include <iostream>
#include <cstdlib>
#include<ctype.h>
#include <ge211_event.hxx>

// What needs to be done : The draw function needs to be fixed : look at the
// brick out one. The
// geometry.hxx file in brick out is really helpful on getting the spacing
// between each box.

//I also started writing the text sprites for the digits in the ui.hxx file.
// The example on how to format them is in the ge211 documentation

// Also feel free to change the pink color because it's really bright


Digit_sprite::Digit_sprite(ge211::Text_sprite digit)
        : red_(digit) , black_(digit)
{
    //ge211::Text_sprite::Builder builder();
    //builder().color(ge211::Color::medium_red());
    //red_.reconfigure(builder());
    //builder().color(ge211::Color::black());
    //black_.reconfigure(builder());
}


Ui::Ui(Model& model)
        : model_(model)
{
    // vector of BLACK digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::black());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_black.push_back(original_digit_sprite_);
    }

    // vector of BLUE digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::medium_blue());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_blue.push_back(original_digit_sprite_);
    }

    // vector of RED digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::medium_red());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_red.push_back(original_digit_sprite_);
    }

    // vector of GREEN digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::medium_green());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_green.push_back(original_digit_sprite_);
    }


    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            Box each_box;
            each_box.width  = individual_box_dims.width;
            each_box.height = individual_box_dims.height;
            each_box.x      = 215 + (40 * y);
            each_box.y      = 125 + (40 * x);
            box_vector.push_back(each_box);
        }
    }
    //define in ui.hxx, the text sprites
    //create sprites and put them into vector
    //push back in the vector text sprites

}


// Use `Sprite_set::add_sprite(Sprite&, Position)` to add each sprite
// to `sprites`.
ge211::Dimensions const individual_box_dims{35, 35};
ge211::Dimensions const mini_box_dims{125, 125};
ge211::Dimensions const horizontal_rectangle_dims{365, 5};
ge211::Dimensions const vertical_rectangle_dims{5, 355};

ge211::Position logical_to_screen(ge211::Position posn){
    posn.x = 215 + (40 * posn.y);
    posn.y = 125 + (40 * posn.x);
    return posn;
}

ge211::Position screen_to_logical(ge211::Position posn){
    posn.x = (posn.y - 125)/(40);
    posn.y = (posn.x - 215)/(40);
    return posn;
}

//void Ui::add_to_set(ge211::Sprite_set& set,
//                bool conflicted, ge211::Position pos){

  //  if (conflicted){
   //     set.add_sprite(digit_sprites_red.at(model_.editing_grid_[pos
  //      .x][pos.y]), logical_to_screen(pos).down_by(10).right_by
  //              (10), 2);
 //   }else if (model_.editing_grid_[pos
   //         .x][pos.y] == 0){
  //  }
   // else {
  //      set.add_sprite(digit_sprites_black.at(model_.editing_grid_[pos
  //              .x][pos.y]), logical_to_screen(pos).down_by(10).right_by
  //              (10), 2);
  //  }
//}


void Ui::draw(ge211::Sprite_set& sprites)
{
    sprites.add_sprite(game_title_,
                       {30, 25}, 1);
    sprites.add_sprite(subtitle,
                       {265, 70}, 1);
    sprites.add_sprite(instructions_one,
                       {585, 215}, 1);
    sprites.add_sprite(instructions_two,
                       {585, 265}, 1);
    sprites.add_sprite(instructions_three,
                       {585, 315}, 1);
    sprites.add_sprite(instructions_four,
                       {585, 365}, 1);

    //borders
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 120}, 1);
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 240}, 1);
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 360}, 1);
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 480}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {210, 125}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {330, 125}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {450, 125}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {570, 125}, 1);
    //sprites.add_sprite(mini_box_sprite_,
                      //{330, 123}, 1);

    for (Box each_box : box_vector) {
        sprites.add_sprite(individual_box_sprite_,
                           each_box.top_left(), 2);
    }

    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            ge211::Position grid_pos = {x, y};

            //starting numbers that cannot be changed
            if (!model_.is_modifiable(grid_pos)) {
                sprites.add_sprite(
                        digit_sprites_black.at(model_.editing_grid_[x][y]),
                        {227 + (40 * y), 126 + (40 * x)}, 3);
            }
            //starting blank boxes
            if (model_.editing_grid_[x][y] == 0 && selection_ != grid_pos){
            }

            if (model_.is_modifiable(grid_pos) && model_.editing_grid_[x][y]
             != 0 && selection_ == grid_pos){
                sprites.add_sprite(selection_sprite_, {215 + (40 * y), 125 +
                                                                       (40 * x)},3);
                if(model_.is_conflicted(grid_pos)){
                    for (int x = 0; x < 9; x++) {
                        for (int y = 0; y < 9; y++) {
                            ge211::Position grid_pos_two = {x, y};
                            if(model_.is_conflicted(grid_pos_two) && model_
                            .editing_grid_[x][y] != 0) {
                                sprites.add_sprite(digit_sprites_red.at(
                                        model_.editing_grid_[x][y]),
                                                   {227 + (40 * y),
                                                    126 + (40 * x)}, 4);
                            }
                        }
                    }
                }else{
                    sprites.add_sprite(digit_sprites_blue.at(model_
                                                                     .editing_grid_[x][y]), {227 + (40 * y),
                                                                                             126 + (40 * x)}, 4);
                }
                //selection_ ={-1,-1};
            }
            else if (model_.is_conflicted(grid_pos) && model_
            .editing_grid_[x][y]
            != 0){
                //ge211::Text_sprite::Builder builder(sans32_);
                //builder.color(ge211::Color::medium_red());
                //conflicted_message_.reconfigure(builder);
                //sprites.add_sprite(conflicted_message_,
                                //   {50, 550}, 1);
                sprites.add_sprite(digit_sprites_red.at(model_.editing_grid_[x][y]),
                                   {227 + (40 * y), 126 + (40 * x)}, 3);
            }else if (selection_ == grid_pos && model_.is_modifiable
            (grid_pos) && model_.editing_grid_[x][y] == 0){

                sprites.add_sprite(selection_sprite_, {215 + (40 * y), 125 +
                (40 * x)},3);
                sprites.add_sprite(starting_digit_sprite_, {227 + (40 * y),
                                                        126 + (40 * x)}, 4);
            }
            else if (!model_.is_conflicted(grid_pos) && model_.editing_grid_[x][y]
                                                       != 0 && model_
                                                       .is_modifiable(grid_pos)){
                sprites.add_sprite(digit_sprites_blue.at(model_
                                                                 .editing_grid_[x][y]), {227 + (40 * y),
                                                                                         126 + (40 * x)}, 4);
            }

            if (model_.is_complete()){
                for (int x = 0; x < 9; x++) {
                    for (int y = 0; y < 9; y++) {
                        ge211::Position grid_pos_three = {x, y};
                        if (model_.is_modifiable(grid_pos_three)) {
                            sprites.add_sprite(digit_sprites_green.at(model_
                                                                              .editing_grid_[x][y]),
                                               {227 + (40 * y), 126 + (40 * x)},
                                               4);
                        }
                    }
                }
                sprites.add_sprite(winning_title,
                                   {150, 515}, 1);
            }

            //ge211::Position grid_pos = {x, y};
            //add_to_set(sprites, model_.is_conflicted(grid_pos),
            //       grid_pos);
        }
    }
}
//void Ui::add_user_sprites(ge211::Sprite_set& sprites, ge211::Position pos){
  //  sprites.add_sprite(user_digit_sprite_, pos);
//}



    //Sprite_set& add_sprite(Sprite const&, Position, int z, Transform const&);
    //ge211::Sprite_set::add_sprite(Sprite&, Position);
    //for (int i = 0; i < 9; i++) {
    //  for (int j = 0; j < 9; j++) {
    //    sprites.add_sprite(individual_box_sprite_, {100, 100},
    //                     0);
    //sprites.add_sprite(individual_box_sprite_, {110, 110},
    //                 0);
    //}
    // for (int j = 0; j < 9; j++)
    //  sprites.add_sprite(individual_box_sprite_,  individual_box_[j][j]
    // .top_left().down_left_by({10,10}), 0);
    //big_box_[i].top_left()
    //         .down_by(100).right_by(10 * i)


///
/// VIEW CONSTANTS
///

// Colors for the digits, for the 81 squares, for the 9 squares, and for the
// giant
//Color of the original digits (these digits cannot be removed) : black
ge211::Color const original_digit_color{0, 0, 0};

// Color of the digits the player inputs that are valid : aqua
ge211::Color const valid_digit_color{0, 255, 255};

// Color of the digits the player inputs that are invalid : red
ge211::Color const invalid_digit_color{255, 0, 0};

//Color of the 81 individual squares on the box  : white
ge211::Color const individual_box_color{255, 255, 255};

// Color of the 9 boxes (each of these boxes contain 9 smaller boxes) : pink
ge211::Color const mini_box_color{255, 0, 255};

//Color of the giant Sudoku grid (grid outline) : black
ge211::Color const rectangle_color{255, 0, 0};

//user selection color
ge211::Color const selection_color{180, 200, 190, 255};

/*
ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.geometry_.scene_dims;
}
*/


///
/// CONTROLLER FUNCTIONS
///

// Determines key functions for the game
void Ui::on_key(ge211::Key key)
{


    //Digit digit;
    if (key == ge211::Key::code('q')) {
        quit();
    }
    if (model_.is_modifiable(selection_)) {

        if (key == ge211::Key::code('\b')) {
            model_.editing_grid_[selection_.x][selection_.y] = 0;
        }
        if (key == ge211::Key::code(' ')) {
            selection_ = {-1, -1};
            valid_selection = false;
        }
        if (key == ge211::Key::up()) {
            int x = selection_.x;
            for (int i = x - 1; i >= 0; i--) {
                if (model_.is_modifiable({i, selection_.y})){
                    selection_ = {i, selection_.y};
                    break;
                }
            }
            if (selection_.x == x) {
                for (int j = selection_.x - 1; j >= 0; j--) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_modifiable({j, i}) && i != selection_.y) {
                            selection_ = {j, i};
                            return;
                        }
                    }
                }
            }
        }
        if (key == ge211::Key::down()) {
            int x = selection_.x;
            for (int i = x + 1; i < 9; i++) {
                if (model_.is_modifiable({i, selection_.y})){
                    selection_ = {i, selection_.y};
                    break;
                }
            }
            if (selection_.x == x) {
                for (int j = selection_.x + 1; j < 9; j++) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_modifiable({j, i}) && i != selection_.y) {
                            selection_ = {j, i};
                            return;
                        }
                    }
                }
            }
        }
        if (key == ge211::Key::left()) {
            int y = selection_.y;
            for (int i = y - 1; i >= 0; i--) {
                if (model_.is_modifiable({selection_.x, i})){
                    selection_ = {selection_.x, i};
                    break;

                }
            }
            if (selection_.y == y) {
                for (int j = selection_.y - 1; j >= 0; j--) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_modifiable({i, j}) && i != selection_.x) {
                            selection_ = {i, j};
                            return;
                        }
                    }
                }
            }
        }
        if (key == ge211::Key::right()) {
            int      y = selection_.y;
            for (int i = y + 1; i < 9; i++) {
                if (model_.is_modifiable({selection_.x, i})) {
                    selection_ = {selection_.x, i};
                    break;
                }
            }
            if (selection_.y == y) {
                for (int j = selection_.y + 1; j < 9; j++) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_modifiable({i, j}) && i != selection_.x) {
                            selection_ = {i, j};
                            return;
                        }
                    }
                }
            }
        }
        //if (digit) { // Idk if we need this line
         if (key == ge211::Key::code('1')) {
             model_.editing_grid_[selection_.x][selection_.y] = 1;
             //builder.color(ge211::Color::medium_cyan());
             //if(model_.is_conflicted(selection_)){
             //    builder.color(ge211::Color::medium_red());
         //}
            //builder << key.as_text();
            //user_digit_sprite_.reconfigure(builder);
        } else if (key == ge211::Key::code('2')) {
             model_.editing_grid_[selection_.x][selection_.y] = 2;

        } else if (key == ge211::Key::code('3')) {
             model_.editing_grid_[selection_.x][selection_.y] = 3;

        } else if (key == ge211::Key::code('4')) {
             model_.editing_grid_[selection_.x][selection_.y] = 4;

        } else if (key == ge211::Key::code('5')) {
             model_.editing_grid_[selection_.x][selection_.y] = 5;

        } else if (key == ge211::Key::code('6')) {
             model_.editing_grid_[selection_.x][selection_.y] = 6;

        } else if (key == ge211::Key::code('7')) {
             model_.editing_grid_[selection_.x][selection_.y] = 7;


        } else if (key == ge211::Key::code('8')) {
             model_.editing_grid_[selection_.x][selection_.y] = 8;

        } else if (key == ge211::Key::code('9')) {
             model_.editing_grid_[selection_.x][selection_.y] = 9;

        }
    }else{

    }
}

// Allows the player to only click on modifiable positions
void Ui::on_mouse_up(ge211::Mouse_button, ge211::Position position)
{

    ge211::Position clicked  = {(position.y - 125)/(40), (position.x - 215)/(40)};
    //auto selected = selection_;

    selection_ = {-1,-1};
    valid_selection = false;

    if (clicked.x > 8 || clicked.x < 0 || clicked.y > 8 || clicked.y < 0){
        return;
    }
    else {
        selection_ = clicked;
        valid_selection = true;
        return;
    }

    //if (model_.is_modifiable(position)){
      //  return;
    //}
}
// NOTES:
// pick 2 colors make 9 squares on color and 9 squares smaller colors
// inside need digits and the background color to change
// use sprites to do that like a stamp - rectangle sprites, loop through grid
// and for each sprite you put one there
//create 9  vector sprites 1-9 and for different colors need 27ish
// 1 variable which is a vector of structs
// define a UI struct that is a digit - holds sprite for each digit
// 1 vector of 9 of each things - member function to show that in a specific
// place it is highlighted

// let them put everything in a conflict and highlight all
//should know what numbers came with the puzzle and what they type





























/*
void interact()
{
    std::cout << "Options:\n"
              << "   p  Print board\n"
              << "   e  Edit a square\n"
              << "   q  Quit\n"
              << "\n";
    return;
}
void getOption(char sudokuBoard[][9])
{
    char option;
    std::cout << "> ";
    std::cin >> option;

    if (option == 'p' || option == 'P') {
//print_grid();
    }
    else if (option == 'e' || option == 'E'){
//editSquare(sudokuBoard);
    }
    else if (option == 'q' || option == 'Q') {
//quit somehow
    }
    else {
        std::cout << "ERROR: Command is invalid.";
    }
    return;
}*/