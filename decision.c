#include <stdio.h>
#include <math.h>

#define CATEGORY_COUNT 9
#define MAX_MEMBERS 10
#define MAX_SCORE 100

enum Category {
    PHYSICAL, KNOWLEDGE, SELF_MGMT, TEAMWORK, KOREAN,
    VOCAL, DANCE, VISUAL, ACTING
};

const char *categoryNames[CATEGORY_COUNT] = {
    "Physical Strength", "Knowledge", "Self-Management", "Teamwork",
    "Korean Language", "Vocal", "Dance", "Visual", "Acting"
};

int main() {
    int scores[MAX_MEMBERS][CATEGORY_COUNT];
    int memberCount, minRequired, totalSum = 0;
    int i, j;

    printf("Enter the number of Milliways members (max 10): ");
    scanf("%d", &memberCount);

    if (memberCount <= 0 || memberCount > MAX_MEMBERS) {
        printf("Invalid number of members.\n");
        return 1;
    }

    printf("Enter the minimum required score (1-11): ");
    scanf("%d", &minRequired);

    if (minRequired < 1 || minRequired > 11) {
        printf("Invalid minimum score.\n");
        return 1;
    }

    // Input and validation
    for (i = 0; i < memberCount; i++) {
        printf("\nEnter scores for member %d:\n", i + 1);
        for (j = 0; j < CATEGORY_COUNT; j++) {
            int score;
            printf("  %s (1-100): ", categoryNames[j]);
            scanf("%d", &score);
            if (score < 1 || score > 100) {
                printf("Invalid score. Please enter a value between 1 and 100.\n");
                return 1;
            }
            scores[i][j] = score;

            // Check for minimum required score
            if (score < minRequired) {
                printf("\nMinimum required score: %d\n", minRequired);
                printf("Member %d scored below minimum in %s.\n", i + 1, categoryNames[j]);
                printf("Entire team must retake this category.\n");
                return 0;
            }
        }
    }

    // Calculate team average score (truncated)
    for (j = 0; j < CATEGORY_COUNT; j++) {
        int categorySum = 0;
        for (i = 0; i < memberCount; i++) {
            categorySum += scores[i][j];
        }
        totalSum += categorySum / memberCount;
    }

    printf("\nTotal Team Score (truncated average): %d\n", totalSum);

    // Decide debut status
    if (totalSum >= 95) {
        printf("Congratulations! Your stage debut is confirmed!\n");
    } else if (totalSum >= 90) {
        printf("The Debut Certification Team will hold a final evaluation meeting to make a decision.\n");
    } else if (totalSum >= 80) {
        // Find 3 lowest-scoring categories (based on average)
        int categoryAvg[CATEGORY_COUNT];
        for (j = 0; j < CATEGORY_COUNT; j++) {
            int sum = 0;
            for (i = 0; i < memberCount; i++) {
                sum += scores[i][j];
            }
            categoryAvg[j] = sum / memberCount;
        }

        // Find three lowest
        int first = 0, second = 1, third = 2;
        if (categoryAvg[second] < categoryAvg[first]) { int temp = first; first = second; second = temp; }
        if (categoryAvg[third] < categoryAvg[first]) { int temp = first; first = third; third = temp; }
        if (categoryAvg[third] < categoryAvg[second]) { int temp = second; second = third; third = temp; }

        for (j = 3; j < CATEGORY_COUNT; j++) {
            if (categoryAvg[j] < categoryAvg[first]) {
                third = second;
                second = first;
                first = j;
            } else if (categoryAvg[j] < categoryAvg[second]) {
                third = second;
                second = j;
            } else if (categoryAvg[j] < categoryAvg[third]) {
                third = j;
            }
        }

        printf("Retake the three lowest-scoring categories (%s, %s, %s) after 30 days.\n",
            categoryNames[first], categoryNames[second], categoryNames[third]);
    } else {
        printf("Team performance too low. Reassess the entire training process.\n");
    }

    return 0;
}
