#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define CATEGORY_COUNT 9
#define MAX_EXAMS 9

const char* categories[CATEGORY_COUNT] = {
    "Physical Strength", "Knowledge", "Self-Management", "Teamwork",
    "Korean Language", "Vocal", "Dance", "Visual", "Acting"
};

int training_start_date = 0;
int exam_dates[MAX_EXAMS] = {0};   // YYYYMMDD
int exam_scheduled[MAX_EXAMS] = {0}; // 0 = not scheduled, 1 = scheduled

// Helper: Convert YYYYMMDD to day count
int convert_to_days(int yyyymmdd) {
    int year = yyyymmdd / 10000;
    int month = (yyyymmdd / 100) % 100;
    int day = yyyymmdd % 100;
    return year * 365 + month * 30 + day;
}

// Helper: Get today's date in YYYYMMDD
int get_today_date() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900 * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
}

// Display exam schedule
void display_schedule() {
    printf("\n--- Scheduled Exams ---\n");
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        if (exam_scheduled[i]) {
            printf("%s: %d\n", categories[i], exam_dates[i]);
        }
    }
}

// Schedule an exam
void schedule_exam() {
    int cat_index, exam_date;
    printf("\nSelect certification category:\n");
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }
    printf("Enter number (1-9): ");
    scanf("%d", &cat_index);
    cat_index--;

    if (cat_index < 0 || cat_index >= CATEGORY_COUNT) {
        printf("Invalid category.\n");
        return;
    }

    printf("Enter exam date (YYYYMMDD): ");
    scanf("%d", &exam_date);

    int start_days = convert_to_days(training_start_date);
    int exam_days = convert_to_days(exam_date);
    int diff = exam_days - start_days;

    if (diff < 30 || diff > 100) {
        printf("Exam must be between 30 and 100 days from training start.\n");
        return;
    }

    // Enforce order rules
    if ((cat_index == 2 || cat_index == 3) && (!exam_scheduled[0] || !exam_scheduled[1])) {
        printf("You must complete Physical Strength and Knowledge first.\n");
        return;
    }

    if (cat_index >= 4 && (!exam_scheduled[2] || !exam_scheduled[3])) {
        printf("You must complete Self-Management and Teamwork first.\n");
        return;
    }

    exam_scheduled[cat_index] = 1;
    exam_dates[cat_index] = exam_date;
    printf("Exam for %s scheduled on %d.\n", categories[cat_index], exam_date);
}

// Bonus: Check for upcoming exams
void check_reminders() {
    int today = get_today_date();
    int today_days = convert_to_days(today);
    printf("\n--- Exam Reminders (next 10 days) ---\n");
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        if (exam_scheduled[i]) {
            int eday = convert_to_days(exam_dates[i]);
            if (eday - today_days <= 10 && eday - today_days >= 0) {
                printf("Reminder: %s exam is in %d days on %d\n",
                       categories[i], eday - today_days, exam_dates[i]);
            }
        }
    }
}

// Bonus: Assign room if today is exam date
void assign_rooms() {
    int today = get_today_date();
    int found = 0;
    printf("\n--- Today's Exams and Room Assignments ---\n");
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        if (exam_scheduled[i] && exam_dates[i] == today) {
            found = 1;
            int room = rand() % 10 + 1;
            printf("%s exam is today. Assigned Room: %d\n", categories[i], room);
        }
    }
    if (!found) {
        printf("No exams scheduled for today.\n");
    }
}

int main() {
    srand(time(NULL));
    printf("Enter training start date (YYYYMMDD): ");
    scanf("%d", &training_start_date);

    int option;
    do {
        printf("\n=== Certification Exam System ===\n");
        printf("1. Schedule an exam\n");
        printf("2. View exam schedule\n");
        printf("3. Check reminders\n");
        printf("4. Assign room (if today is exam day)\n");
        printf("0. Exit\n");
        printf("Select option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: schedule_exam(); break;
            case 2: display_schedule(); break;
            case 3: check_reminders(); break;
            case 4: assign_rooms(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (option != 0);

    return 0;
}
