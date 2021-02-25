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

//compile: wasic++ -fno-exceptions foo.cpp -o foo.wasm
//without main function: wasic++ -Wl,--allow-undefined -fno-exceptions foo.cpp -o foo.wasm
//run: wasmer foo.wasm machine_play 19
//run with SIMD 128: wasmer run --llvm --enable-simd foo.wasm machine_play 19

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <list>
#include <iterator>
#include <limits>
#include <cstdlib>
#include <math.h>

#include "gmkopp.h"
#include "include/cJSON.c"


using namespace std;

struct k_com_w{
	long long k_com;
	float opened_w;
	float blocking_left_w;
	float blocking_right_w;
};

struct k_com_w k_com_w_array[25]={
	{10000, 5, 1, 5}, {1000, 5, 5, 5}, {100, 5, 5, 5}, {10, 5, 5, 5}, {1, 5, 5, 1},//5
	{11000, 50, 1, 50}, {10100, 5, 1, 5}, {10010, 5, 1, 5}, {10001, 5, 1, 1}, {1100, 50, 50, 50}, {1010, 5, 5, 5}, {1001, 5, 5, 1}, {110, 50, 50, 50}, {101, 5, 5, 1}, {11, 50, 50, 1},//10
	{11100, 1000, 12, 12}, {10110, 1000, 12, 12}, {10011, 300, 12, 12}, {1110, 1000, 12, 12}, {1011, 1000, 12, 12}, {111, 1000, 12, 12},//6
	{11110, 10000, 5000, 5000}, {10111, 8000, 4000, 4000}, {1111, 10000, 5000, 5000},//3
	{11111, 1000000, 1000000, 1000000}//1
};

size_t size_of_k_com_w_array = sizeof(k_com_w_array)/sizeof(k_com_w_array[0]);

//list <long> threat_ranking_pt[TOKEN_SIZE];//array of list for ranking threats

long w_tactic_open[5]={5, 100, 2000, 45000, 1000000};//open both 2 sides
long w_tactic_blocking[5]={2, 50, 1000, 22500, 1000000};//blocked one side

//draw game board
void draw_game_board(int gboard_x, int gboard_y, char player_color, struct gmkgame **gboard, list <struct gmkgame> gmkplay_list){
	//Test CJSON
	cJSON *root = NULL;
	cJSON *tx_body = NULL;
	//int i_rand = rand() % arr_size;//select a random contract in array
	/* Our object of block header: */
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "txobj", tx_body = cJSON_CreateObject());
	cJSON_AddStringToObject(tx_body, "scid", "F0C119591C29FE7FA0D17B69ABDE718E39017E2A74027CC79A33406B87A2AC60");
	cJSON_AddNumberToObject(tx_body, "size", 0);
	///////////////////Finish tx json package//////////////////////////////////////////////////////////
	/* declarations */
	char *out = NULL;

	/* unformatted print */
	out = cJSON_PrintUnformatted(root);//cJSON_Print(root);

	printf("%s\n", out);

	cJSON_Delete(root);
	//End Test CJSON//
	cout << "Gomoku - XTblock's dAI Framework v0.5" << endl;
	cout << "Total board game cells: " << gboard_x*gboard_y << endl;
	//cout << "Total winning patterns: " << gmk_winning_pattern_list.size() << endl;
	//cout << "Player color: " << player_color << endl;
	//cout << "Player chess: " << player_chess << endl << "Machine chess: " << machine_chess << endl;
	cout << "Total occupied cells: " << gmkplay_list.size( )<< endl;
	//showgame(gmkplay_list);

	fflush(stdout);
	//counting to find winning patterns
	int win_cnt=0, prev_player= 0;
	//check vector x
	cout << endl;
	for(int j=gboard_y-1; j>=0; j--){
		//cout << x-(i+1) << " ";
		printf("%2d ", j+1);//y-(j+1));
		for(int i=0; i< gboard_x; i++){
			if(gboard[j][i].player== 0) cout << "[" << " " << "]";
			else if(gboard[j][i].player == 1) cout << " " << "X" << " ";
			else if(gboard[j][i].player == -1) cout << " " << "O" << " ";
		}
		cout << endl;
	}
	printf("   ");

	for(int p=0; p< gboard_x; p++) printf("%2d ", p+1);//cout << "[" << p << "]";
	cout << endl;
}

//function for printing the elements in a list
void showgame(list <struct gmkgame> g)
{
    list <struct gmkgame> :: iterator it;
    //cout << "Total occupied cells: " << g.size() << endl;
    for(it = g.begin(); it != g.end(); ++it) {
        //cout << '\t' << it->game_id;
        cout << "("<< it->x;
        cout << ",";
        cout << it->y;
        cout << "):" << it->player;
        cout << "; ";
    }
    //cout << '\n';
}

//function for printing the elements in a list
void show_winning_patterns(list <struct gmk_winning_pattern> g)
{
    list <struct gmk_winning_pattern> :: iterator it;
    //cout << "Total occupied cells: " << g.size() << endl;
    for(it = g.begin(); it != g.end(); ++it) {
    	for(int i=0; i< TOKEN_SIZE; i++){
    		cout << it->cell[i].x << "," << it->cell[i].y << " ";
    	}
        cout << '\n';
    }
}

void print_winning_pattern(struct gmk_winning_pattern g){
	cout << g.pattern_id << " | ";
	for(int i=0; i< TOKEN_SIZE; i++){
		cout << g.cell[i].x << "," << g.cell[i].y << " ";
	}
	cout << "(" << g.n_occupied << ")" << "(" << g.weight << ")" << "(" << g.occupied_pattern << ")";
}

void log_winning_pattern(char filename[50], list <struct gmk_winning_pattern> *gmk_for_machine){
	ofstream myfile;
	myfile.open (filename, std::ofstream::trunc );

	list <struct gmk_winning_pattern> :: iterator it;

	for(it = gmk_for_machine->begin(); it != gmk_for_machine->end(); ++it){
		for(int i=0; i< TOKEN_SIZE; i++)
			myfile << it->cell[i].x << "," << it->cell[i].y << " ";

		myfile << "(" << it->n_occupied << ")" << "(" << it->weight << ")"<< ": " << it->vector << endl;
	}
	myfile.close();
}

void fire_top_moves(char filename[50], std::list <struct tactic_weight> *get_tactic_moves){
	ofstream myfile;
	myfile.open (filename, std::ofstream::trunc );

	list <struct tactic_weight> :: iterator itg;
	list <struct gmk_winning_pattern> :: iterator it;

	//cout << endl << endl << "Returned top moves for next player's ply calculation..." << endl;
	for(itg = get_tactic_moves->begin(); itg != get_tactic_moves->end(); ++itg) {
		if(itg->player_pt == 0) itg->player_pt =1;
		//if(itg->machine_pt == 0) itg->machine_pt = 1;
		myfile << (float)itg->machine_pt/(float)itg->player_pt << ",";
	}
	//cout << endl;

	/*
	for(it = gmk_for_machine->begin(); it != gmk_for_machine->end(); ++it){
		for(int i=0; i< TOKEN_SIZE; i++)
			myfile << it->cell[i].x << "," << it->cell[i].y << " ";

		myfile << "(" << it->n_occupied << ")" << "(" << it->weight << ")"<< ": " << it->vector << endl;
	}*/
	myfile.close();
}

//function for finding related winning patterns with the cell
int find_patterns(list <struct gmk_winning_pattern> g, struct gmkgame *cell)
{
	int cnt= 0;
    list <struct gmk_winning_pattern> :: iterator it;
    //cout << "Total occupied cells: " << g.size() << endl;
    for(it = g.begin(); it != g.end(); ++it) {
    	for(int i=0; i< TOKEN_SIZE; i++){
			if(cell->x == it->cell[i].x && cell->y==it->cell[i].y){
				//print_winning_pattern(*it);
				cell->player= it->cell[i].player;
				//cout << '\n';
				cnt ++;
			}else cell->player= 0;
    	}
    }
    //if(cnt >0) cout << "Number of related patterns: " << cnt << endl;

    return cnt;
}

//////////////////////////////////
int set_n_occupied(list <struct victory_threats> *vct_search, list <struct gmk_winning_pattern> *winning_list, struct gmkgame *cell, int machine_chess, int player_chess){
	int cnt= 0;
	list <struct victory_threats> :: iterator itvct;
	list <struct gmk_winning_pattern> :: iterator it, itm, itp;

	for(it = winning_list->begin(); it != winning_list->end(); ++it) {
		for(int i=0; i< TOKEN_SIZE; i++){
			if(cell->x == it->cell[i].x && cell->y==it->cell[i].y){
				cnt ++;
				it->n_occupied++;
				it->weight+= cell->player;
				it->cell[i].player= cell->player;

				if(it->n_occupied == abs(it->weight)){
					it->occupied_pattern += pow(10, TOKEN_SIZE - (i+1));

					for(itvct = vct_search->begin(); itvct != vct_search->end(); ++itvct) {
						//int count_i=0;
						for(itm = itvct->patterns[it->vector].begin(); itm != itvct->patterns[it->vector].end(); ++itm) {
							if(itm->pattern_id == it->pattern_id){
								//cout << ++count_i << "<>" << i << " Updating: "<< itm->pattern_id  << " <> " << it->pattern_id << endl;
								itm->n_occupied = it->n_occupied;
								itm->weight = it->weight;
								itm->cell[i].player = it->cell[i].player;
								itm->occupied_pattern = it->occupied_pattern;
							}
						}
					}
				}
				else{
					it->occupied_pattern = 0;//decayed
					it->decayed = 1;

					for(itvct = vct_search->begin(); itvct != vct_search->end(); ++itvct) {
						for(itm = itvct->patterns[it->vector].begin(); itm != itvct->patterns[it->vector].end(); ){//++itm) {
							if(itm->pattern_id == it->pattern_id){
								//cout << itm->pattern_id  << " <> " << it->pattern_id << endl;
								//cout << cnt << "set occupied " << cell->player << " <"<< it->decayed << "> "<< it->cell[i].player << " | ";
								//cout<< "Erasing: ";
								//print_winning_pattern(*itm);
								//cout << endl;
								itm = itvct->patterns[it->vector].erase(itm);
							}else itm++;
						}
					}
				}

				//cout << cnt << "set occupied " << cell->player << " <"<< it->decayed << "> "<< it->cell[i].player << " | ";

				//print_winning_pattern(*it);
				//cout << endl;

				break;
			}
		}
	}
	//////////////////////////////
	for(itvct = vct_search->begin(); itvct != vct_search->end(); ){//++itvct) {
		if(cell->x == itvct->cell.x && cell->y==itvct->cell.y){
			itvct->cell.player = cell->player;

			itvct = vct_search->erase(itvct);

			break;
		}else itvct++;
	}

	////////////////////////////////////
	/*
	cout << "[Set Occupied] Number of empty cells: " << vct_search->size() << endl;

	for(itvct = vct_search->begin(); itvct != vct_search->end(); ++itvct) {
		cout << itvct->cell.x << "," << itvct->cell.y << ": ";
		cout << endl << "patterns ";
		for(int i =0; i< TOTAL_VECTOR; i++){
			cout << i << ": " << itvct->patterns[i].size() << "\t";
			for(itm = itvct->patterns[i].begin(); itm != itvct->patterns[i].end(); ++itm){
				print_winning_pattern(*itm);
				cout << endl;
			}
		}
		cout << endl;
	}
	*/
	//if(cnt >0) cout << "Number of related patterns: " << cnt << endl;

	return cnt;
}

bool compare_pattern(struct gmk_winning_pattern &p1, struct gmk_winning_pattern &p2){
	return (p1.weight < p2.weight);
}

bool compare_tactic_machine_pt(struct tactic_weight &p1, struct tactic_weight &p2){
	return (p1.machine_pt < p2.machine_pt);
}

bool compare_tactic_machine_pt_level(struct tactic_weight &p1, struct tactic_weight &p2){
	return (p1.machine_pt_level < p2.machine_pt_level);
}

bool compare_tactic_player_pt(struct tactic_weight &p1, struct tactic_weight &p2){
	return (p1.player_pt < p2.player_pt);
}

bool compare_tactic_player_pt_level(struct tactic_weight &p1, struct tactic_weight &p2){
	return (p1.player_pt_level < p2.player_pt_level);
}

bool compare_tactic_ratio_pt(struct tactic_weight &p1, struct tactic_weight &p2){
	return (p1.ratio < p2.ratio);
}

bool compare_machine_uct(struct tactic_weight &p1, struct tactic_weight &p2){
	return (p1.machine_uct < p2.machine_uct);
}

bool compare_player_uct(struct tactic_weight &p1, struct tactic_weight &p2){
	return (p1.player_uct < p2.player_uct);
}

long tactic_play(int gboard_x, int gboard_y, struct gmkgame **gboard, list <struct gmk_winning_pattern> gmk_for_machine, int advantage_i, struct gmkgame cell, int machine_chess, int player_chess, int *get_highest_pattern_level){
	long pt=0, prev_pt=0;
	int n_spy =0, n_consecutive = 0;

	//ofstream myfile;
	//myfile.open ("machine_plays.txt", std::ofstream::trunc );

	if(abs(machine_chess)>0) cell.player= machine_chess;
	else if(abs(player_chess)>0) cell.player = player_chess;

	int cnt=0;
	//int machine_advantage_cnt= 0, player_advantage_cnt= 0;
	list <struct gmk_winning_pattern> new_advantages_list;
	list <struct gmk_winning_pattern> :: iterator it;

	//tactic set occupied
	//cout << "Set occupied" << endl;

	for(it = gmk_for_machine.begin(); it != gmk_for_machine.end(); ++it) {
		int spy_check = 0;

		switch (it->vector){
			case 0:
				if(it->cell[0].y-1 >=0){
					if(gboard[it->cell[0].y-1][it->cell[0].x].player != 0 && (machine_chess + player_chess) != gboard[it->cell[0].y-1][it->cell[0].x].player){
						spy_check = 1;
						it->blocking_left =1;
						//cout << gboard[it->cell[0].y-1][it->cell[0].x].player << " " << (machine_chess + player_chess) << " ";
						//cout << "(" << it->vector << "down)" << "Spy on: " << it->cell[0].x << " " << it->cell[0].y-1 << endl;
					}
				}
				if(spy_check ==0){
					if(it->cell[TOKEN_SIZE-1].y+1 < gboard_y){
						if(gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x].player != 0 && (machine_chess + player_chess) != gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x].player){
							spy_check = 1;
							it->blocking_right =1;
							//cout << gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x].player << " " << (machine_chess + player_chess) << " ";
							//cout << "(" << it->vector << "up)" << "Spy on: " << it->cell[TOKEN_SIZE-1].x << " " << it->cell[TOKEN_SIZE-1].y+1 << endl;
						}
					}
				}
				break;
			case 1:
				if(it->cell[0].x-1 >= 0){
					if(gboard[it->cell[0].y][it->cell[0].x-1].player != 0 && (machine_chess + player_chess) != gboard[it->cell[0].y][it->cell[0].x-1].player){
						spy_check = 1;
						it->blocking_left =1;
						//cout << gboard[it->cell[0].y][it->cell[0].x-1].player << " " << (machine_chess + player_chess) << " ";
						//cout << "(" << it->vector << "down)" << "Spy on: " << it->cell[0].x-1 << " " << it->cell[0].y << endl;
					}
				}
				if(spy_check ==0){
					if(it->cell[TOKEN_SIZE-1].x+1 < gboard_x){
						if(gboard[it->cell[TOKEN_SIZE-1].y][it->cell[TOKEN_SIZE-1].x+1].player != 0 && (machine_chess + player_chess) != gboard[it->cell[TOKEN_SIZE-1].y][it->cell[TOKEN_SIZE-1].x+1].player){
							spy_check = 1;
							it->blocking_right =1;
							//cout << gboard[it->cell[TOKEN_SIZE-1].y][it->cell[TOKEN_SIZE-1].x+1].player << " " << (machine_chess + player_chess) << " ";
							//cout << "(" << it->vector << "up)" << "Spy on: " << it->cell[TOKEN_SIZE-1].x+1 << " " << it->cell[TOKEN_SIZE-1].y << endl;
						}
					}
				}
				break;
			case 2:
				if(it->cell[0].x-1 >= 0 && it->cell[0].y-1 >=0){
					if(gboard[it->cell[0].y-1][it->cell[0].x-1].player != 0 && (machine_chess + player_chess) != gboard[it->cell[0].y-1][it->cell[0].x-1].player){
						spy_check = 1;
						it->blocking_left =1;
						//cout << gboard[it->cell[0].y-1][it->cell[0].x-1].player << " " << (machine_chess + player_chess) << " ";
						//cout << "(" << it->vector << "down)" << "Spy on: " << it->cell[0].x-1 << " " << it->cell[0].y-1 << endl;
					}
				}

				if(spy_check ==0){
					if(it->cell[TOKEN_SIZE-1].x+1 < gboard_x && it->cell[TOKEN_SIZE-1].y+1 < gboard_y){
						if(gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x+1].player != 0 && (machine_chess + player_chess) != gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x+1].player){
							spy_check = 1;
							it->blocking_right =1;
							//cout << gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x+1].player << " " << (machine_chess + player_chess) << " ";
							//cout << "(" << it->vector << "up)" << "Spy on: " << it->cell[TOKEN_SIZE-1].x+1 << " " << it->cell[TOKEN_SIZE-1].y+1 << endl;
						}
					}
				}
				break;
			case 3:
				if(it->cell[0].y-1 >=0 && it->cell[0].x+1 < gboard_x){
					if(gboard[it->cell[0].y-1][it->cell[0].x+1].player != 0 && (machine_chess + player_chess) != gboard[it->cell[0].y-1][it->cell[0].x+1].player){
						spy_check = 1;
						it->blocking_left =1;
						//cout << gboard[it->cell[0].y-1][it->cell[0].x+1].player << " " << (machine_chess + player_chess) << " ";
						//cout << "(" << it->vector << "down)" << "Spy on: " << it->cell[0].x+1 << " " << it->cell[0].y-1 << endl;
					}
				}
				if(spy_check ==0){
					if(it->cell[TOKEN_SIZE-1].x-1 >=0 && it->cell[TOKEN_SIZE-1].y+1 < gboard_y){
						if(gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x-1].player != 0 && (machine_chess + player_chess) != gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x-1].player){
							spy_check = 1;
							it->blocking_right =1;
							//cout << gboard[it->cell[TOKEN_SIZE-1].y+1][it->cell[TOKEN_SIZE-1].x-1].player << " " << (machine_chess + player_chess) << " ";
							//cout << "(" << it->vector << "up)" << "Spy on: " << it->cell[TOKEN_SIZE-1].x-1 << " " << it->cell[TOKEN_SIZE-1].y+1 << endl;
						}
					}
				}
				break;
		}

		for(int i=0; i< TOKEN_SIZE; i++){
			if(cell.x == it->cell[i].x && cell.y==it->cell[i].y){
				cnt ++;
				it->n_occupied++;
				it->weight+= cell.player;
				it->cell[i].player= cell.player;

				if(it->n_occupied == abs(it->weight)) it->occupied_pattern += pow(10, TOKEN_SIZE - (i+1));
				//else it->occupied_pattern = 0;//decayed

				if(spy_check ==1){
					//it->spy= 1;
					it->spy++;
					n_spy++;
				}

				if(i == 0 && it->n_occupied > 1){
					if(it->cell[i+1].player ==0) it->non_consecutive = 1;
				}
				else if(i==TOKEN_SIZE-1  && it->n_occupied > 1){
					if(it->cell[i-1].player ==0) it->non_consecutive = 1;
				}
				else{
					if((it->cell[i+1].player ==0 || it->cell[i-1].player ==0) && it->n_occupied > 1) it->non_consecutive = 1;
				}

				if(it->spy !=1 && it->non_consecutive ==1) n_consecutive++;

				//if(it->spy != 1)
				new_advantages_list.push_back(*it);
				//else if (it->spy == 1 && advantage_i >1) new_advantages_list.push_back(*it);
				/*
				myfile << cnt << " | (" << cell.x  << "," << cell.y << ")";
				for(int q=0; q< TOKEN_SIZE; q++){
					myfile << it->cell[q].x << "," << it->cell[q].y << " ";
				}
				myfile << "(" << it->n_occupied << ")" << "(" << it->weight << ")";
				myfile << endl;
				*/
				//it= gmk_for_machine.erase(it);

				break;
			}
		}
	}

	if(new_advantages_list.size() > 0){
		if(n_spy > 0 && advantage_i - 1 == 0){
			if(new_advantages_list.size() - n_spy > 0) (*get_highest_pattern_level) = advantage_i+1;
			else{
				/*
				if(advantage_i+1 == TOKEN_SIZE - 1){
					(*get_highest_pattern_level) = advantage_i+1;
					n_spy--;
					n_consecutive--;
				}
				else*/
					(*get_highest_pattern_level) = advantage_i;
			}
		}
		else (*get_highest_pattern_level) = advantage_i+1;
		//if(abs(player_chess) > 0) myfile << (*get_highest_pattern_level) << " player's advantage: " << new_advantages_list.size() << endl;
		//else if(abs(machine_chess) > 0) myfile << (*get_highest_pattern_level) << " machine's advantage: " << new_advantages_list.size() << endl;

		/*
		if((*get_highest_pattern_level) < TOKEN_SIZE - 1){
			pt+= (new_advantages_list.size() - n_spy - n_consecutive) * w_tactic_open[advantage_i+1] + (long)((float)(n_spy + n_consecutive)*(float)w_tactic_blocking[advantage_i+1]);
		}
		else{
			pt+= new_advantages_list.size() * w_tactic_open[advantage_i+1];
		}
		*/

		//calculate weight (pt)
		long top_vector_score[TOTAL_VECTOR];
		for(int t =0; t< TOTAL_VECTOR; t++){
			top_vector_score[t] = 0;
		}

		for(it = new_advantages_list.begin(); it != new_advantages_list.end(); ++it) {
			for(int k=0; k< size_of_k_com_w_array; k++){
				if(k_com_w_array[k].k_com == it->occupied_pattern){
					/*
					if(abs(player_chess) > 0) cout << "P: ";
					if(abs(machine_chess) > 0) cout << "M: ";

					print_winning_pattern(*it);	cout << "\t" << "("<< cell.x << ", "<< cell.y << ")\t";// +" << k_com_w_array[k].opened_w << "\t";

					if(it->vector ==0) cout << " | ";
					if(it->vector ==1) cout << " __ ";
					if(it->vector ==2) cout << " / ";
					if(it->vector ==3) cout << " \\ ";

					cout << k_com_w_array[k].k_com << " occupied pattern: " << it->occupied_pattern;
					*/
					if(it->spy==0){
						pt += k_com_w_array[k].opened_w;// * (*get_highest_pattern_level);
						if(top_vector_score[it->vector] < k_com_w_array[k].opened_w)  top_vector_score[it->vector] = k_com_w_array[k].opened_w;
					}
					else if(it->spy == 1){
						if(it->blocking_left ==1){
							pt += k_com_w_array[k].blocking_left_w;// * advantage_i;//(*get_highest_pattern_level);
							if(top_vector_score[it->vector] < k_com_w_array[k].blocking_left_w)  top_vector_score[it->vector] = k_com_w_array[k].blocking_left_w;
						}
						else if(it->blocking_right ==1){
							pt += k_com_w_array[k].blocking_right_w;// * advantage_i;//(*get_highest_pattern_level);
							if(top_vector_score[it->vector] < k_com_w_array[k].blocking_right_w)  top_vector_score[it->vector] = k_com_w_array[k].blocking_right_w;
						}
					}
					else if(it->spy == 2){
						if(it->blocking_left > it->blocking_right){
							pt += k_com_w_array[k].blocking_right_w;// * advantage_i;//(*get_highest_pattern_level);
							if(top_vector_score[it->vector] < k_com_w_array[k].blocking_right_w)  top_vector_score[it->vector] = k_com_w_array[k].blocking_right_w;
						}
						else{
							pt += k_com_w_array[k].blocking_left_w;// * advantage_i;//(*get_highest_pattern_level);
							if(top_vector_score[it->vector] < k_com_w_array[k].blocking_left_w)  top_vector_score[it->vector] = k_com_w_array[k].blocking_left_w;
						}
					}

					//cout << " sub-pt: " << pt << endl;
				}
			}
		}

		pt = 0;
		for(int t =0; t< TOTAL_VECTOR; t++){
			pt += top_vector_score[t];
		}
		//cout << " total-pt: " << pt << endl;
	}
	//considering to hide this part
	///////////////////////////////
	/*else if(gmk_for_machine.size() > 0){

		(*get_highest_pattern_level) = advantage_i;

		if(abs(player_chess) > 0) myfile << (*get_highest_pattern_level) << " player's advantage: " << gmk_for_machine.size() << endl;
		else if(abs(machine_chess) > 0) myfile << (*get_highest_pattern_level) << " machine's advantage: " << gmk_for_machine.size() << endl;

		//pt+= gmk_for_machine.size() * w_tactic_open[advantage_i];
	}*/
	/////////////////////////////////
	//myfile.close();

	return pt;
}

///////////////////////////////////

//search next playing cell for machine
int machine_play(list <struct victory_threats> *vct_search, int n_ply, int started_chess, int gboard_x, int gboard_y, struct gmkgame **gboard, list <struct gmk_winning_pattern> *gmk_for_machine, struct gmkgame *cell, int machine_chess, int player_chess, int cur_move, struct gmkgame *next_play_proposal, std::list <struct tactic_weight> *get_tactic_moves, int max_tmoves, int total_max_tmoves, int *original_machine_highest_level, int *original_player_highest_level)
{
	int rs= 0;
	int cnt=0;

	list <struct gmk_winning_pattern> tactic_gmk_for_machine= *gmk_for_machine;
	//list <struct gmk_winning_pattern> vct_gmk_for_machine= *gmk_for_machine;

	struct gmkgame tactic_cell, tactic_next_play;

	log_winning_pattern((char *)"winning_patterns.txt", gmk_for_machine);
	log_winning_pattern((char *)"winning_patterns-clone.txt", &tactic_gmk_for_machine);

	int machine_advantage_cnt= 0, player_advantage_cnt= 0;
	list <struct gmk_winning_pattern> sorted_advantages_for_machine[TOKEN_SIZE];
	list <struct gmk_winning_pattern> sorted_advantages_for_player[TOKEN_SIZE];

	list <struct gmk_winning_pattern> :: iterator it, itm;
	list <struct tactic_weight> tactic_with_player_pt;
	list <struct tactic_weight> vct_with_player_pt;

	list <struct victory_threats> vct_search_branch[10];
	list <struct gmk_winning_pattern> tactic_gmk_for_machine_branch[10];


	//check highest token level
	int player_highest_token = 0, machine_highest_token = 0;

	cnt=0;
	//for(it = gmk_for_machine->begin(); it != gmk_for_machine->end(); ++it) {
	for(it = tactic_gmk_for_machine.begin(); it != tactic_gmk_for_machine.end(); ++it) {
		if(it->n_occupied > 0){
			if(abs(it->weight) == it->n_occupied){
				cnt++;
				if(abs(machine_chess + it->weight) > abs(it->weight)){
					machine_advantage_cnt++;
					sorted_advantages_for_machine[abs(it->weight)-1].push_back(*it);

					//cout << machine_advantage_cnt << " machine | ";
					//print_winning_pattern(*it);

					//if(it->vector ==0) cout << " | ";
					//if(it->vector ==1) cout << " __ ";
					//if(it->vector ==2) cout << " / ";
					//if(it->vector ==3) cout << " \\ ";

					//cout << '\n';

				}
				else if(abs(player_chess + it->weight) > abs(it->weight)){
					player_advantage_cnt++;
					sorted_advantages_for_player[abs(it->weight)-1].push_back(*it);

					//cout << player_advantage_cnt << " player | ";
					//print_winning_pattern(*it);

					//if(it->vector ==0) cout << " | ";
					//if(it->vector ==1) cout << " __ ";
					//if(it->vector ==2) cout << " / ";
					//if(it->vector ==3) cout << " \\ ";

					//cout << '\n';
				}

			}else {
				if(abs(it->weight) < it->n_occupied){
					//it= gmk_for_machine->erase(it);
				}
			}
		}
	}

	//cout << "Before deploying tactic..." << endl;
	for(int i=TOKEN_SIZE-1; i>=0; --i){
		if(player_highest_token == 0 && sorted_advantages_for_player[i].size()>0){
			for(it = sorted_advantages_for_player[i].begin(); it != sorted_advantages_for_player[i].end(); ++it) {
				if(it->spy > 0){
					player_highest_token = i-1;
				}else{
					player_highest_token = i; break;
				}
			}
			//player_highest_token = i;
			//cout << "highest: "<< player_highest_token << " player's advantage: " << sorted_advantages_for_player[i].size() << endl;
		}

		if(machine_highest_token == 0 && sorted_advantages_for_machine[i].size()>0){

			for(it = sorted_advantages_for_machine[i].begin(); it != sorted_advantages_for_machine[i].end(); ++it) {
				if(it->spy > 0){
					machine_highest_token = i-1;
				}else{
					machine_highest_token = i; break;
				}
			}
			//cout << "highest: " << machine_highest_token << " machine's advantage: " << sorted_advantages_for_machine[i].size() << endl;
		}

		if(player_highest_token > 0 && machine_highest_token > 0) break;
	}

	(*original_machine_highest_level) = machine_highest_token;
	(*original_player_highest_level) = player_highest_token;
	////////////////////////////////////////////////
	//Game Over

	if(player_highest_token == TOKEN_SIZE-1){
		rs = player_chess;
		//break;
		return rs;
	}
	/*
	else if(machine_highest_token == TOKEN_SIZE-1){
		rs = machine_chess;
		//break;
		return rs;
	}*/
	//End Game//////////////////////////

	///////////////////////////////////////////////
	//start tactic play calculation
	//calculate 2 pattern levels
	//int level_cal = 0;
	/////////////////////////////////////////////////
	long top_vector_score[TOTAL_VECTOR];
	for(int t =0; t< TOTAL_VECTOR; t++){
		top_vector_score[t] = 0;
	}

	for(int i=TOKEN_SIZE-1; i>=0; i--){
		//if(level_cal > 0) level_cal++;
		if(sorted_advantages_for_machine[i].size()>0){
			//if(level_cal == 0) level_cal++;

			//cout << endl << i << " machine's advantage: " << sorted_advantages_for_machine[i].size() << endl;

			for(it = sorted_advantages_for_machine[i].begin(); it != sorted_advantages_for_machine[i].end(); ++it) {
				for(int j=0; j< TOKEN_SIZE; j++){
					//cout << endl << "3: " << it->cell[j].x << "," << it->cell[j].y << ": "<< it->cell[j].player << endl;
					if(it->cell[j].player == 0){
						struct tactic_weight temp_tactic_weight;
						temp_tactic_weight.player_pt = 0;
						temp_tactic_weight.ratio = 0;
						temp_tactic_weight.n_visited = 1;
						temp_tactic_weight.player_pt_level =0;
						temp_tactic_weight.machine_pt_level =0;
						temp_tactic_weight.machine_n_fork = 0;
						temp_tactic_weight.player_n_fork = 0;
						temp_tactic_weight.n_op_decayed = 0;
						temp_tactic_weight.pattern_id = it->pattern_id;
						int pattern_vector = it->vector;

						//if(i==3) cout << endl << "3: " << it->cell[j].x << "," << it->cell[j].y << ": "<< it->cell[j].player << endl;
						temp_tactic_weight.machine_pt = tactic_play(gboard_x, gboard_y, gboard, sorted_advantages_for_machine[i], i, it->cell[j], machine_chess, 0, &temp_tactic_weight.machine_pt_level);

						if(top_vector_score[it->vector] < temp_tactic_weight.machine_pt)  top_vector_score[it->vector] = temp_tactic_weight.machine_pt;

						//cout << "machine pt level"<< temp_tactic_weight.machine_pt_level << endl;;

						temp_tactic_weight.cell.x = it->cell[j].x;
						temp_tactic_weight.cell.y = it->cell[j].y;

						list <struct tactic_weight> :: iterator itw;
						list <int> :: iterator itvec;
						int existed_it= 0;

						if(tactic_with_player_pt.size() > 0)
						for(itw = tactic_with_player_pt.begin(); itw != tactic_with_player_pt.end(); ++itw) {
							if(itw->pattern_vector_list.size()> 0){
								//cout << "(" << itw->cell.x << "," << itw->cell.y << ")";
								//cout << " -> list of vector: ";
								for(itvec = itw->pattern_vector_list.begin(); itvec != itw->pattern_vector_list.end(); ++itvec) {
									//cout << (*itvec) << " ";
								}
								//cout << endl;
							}
							if(itw->cell.x == it->cell[j].x && itw->cell.y==it->cell[j].y){
								int flag_new_vector = 1;

								for(itvec = itw->pattern_vector_list.begin(); itvec != itw->pattern_vector_list.end(); ++itvec) {
									//cout << "comparing "<< (*itvec) << " vs " << pattern_vector << endl;
									if((*itvec) == pattern_vector){
										//cout << "existed vector "<< (*itvec) << " " << endl;
										flag_new_vector = 0;
										break;
									}
								}

								//if(itvec == temp_tactic_weight.pattern_vector_list.end()) temp_tactic_weight.n_fork++;

								if(flag_new_vector == 1 && temp_tactic_weight.machine_pt_level >=2){
									if(itw->machine_pt_level < temp_tactic_weight.machine_pt_level) itw->machine_pt_level = temp_tactic_weight.machine_pt_level;
									temp_tactic_weight.machine_n_fork++;
									itw->machine_n_fork++;// = temp_tactic_weight.n_fork;
									itw->machine_pt += temp_tactic_weight.machine_pt;

									itw->pattern_vector_list.push_back(pattern_vector);
									//cout << endl << "new vector "<< pattern_vector << endl;
								}

								/*
								if(started_chess == machine_chess){
									if(itvec == temp_tactic_weight.pattern_vector_list.end() && itw->player_pt_level >=1){
										temp_tactic_weight.n_fork++;
										itw->n_fork++;// = temp_tactic_weight.n_fork;
										//if(temp_tactic_weight.player_pt > itw->player_pt_level) itw->player_pt_level = temp_tactic_weight.player_pt;
									}
								}
								else{
									if(itvec == temp_tactic_weight.pattern_vector_list.end() && itw->player_pt_level >=1){
										temp_tactic_weight.n_fork++;
										itw->n_fork++;// = temp_tactic_weight.n_fork;
										//if(temp_tactic_weight.player_pt > itw->player_pt_level) itw->player_pt_level = temp_tactic_weight.player_pt;
									}
								}*/
								//if(itw->machine_pt_level>=2 && temp_tactic_weight.machine_pt_level >=2) temp_tactic_weight.n_fork++;

								//itw->machine_pt+= temp_tactic_weight.machine_pt;
								//cout << itw->machine_pt << endl;


								if(temp_tactic_weight.machine_n_fork > 1) {
									//itw->machine_pt += temp_tactic_weight.machine_pt * (temp_tactic_weight.machine_pt_level) * temp_tactic_weight.n_fork;
									if(started_chess == machine_chess)
									//itw->machine_pt += temp_tactic_weight.machine_pt * (long) pow(temp_tactic_weight.machine_n_fork, temp_tactic_weight.machine_n_fork);//pow if machine plays Black chess
									itw->machine_pt += temp_tactic_weight.machine_pt * (long) pow(temp_tactic_weight.machine_n_fork, temp_tactic_weight.machine_n_fork);//pow if machine plays Black chess
										//itw->machine_pt += temp_tactic_weight.machine_pt * temp_tactic_weight.machine_n_fork;
									else itw->machine_pt += temp_tactic_weight.machine_pt * temp_tactic_weight.machine_n_fork;
									//if(itw->machine_pt_level < temp_tactic_weight.machine_pt_level) itw->machine_pt += w_tactic_open[temp_tactic_weight.machine_pt_level+1]/2;//w_tactic_open[TOKEN_SIZE - 1]/2;//value a fork of 3 as 1/2 point of 5
									//else  itw->machine_pt += w_tactic_open[itw->machine_pt_level+1]/2;
								}
								else itw->machine_pt += temp_tactic_weight.machine_pt;
								//itw->machine_pt += temp_tactic_weight.machine_pt;

								//calculate pt for decaying opponent's chess groups
								list <struct gmk_winning_pattern> :: iterator itd;
								for(int t=TOKEN_SIZE-1; t>=0; t--){
									for(itd = sorted_advantages_for_player[t].begin(); itd != sorted_advantages_for_player[t].end(); ++itd) {
										for(int q=0; q< TOKEN_SIZE; q++){
											if(itd->cell[q].x == temp_tactic_weight.cell.x && itd->cell[q].y == temp_tactic_weight.cell.y){
												temp_tactic_weight.n_op_decayed++;

												for(int n=0; n< size_of_k_com_w_array; n++){
													if(k_com_w_array[n].k_com == itd->occupied_pattern){
														//if(started_chess == machine_chess)
														itw->machine_pt += k_com_w_array[n].opened_w;// * 1.05;
														//else itw->machine_pt += k_com_w_array[n].opened_w * itw->n_fork;//times by n=100 in case machine is White chess
													}
												}

												break;
											}
										}
									}
								}

								/*
								if(itw->machine_pt_level < temp_tactic_weight.machine_pt_level){
									//itw->machine_pt += temp_tactic_weight.machine_pt;
									itw->machine_pt_level = temp_tactic_weight.machine_pt_level;
								}
								else if(itw->machine_pt_level == temp_tactic_weight.machine_pt_level) {
									//itw->machine_pt += temp_tactic_weight.machine_pt;

									//if(temp_tactic_weight.machine_pt_level < TOKEN_SIZE -1)
										//itw->machine_pt += w_tactic_open[temp_tactic_weight.machine_pt_level+1];
									//else itw->machine_pt += w_tactic_open[temp_tactic_weight.machine_pt_level];

								}*/

								existed_it = 1;
								break;
							}
						}

						/////////////////////////////////
						if(existed_it!=1){
							if(temp_tactic_weight.machine_pt_level >=2){
								temp_tactic_weight.machine_n_fork++;
								temp_tactic_weight.pattern_vector_list.push_back(pattern_vector);
								//cout << "(" << it->cell[j].x<< "," << it->cell[j].y << ")" << " new vector: " << pattern_vector << endl;
							}

							tactic_with_player_pt.push_back(temp_tactic_weight);
						}
					}
				}
			}
		}
		//only calculate the 2 highest pattern level
		//if(level_cal == 2) break;
	}

	/////////////////////////////
	//level_cal = 0;
	for(int t =0; t< TOTAL_VECTOR; t++){
		top_vector_score[t] = 0;
	}

	for(int i=TOKEN_SIZE-1; i>=0; i--){
		//if(level_cal > 0) level_cal++;
		if(sorted_advantages_for_player[i].size()>0){
			//if(level_cal == 0) level_cal++;

			//cout << endl << i << " player's advantage: " << sorted_advantages_for_player[i].size() << endl;

			for(it = sorted_advantages_for_player[i].begin(); it != sorted_advantages_for_player[i].end(); ++it) {
				for(int j=0; j< TOKEN_SIZE; j++){
					//if(i==3)
						//cout << endl << "3: " << it->cell[j].x << "," << it->cell[j].y << ": "<< it->cell[j].player << endl;
					if(it->cell[j].player == 0){
						struct tactic_weight temp_tactic_weight;
						temp_tactic_weight.machine_pt= 0;
						temp_tactic_weight.ratio = 0;
						temp_tactic_weight.n_visited = 1;
						temp_tactic_weight.player_pt_level =0;
						temp_tactic_weight.machine_pt_level =0;
						temp_tactic_weight.machine_n_fork = 0;
						temp_tactic_weight.player_n_fork = 0;
						temp_tactic_weight.n_op_decayed = 0;
						temp_tactic_weight.pattern_id = it->pattern_id;
						int pattern_vector = it->vector;

						//if(i==3) cout << endl << "3: " << it->cell[j].x << "," << it->cell[j].y << endl;
						temp_tactic_weight.player_pt = tactic_play(gboard_x, gboard_y, gboard, sorted_advantages_for_player[i], i, it->cell[j], 0, player_chess, &temp_tactic_weight.player_pt_level);

						if(top_vector_score[it->vector] < temp_tactic_weight.player_pt)  top_vector_score[it->vector] = temp_tactic_weight.player_pt;

						//cout << "player pt level "<< temp_tactic_weight.player_pt_level << endl;

						temp_tactic_weight.cell.x = it->cell[j].x;
						temp_tactic_weight.cell.y = it->cell[j].y;

						list <struct tactic_weight> :: iterator itw;
						list <int> :: iterator itvec;
						int existed_it= 0;

						if(tactic_with_player_pt.size() > 0)
						for(itw = tactic_with_player_pt.begin(); itw != tactic_with_player_pt.end(); ++itw) {
							if(itw->pattern_vector_list.size()> 0){
								//cout << "(" << itw->cell.x << "," << itw->cell.y << ")";
								//cout << " -> list of vector: ";
								for(itvec = itw->pattern_vector_list.begin(); itvec != itw->pattern_vector_list.end(); ++itvec) {
									//cout << (*itvec) << " ";
								}
								//cout << endl;
							}
							if(itw->cell.x == it->cell[j].x && itw->cell.y==it->cell[j].y){
								int flag_new_vector = 1;
								for(itvec = itw->pattern_vector_list.begin(); itvec != itw->pattern_vector_list.end(); ++itvec) {
									//cout << "comparing "<< (*itvec) << " vs " << pattern_vector << endl;
									if((*itvec) == pattern_vector){
										//cout << "existed vector "<< (*itvec) << " " << endl;
										flag_new_vector = 0;
										break;
									}
								}

								if(flag_new_vector == 1 && temp_tactic_weight.player_pt_level >=2){
									if(itw->player_pt_level < temp_tactic_weight.player_pt_level) itw->player_pt_level = temp_tactic_weight.player_pt_level;
									temp_tactic_weight.player_n_fork++;
									itw->player_n_fork++;// = temp_tactic_weight.n_fork;
									itw->player_pt += temp_tactic_weight.player_pt;

									itw->pattern_vector_list.push_back(pattern_vector);
									//cout << endl << "new vector "<< pattern_vector << endl;
								}

								/*
								if(started_chess == machine_chess){
									if(itvec == temp_tactic_weight.pattern_vector_list.end() && itw->player_pt_level >=1){
										temp_tactic_weight.n_fork++;
										itw->n_fork++;// = temp_tactic_weight.n_fork;
										//if(temp_tactic_weight.player_pt > itw->player_pt_level) itw->player_pt_level = temp_tactic_weight.player_pt;
									}
								}
								else{
									if(itvec == temp_tactic_weight.pattern_vector_list.end() && itw->player_pt_level >=1){
										temp_tactic_weight.n_fork++;
										itw->n_fork++;// = temp_tactic_weight.n_fork;
										//if(temp_tactic_weight.player_pt > itw->player_pt_level) itw->player_pt_level = temp_tactic_weight.player_pt;
									}
								}*/

								//if(itw->player_pt_level>=2 && temp_tactic_weight.player_pt_level >=2) temp_tactic_weight.n_fork++;

								//itw->player_pt+= temp_tactic_weight.player_pt;
								//cout << itw->player_pt << endl;


								if(temp_tactic_weight.player_n_fork > 1){
									if(started_chess == machine_chess) itw->player_pt+= temp_tactic_weight.player_pt * temp_tactic_weight.player_n_fork;
									else
									//itw->player_pt += temp_tactic_weight.player_pt * (long) pow(temp_tactic_weight.player_n_fork, temp_tactic_weight.player_n_fork);//pow if machine plays White chess
									itw->player_pt += temp_tactic_weight.player_pt * (long) pow(temp_tactic_weight.player_n_fork, temp_tactic_weight.player_n_fork);//pow if machine plays White chess
									/////////////////////////////////////////
									//itw->player_pt += temp_tactic_weight.player_pt * temp_tactic_weight.player_pt_level * (long) pow(temp_tactic_weight.n_fork, temp_tactic_weight.n_fork);//pow if machine plays White chess
									//if(itw->player_pt_level < temp_tactic_weight.player_pt_level) itw->player_pt += w_tactic_open[temp_tactic_weight.player_pt_level+1]/2;//w_tactic_open[TOKEN_SIZE - 1]/2;//value a fork of 3 as 1/2 point of 5
									//else  itw->player_pt += w_tactic_open[itw->player_pt_level+1]/2;
									//itw->player_pt += w_tactic_open[TOKEN_SIZE - 1]/2;//value a fork of 3 as 1/2 point of 5
								}
								//else itw->player_pt += temp_tactic_weight.player_pt;

								/*
								if(itw->player_pt_level < temp_tactic_weight.player_pt_level){
									//itw->player_pt += temp_tactic_weight.player_pt;
									itw->player_pt_level = temp_tactic_weight.player_pt_level;
								}
								else if(itw->player_pt_level == temp_tactic_weight.player_pt_level) {
									//itw->player_pt += temp_tactic_weight.player_pt;

									//if(temp_tactic_weight.player_pt_level < TOKEN_SIZE-1)
										//itw->player_pt += w_tactic_open[temp_tactic_weight.player_pt_level+1];
									//else itw->player_pt += w_tactic_open[temp_tactic_weight.player_pt_level];
								}*/

								existed_it = 1;
								break;
							}
						}

						if(existed_it!=1){
							if(temp_tactic_weight.player_pt_level >=2){
								temp_tactic_weight.player_n_fork++;
								temp_tactic_weight.pattern_vector_list.push_back(pattern_vector);
								//cout << "(" << it->cell[j].x<< "," << it->cell[j].y << ")" << " new vector: " << pattern_vector << endl;
							}
							tactic_with_player_pt.push_back(temp_tactic_weight);
						}
					}
				}
			}
		}
		//only calculate the 2 highest pattern level
		//if(level_cal == 2) break;
	}


	//the list for both 2 sides
	list <struct tactic_weight> highest_player_pt_level_list;
	list <struct tactic_weight> highest_machine_pt_level_list;
	list <struct tactic_weight> :: iterator itw, itg;
	list <struct tactic_weight> :: reverse_iterator ritw, ritg;

	//if(cell->player == machine_chess)
	tactic_with_player_pt.sort(compare_tactic_machine_pt_level);
	//else if(cell->player == player_chess)
	//tactic_with_player_pt.sort(compare_tactic_player_pt_level);

	long biggest_player_pt= 0, biggest_machine_pt=0;

	machine_highest_token = tactic_with_player_pt.back().machine_pt_level;

	//for(itw = tactic_with_player_pt.end(); itw != tactic_with_player_pt.begin(); --itw) {
	for(itw = tactic_with_player_pt.begin(); itw != tactic_with_player_pt.end(); ++itw) {
		if(itw->machine_pt_level == machine_highest_token){
			highest_machine_pt_level_list.push_back(*itw);
			//cout << "("<< itw->machine_pt << "," << itw->machine_pt_level<< ":" << itw->player_pt << ","<< itw->player_pt_level<< ")" << itw->cell.x << "," << itw->cell.y << "; " ;
		}//else break;
	}

	tactic_with_player_pt.sort(compare_tactic_player_pt_level);

	player_highest_token = tactic_with_player_pt.back().player_pt_level;

	//cout << endl;

	//for(itw = tactic_with_player_pt.end(); itw != tactic_with_player_pt.begin(); --itw) {
	for(itw = tactic_with_player_pt.begin(); itw != tactic_with_player_pt.end(); ++itw) {
		if(itw->player_pt_level == player_highest_token){
			highest_player_pt_level_list.push_back(*itw);
			//cout << "("<< itw->machine_pt << "," << itw->machine_pt_level<< ":" << itw->player_pt << ","<< itw->player_pt_level<< ")" << itw->cell.x << "," << itw->cell.y << "; " ;
		}//else break;
	}

	//compare machine and player for the selection
	//highest_machine_pt_level_list.sort(compare_tactic_machine_pt);
	//biggest_machine_pt = highest_machine_pt_level_list.back().machine_pt;

	tactic_with_player_pt.sort(compare_tactic_machine_pt);
	biggest_machine_pt = tactic_with_player_pt.back().machine_pt;

	next_play_proposal->x = tactic_with_player_pt.back().cell.x;
	next_play_proposal->y = tactic_with_player_pt.back().cell.y;

	cout << "Max machine-pt: " << biggest_machine_pt << " ("<< next_play_proposal->x << "," << next_play_proposal->y << "," << tactic_with_player_pt.back().machine_n_fork << "," << tactic_with_player_pt.back().machine_pt_level << ")" << endl;

	int top_moves = 0;
	for(ritw = tactic_with_player_pt.rbegin(); ritw != tactic_with_player_pt.rend(); ++ritw) {
		ritw->n_visited++;
		get_tactic_moves->push_back(*ritw);
		if(++top_moves==max_tmoves) break;
	}

	struct tactic_weight empty_tactic;
	empty_tactic.machine_pt = 0;
	empty_tactic.player_pt = 1;

	/*
	if(top_moves < max_tmoves){
		for(int i = top_moves; i< max_tmoves; i++) get_tactic_moves->push_back(empty_tactic);
	}
	*/

	//highest_player_pt_level_list.sort(compare_tactic_player_pt);
	//biggest_player_pt = highest_player_pt_level_list.back().player_pt;

	tactic_with_player_pt.sort(compare_tactic_player_pt);
	biggest_player_pt = tactic_with_player_pt.back().player_pt;

	cout << "Max player-pt: " << biggest_player_pt << " ("<< tactic_with_player_pt.back().cell.x << "," << tactic_with_player_pt.back().cell.y << "," << tactic_with_player_pt.back().player_n_fork << "," << tactic_with_player_pt.back().player_pt_level << ")" << endl;

	top_moves= 0;
	bool found_f = false;

	for(ritw = tactic_with_player_pt.rbegin(); ritw != tactic_with_player_pt.rend(); ++ritw) {
		found_f = false;
		for(itg = get_tactic_moves->begin(); itg != get_tactic_moves->end(); ++itg) {
			if(itg->cell.x == ritw->cell.x && itg->cell.y == ritw->cell.y){
				found_f = true;
				break;
			}
		}

		if(found_f == false){
			get_tactic_moves->push_back(*ritw);
			if(++top_moves== max_tmoves) break;
		}
	}

	////////////////////////////////////////////////////////////////////
	//select next play by comparing points then by highest token rankings
	float prev_ratio = 0;

	if(started_chess == machine_chess){
		//if(biggest_machine_pt >= biggest_player_pt || biggest_machine_pt >= 1000000){
		if((float)biggest_machine_pt >= ((float)biggest_player_pt) || biggest_machine_pt >= 1000000){
			//next_play_proposal->x = highest_machine_pt_level_list.back().cell.x;
			//next_play_proposal->y = highest_machine_pt_level_list.back().cell.y;

		}else{
			next_play_proposal->x = tactic_with_player_pt.back().cell.x;
			next_play_proposal->y = tactic_with_player_pt.back().cell.y;

			//cout << next_play_proposal->x << " " << next_play_proposal->y << endl;
		}
	}
	else{
		//if((float)biggest_machine_pt >= ((float)biggest_player_pt * 1.15) || biggest_machine_pt >= 90000){//1000000){
		if((float)biggest_machine_pt >= ((float)biggest_player_pt) || biggest_machine_pt >= 90000){
			//next_play_proposal->x = highest_machine_pt_level_list.back().cell.x;
			//next_play_proposal->y = highest_machine_pt_level_list.back().cell.y;

		}else{
			next_play_proposal->x = tactic_with_player_pt.back().cell.x;
			next_play_proposal->y = tactic_with_player_pt.back().cell.y;

			//cout << next_play_proposal->x << " " << next_play_proposal->y << endl;
		}
	}

	/////////////////////////////////
	//print possible moves
	/*
	cout << endl << endl << "All Current Ply's Possible Moves: " << endl;

	for(itw = tactic_with_player_pt.begin(); itw != tactic_with_player_pt.end(); ++itw) {
		cout << "("<< itw->machine_pt << "," << itw->machine_n_fork << "," << itw->machine_pt_level << ":" << itw->player_pt << ","<< itw->player_n_fork << "," << itw->player_pt_level<< ")" << itw->cell.x << "," << itw->cell.y << ";  " ;
	}
	*/
	/////////////////////////////////
	//Victory Continuous Threats Search
	////////////////////////////////////

	list <struct victory_threats> :: iterator itvct;

	//for(int i=0; i< total_max_tmoves; i++){
	/*
	for(int i=0; i< get_tactic_moves->size(); i++){
		vct_search_branch[i] = *vct_search;
		tactic_gmk_for_machine_branch[i] = *gmk_for_machine;
	}*/

	int any_fork = 0;

	cout << endl << endl << n_ply << " Top moves for next ply calculation..." << endl;
	for(itg = get_tactic_moves->begin(); itg != get_tactic_moves->end(); ++itg) {
		if(itg->machine_n_fork > 1 || itg->player_n_fork > 1){
			any_fork = 1;cout << "fork " << any_fork << endl;
		}
		cout << "("<< itg->machine_pt << "," << itg->machine_n_fork << "," << itg->machine_pt_level << ":" << itg->player_pt << ","<< itg->player_n_fork << "," << itg->player_pt_level<< ")" << itg->cell.x << "," << itg->cell.y << ";  " ;
	}
	cout << endl;
	//cout << "[Machine Play] Number of empty cells: " << vct_search->size() << endl;
	//////////////////////////////////////////////
	int max_tactic_pt = 0;
	for(itg = get_tactic_moves->begin(); itg != get_tactic_moves->end(); ++itg) {
		if(max_tactic_pt < itg->player_pt) max_tactic_pt = itg->player_pt;
	}

	for(itg = get_tactic_moves->begin(); itg != get_tactic_moves->end(); ++itg) {
		if(max_tactic_pt < itg->machine_pt) max_tactic_pt = itg->machine_pt;
	}
	///////////////////////////////
	if(machine_highest_token == TOKEN_SIZE-1){
		rs = machine_chess;
		//break;
	}

	//need a vct search function

	std::list <struct tactic_weight> cp_get_tactic_moves = *get_tactic_moves;

	cout << endl << "fork " << any_fork << endl;
	if(rs==0){// && any_fork == 0 && machine_highest_token < 3 && player_highest_token < 3){
		//recursive play

		cur_move = player_chess;

		for(itg = cp_get_tactic_moves.begin(); itg != cp_get_tactic_moves.end(); ++itg) {
			//cout << endl << "Tactic selected: "<< itg->cell.x << "," << itg->cell.y << endl;
			list <struct gmk_winning_pattern> next_tactic_gmk_for_machine= tactic_gmk_for_machine;

			struct gmkgame **cp_gboard = (struct gmkgame **) malloc(sizeof(struct gmkgame *) *gboard_x);
			for (int v=0; v<gboard_y; v++) cp_gboard[v] = ( struct gmkgame *)malloc(gboard_y * sizeof( struct gmkgame));

			for(int r=0; r< gboard_y; r++){
				for(int c=0; c< gboard_x; c++){
					cp_gboard[r][c].c_weight = gboard[r][c].c_weight;
					cp_gboard[r][c].player= gboard[r][c].player;
					cp_gboard[r][c].x = gboard[r][c].x;
					cp_gboard[r][c].y = gboard[r][c].y;
				}
			}

			struct gmkgame get_next_play_proposal;
			get_next_play_proposal.c_weight=0;
			get_next_play_proposal.player=0;
			get_next_play_proposal.x=-1;
			get_next_play_proposal.y=-1;

			std::list <struct tactic_weight> get_next_tactic_moves;

			int rs1= 0;

			struct gmkgame tactic_cell;
			tactic_cell.player = 0;
			tactic_cell.c_weight = itg->cell.c_weight;
			tactic_cell.x = itg->cell.x;
			tactic_cell.y = itg->cell.y;

			//cout << tactic_cell.player << " " << tactic_cell.x << " " << tactic_cell.y << endl;

			//if(tactic_cell.player==0) {

				itg->cell.player = machine_chess;
				cp_gboard[itg->cell.y][itg->cell.x].player = itg->cell.player;
				cp_gboard[itg->cell.y][itg->cell.x].x= itg->cell.x;
				cp_gboard[itg->cell.y][itg->cell.x].y= itg->cell.y;

				//prev_gmkplay_list_size = gmkplay_list.size();
				//gmkplay_list.push_back(gmkplay);

				//g = &gboard[input_y][input_x];
				////////////////////////////////////////////////
				set_n_occupied(vct_search, &next_tactic_gmk_for_machine, &itg->cell, machine_chess, player_chess);
				///////////////////////////////////////////////
				//log after play
				//log_winning_pattern((char *)"winning_patterns.txt", &gmk_winning_pattern_list);
				/////////////////////////////////////////
				//gmk_winning_pattern_list.sort(compare_pattern);
			//}

			if(n_ply > 0){
				int rmachine_chess, rplayer_chess;

				if((n_ply-1)%2 == 1) {
					rmachine_chess = player_chess;
					rplayer_chess = machine_chess;
				}else{
					rmachine_chess = machine_chess;
					rplayer_chess = player_chess;
				}

				//if(itg->machine_n_fork < 2 || itg->player_n_fork < 2){
					int original_machine_hi_level=0, original_player_hi_level=0;
					rs1 = machine_play(vct_search, n_ply-1, started_chess, gboard_x, gboard_y, cp_gboard, &next_tactic_gmk_for_machine, &itg->cell, rmachine_chess, rplayer_chess, cur_move, &get_next_play_proposal, &get_next_tactic_moves, MIN_TOP_MOVES, TOTAL_MIN_TOP_MOVES, &original_machine_hi_level, &original_player_hi_level);

					//update tactic moves
					list <struct tactic_weight> :: iterator itt1, itt2;
					list <struct tactic_weight> :: reverse_iterator ritw, ritg;
					for(itt1 = get_next_tactic_moves.begin(); itt1 != get_next_tactic_moves.end(); ++itt1) {
						int is_duplicated = 0;
						for(itt2 = get_tactic_moves->begin(); itt2 != get_tactic_moves->end(); ++itt2) {
							if(itt1->cell.x == itt2->cell.x && itt1->cell.y == itt2->cell.y){
								itt2->n_visited++;
								itt2->machine_pt += itt1->machine_pt;
								itt2->player_pt += itt1->player_pt;
								is_duplicated= 1; break;
							}
						}
						//if(is_duplicated == 0) get_tactic_moves->push_back(*itt1);
					}

					////////////
					/*
					if (rs1 != 0){// || itg->machine_n_fork > 1 || itg->player_n_fork > 1){
						cout << endl << rs1 << " Won at ply # " << n_ply << endl;

						if((n_ply-1)%2 == 0){
							if(rs1 == machine_chess){
								next_play_proposal->x = get_next_play_proposal.x;//itg->cell.x;
								next_play_proposal->y = get_next_play_proposal.y;//itg->cell.y;

								cout << endl << "Deep selected at ply "<< n_ply << ": " << next_play_proposal->x << "," << next_play_proposal->y << endl;
							}else{
								next_play_proposal->x = -1;
								next_play_proposal->y = -1;
							}
						}

						if((n_ply-1)%2 == 1){
							if(rs1 == player_chess){
								next_play_proposal->x = get_next_play_proposal.x;//itg->cell.x;
								next_play_proposal->y = get_next_play_proposal.y;//itg->cell.y;

								cout << endl << "Deep selected at ply "<< n_ply << ": " << next_play_proposal->x << "," << next_play_proposal->y << endl;
							}else{
								next_play_proposal->x = -1;
								next_play_proposal->y = -1;
							}
						}
						///////
						for (int i = 0; i < gboard_y; i++) {
							free(cp_gboard[i]);
						}
						free(cp_gboard);

						break;
					}*/
				//}
				/*
				else{
					if((n_ply-1)%2 == 0){
						//if(rs1 == machine_chess){
							next_play_proposal->x = itg->cell.x;
							next_play_proposal->y = itg->cell.y;

							cout << endl << "Deep selected at ply "<< n_ply << ": " << next_play_proposal->x << "," << next_play_proposal->y << endl;
						//}else{
							//next_play_proposal->x = -1;
							//next_play_proposal->y = -1;
						//}
					}

					if((n_ply-1)%2 == 1){
						//if(rs1 == player_chess){
							next_play_proposal->x = itg->cell.x;
							next_play_proposal->y = itg->cell.y;

							cout << endl << "Deep selected at ply "<< n_ply << ": " << next_play_proposal->x << "," << next_play_proposal->y << endl;
						//}else{
							//next_play_proposal->x = -1;
							//next_play_proposal->y = -1;
						//}
					}
					break;
				}*/
			}

			//if(next_play_proposal->x == -1) itg = get_tactic_moves->erase(itg);

			for (int i = 0; i < gboard_y; i++) {
				free(cp_gboard[i]);
			}
			free(cp_gboard);
		}
	}

	cout << endl << endl << n_ply << "Recalculated Top moves. Selecting next move." << endl;
	int most_visited_times = 0;

	for(itg = get_tactic_moves->begin(); itg != get_tactic_moves->end(); ++itg) {
		if(most_visited_times < itg->n_visited){
			most_visited_times = itg->n_visited;
		}
	}

	for(itg = get_tactic_moves->begin(); itg != get_tactic_moves->end(); ++itg) {
		itg->machine_uct = (float) itg->machine_pt / (float) most_visited_times;//(float) itg->n_visited;
		itg->player_uct = (float) itg->player_pt / (float) most_visited_times;//(float) itg->n_visited;

		cout << endl << "machine-uct: "<< itg->machine_uct<< " n_visited: "<< itg->n_visited << " ("<< itg->machine_pt << "," << itg->machine_n_fork << "," << itg->machine_pt_level << ":" << itg->player_pt << ","<< itg->player_n_fork << "," << itg->player_pt_level<< ")"<< " player-uct: "<< itg->player_uct<< " n_visited: "<< itg->n_visited << "\t"<< itg->cell.x << "," << itg->cell.y << ";  " ;
	}
	cout << endl;

	if((*original_machine_highest_level) < 3 && (*original_player_highest_level) < 2){// && any_fork == 0){
		struct tactic_weight machine_selected_move, player_selected_move;

		get_tactic_moves->sort(compare_machine_uct);
		machine_selected_move = get_tactic_moves->back();

		get_tactic_moves->sort(compare_player_uct);
		player_selected_move = get_tactic_moves->back();

		if(machine_selected_move.machine_uct >= player_selected_move.player_uct){
			next_play_proposal->x = machine_selected_move.cell.x;
			next_play_proposal->y = machine_selected_move.cell.y;
		}else{
			next_play_proposal->x = player_selected_move.cell.x;
			next_play_proposal->y = player_selected_move.cell.y;
		}
	}
	//if not selected by recursive play
	/*
	//if(next_play_proposal->x == -1){
		tactic_with_player_pt.sort(compare_tactic_machine_pt);
		biggest_machine_pt = tactic_with_player_pt.back().machine_pt;

		next_play_proposal->x = tactic_with_player_pt.back().cell.x;
		next_play_proposal->y = tactic_with_player_pt.back().cell.y;

		cout << "Max machine-pt: " << biggest_machine_pt << " ("<< next_play_proposal->x << "," << next_play_proposal->y << "," << tactic_with_player_pt.back().machine_n_fork << "," << tactic_with_player_pt.back().machine_pt_level << ")" << endl;

		tactic_with_player_pt.sort(compare_tactic_player_pt);
		biggest_player_pt = tactic_with_player_pt.back().player_pt;

		cout << "Max player-pt: " << biggest_player_pt << " ("<< tactic_with_player_pt.back().cell.x << "," << tactic_with_player_pt.back().cell.y << "," << tactic_with_player_pt.back().player_n_fork << "," << tactic_with_player_pt.back().player_pt_level << ")" << endl;

		////////////////////////////////////////////////////////////////////
		//select next play by comparing points then by highest token rankings
		//float prev_ratio = 0;

		if(started_chess == machine_chess){
			//if(biggest_machine_pt >= biggest_player_pt || biggest_machine_pt >= 1000000){
			if((float)biggest_machine_pt >= ((float)biggest_player_pt) || biggest_machine_pt >= 1000000){
				//next_play_proposal->x = highest_machine_pt_level_list.back().cell.x;
				//next_play_proposal->y = highest_machine_pt_level_list.back().cell.y;

			}else{
				next_play_proposal->x = tactic_with_player_pt.back().cell.x;
				next_play_proposal->y = tactic_with_player_pt.back().cell.y;

				//cout << next_play_proposal->x << " " << next_play_proposal->y << endl;
			}
		}
		else{
			//if((float)biggest_machine_pt >= ((float)biggest_player_pt * 1.15) || biggest_machine_pt >= 90000){//1000000){
			if((float)biggest_machine_pt >= ((float)biggest_player_pt) || biggest_machine_pt >= 90000){
				//next_play_proposal->x = highest_machine_pt_level_list.back().cell.x;
				//next_play_proposal->y = highest_machine_pt_level_list.back().cell.y;

			}else{
				next_play_proposal->x = tactic_with_player_pt.back().cell.x;
				next_play_proposal->y = tactic_with_player_pt.back().cell.y;

				//cout << next_play_proposal->x << " " << next_play_proposal->y << endl;
			}
		}
	//}	*/

    return rs;
}

//////////////////
int main(int argc, char **argv) {
	//bar_c();
	//bar_cpp();

	srandom((unsigned)time(NULL));

	list <struct gmkgame> gmkplay_list;
	list <struct gmk_winning_pattern> gmk_winning_pattern_list;
	/*
	tree<string> gmk_tree;
	tree<string>::iterator gmk_root, gmk_head, gmk_cursor;
	if(gmk_tree.empty()){
		//Can't remove this node, a fixed node for this algorithm otherwise the bush of trees will be erased when try to erase a root item.
		gmk_root = gmk_tree.set_head(ROOT);
	}*/

	int maxx, maxy; maxx=maxy=19;//15
	int ply_cnt= 1;
	//ply_cnt%2= 1, black(x)
	//ply_cnt%2=0, white(o)

	list <struct victory_threats> :: iterator itvct;
	list <struct victory_threats> vct_search;
	struct victory_threats vct_interim;

	struct gmkgame **gboard = (struct gmkgame **) malloc(sizeof(struct gmkgame *) *maxx);
	for (int i=0; i<maxy; i++) gboard[i] = ( struct gmkgame *)malloc(maxy * sizeof( struct gmkgame));

	for(int i=0; i< maxy; i++){
		for(int j=0; j< maxx; j++){
			gboard[i][j].player= 0;
			gboard[i][j].x = j;
			gboard[i][j].y = i;
			//////////////////////////////////
			vct_interim.cell.x = i;
			vct_interim.cell.y = j;
			vct_interim.cell.player = 0;
			vct_search.push_back(vct_interim);
		}
	}

	//token string
	string token_str[6], temp_str[6];
	/*
	//0: |
	//1: __
	//2: / needs 2 strings
	//3: \ needs 2 strings
	*/
	//tokenizing game board by grouping of TOKEN_SIZE consecutive cells
	//tokens for | and __
	int token_cnt= 0;

	for(int i=0; i< maxx; i++){
		for(int j=0; j< maxy; j++){
			int itcnt=0;
			struct gmk_winning_pattern gmk_win_pattern_item[2];

			for(int k=0; k<TOKEN_SIZE; k++){
				if(k== 0){
					temp_str[0]= temp_str[1]= "";
					temp_str[0]+= "[";
					temp_str[1]+= "[";
				}
				if ((j+k) < maxy){
					itcnt++;
					temp_str[0]+= "{\"x\":" + to_string(i)+ ",\"y\":" + to_string(j+k) + "}";
					gmk_win_pattern_item[0].cell[k].x = i;
					gmk_win_pattern_item[0].cell[k].y = j+k;
					gmk_win_pattern_item[0].occupied_pattern = 0;

					temp_str[1]+= "{\"x\":" + to_string(j+k)+ ",\"y\":" + to_string(i) + "}";
					gmk_win_pattern_item[1].cell[k].x = j+k;
					gmk_win_pattern_item[1].cell[k].y = i;
					gmk_win_pattern_item[1].occupied_pattern = 0;
				}
				if(k<4 && (j+k+1) < maxy){
					temp_str[0]+= ",";
					temp_str[1]+= ",";
				}
				else if(k==4 || (j+k)>= maxy){
					temp_str[0]+= "]";
					temp_str[1]+= "]";
					break;
				}
			}
			if(itcnt==TOKEN_SIZE){
				token_cnt+=2;
				temp_str[0] += '\n';
				temp_str[1] += "\n";
				token_str[0] += temp_str[0];
				token_str[1] += temp_str[1];

				gmk_win_pattern_item[0].vector = 0;
				gmk_win_pattern_item[0].spy = 0;
				gmk_win_pattern_item[0].decayed= 0;

				gmk_win_pattern_item[0].pattern_id = "";
				for(int p=0; p< TOKEN_SIZE; p++) gmk_win_pattern_item[0].pattern_id+= to_string(gmk_win_pattern_item[0].cell[p].x) + to_string(gmk_win_pattern_item[0].cell[p].y);

				gmk_winning_pattern_list.push_back(gmk_win_pattern_item[0]);

				//////////////////////////////////////
				gmk_win_pattern_item[1].spy = 0;
				gmk_win_pattern_item[1].vector = 1;
				gmk_win_pattern_item[1].decayed= 0;

				gmk_win_pattern_item[1].pattern_id = "";
				for(int p=0; p< TOKEN_SIZE; p++) gmk_win_pattern_item[1].pattern_id+= to_string(gmk_win_pattern_item[1].cell[p].x) + to_string(gmk_win_pattern_item[1].cell[p].y);

				gmk_winning_pattern_list.push_back(gmk_win_pattern_item[1]);
			}
		}
	}

	/*
	//tokens for /
	*/
	for(int i=0; i< maxx; i++){
		//for(int j=0; j< y; j++){
			if(i+4< maxx){
				int itcnt=0;
				int h=i;
				int j= 0;
				struct gmk_winning_pattern gmk_win_pattern_item[2];

				do{
					//cout << h << ":" << j << endl;
					for(int k=0; k<TOKEN_SIZE; k++){
						if(k== 0){
							temp_str[2]= "";
							//temp_str[3]= "";
							temp_str[2]+= "[";

							if(h != j){
								temp_str[3]= "";
								temp_str[3]+= "[";
							}
							//temp_str[3]+= "[";
						}
						//if ((j+k) < y){
							itcnt++;
							temp_str[2]+= "{\"x\":" + to_string(h+k)+ ",\"y\":" + to_string(j+k) + "}";

							gmk_win_pattern_item[0].cell[k].x = h+k;
							gmk_win_pattern_item[0].cell[k].y = j+k;
							gmk_win_pattern_item[0].occupied_pattern = 0;

							if(h != j){
								itcnt++;
								temp_str[3]+= "{\"x\":" + to_string(j+k)+ ",\"y\":" + to_string(h+k) + "}";
								gmk_win_pattern_item[1].cell[k].x = j+k;
								gmk_win_pattern_item[1].cell[k].y = h+k;
								gmk_win_pattern_item[1].occupied_pattern = 0;
							}

						//}
						if(k<4){// && (j+k+1) < y){
							temp_str[2]+= ",";
							if(h != j) temp_str[3]+= ",";
						}
						else if(k==4){// || (j+k)>= y){
							temp_str[2]+= "]";
							if(h != j) temp_str[3]+= "]";
							//break;
						}
					}
					//if(k==TOKEN_SIZE){
						token_cnt++;
						temp_str[2] += '\n';
						token_str[2] += temp_str[2];

						gmk_win_pattern_item[0].spy = 0;
						gmk_win_pattern_item[0].vector = 2;
						gmk_win_pattern_item[0].decayed= 0;
						gmk_win_pattern_item[0].pattern_id = "";
						for(int p=0; p< TOKEN_SIZE; p++) gmk_win_pattern_item[0].pattern_id+= to_string(gmk_win_pattern_item[0].cell[p].x) + to_string(gmk_win_pattern_item[0].cell[p].y);
						gmk_winning_pattern_list.push_back(gmk_win_pattern_item[0]);

						if(h!=j){
							token_cnt++;
							temp_str[3] += "\n";
							token_str[3] += temp_str[3];

							gmk_win_pattern_item[1].spy = 0;
							gmk_win_pattern_item[1].vector = 2;
							gmk_win_pattern_item[1].decayed= 0;
							gmk_win_pattern_item[1].pattern_id = "";
							for(int p=0; p< TOKEN_SIZE; p++) gmk_win_pattern_item[1].pattern_id+= to_string(gmk_win_pattern_item[1].cell[p].x) + to_string(gmk_win_pattern_item[1].cell[p].y);
							gmk_winning_pattern_list.push_back(gmk_win_pattern_item[1]);
						}
					//}
					++h; j++;
				}while(h+4< maxx && j+4 < maxy);
			}
		//}
	}

	//cout << "token str 0 \n" << token_str[0];
	//cout << "token str 1 \n" << token_str[1];
	//token_str[2] += temp_str[3];
	//cout << "token str 2 \n" << token_str[2];
	//cout << "token str 3 \n" << token_str[3];

	/*
	//tokens for \
	*/
	int count4= 0, count5=0;
	for(int i=maxx-1; i>=0; i--){
		//for(int j=0; j< y; j++){
			if(i-4 >= 0){
				int itcnt=0;
				int h=i;
				int j= 0;
				struct gmk_winning_pattern gmk_win_pattern_item[2];

				do{
					//cout << h << ":" << j << endl;
					for(int k=0; k<TOKEN_SIZE; k++){
						if(k== 0){
							temp_str[4]= "";
							//temp_str[3]= "";
							temp_str[4]+= "[";

							if(h + j == i && h+j != maxx-1){
								temp_str[TOKEN_SIZE]= "";
								temp_str[TOKEN_SIZE]+= "[";
							}
							//temp_str[3]+= "[";
						}
						//if ((j+k) < y){
							itcnt++;

							temp_str[4]+= "{\"x\":" + to_string(h-k)+ ",\"y\":" + to_string(j+k) + "}";

							gmk_win_pattern_item[0].cell[k].x = h-k;
							gmk_win_pattern_item[0].cell[k].y = j+k;
							gmk_win_pattern_item[0].occupied_pattern = 0;

							if(h + j == i && h+j != maxx-1){
								itcnt++;
								temp_str[TOKEN_SIZE]+= "{\"x\":" + to_string(h+(maxx-i-1)-k)+ ",\"y\":" + to_string(maxx-1-h+k) + "}";

								gmk_win_pattern_item[1].cell[k].x = h+(maxx-i-1)-k;
								gmk_win_pattern_item[1].cell[k].y = maxx-1-h+k;
								gmk_win_pattern_item[1].occupied_pattern = 0;
							}

						//}
						if(k<4){// && (j+k+1) < y){
							temp_str[4]+= ",";
							if(h + j < maxx-1 && h+j != maxx-1) temp_str[TOKEN_SIZE]+= ",";
						}
						else if(k==4){// || (j+k)>= y){
							temp_str[4]+= "]";
							if(h + j == i && h+j != maxx-1) temp_str[TOKEN_SIZE]+= "]";
							//break;
						}
					}
					//if(k==TOKEN_SIZE){
						token_cnt++;
						temp_str[4] += '\n';
						token_str[4] += temp_str[4];

						gmk_win_pattern_item[0].spy = 0;
						gmk_win_pattern_item[0].vector = 3;
						gmk_win_pattern_item[0].decayed= 0;
						gmk_win_pattern_item[0].pattern_id = "";

						for(int p=0; p< TOKEN_SIZE; p++) gmk_win_pattern_item[0].pattern_id+= to_string(gmk_win_pattern_item[0].cell[p].x) + to_string(gmk_win_pattern_item[0].cell[p].y);
						gmk_winning_pattern_list.push_back(gmk_win_pattern_item[0]);

						if(h + j == i && h+j != maxx-1){
							token_cnt++;
							temp_str[TOKEN_SIZE] += "\n";
							token_str[TOKEN_SIZE] += temp_str[TOKEN_SIZE];

							gmk_win_pattern_item[1].spy = 0;
							gmk_win_pattern_item[1].vector = 3;
							gmk_win_pattern_item[1].decayed= 0;
							gmk_win_pattern_item[1].pattern_id = "";
							for(int p=0; p< TOKEN_SIZE; p++) gmk_win_pattern_item[1].pattern_id+= to_string(gmk_win_pattern_item[1].cell[p].x) + to_string(gmk_win_pattern_item[1].cell[p].y);
							gmk_winning_pattern_list.push_back(gmk_win_pattern_item[1]);
						}

					//}
					--h; j++;
				}while(h-4 >= 0 && j+4 < maxy);
			}
		//}
	}


	//building VCT data/////////////////////////////////
	list <struct gmk_winning_pattern> :: iterator itwin;

	for(itwin = gmk_winning_pattern_list.begin(); itwin != gmk_winning_pattern_list.end(); ++itwin) {
		for(int i=0; i< TOKEN_SIZE; i++){
			itwin->cell[i].player= 0;
			for(itvct = vct_search.begin(); itvct != vct_search.end(); ++itvct) {
				if(itwin->cell[i].x == itvct->cell.x && itwin->cell[i].y == itvct->cell.y){
					itvct->patterns[itwin->vector].push_back(*itwin);
					break;
				}
			}
		}
	}

	/*cout << "Total cells: " << vct_search.size() << endl;
	for(itvct = vct_search.begin(); itvct != vct_search.end(); ++itvct) {
		cout << itvct->cell.x << "," << itvct->cell.y << ": ";
		for(int i =0; i< TOTAL_VECTOR; i++) cout << i << ": " << itvct->patterns[i].size() << "\t";
		cout << endl;
	}*/
	/////////////////////////////////////////

	//cout << "token str 4 \n" << token_str[4];
	//cout << "token str TOKEN_SIZE \n" << token_str[TOKEN_SIZE];

	//show_winning_patterns(gmk_winning_pattern_list);
	//cout << endl << "Finding related winning patterns: " << endl;
	//int rand_n;
	//do{
		//rand_n= rand() % gmkplay_list.size();
	//}while(rand_n >= gmkplay_list.size());

	//auto l_front = gmkplay_list.begin();
	//std::advance(l_front, rand_n);

	//struct gmkgame last_play = *l_front;
	//cout << "Last Play: " << last_play.x << " " << last_play.y << endl;
	//find_patterns(gmk_winning_pattern_list, last_play);

	//cout << "Total winning patterns: " << token_cnt << endl;

	for(int i=0; i< maxx; i++){
		struct gmkgame g;
		for(int j=0; j< maxy; j++){
			g.x = i; g.y= j;
			//cout << endl;
			//g.c_weight= find_patterns(gmk_winning_pattern_list, &g);
			//cout << "W: "<< g.c_weight << ", Cell: [" << g.x << " " << g.y << "] ";

			//if(g.player==1) cout << "(1)";
			//else if(g.player==2) cout << "(-1)";
			//else cout << "(0)";
			//cout << endl;
		}
		//cout << endl;
	}

	//draw playing tree to find winning patterns
	//list <struct gmkgame> :: iterator it;
	//for(it = gmkplay_list.begin(); it != gmkplay_list.end(); ++it) {
		/*string tree_node_obj = "{\"x\":"+ to_string(it->x)+ ",\"y\":" + to_string(it->y) +"}";
		cout << tree_node_obj << endl;
		//if(gboard[it->x][it->y].occupied > 0){
			if(gmk_tree[gboard[it->x][it->y].occupied-1].number_of_children(gmk_root[gboard[it->x][it->y].occupied-1]) == 0){
				gmk_head[gboard[it->x][it->y].occupied-1] = gmk_cursor[gboard[it->x][it->y].occupied-1] = gmk_tree[gboard[it->x][it->y].occupied-1].append_child(gmk_root[gboard[it->x][it->y].occupied-1], tree_node_obj);
			}
		//}
		*/
		/*
		else{
			//std::string prev_hash = "{\"" + (string)js_block_header[BLOCK_HEADER]["xtb_prev_block_hash"] + "\",\"" + (string)js_block_header[BLOCK_HEADER][IPFS_PREV_BLOCK_H] + "\"}";
			std::string prev_hash = js_block_header[BLOCK_HEADER][IPFS_PREV_BLOCK_H].get<string>();
			//std::string prev_hash = js_block_header[BLOCK_HEADER]["xtb_prev_block_hash"];
			cout << prev_hash.size() << ": "<< prev_hash << endl;
			if(prev_hash.compare((*reversible_cursor[block_shard_id-1]))==0){//found at current position of cursor
				reversible_cursor[block_shard_id-1] = reversible_tree[block_shard_id-1].append_child(reversible_cursor[block_shard_id-1], tree_node_obj);//js_block_header[BLOCK_HEADER][BLOCK_H]);//);
				f_adding_reversible_block=1;
			}else{
				///////////////////////////////////////////////
				tree<string>::iterator it = find(reversible_root[block_shard_id-1], reversible_tree[block_shard_id-1].end(), prev_hash.data());
				//tree<string>::iterator it = find(reversible_tree[block_shard_id-1].begin(), reversible_tree[block_shard_id-1].end(), prev_hash);
				////////////////////////////
				if(it != reversible_tree[block_shard_id-1].end()){
					reversible_tree[block_shard_id-1].append_child(it, tree_node_obj);//js_block_header[BLOCK_HEADER][BLOCK_H]);//);
					if(reversible_tree[block_shard_id-1].n_ply(reversible_cursor[block_shard_id-1]) < reversible_tree[block_shard_id-1].n_ply(it)){
						reversible_cursor[block_shard_id-1] = it;
					}
					f_adding_reversible_block=1;
				}else{
					//The block doesn't belong to this chain
					//////////////////////////////
					//need to add garbage block collector for deleting unused block files
					/////////////////////////////
				}
			}
		}*/
	//}

	//for(int i=0; i< 2; i++) kptree::print_tree_bracketed(gmk_tree[i], std::cout);
	//cout << "\nDepth of Reversible Chain: " << reversible_tree[block_shard_id-1].n_ply(reversible_cursor[block_shard_id-1]) << endl;

	//qualify a new irreversible block
	//irre_depth = (n_active_bp/3 * 2 + 1);
	//if(reversible_tree[block_shard_id-1].n_ply(reversible_cursor[block_shard_id-1]) >= irre_depth){
		/*
		cout << "\nOldest Block is Irreversible: "<<endl;
		kptree::print_tree_bracketed(reversible_tree[block_shard_id-1], std::cout);
		tree<std::string>::pre_order_iterator it_rm = reversible_head[block_shard_id-1];
		tree<std::string>::pre_order_iterator it_next_rm = it_rm;
		//////////////////////////////////////////////
		//Double check this below section

		zlist_t *sib_list = zlist_new ();
		assert (sib_list);

		while(1){
			it_next_rm= reversible_tree[block_shard_id-1].next_sibling(it_next_rm);
			if(it_next_rm != NULL) zlist_append (sib_list, &it_next_rm);
			else break;
			cout << "while(1)" << endl;
		}

		tree<std::string>::pre_order_iterator *sib_next_rm;
		//move cursor to the start of the list
		zlist_first(sib_list);
		//while(sib_next_rm = (tree<std::string>::pre_order_iterator *)zlist_next(sib_list)){
		while(sib_next_rm = (tree<std::string>::pre_order_iterator *)zlist_pop(sib_list)){
			//Remove sibling(s) and their children to prune the chain
			reversible_tree[block_shard_id-1].erase(*sib_next_rm);
			/////////////////////////////////
			//need to add garbage collector for deleting unused block files
			////////////////////////////
			cout << "while(sib)" << endl;
		}
		zlist_destroy(&sib_list);

		//Double check the above section

		//Rearrange the tree to prepare for processing the irreversible block
		reversible_tree[block_shard_id-1].reparent(reversible_root[block_shard_id-1], reversible_tree[block_shard_id-1].begin(it_rm), reversible_tree[block_shard_id-1].next_sibling(reversible_tree[block_shard_id-1].begin(it_rm)));
		////////////////////////////////////////////////
		*/

	////////////////////////////////////
	char player_color= '-';
	int player_chess, machine_chess, prev_gmkplay_list_size= 0;
	int start_game = 0, started_chess = 0;

	int input_x=-1, input_y=-1;

	struct gmkgame gmkplay;
	struct gmkgame next_play_proposal;
	struct gmkgame *g;

	draw_game_board(maxx, maxy, player_color, gboard, gmkplay_list);

	if (argc == 3) {
		if(strcmp("machine_play", argv[1])== 0){
			maxx = maxy = (int) strtol(argv[2], NULL, 10);
			draw_game_board(maxx, maxy, player_color, gboard, gmkplay_list);
		}
		else{
			printf ("Usage: %s machine_play\n", argv[0]);
			printf ("\n");
			return 0;
		}
	}

	return 0;
}
