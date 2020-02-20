#include "textDisplay.h"
#include "../game/board/cell.h"
#include "../game/player.h"
#include "../game/board/board.h"
#include <iostream>
#include <typeinfo>

TextDisplay::TextDisplay() : next_block_p1{BlockType::NoType}, next_block_p2{BlockType::NoType}, score_p1{0}, score_p2{0},
							 hi_score_p1{0}, hi_score_p2{0}, level_p1{0}, level_p2{0}
{
	for (size_t r = 0; r < HEIGHT; ++r)
	{
		std::vector<char> row_p1; //row for player 1
		std::vector<char> row_p2; //row for player 2
		for (size_t col = 0; col < WIDTH; ++col)
		{
			row_p1.push_back(' '); //fill row for p1 with spaces
			row_p2.push_back(' '); //fill row for p2 with spaces
		}
		first_display.push_back(row_p1);  //place row1 into first display
		second_display.push_back(row_p2); //place row2 into second display
	}
}

char TextDisplay::colourToChar(Colour colour)
{
	switch (colour)
	{
	case (Colour::Orange):
		return 'L';
	case (Colour::DarkBlue):
		return 'J';
	case (Colour::LightBlue):
		return 'I';
	case (Colour::Green):
		return 'S';
	case (Colour::Purple):
		return 'T';
	case (Colour::Red):
		return 'Z';
	case (Colour::Yellow):
		return 'O';
	case (Colour::Brown):
		return '*';
	default:
		return ' ';
	}
}

void TextDisplay::notify(Subject &whoNotified)
{
	Info info = whoNotified.getInfo();
	if (typeid(whoNotified) == typeid(Player))
	{ //if subject is a player
		if (info.id == 1)
		{ //if id corresponds to player1, then:
			level_p1 = info.level;
			score_p1 = info.score;		 //change p1 score to the score of the subject
			hi_score_p1 = info.hi_score; //change p1 high score to the high score of the subject
		}
		if (info.id == 2)
		{ //if id corresponds to player2, then:
			level_p2 = info.level;
			score_p2 = info.score;		 //change p2 score to the score of the subject
			hi_score_p2 = info.hi_score; //change p2 high score to the high score of the subject
		}
	}
	if (typeid(whoNotified) == typeid(Board))
	{ //if subject is a board
		if (info.id == 1)
		{ //if id corresponds to player1, then:
			blind_p1 = info.blind;
			next_block_p1 = info.next_block; //change p1 next block to the subject's next block
		}
		if (info.id == 2)
		{ //if id corresponds to player2, then:
			blind_p2 = info.blind;
			next_block_p2 = info.next_block; //change p2 next block to the subject's next block
		}
	}
	if (typeid(whoNotified) == typeid(Cell))
	{ //if subject is a cell
		if (info.id == 1)
		{ //if id corresponds to player1, then:
			first_display[info.row][info.col] = colourToChar(info.colour);
		}
		if (info.id == 2)
		{ //if id corresponds to player2, then:
			second_display[info.row][info.col] = colourToChar(info.colour);
		}
	}
}

std::string blockTypeToString(BlockType block_type, int &first_line, int &second_line)
{ //converts blocktype to string
	switch (block_type)
	{
	case (BlockType::S):
		first_line = 3; 	// SS
		second_line = 2; 	//SS
		return "S";
	case (BlockType::O):
		first_line = 2; 	//OO
		second_line = 2; 	//OO
		return "O";
	case (BlockType::Z):
		first_line = 2;		//ZZ
		second_line = 3;	// ZZ
		return "Z";
	case (BlockType::I):
		first_line = 0;		//
		second_line = 4;	//IIII
		return "I";
	case (BlockType::L):
		first_line = 3; 	//  L
		second_line = 3; 	//LLL
		return "L";
	case (BlockType::J):
		first_line = 1;		//J
		second_line = 3;	//JJJ
		return "J";
	case (BlockType::T):
		first_line = 3;		//TTT
		second_line = 2; 	// T
		return "T";
	default:
		return " ";
	}
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &t)
{
	int default_space = 8; //default amount of space between text in the display
	int min_spaces = 1;
	int level_space = std::max(min_spaces, 12 - (int)(std::to_string(t.level_p1).length())); //# of spaces needed between level text
	int score_space = std::max(min_spaces, 12 - (int)(std::to_string(t.score_p1).length())); //# of spaces needed between score text
	int hi_score_space = std::max(min_spaces, 9 - (int)(std::to_string(t.score_p1).length())); //# of spaces needed between high score text
	int first_line_p1 = 0; 	//used for next block
	int second_line_p1 = 0; //used for next block
	int first_line_p2 = 0; 	//used for next block
	int second_line_p2 = 0; //used for next block
	out << std::string(WIDTH * 2 + 8, '-') << std::endl;				 //line of dashes
	out << std::string("Level: ") << t.level_p1 << std::string(level_space, ' '); //level p1
	out << std::string("Level: ") << t.level_p2 << std::endl;				  //level p2
	out << std::string("Hi-score: ") << t.hi_score_p1 << std::string(hi_score_space, ' '); //hiscore p1
	out << std::string("Hi-score: ") << t.hi_score_p2 << std::endl;	
	out << std::string("Score: ") << t.score_p1 << std::string(score_space, ' ');	  //score p1
	out << std::string("Score: ") << t.score_p2 << std::endl;				  //score p2
	out << std::string(WIDTH * 2 + 8, '-') << std::endl;					//line of dashes
	for(int row = HEIGHT - 4; row >= 0; --row){
		for(size_t col_p1 = 0; col_p1 < WIDTH; ++col_p1){
			if (t.blind_p1 && col_p1 >= 3 && col_p1 <= 9 && row >= 3 && row <= 12) {
				out << '?';
			}
			else
			{
				out << t.first_display[row][col_p1];
			}
		}
		out << std::string(8, '.');
		for (size_t col_p2 = 0; col_p2 < WIDTH; ++col_p2)
		{
			if (t.blind_p2 && col_p2 >= 3 && col_p2 <= 9 && row >= 3 && row <= 12)
			{
				out << '?';
			}
			else
			{
				out << t.second_display[row][col_p2];
			}
		}
		out << std::endl;
	}
	out << std::string(WIDTH * 2 + 8, '-') << std::endl;
	out << std::string("Next Block:") << std::string(default_space, ' ') << std::string("Next Block:") << std::endl; //8 spaces in between, Next Block: takes 11 columns
	std::string temp_p1 = blockTypeToString(t.next_block_p1, first_line_p1, second_line_p1);
	std::string temp_p2 = blockTypeToString(t.next_block_p2, first_line_p2, second_line_p2);
	bool line1 = true; //checks if we are on the first line of next block display or the second
	if(line1){ //for the first line
		if(temp_p1 == "S"){
			out << " " << std::string(first_line_p1 - 1, temp_p1[0]) << std::string(19 - first_line_p1, ' ');
		}else if(temp_p1 == "L"){
			out << "  " << std::string(first_line_p1 - 2, temp_p1[0]) << std::string(19 - first_line_p1, ' ');
		}else{
			out << std::string(first_line_p1, temp_p1[0]) << std::string(19 - first_line_p1, ' ');
		}
		if(temp_p2 == "S"){
			out << " " << std::string(first_line_p2 - 1, temp_p2[0]) << std::endl;
		}else if(temp_p2 == "L"){
			out << "  " << std::string(first_line_p2 - 2, temp_p2[0]) << std::endl;
		}else{
			out << std::string(first_line_p2, temp_p2[0]) << std::endl;
		}
		line1 = false;
	}
	if(!line1){ //for the second line
		if(temp_p1 == "Z"){
			out << " " << std::string(second_line_p1 - 1, temp_p1[0]) << std::string(19 - second_line_p1, ' ');
		}else if(temp_p1 == "T"){
			out << " " << std::string(second_line_p1 - 1, temp_p1[0]) << std::string(19 - second_line_p1, ' ');
		}else{
			out << std::string(second_line_p1, temp_p1[0]) << std::string(19 - second_line_p1, ' ');
		}
		if(temp_p2 == "Z"){
			out << " " << std::string(second_line_p2 - 1, temp_p2[0]) << std::endl;
		}else if(temp_p2 == "T"){
			out << " " << std::string(second_line_p2 - 1, temp_p2[0]) << std::endl;
		}else{
			out << std::string(second_line_p2, temp_p2[0]) << std::endl;
		}
	}
	out << std::string(WIDTH * 2 + 8, '-');
	return out;
}
