#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Define the number of total candidates and successful ones
#define TOTAL_CANDIDATES 6
#define MAX_NAME_LEN 100
#define MAX_STR_LEN 256

// Struct for candidate
typedef struct {
    int id;
    float height;
    float bmi;
    int pass; // 1 for pass, 0 for fail
} Candidate;

// Struct for full member info
typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NAME_LEN];
    char education[MAX_STR_LEN];
    float height;
    float weight;
    char blood_type[3];
    char allergy[MAX_STR_LEN];
    char hobby[MAX_STR_LEN];
    char sns[MAX_STR_LEN];
    float bmi;
} Member;

// Function to classify BMI
void print_bmi_status(float bmi) {
    int category;
    if (bmi < 18.5) category = 0;
    else if (bmi < 25.0) category = 1;
    else if (bmi < 30.0) category = 2;
    else category = 3;

    switch (category) {
        case 0:
            printf("BMI status: Underweight\n");
            break;
        case 1:
            printf("BMI status: Normal\n");
            break;
        case 2:
            printf("BMI status: Overweight\n");
            break;
        case 3:
            printf("BMI status: Obese\n");
            break;
    }
}

int main() {
    // 1. candidate##_arr
    Candidate candidate_arr[TOTAL_CANDIDATES] = {
        {1001, 1.68, 18.5, 1},
        {1002, 1.78, 21.3, 1},
        {1003, 1.63, 24.9, 1},
        {1004, 1.75, 29.1, 1},
        {1005, 1.60, 30.5, 0},
        {1006, 1.82, 22.2, 0}
    };

    // 2. Interview passed members
    Member milliways_arr[4];
    int count = 0;

    for (int i = 0; i < TOTAL_CANDIDATES; i++) {
        if (candidate_arr[i].pass == 1) {
            Member m;

            // Copy candidate height and BMI
            m.height = candidate_arr[i].height;
            m.bmi = candidate_arr[i].bmi;
            m.weight = m.bmi * (m.height * m.height); // weight = BMI * height²

            // Fill additional info (mock interview results)
            switch (candidate_arr[i].id) {
                case 1001: // Ji-yeon
                    strcpy(m.name, "Park Ji-yeon");
                    strcpy(m.nickname, "Ariel");
                    strcpy(m.education, "Dropped out of high school");
                    strcpy(m.blood_type, "A");
                    strcpy(m.allergy, "Dairy products");
                    strcpy(m.hobby, "dance practice, composition");
                    strcpy(m.sns, "Instagram - @Ariel_Jiyeon");
                    break;
                case 1002: // Ethan
                    strcpy(m.name, "Ethan Smith");
                    strcpy(m.nickname, "Lion");
                    strcpy(m.education, "Dropped out of 3rd year of middle school");
                    strcpy(m.blood_type, "THE");
                    strcpy(m.allergy, "peanut");
                    strcpy(m.hobby, "Song writing, health training");
                    strcpy(m.sns, "Twitter - @Simba_Ethan");
                    break;
                case 1003: // Helena
                    strcpy(m.name, "Helena Silva");
                    strcpy(m.nickname, "Belle");
                    strcpy(m.education, "Middle school graduate");
                    strcpy(m.blood_type, "B");
                    strcpy(m.allergy, "fish");
                    strcpy(m.hobby, "Singing, drawing");
                    strcpy(m.sns, "Instagram - @Belle_Helena");
                    break;
                case 1004: // Liam
                    strcpy(m.name, "Liam Wilson");
                    strcpy(m.nickname, "Aladdin");
                    strcpy(m.education, "Dropped out of 2nd year of middle school");
                    strcpy(m.blood_type, "AB");
                    strcpy(m.allergy, "shellfish");
                    strcpy(m.hobby, "Dancing, producing music");
                    strcpy(m.sns, "Instagram - @Aladdin_Liam");
                    break;
            }

            // Save to array
            milliways_arr[count++] = m;
        }
    }

    // 3. Output list
    for (int i = 0; i < count; i++) {
        printf("---- Member %d ----\n", i + 1);
        printf("Name: %s\n", milliways_arr[i].name);
        printf("Nickname: %s\n", milliways_arr[i].nickname);
        printf("Education: %s\n", milliways_arr[i].education);
        printf("Height: %.2fm\n", milliways_arr[i].height);
        printf("Weight: %.1fkg\n", milliways_arr[i].weight);
        printf("Blood Type: %s\n", milliways_arr[i].blood_type);
        printf("Allergy: %s\n", milliways_arr[i].allergy);
        printf("Hobby: %s\n", milliways_arr[i].hobby);
        printf("SNS: %s\n", milliways_arr[i].sns);
        printf("BMI: %.1f\n", milliways_arr[i].bmi);
        print_bmi_status(milliways_arr[i].bmi);
        printf("\n");
    }

    return 0;
}
