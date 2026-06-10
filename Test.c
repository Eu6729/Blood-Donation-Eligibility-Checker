#include <stdio.h>

int main(void){
    int choice = 0;

    do{
        printf("Welcome to the Blood Donation Eligibility Checker!\n");
        printf("1. Check for eligibility\n2. Exit\nChoose: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        if(choice == 2){
            printf("Program terminated");
            return 0;
        }
    }while(choice != 1);

    int age = 0, weight = 0;

    printf("How old are you?: ");
    scanf("%d", &age);
    while(getchar() != '\n');

    printf("Please enter your weight in KG: ");
    scanf("%d", &weight);
    while(getchar() != '\n');

    if((age < 18 || age > 65) || weight < 50){  //first eligibility check(Basic profile)
        printf("Sorry, you are not eligible.\n");
        if(age < 18 || age > 65)
            printf("Your age is below 18 or above 65.\n");
        if(weight < 50)
            printf("Your weight is below 50kg.\n");
        return 0;
    }

    int high_risk = 0, ill_choice = 0;
    printf("\nPlease enter 1 for YES, and 2 for NO.\n");
    printf("Do you have any history of HIV, drug abuse, or any other high risk behaviour?\nAnswer: ");
    scanf("%d", &high_risk);
    while(getchar() != '\n');

    printf("\nAre you suffering from any illnesses?\nAnswer: ");
    scanf("%d", &ill_choice);
    while(getchar() != '\n');
    if(ill_choice == 1){    //seperate if statements for evaluating kind of illness.
        int ill_categ = 0;
        printf("Please enter the corresponding number for you illness\n");
        printf("What kind of illness are you currently suffering from?\n"
            "Is it serious like a fever, TB, cancer, HIV, or other systemic infection? If so enter 1.\n"
            "Is it a minor illness such as cold, mild sore throat, no fever? If so enter 2.\n"
            "Answer: ");
        scanf("%d", &ill_categ);
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

    if(high_risk == 1){     //second check (permanent disqualifiers)
        printf("Sorry, you are ineligible as you are a high risk donor..\n");
        return 0;
    }

    float hemo = 0;
    int travel = 0, meds = 0, tattoo = 0, preg = 0, sex = 0, hemo_eligibility = 0;

    printf("What's your biological sex?\n1 for MALE, 2 for FEMALE: ");
    scanf("%d", &sex);
    while(getchar() != '\n');

    printf("Please enter your hemoglobin levels: ");
    scanf("%f", &hemo);
    while(getchar() != '\n');

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
    scanf("%d", &travel);
    while(getchar() != '\n');

    printf("\nHave you been taking medications recently?\n1 for YES, 2 for NO: "); //temporary, see google docs tab "code future changes"
    scanf("%d", &meds);
    while(getchar() != '\n');

    printf("\nDid you get a tatto within the last 12 months?\n1 for YES, 2 for NO: ");
    scanf("%d", &tattoo);
    while(getchar() != '\n');

    if(sex == 2){
        printf("\nAre you currently pregrant or breastfeeding?\n1 for YES, 2 for NO: ");
        scanf("%d", &preg);
        while(getchar() != '\n');
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
