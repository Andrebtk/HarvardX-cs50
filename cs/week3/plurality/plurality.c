#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int debug=0;

    for(int i = 0; i < candidate_count; i++)
    {

        if(strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
        }else{
            debug++;
        }


        if(debug == candidate_count){
            return false;
        }


    }
    return true;


}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winner_arr[candidate_count];
    int winner_score = -1;

    //printf("\n");
    for(int i = 0; i < candidate_count; i++){



        if(winner_score < candidates[i].votes){
            winner_arr[0] = i;
            winner_score = candidates[i].votes;
        }
        if(winner_score == candidates[i].votes){
            winner_arr[1] = i;
        }
    }

    if(winner_arr[0] == winner_arr[1]){
        winner_arr[1] = 0;
    }

    if(candidates[0].votes == candidates[1].votes && candidates[1].votes == candidates[2].votes){
        for(int i=0; i<3; i++){
            printf("%s\n", candidates[i].name);
        }
    }else f(winner_arr[1] == 0){
        printf("%s\n", candidates[0].name);
    }else{
        for(int i=0; i<2; i++){
            printf("%s\n", candidates[winner_arr[i]].name);
        }

    }



    return;
}

