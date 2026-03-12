#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <stdbool.h>
#include "../common/protocol.h"

#define MAX_CLIENTS 100
#define MAX_USERNAME 32
#define ROOM_CODE_LEN 6
#define WORD_LEN 5
#define MAX_ATTEMPTS 6

typedef struct {
    SOCKET sock;
    char username[MAX_USERNAME];
    bool is_active;
    int score;
    char current_guess[WORD_LEN + 1];
    bool has_guessed;
} Client;

typedef struct {
    char room_code[ROOM_CODE_LEN + 1];
    Client* clients[MAX_CLIENTS];
    int num_clients;
    CRITICAL_SECTION lock;
    
    bool game_in_progress;
    char secret_word[WORD_LEN + 1];
    int current_round;
    int total_rounds;
    
    CONDITION_VARIABLE guess_cond;
    int guess_count;
} Room;

// Main
void broadcast_to_room(Room* room, const char* message, Client* exclude_client);

// Game logic
void load_words(void);
char* get_random_word(void);
void evaluate_guess(const char* secret, const char* guess, char* result);

// Room management
Room* create_room(void);
Room* find_room(const char* code);
bool join_room(Room* room, Client* client);
void leave_room(Room* room, Client* client);
void start_game(Room* room);

// Scoreboard
void init_scores(void);
void save_scores(void);
void update_score_file(const char* username, int points);
void get_top_scores(char* output_buffer, int max_len);

#endif
