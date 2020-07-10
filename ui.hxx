#pragma once

#include <vector>
#include "model.hxx"
#include <ge211.hxx>
#include "ge211_geometry.hxx"
#include "ge211_sprites.hxx"
#include "ge211_forward.hxx"
#include "ge211_resource.hxx"


extern ge211::Color const
                               original_digit_color,
                               valid_digit_color,
                               invalid_digit_color,
                               individual_box_color,
                               mini_box_color,
                               rectangle_color,
                               selection_color;
extern ge211::Dimensions const individual_box_dims, mini_box_dims,
horizontal_rectangle_dims, vertical_rectangle_dims;

using Box = ge211::Rectangle;

using Text = ge211::Text_sprite;

class Digit_sprite
{
public:
    explicit Digit_sprite(ge211::Text_sprite digit);


private:
    ge211::Text_sprite black_;
    ge211::Text_sprite red_;
};

struct Ui : ge211::Abstract_game
{
    explicit Ui(Model&);

    Box individual_box_[9][9];
    Box mini_box_[9];
    Box big_box_[1];

    Text original_digit_;
    Text valid_digit_;
    Text invalid_digit_;



    //Declaring font for number text
    ge211::Font sans32_{"sans.ttf", 20};

    //instruction font
    ge211::Font sans_smaller{"sans.ttf", 13};

    //non-selection
    ge211::Position selection_{-1, -1};

    // (GE211 calls this to find out how big to make the window.)
    // ge211::Dimensions initial_window_dimensions() const override;

    //void create_black_vector();

   // void create_red_vector();


    void add_to_set(ge211::Sprite_set& set,
                    bool conflicted,
                    ge211::Position pos);

    void draw(ge211::Sprite_set&) override;

    void add_user_sprites(ge211::Sprite_set& sprites, ge211::Position pos);

    ///
    /// MEMBER FUNCTIONS (for the controller)
    ///

    void on_key(ge211::Key) override;

    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

    ///
    /// MEMBER VARIABLE (model reference)
    ///

    Model& model_;

    ///
    /// MEMBER VARIABLES (for the view)
    ///

    ge211::Rectangle_sprite const individual_box_sprite_
                                          {individual_box_dims,
                                           individual_box_color};
    ge211::Rectangle_sprite const
                                  mini_box_sprite_
                                          {mini_box_dims, mini_box_color};
    ge211::Rectangle_sprite const
                                  horizontal_rectangle_sprite{horizontal_rectangle_dims,
                                                            rectangle_color};
    ge211::Rectangle_sprite const
            vertical_rectangle_sprite{vertical_rectangle_dims,
                                        rectangle_color};

    ge211::Rectangle_sprite selection_sprite_{individual_box_dims,
                                              selection_color};


    Text
            original_digit_sprite_;
    Text
            starting_digit_sprite_{"_", sans32_};
    Text
            user_digit_sprite_{" ", sans32_};


    ge211::Text_sprite const
            game_title_{"IF YOU CANNOT SOLVE THIS "
                        "YOU WILL HAVE DISAPPOINTED THE CREATOR: ",
                        sans32_};
    ge211::Text_sprite const
            subtitle{"Designed by Bradley Pawlow",
                        sans32_};

    ge211::Text_sprite const
            instructions_one{"Left Click Mouse >>>> Select Box",
                        sans_smaller};

    ge211::Text_sprite const
            instructions_two{"SPACE_BAR >>>> "
                             "Deselect Box ",
                             sans_smaller};
    ge211::Text_sprite const
            instructions_three{"'q' >>>> Quit",
                             sans_smaller};

    ge211::Text_sprite const
            instructions_four{"Red Digit >>>> Invalid/Conflicted",
                               sans_smaller};

    ge211::Text_sprite const
            instructions_five{"(Already located in the same subgrid, row, "
                              "or\"\n"
                              "                                \" column.)\"",
                              sans_smaller};

    ge211::Text_sprite
            conflicted_message_{"This number is conflicted and is "
                                "already located in the same subgrid, row, or"
                                " column."
                                "Try another "
                                "number. ",
                        sans32_};
    ge211::Text_sprite const
            winning_title{"CONGRATULATIONS YOU SOLVED THIS PUZZLE!",
                        sans32_};

    ge211::Text_sprite const
            valid_digit_sprite_{"0", sans32_};
    ge211::Text_sprite const
            invalid_digit_sprite_{"0", sans32_};


    std::vector<Text> digit_sprites_black;

    std::vector<Text> digit_sprites_red;

    std::vector<Text> digit_sprites_cyan;

    std::vector<Text> digit_sprites_green;


    //vector holding all 81 boxes of sudoku
    std::vector<Box> box_vector;
};