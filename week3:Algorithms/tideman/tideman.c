#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    printf("preferences\n");
    /*for (int i=0;i<candidate_count;i++){
        for (int j=0;j<candidate_count;j++){
            printf("%d ",preferences[i][j]);
        }
        printf("\n");
    }
    printf("locked\n");
    for (int i=0;i<candidate_count;i++){
        for (int j=0;j<candidate_count;j++){
            printf("%d ",locked[i][j]);
        }
        printf("\n");
    }
    printf("pair\n");
    for (int i=0;i<pair_count;i++)
    {
        printf("%d %d\n",pairs[i].winner,pairs[i].loser);
    }*/
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int i,j;
    bool flag = true;
    for (i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            flag = false;
            break;
        }
    }
    if (flag)
        return false;
    ranks[rank] = i;
    return ranks;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int i, j;
    for (i = 0; i < candidate_count; i++)
    {
        for (j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int i, j;
    pair temp;
    for (i = 0; i < pair_count-1; i++)
    {
        for (j = 0; j < pair_count-i-1; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[j].winner][pairs[j].loser])
            {
                temp.winner = pairs[i].winner;
                temp.loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = temp.winner;
                pairs[j].loser = temp.loser;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser] == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            /// If after adding pairs[i],graph without lock
            printf("check:%d %d\n",i,check());
            if (check())
            {
                locked[pairs[i].winner][pairs[i].loser] = false;
            }
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool flag = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
                flag = false;
        }
        if (flag)
            printf("%s\n", candidates[i]);
    }
}
bool dfs(int node, bool visited[], bool recursion_stack[]);
bool check()
{
    // visited数组用于标记节点是否被访问过，初始值为false
    bool visited[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = false;
    }

    // recursion_stack数组用于标记递归调用栈中的节点
    bool recursion_stack[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        recursion_stack[i] = false;
    }

    // 从每个未访问的节点开始进行深度优先遍历
    for (int i = 0; i < candidate_count; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, visited, recursion_stack))
            {
                return true;
            }
        }
    }
    return false;
}

// 深度优先遍历函数
bool dfs(int node, bool visited[], bool recursion_stack[])
{
    visited[node] = true;
    recursion_stack[node] = true;

    // 遍历当前节点的所有邻居节点
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[node][i])
        {
            // 如果邻居节点未被访问过，则递归调用dfs函数
            if (!visited[i])
            {
                if (dfs(i, visited, recursion_stack))
                {
                    return true;
                }
            }
            // 如果邻居节点已经被访问过且在递归调用栈中，则说明存在环
            else if (recursion_stack[i])
            {
                return true;
            }
        }
    }

    recursion_stack[node] = false;
    return false;
}