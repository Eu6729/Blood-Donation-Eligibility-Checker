#include <stdio.h>

int get_int() {
    int temp = 0;
    while (temp != 1 && temp != 2) {
        scanf(" %d", &temp);
        while(getchar() != '\n');
        if (temp == 1 || temp == 2) {
            return temp;
        }
        printf("Please enter either 1(Yes) or 2(No): ");
    }
}

int main(void){
    int choice = 0;

    do{
        printf("\nWelcome to the Blood Donation Eligibility Checker!\n");
        printf("1. Check for eligibility\n2. Exit\nChoose: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        if(choice == 2){
            printf("Program terminated");
            return 0;
        }
    }while(choice != 1);

    int age = 0, weight = 0;

    printf("\nHow old are you?: ");
    scanf("%d", &age);
    while(getchar() != '\n');

    printf("Please enter your weight in KG: ");
    scanf("%d", &weight);
    while(getchar() != '\n');

    if((age < 18 || age > 65) || weight < 50){  //first eligibility check(Basic profile)
        printf("\nSorry, you are not eligible.\n");
        if(age < 18)
            printf("Your age is below 18 .\n");
        else if(age > 65)
            printf("Your age is above 65.\n");
        if(weight < 50)
            printf("Your weight is below 50kg.\n");
        return 0;
    }

    int high_risk = 0, ill_choice = 0;
    printf("\nPlease enter 1 for YES, and 2 for NO.\n");
    printf("Do you have any history of HIV, drug abuse, or any other high risk behaviour?\nAnswer: ");
    high_risk = get_int();

    if(high_risk == 1){     //second check (permanent disqualifiers)
        printf("Sorry, you are ineligible as you are a high risk donor..\n");
        return 0;
    }

    printf("\nAre you suffering from any illnesses?\nAnswer: ");
    ill_choice = get_int();
    if(ill_choice == 1){    //seperate if statements for evaluating kind of illness.
        int ill_categ = 0;
        printf("Please enter the corresponding number for you illness\n");
        printf("What kind of illness are you currently suffering from?\n"
            "Is it serious like a fever, TB, cancer, HIV, or other systemic infection? If so enter 1.\n"
            "Is it a minor illness such as cold, mild sore throat, no fever? If so enter 2.\n"
            "Answer: ");
        ill_categ = get_int();
        if(ill_categ == 1){
            printf("Sorry, you are not eligible as you are currently suffering from a major illness.\n");
            return 0;
        }
        else if(ill_categ == 2){
            printf("Sorry, you are being temporarily deferred as you are suffering from a minor illness, get well soon!\n"
                    "Please return once you are well\n");
            return 0;
        }
    }

    float hemo = 0;
    int travel = 0, meds = 0, tattoo = 0, preg = 0, sex = 0, hemo_eligibility = 0;

    printf("\nWhat's your biological sex?\n1 for MALE, 2 for FEMALE: ");
    sex = get_int();

    printf("\nPlease enter your hemoglobin levels: ");
    do {
        scanf(" %f", &hemo);
        while(getchar() != '\n');
    } while (hemo <= 0);

    if(sex == 1){
        if(hemo >= 12.5){
            hemo_eligibility = 1;
        }
        else{
            hemo_eligibility = 2;
        }
    }
    else if(sex == 2){
        if(hemo >= 13.0){
            hemo_eligibility = 1;
        }
        else{
            hemo_eligibility = 2;
        }
    }

    printf("\nHave you travelled to a high risk area (e.g., areas infested with malaria or zika) within the last 12 months?\n1 for YES, 2 for NO: "); 
    travel = get_int();

    printf("\nHave you been taking medications recently?\n1 for YES, 2 for NO: "); //temporary, see google docs tab "code future changes"
    meds = get_int();

    printf("\nDid you get a tatto within the last 12 months?\n1 for YES, 2 for NO: ");
    tattoo = get_int();

    if(sex == 2){
        printf("\nAre you currently pregrant or breastfeeding?\n1 for YES, 2 for NO: ");
        preg = get_int();
    }

    if(travel == 1 || meds == 1 || tattoo == 1 || preg == 1 || hemo_eligibility == 2){ // third and final check, temporary deferrals
        printf("Sorry you are being temporarily deferred due to the the following.\n");
        if(travel == 1)
            printf("You have recently travelled to high risk areas.\n");
        if(meds == 1)
            printf("You have taken medications that make you ineligible to be a blood donor.\n");
        if(tattoo == 1)
            printf("You got a tattoo within the last 12 months.\n");
        if(preg == 1 && sex == 2)
            printf("You are currently pregrant or breastfeeding.\n");
        if(hemo_eligibility == 2)
            printf("Your hemoglobin level is below the required threshold.\n");
        printf("Please return when those above no longer apply to you.\n");
        return 0;
    }

    printf("\nCongratulations, you are eligible to be a blood donor!\n");
return 0;
}
