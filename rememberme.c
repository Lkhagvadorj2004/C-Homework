#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 6
#define MAX_MSGS 10
#define MAX_STR 256

// Immutable memorial array (failures only) - Name,...,Email
const char* memorial01_arr[2] = {
    "Candidate Five,1.60,30.5,fail,five@example.com",
    "Candidate Six,1.82,22.2,fail,six@example.com"
};

// Rolling paper array
char rollingpp01[MAX_MSGS][MAX_STR];

// Candidate name map for failed candidates
const char* failed_names[2] = {
    "Candidate Five",
    "Candidate Six"
};

// Function to retrieve email by candidate name
const char* get_email_by_name(const char* name) {
    for (int i = 0; i < 2; i++) {
        if (strstr(memorial01_arr[i], name) != NULL) {
            // Extract email from memorial line
            const char* ptr = strrchr(memorial01_arr[i], ',');
            if (ptr != NULL) return ptr + 1;
        }
    }
    return NULL;
}

// Display messages for a specific candidate
void display_messages(const char* recipient_name) {
    int found = 0;
    printf("\n--- Rolling Papers for %s ---\n", recipient_name);
    for (int i = 0; i < MAX_MSGS; i++) {
        if (strstr(rollingpp01[i], recipient_name) != NULL) {
            printf("%s\n", rollingpp01[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No messages found for %s.\n", recipient_name);
    }
}

// Check if a name is an unsuccessful candidate
int is_failed_candidate(const char* name) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(name, failed_names[i]) == 0) return 1;
    }
    return 0;
}

int main() {
    // Step 1: All passed candidates must write messages
    const char* successful_names[4] = {
        "Park Ji-yeon",
        "Ethan Smith",
        "Helena Silva",
        "Liam Wilson"
    };

    char recipient[MAX_STR];
    char message[MAX_STR];
    int msg_index = 0;

    printf("=== Rolling Paper Input ===\n");
    for (int i = 0; i < 4; i++) {
        printf("\n%s's turn to write a message.\n", successful_names[i]);
        printf("Enter recipient's name (Candidate Five or Candidate Six): ");
        fgets(recipient, MAX_STR, stdin);
        recipient[strcspn(recipient, "\n")] = '\0';  // remove newline

        if (!is_failed_candidate(recipient)) {
            printf("Invalid recipient. Skipping.\n");
            continue;
        }

        printf("Enter message to %s: ", recipient);
        fgets(message, MAX_STR, stdin);
        message[strcspn(message, "\n")] = '\0';

        snprintf(rollingpp01[msg_index++], MAX_STR, "\"%s\": \"%s\"", successful_names[i], message);
    }

    // Step 2: View messages for failed candidate
    char query_name[MAX_STR];
    printf("\n=== Retrieve Rolling Paper ===\n");
    printf("Enter failed candidate name to view messages: ");
    fgets(query_name, MAX_STR, stdin);
    query_name[strcspn(query_name, "\n")] = '\0';

    if (is_failed_candidate(query_name)) {
        const char* email = get_email_by_name(query_name);
        display_messages(query_name);

        // Bonus: Send email
        printf("\nWould you like to send this message to %s (%s)? (yes/no): ", query_name, email);
        char decision[MAX_STR];
        fgets(decision, MAX_STR, stdin);
        decision[strcspn(decision, "\n")] = '\0';

        if (strcmp(decision, "yes") == 0) {
            printf("Email has been sent to %s.\n", email);
        } else {
            printf("Email was not sent.\n");
        }
    } else {
        printf("This candidate was not in the failed list.\n");
    }

    return 0;
}
