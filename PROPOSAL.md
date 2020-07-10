# Proposal: Sudoku, Beginner's Edition

## Synopsis

### Elements 

Our game will have multiple elements and add-ons from a typical Sudoku game:

Two Basic Elements:

    - A stationary array of boxes aligned in rows and columns 
    divided into sections similar to a matrix format (depending on the 
    difficulty, there can be a change in grid size, standard is 9x9 grid) and 
    - A designated number assigned to some of the boxes (depending on 
    difficulty there can be a change in the amount of given numbers)
 
Three Additional Elements: 

    - Tips and tricks in the initial phase of the puzzle for beginners,
    - Division between easy, medium, and hard difficulties, and 
    - Hints along the way when users are stuggling with puzzle.
    
### Goal

The player's goal is to complete the entire 9x9 grid with numbers so that 
each row, column and 3x3 section contain all of the digits between 1 and 9. 
No number can be repeated in its specific row, column, and section. 

### Gameplay 

The grid starts off with anywhere from 15 to 20 numbers scattered around the
grid and divided into different 3x3 sections. The player begins by filling in
the empty boxes with numbers that are intended to achieve the goal stated above. 
Once all boxes are filled in or once the player gives up, the player's mistakes 
are revealed. From that point on, the player can attempt to correct their 
mistakes or see the complete solution. 
  
## Functional requirements

1. The 9x9 grid is placed on the screen with outlines seperating the boxes. 
2. 3x3 subgrids are created with coordinates to represent the sections inside 
the original grid.   
3. The numbers are printed and assigned to specific cells.
4. The player can choose to reveal the solutions to the puzzle by pressing the 
space bar or clicking the mouse. 
5. The player is informed if they have failed to correctly solve the puzzle. 
6. There is test to see whether the player has completely filled out the puzzle 
with numbers or if there are blank cells. 
7. If the player types in a valid number in the cell, then the value is stored 
in that cell unless changed later. 
8. If the player does not type in a valid number, then they are informed it is
not valid. 
9. If the player is struggling to correct their mistakes or complete the puzzle
in a certain amount of time, then they will be given a hint (such as an 
automatically filled in number)
10. The player is given instructions on how to play the game and some tips and 
tricks in the beginning of the puzzle.  
11. The game checks whether a number has been repeated in a subgrid, row, or 
column. 
12. The player is able to choose an easy, medium, or hard puzzle. 
13. There is a test that checks that the puzzle is always solvable or each 
individual row, column, and subgrid are solvable. 

## Open questions

    - What are the best setups to generate a grid that is categorized as 
    "hard diffuculty" and another grid that is "easy difficulty?"
    - How can we incorporate tips and tricks for beginners in text format prior 
    to the game starting?
    - How should we show to the player each box that is incorrect? 
    



