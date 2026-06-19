#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int get_input_1_or_2(const char *opt1, const char *opt2) { //new parameters for dynamic error message.
    char buffer[100];
    int choice = 0;
    char extra;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again: ");
            continue;
        }

        if (sscanf(buffer, "%d %c", &choice, &extra) == 1) {
            if (choice == 1 || choice == 2) {
                return choice;
            }
        }
        printf("Invalid input. Please enter either 1(%s) or 2(%s): ", opt1, opt2); //give correct choices, no longer just yes or no.
    }
}

double get_positive_measurement() {
    char buffer[100];
    double value = 0;
    char extra;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again: ");
            continue;
        }

        if (sscanf(buffer, "%lf %c", &value, &extra) == 1) {
            if (value > 0) {
                return value;
            }
        }
        printf("Invalid input. Please enter a valid positive number: ");
    }
}

struct MedHistory{
    int meds_anti;
    int meds_pros;
    int pros_fin;
    int pros_dut;
    int meds_acne;
    int acne_iso;
    int acne_aci;
    int meds_blood;
    int blood_coag;
    int blood_plate;
    int meds_HIV;
    int HIV_oral;
    int HIV_inject;
    int meds_art;
    int art_upa;
    int art_myco;
    int art_lef;
};

struct MedHistory user_meds = {2}; //default to no

int main(void) {
    int menu_choice = 0;

    printf("\nWelcome to the Blood Donation Eligibility Checker!\n");
    printf("1. Check for eligibility\n2. Exit\nChoose: ");
    
    menu_choice = get_input_1_or_2("Check Eligibility", "Exit");
    if (menu_choice == 2) {
        printf("Program terminated.\n");
        return 0;
    }

    printf("\nSTEP 1: Basic Profiles\n");
    printf("How old are you?: ");
    double actual_age = get_positive_measurement();

    printf("Please enter your weight in KG: ");
    double actual_weight = get_positive_measurement();

    printf("What's your biological sex?\n1 for MALE, 2 for FEMALE: ");
    // Customized for Biological Sex
    int actual_sex = get_input_1_or_2("MALE", "FEMALE");

    printf("\nSTEP 2: Medical History & Screening\n");
    printf("Please enter your hemoglobin level (g/dL): ");
    double actual_hemo = get_positive_measurement();

    printf("Have you travelled to malaria or Zika-prone areas within the last 12 months?\n1 for YES, 2 for NO: "); 
    int actual_travel = get_input_1_or_2("YES", "NO");

    printf("Have you taken medications recently?\n1 for YES, 2 for NO: "); 
    int actual_meds = get_input_1_or_2("YES", "NO");

    if(actual_meds == 1){
        printf("Have you taken antibiotics within the last 48 hours?\n1 for YES, 2 for NO: ");
        user_meds.meds_anti = get_input_1_or_2("YES", "NO");

        printf("Have you been taking Hair loss and/or prostate medications?\n1 for YES, 2 for NO: ");
        user_meds.meds_pros = get_input_1_or_2("YES", "NO");
        if(user_meds.meds_pros == 1){
            printf("\tHave you been taking Finasteride (Propecia for hair loss, Proscar for prostate) within the last 1 month?\n\t1 for YES, 2 for NO: ");
             user_meds.pros_fin = get_input_1_or_2("YES", "NO");

            printf("\tHave you been taking Dutasteride (Avodart, Jalyn) within the last 6 months?\n\t1 for YES, 2 for NO: ");
             user_meds.pros_dut = get_input_1_or_2("YES", "NO");
        }

        printf("Have you taken any acne treatments recently?\n1 for YES, 2 for NO: ");
        user_meds.meds_acne = get_input_1_or_2("YES", "NO");
        if( user_meds.meds_acne == 1){
            printf("\tDid you take Isotretinoin (Accutane, Claravis, Absorica, Amnesteem) for your acne within the last 1 month?\n\t1 for YES, 2 for NO: ");
            user_meds.acne_iso = get_input_1_or_2("YES", "NO");
            printf("\tDid you take Acitretin (Soriatane) for your acne within the last 3 years?\n\t1 for YES, 2 for NO: ");
            user_meds.acne_aci = get_input_1_or_2("YES", "NO");
        }

        printf("Have you been taking blood thinners and/or antiplatelet drugs?\n1 for YES, 2 for NO: ");
        user_meds.meds_blood = get_input_1_or_2("YES", "NO");
        if(user_meds.meds_blood == 1){
            printf("\tHave you been taking Anticoagulants (Coumadin/Warfarin, Eliquis, Xarelto, Lovenox, Heparin) within the last 7 days?\n\t1 for YES, 2 for NO: ");
            user_meds.blood_coag = get_input_1_or_2("YES", "NO");
            printf("\tHave you been taking Antiplatelet Agents (Plavix, Effient, Brilinta) within the last 7 days?\n\t1 for YES, 2 for NO: ");
            user_meds.blood_plate = get_input_1_or_2("YES", "NO");
        }

        printf("Have you been taking HIV Prevention Medications (PrEP and PEP) recently?\n1 for YES, 2 for NO: ");
        user_meds.meds_HIV = get_input_1_or_2("YES", "NO");
        if(user_meds.meds_HIV == 1){
            printf("\tHave you been taking Oral PrEP/PEP (Truvada, Descovy) for the last 3 months?\n\t1 for YES, 2 for NO: ");
            user_meds.HIV_oral = get_input_1_or_2("YES", "NO");
            printf("\tHave you been taking Injectable PrEP (Apretude) within the last 2 years?\n\t1 for YES, 2 for NO: ");
            user_meds.HIV_inject = get_input_1_or_2("YES", "NO");
        }

        printf("Have you been taking Rheumatoid Arthritis & Immunosuppressants recently?\n1 for YES, 2 for NO: ");
        user_meds.meds_art = get_input_1_or_2("YES", "NO");
        if(user_meds.meds_art == 1){
            printf("\tHave you been taking Upadacitinib (Rinvoq) within the last 1 month?\n\t1 for YES, 2 for NO: ");
            user_meds.art_upa = get_input_1_or_2("YES", "NO");
            printf("\tHave you been taking Mycophenolate mofetil (CellCept) within the last 6 weeks?\n\t1 for YES, 2 for NO: ");
            user_meds.art_myco = get_input_1_or_2("YES", "NO");
            printf("\tHave you been taking Leflunomide (Arava) within the last 2 years?\n\t1 for YES, 2 for NO: ");
            user_meds.art_lef = get_input_1_or_2("YES", "NO");
        }

        printf("\n\n");
    }

    printf("Have you had a tattoo or piercing in the last 12 months?\n1 for YES, 2 for NO: ");
    int actual_tattoo = get_input_1_or_2("YES", "NO");

    printf("Do you have a history of HIV, IV drug use, or other high-risk behaviour?\n1 for YES, 2 for NO: ");
    int actual_risk = get_input_1_or_2("YES", "NO");

    int actual_illness = 2;
    int illness_severity = 0;
    printf("Are you currently experiencing any illness or symptoms?\n1 for YES, 2 for NO: ");
    actual_illness = get_input_1_or_2("YES", "NO");
    
    if (actual_illness == 1) {
        printf("What kind of illness?\n1 for Major (fever, TB, cancer, HIV, etc.)\n2 for Minor (Mild cold/sore throat, etc.): ");
        // Customized for Illness Severity
        illness_severity = get_input_1_or_2("Major", "Minor");
    }

    int actual_preg = 2;
    if (actual_sex == 2) {
        printf("Are you currently pregnant or breastfeeding?\n1 for YES, 2 for NO: ");
        actual_preg = get_input_1_or_2("YES", "NO");
    }

    // --- Logic Processing Block ---
    bool p = (actual_age >= 18 && actual_age <= 65);
    bool q = (actual_weight >= 50);
    bool r = (actual_sex == 1); // True = Male, False = Female
    
    bool s = false;
    if (r) { 
        s = (actual_hemo >= 13.0);
    } else { 
        s = (actual_hemo >= 12.0);
    }

    bool t = (actual_travel == 1);
    bool u = (actual_meds == 1) && (
            user_meds.meds_anti == 1||
            user_meds.pros_fin == 1 ||
            user_meds.pros_dut == 1 ||
            user_meds.acne_iso == 1 ||
            user_meds.acne_aci == 1 ||
            user_meds.blood_coag == 1 ||
            user_meds.blood_plate == 1 ||
            user_meds.HIV_oral == 1 ||
            user_meds.HIV_inject == 1 ||
            user_meds.art_lef == 1 ||
            user_meds.art_myco == 1 ||
            user_meds.art_upa == 1);
    bool v = (actual_tattoo == 1);
    bool x = (actual_risk == 1);
    bool y = (actual_preg == 1);
    
    bool w_healthy = (actual_illness == 2);
    bool w_minor   = (actual_illness == 1 && illness_severity == 2);
    bool w_major   = (actual_illness == 1 && illness_severity == 1);

    printf("\n=========================================\n");
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
        if (u) {
            printf(" - Active window for recent medication processing:\n");
            if (user_meds.meds_anti == 1) printf("   * Antibiotics (last 48 hours)\n");
            if (user_meds.pros_fin == 1) printf("   * Finasteride (last 1 month)\n");
            if (user_meds.pros_dut == 1) printf("   * Dutasteride (last 6 months)\n");
            if (user_meds.acne_iso == 1) printf("   * Isotretinoin (last 1 month)\n");
            if (user_meds.acne_aci == 1) printf("   * Acitretin (last 3 years)\n");
            if (user_meds.blood_coag == 1) printf("   * Anticoagulants (last 7 days)\n");
            if (user_meds.blood_plate == 1) printf("   * Antiplatelet Agents (last 7 days)\n");
            if (user_meds.HIV_oral == 1) printf("   * Oral PrEP/PEP (last 3 months)\n");
            if (user_meds.HIV_inject == 1) printf("   * Injectable PrEP (last 2 years)\n");
            if (user_meds.art_upa == 1) printf("   * Upadacitinib (last 1 month)\n");
            if (user_meds.art_myco == 1) printf("   * Mycophenolate mofetil (last 6 weeks)\n");
            if (user_meds.art_lef == 1) printf("   * Leflunomide (last 2 years)\n");
        }
        if (v) printf(" - Piercing/Tattoo deferral window has not yet passed.\n");
        if (!r && y) printf(" - Pregnancy/Breastfeeding requires structural recovery windows.\n");
        printf("\nPlease return to donate once the above items clear up!\n");
        return 0;
    }
    return 0;
}