/*
BSD 2-Clause License

Copyright (c) 2021, XTblock.io, AL.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef __cplusplus
extern "C" {
#endif

#define TOKEN_SIZE 5
#define TOTAL_VECTOR 4
#define MIN_TOP_MOVES 2
#define TOTAL_MIN_TOP_MOVES 4
#define MAX_TOP_MOVES 3
#define TOTAL_MAX_TOP_MOVES 6

// all of your legacy C code here

//////////////////////
#ifdef __cplusplus

using namespace std;

struct gmkcell{
	//int board;
	int x;//0->18, board 19x19
	int y;//0->18, board 19x19
	int occupied;
	int weight;
};

struct gmkgame{
	//string game_id;
	int x;
	int y;
	int player;//black, X: 1; white, O: -1; blank: 0
	int c_weight;
};

struct gmk_winning_pattern{
	struct gmkgame cell[TOKEN_SIZE];
	string pattern_id;
	long long occupied_pattern;
	int n_occupied;
	int weight;
	int non_consecutive;
	int spy;
	int blocking_left;
	int blocking_right;
	int vector;
	int decayed;
	/*
	//0: |
	//1: __
	//2: / needs 2 strings
	//3: \ needs 2 strings
	*/
};

struct tactic_weight{
	struct gmkgame cell;
	string pattern_id;
	list <int> pattern_vector_list;

	int machine_pt_level;//highest pattern level
	long machine_pt;
	float machine_uct;

	int player_pt_level;//highest pattern level
	long player_pt;
	float player_uct;
	int n_visited;//number of visits

	int machine_n_fork;//count fork group
	int player_n_fork;

	int n_op_decayed;//count the opponent's decayed group by the move
	float ratio;
};

struct victory_threats{
	struct gmkgame cell;

	list <struct gmk_winning_pattern> patterns[TOTAL_VECTOR];
	//list <struct gmk_winning_pattern> player_patterns[TOTAL_VECTOR];
	//list <struct gmk_winning_pattern> empty_patterns[TOTAL_VECTOR];
};

//function for printing the elements in a list
void showgame(std::list <struct gmkgame> g);

//function for printing the elements in a list
void show_winning_patterns(std::list <struct gmk_winning_pattern> g);
void print_winning_pattern(struct gmk_winning_pattern g);
void log_winning_pattern(char filename[50], std::list <struct gmk_winning_pattern> *gmk_for_machine);
//function for finding related winning patterns with the cell
int find_patterns(std::list <struct gmk_winning_pattern> g, struct gmkgame *cell);

int set_n_occupied(list <struct victory_threats> *vct_search, list <struct gmk_winning_pattern> *winning_list, struct gmkgame *cell, int machine_chess, int player_chess);

void fire_top_moves(char filename[50], std::list <struct tactic_weight> *get_tactic_moves);

bool compare_pattern(struct gmk_winning_pattern &p1, struct gmk_winning_pattern &p2);

bool compare_tactic_machine_pt(struct tactic_weight &p1, struct tactic_weight &p2);

bool compare_tactic_machine_pt_level(struct tactic_weight &p1, struct tactic_weight &p2);

bool compare_tactic_player_pt(struct tactic_weight &p1, struct tactic_weight &p2);

bool compare_tactic_player_pt_level(struct tactic_weight &p1, struct tactic_weight &p2);

bool compare_tactic_ratio_pt(struct tactic_weight &p1, struct tactic_weight &p2);

bool compare_machine_uct(struct tactic_weight &p1, struct tactic_weight &p2);

bool compare_player_uct(struct tactic_weight &p1, struct tactic_weight &p2);

//draw game board
void draw_game_board(int gboard_x, int gboard_y, char player_color, struct gmkgame **gboard, list <struct gmkgame> gmkplay_list);

long tactic_play(int gboard_x, int gboard_y, struct gmkgame **gboard, list <struct gmk_winning_pattern> gmk_for_machine, int advantage_i, struct gmkgame cell, int machine_chess, int player_chess, int *get_highest_pattern_level);

//search next playing cell for machine
int machine_play(list <struct victory_threats> *vct_search, int n_ply, int started_chess, int gboard_x, int gboard_y, struct gmkgame **gboard, list <struct gmk_winning_pattern> *gmk_for_machine, struct gmkgame *cell, int machine_chess, int player_chess, int cur_move, struct gmkgame *next_play_proposal, std::list <struct tactic_weight> *get_tactic_moves, int max_tmoves, int total_max_tmoves, int *original_machine_highest_level, int *original_player_highest_level);

}
#endif
