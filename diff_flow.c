#include <stdio.h>
#include <stdbool.h>

int get_input_1_or_2() {
    int choice = 0;
    while (choice != 1 && choice != 2) {
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
        }
        if (choice == 1 || choice == 2) {
            return choice;
        }
        printf("Please enter either 1(Yes) or 2(No): ");
    }
    return choice;
}

double get_positive_measurement() {
    double value = 0;
    while (value <= 0) {
        if (scanf("%lf", &value) != 1) {
            while (getchar() != '\n');
        }
        if (value <= 0) {
            printf("Please enter a valid positive number: ");
        }
    }
    return value;
}

int main(void) {
    int menu_choice = 0;

    printf("\nWelcome to the Blood Donation Eligibility Checker!\n");
    printf("1. Check for eligibility\n2. Exit\nChoose: ");
    if (scanf("%d", &menu_choice) != 1 || menu_choice == 2) {
        printf("Program terminated.\n");
        return 0;
    }

    printf("\nSTEP 1: Basic Profiles\n");
    printf("How old are you?: ");
    double actual_age = get_positive_measurement();

    printf("Please enter your weight in KG: ");
    double actual_weight = get_positive_measurement();

    printf("What's your biological sex?\n1 for MALE, 2 for FEMALE: ");
    int actual_sex = get_input_1_or_2();

    printf("\nSTEP 2: Medical History & Screening\n");
    printf("Please enter your hemoglobin level (g/dL): ");
    double actual_hemo = get_positive_measurement();

    printf("Have you travelled to malaria or Zika-prone areas within the last 12 months?\n1 for YES, 2 for NO: "); 
    int actual_travel = get_input_1_or_2();

    printf("Have you taken antibiotics or certain medications in the past week?\n1 for YES, 2 for NO: "); 
    int actual_meds = get_input_1_or_2();

    printf("Have you had a tattoo or piercing in the last 12 months?\n1 for YES, 2 for NO: ");
    int actual_tattoo = get_input_1_or_2();

    printf("Do you have a history of HIV, IV drug use, or other high-risk behaviour?\n1 for YES, 2 for NO: ");
    int actual_risk = get_input_1_or_2();

    int actual_illness = 2;
    int illness_severity = 0;
    printf("Are you currently experiencing any illness or symptoms?\n1 for YES, 2 for NO: ");
    actual_illness = get_input_1_or_2();
    if (actual_illness == 1) {
        printf("What kind of illness?\n1 for Major (fever, TB, cancer, HIV, or other systemic infection)\n2 for Minor (Mild cold/sore throat, etc.): ");
        illness_severity = get_input_1_or_2();
    }

    int actual_preg = 2;
    if (actual_sex == 2) {
        printf("Are you currently pregnant or breastfeeding?\n1 for YES, 2 for NO: ");
        actual_preg = get_input_1_or_2();
    }



    bool p = (actual_age >= 18 && actual_age <= 65);
    bool q = (actual_weight >= 50);
    bool r = (actual_sex == 1); // True = Male, False = Female
    
    bool s = false;
    if (r) { // If Male
        s = (actual_hemo >= 13.0);
    } else { // If Female
        s = (actual_hemo >= 12.0);
    }

    bool t = (actual_travel == 1);
    bool u = (actual_meds == 1);
    bool v = (actual_tattoo == 1);
    bool x = (actual_risk == 1);
    bool y = (actual_preg == 1);
    
    bool w_healthy = (actual_illness == 2);
    bool w_minor   = (actual_illness == 1 && illness_severity == 2);
    bool w_major   = (actual_illness == 1 && illness_severity == 1);

    if (!p || !q || w_major || x) {
        printf("Output Status: INELIGIBLE\n");
        printf("Reasoning:\n");
        if (!p) printf(" - Age is outside the safe range (18-65).\n");
        if (!q) printf(" - Weight is below the 50kg threshold.\n");
        if (w_major) printf(" - Currently suffering from a major active illness.\n");
        if (x) printf(" - High-risk behavioral/medical history flags.\n");
        return 0;
    }

    if (p && q && s && !t && !u && !v && !x && (r || !y) && w_healthy) {
        printf("Output Status: ELIGIBLE\n");
        printf("Congratulations! You meet all health and safety conditions to donate blood.\n");
        return 0;
    }

    if (p && q && !x && (!s || w_minor || t || u || v || (!r && y))) {
        printf("Output Status: TEMPORARILY DEFERRED\n");
        printf("Reasoning for temporary hold:\n");
        if (!s) printf(" - Hemoglobin levels are temporarily outside the target range.\n");
        if (w_minor) printf(" - Recovering from a minor illness. Please return when symptoms clear.\n");
        if (t) printf(" - Recent travel to infectious zones requiring a standard wait window.\n");
        if (u) printf(" - Active window for recent medication processing.\n");
        if (v) printf(" - Piercing/Tattoo deferral window has not yet passed.\n");
        if (!r && y) printf(" - Pregnancy/Breastfeeding requires structural recovery windows.\n");
        printf("\nPlease return to donate once the above items clear up!\n");
        return 0;
    }
    return 0;
}
