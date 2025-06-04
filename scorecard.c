#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_CATEGORIES 5
#define MAX_JUDGES 10
#define MAX_NAME_LENGTH 50

// Candidate structure
char *candidate_names[NUM_CANDIDATES] = {
    "Jiyeon Park",
    "Ethan Smith",
    "Helena Silva",
    "Liam Wilson",
    "Soojin Lee",
    "Carlos Mendes"
};

int candidate_ids[NUM_CANDIDATES] = {
    120134, 843291, 567842, 983475, 294001, 654378
};

// Scoring sheet for each candidate [ID, Music, Dance, Vocal, Visual, Expression, Total]
int scores[NUM_CANDIDATES][7] = {0};

// Function declarations
void input_scores();
int validate_score(int);
void print_scores();
void modify_scores();
void calculate_totals();
void display_final_results();

int main() {
    input_scores();
    return 0;
}

void input_scores() {
    char judge_name[MAX_NAME_LENGTH];
    char expertise[MAX_NAME_LENGTH];
    char submit;

    while (1) {
        printf("####################################\n");
        printf("#     Audition Evaluation Entry    #\n");
        printf("####################################\n");
        printf("> Judge Name: ");
        fgets(judge_name, MAX_NAME_LENGTH, stdin);
        judge_name[strcspn(judge_name, "\n")] = 0; // Remove newline

        printf("> Expertise: ");
        fgets(expertise, MAX_NAME_LENGTH, stdin);
        expertise[strcspn(expertise, "\n")] = 0;

        for (int i = 0; i < NUM_CANDIDATES; i++) {
            printf("++++++++++++++++++++++++++++++++++++\n");
            printf("Candidate: %s\n", candidate_names[i]);
            scores[i][0] = candidate_ids[i]; // Assign candidate ID
            for (int j = 1; j <= NUM_CATEGORIES; j++) {
                const char *categories[] = {"Music Proficiency", "Dance", "Vocal", "Visual", "Expression"};
                int value;
                do {
                    printf("%s: ", categories[j - 1]);
                    scanf("%d", &value);
                } while (!validate_score(value));
                scores[i][j] = value;
            }
            getchar(); // clear newline
        }

        calculate_totals();
        printf("++++++++++++++++++++++++++++++++++++\n");
        printf("Submission completed.\nPlease review your input!\n");
        printf("------------------------------------\n");
        print_scores();

        printf("Would you like to submit? (Y/N): ");
        scanf(" %c", &submit);
        getchar(); // consume newline

        if (submit == 'Y' || submit == 'y') {
            printf("***Final submission completed.***\n");
            display_final_results();
            break;
        } else {
            modify_scores();
        }
    }
}

int validate_score(int score) {
    if (score >= 10 && score <= 100) return 1;
    printf("Invalid score. Please enter a value between 10 and 100.\n");
    return 0;
}

void print_scores() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d\n", candidate_names[i], scores[i][6]);
    }
}

void calculate_totals() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int total = 0;
        for (int j = 1; j <= NUM_CATEGORIES; j++) {
            total += scores[i][j];
        }
        scores[i][6] = total;
    }
}

void modify_scores() {
    char name[MAX_NAME_LENGTH];
    int id, found;
    char proceed;

    while (1) {
        printf("Enter candidate name to modify or type 'exit' to finish: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = 0;
        if (strcmp(name, "exit") == 0) break;

        printf("Enter 6-digit Candidate ID: ");
        scanf("%d", &id);
        getchar(); // consume newline

        found = 0;
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (strcmp(candidate_names[i], name) == 0 && candidate_ids[i] == id) {
                found = 1;
                for (int j = 1; j <= NUM_CATEGORIES; j++) {
                    const char *categories[] = {"Music Proficiency", "Dance", "Vocal", "Visual", "Expression"};
                    int value;
                    do {
                        printf("%s: ", categories[j - 1]);
                        scanf("%d", &value);
                    } while (!validate_score(value));
                    scores[i][j] = value;
                }
                calculate_totals();
                break;
            }
        }
        if (!found) {
            printf("Candidate not found or ID mismatch.\n");
        }
    }
    printf("Final modifications completed.\n");
    print_scores();
    printf("Exiting program.\n");
}

void display_final_results() {
    // Sort candidates by total score (Bubble sort)
    int sorted[NUM_CANDIDATES];
    for (int i = 0; i < NUM_CANDIDATES; i++) sorted[i] = i;

    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = 0; j < NUM_CANDIDATES - i - 1; j++) {
            if (scores[sorted[j]][6] < scores[sorted[j + 1]][6]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[sorted[i]]);
    }
}
