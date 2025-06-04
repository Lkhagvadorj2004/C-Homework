#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 50
#define MAX_EMAIL 50
#define MAX_NATIONALITY 30
#define MAX_SKILL 30
#define MAX_INTRO 200
#define MAX_GROUP_NAME 50
#define CANDIDATES 6

struct member_info {
    char name[MAX_NAME];
    char dob[9];  // YYYYMMDD format
    char gender;
    char email[MAX_EMAIL];
    char nationality[MAX_NATIONALITY];
    float bmi;
    char primary_skill[MAX_SKILL];
    char secondary_skill[MAX_SKILL];
    int topik;
    char mbti[5];
    char intro[MAX_INTRO];
};

// Function to calculate age from DOB (YYYYMMDD format)
int calculate_age(const char* dob) {
    int birth_year = (dob[0] - '0') * 1000 + (dob[1] - '0') * 100 + 
                     (dob[2] - '0') * 10 + (dob[3] - '0');
    return 2025 - birth_year;  // Current year is 2025
}

int main() {
    struct member_info candidate01, candidate02, candidate03,
                      candidate04, candidate05, candidate06;
    struct member_info* candidates[] = {
        &candidate01, &candidate02, &candidate03,
        &candidate04, &candidate05, &candidate06
    };
    
    char group_name[MAX_GROUP_NAME] = {0};
    
    // Get group name
    printf("Enter audition group name: ");
    int c, i = 0;
    while ((c = getchar()) != '\n' && c != EOF && i < MAX_GROUP_NAME - 1) {
        group_name[i++] = c;
    }
    group_name[i] = '\0';
    
    // Input data for each candidate
    for (i = 0; i < CANDIDATES; i++) {
        printf("\n####################################\n");
        printf("[%s] Audition Candidate Data Entry\n", group_name);
        printf("####################################\n");
        printf("Entering information for candidate %d.\n", i + 1);
        printf("---------------------------------\n");
        
        printf("1. Name: ");
        scanf(" %[^\n]", candidates[i]->name);
        
        printf("2. Date of Birth (YYYY/MM/DD format): ");
        char temp_dob[11];
        scanf(" %s", temp_dob);
        // Convert YYYY/MM/DD to YYYYMMDD
        int j = 0;
        for (int k = 0; k < 10; k++) {
            if (temp_dob[k] != '/') {
                candidates[i]->dob[j++] = temp_dob[k];
            }
        }
        candidates[i]->dob[8] = '\0';
        
        printf("3. Gender (F for Female, M for Male): ");
        scanf(" %c", &candidates[i]->gender);
        
        printf("4. Email: ");
        scanf(" %s", candidates[i]->email);
        
        printf("5. Nationality: ");
        scanf(" %[^\n]", candidates[i]->nationality);
        
        printf("6. BMI: ");
        scanf("%f", &candidates[i]->bmi);
        
        printf("7. Primary Skill: ");
        scanf(" %[^\n]", candidates[i]->primary_skill);
        
        printf("8. Secondary Skill: ");
        scanf(" %[^\n]", candidates[i]->secondary_skill);
        
        printf("9. Korean Proficiency Level (TOPIK): ");
        scanf("%d", &candidates[i]->topik);
        
        printf("10. MBTI: ");
        scanf(" %s", candidates[i]->mbti);
        
        printf("11. Introduction: ");
        scanf(" %[^\n]", candidates[i]->intro);
    }
    
    // Display all candidates
    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("===============================================================================================\n");
    printf("Name (Age)    | DOB      | Gender | Email                | Nationality | BMI  | Primary  | Secondary | TOPIK | MBTI |\n");
    printf("===============================================================================================\n");
    
    for (i = 0; i < CANDIDATES; i++) {
        int age = calculate_age(candidates[i]->dob);
        printf("%-12s (%2d) | %8s | %-6c | %-20s | %-11s | %4.1f | %-8s | %-9s | %5d | %-4s |\n",
               candidates[i]->name, age,
               candidates[i]->dob,
               candidates[i]->gender,
               candidates[i]->email,
               candidates[i]->nationality,
               candidates[i]->bmi,
               candidates[i]->primary_skill,
               candidates[i]->secondary_skill,
               candidates[i]->topik,
               candidates[i]->mbti);
        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[i]->intro);
        printf("---------------------------------------------------------------------------------------------\n");
    }
    
    return 0;
}
