#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define the different screens of the application
typedef enum { STATE_MENU, STATE_PROFILE, STATE_MEDICAL, STATE_RESULT } AppState;

int main(void) {
    // 1. Initialization
    const int screenWidth = 800;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "Blood Donation Eligibility Checker");
    SetTargetFPS(60);

    // Make the UI font slightly larger
    GuiLoadStyleDefault();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    AppState currentState = STATE_MENU;

    // --- State Variables (Replacing local variables in your console version) ---
    // Profile
    float age = 25.0f;
    float weight = 60.0f;
    int sex = 0; // 0: Male, 1: Female

    // Medical
    float hemo = 13.0f;
    bool travel = false;
    bool meds = false;
    bool tattoo = false;
    bool risk = false;
    
    int illness = 0; // 0: None, 1: Minor, 2: Major
    bool preg = false;

    // Results Buffer
    int resultStatus = 0; // 0: Ineligible, 1: Eligible, 2: Deferred
    char reasons[10][256]; 
    int reasonCount = 0;

    // 2. Main Game/App Loop
    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
            
            // ----------------------------------------------------
            // STATE: MAIN MENU
            // ----------------------------------------------------
            case STATE_MENU: {
                DrawText("Blood Donation Eligibility Checker", 150, 150, 30, DARKGRAY);
                
                if (GuiButton((Rectangle){ 250, 250, 300, 60 }, "Start Eligibility Check")) {
                    currentState = STATE_PROFILE;
                }
                if (GuiButton((Rectangle){ 250, 330, 300, 60 }, "Exit")) {
                    CloseWindow();
                    return 0; 
                }
            } break;

            // ----------------------------------------------------
            // STATE: PROFILE INPUTS
            // ----------------------------------------------------
            case STATE_PROFILE: {
                DrawText("STEP 1: Basic Profile", 50, 50, 30, DARKGRAY);

                GuiLabel((Rectangle){ 50, 120, 150, 30 }, "Age:");
                GuiSliderBar((Rectangle){ 200, 120, 300, 30 }, "1", "100", &age, 1, 100);
                DrawText(TextFormat("\t%.0f years", age), 520, 125, 20, DARKGRAY);

                GuiLabel((Rectangle){ 50, 180, 150, 30 }, "Weight (kg):");
                GuiSliderBar((Rectangle){ 200, 180, 300, 30 }, "30", "150", &weight, 30, 150);
                DrawText(TextFormat("\t%.1f kg", weight), 520, 185, 20, DARKGRAY);

                GuiLabel((Rectangle){ 50, 240, 150, 30 }, "Biological Sex:");
                GuiToggleGroup((Rectangle){ 200, 240, 150, 30 }, "MALE;FEMALE", &sex);

                // Navigation
                if (GuiButton((Rectangle){ 50, 500, 150, 50 }, "Back")) {
                    currentState = STATE_MENU;
                }
                if (GuiButton((Rectangle){ 600, 500, 150, 50 }, "Next")) {
                    currentState = STATE_MEDICAL;
                }
            } break;

            // ----------------------------------------------------
            // STATE: MEDICAL HISTORY
            // ----------------------------------------------------
            case STATE_MEDICAL: {
                DrawText("STEP 2: Medical History", 50, 50, 30, DARKGRAY);

                GuiLabel((Rectangle){ 50, 100, 250, 30 }, "Hemoglobin (g/dL):");
                GuiSliderBar((Rectangle){ 300, 100, 300, 30 }, "5", "20", &hemo, 5, 20);
                DrawText(TextFormat("\t%.1f", hemo), 620, 105, 20, DARKGRAY);

                // Checkboxes for Yes/No questions
                GuiCheckBox((Rectangle){ 50, 160, 20, 20 }, "Travelled to malaria/Zika areas in last 12 mos?", &travel);
                GuiCheckBox((Rectangle){ 50, 200, 20, 20 }, "Taken antibiotics/meds in past week?", &meds);
                GuiCheckBox((Rectangle){ 50, 240, 20, 20 }, "Tattoo or piercing in last 12 months?", &tattoo);
                GuiCheckBox((Rectangle){ 50, 280, 20, 20 }, "History of HIV, IV drugs, high-risk behavior?", &risk);

                GuiLabel((Rectangle){ 50, 330, 250, 30 }, "Current Illness:");
                GuiToggleGroup((Rectangle){ 300, 330, 100, 30 }, "None;Minor;Major", &illness);

                // Only show pregnancy option if Female (sex == 1)
                if (sex == 1) { 
                    GuiCheckBox((Rectangle){ 50, 380, 20, 20 }, "Currently pregnant or breastfeeding?", &preg);
                } else {
                    preg = false; // Auto-reset if switched back to Male
                }

                // Navigation
                if (GuiButton((Rectangle){ 50, 500, 150, 50 }, "Back")) {
                    currentState = STATE_PROFILE;
                }
                
                // CALCULATION LOGIC TRIGGERED HERE
                if (GuiButton((Rectangle){ 600, 500, 150, 50 }, "Calculate")) {
                    
                    reasonCount = 0; // Reset reasons list

                    // Re-implementing your boolean logic
                    bool p = (age >= 18.0f && age <= 65.0f);
                    bool q = (weight >= 50.0f);
                    bool r = (sex == 0); // 0 = Male, 1 = Female
                    
                    bool s = r ? (hemo >= 13.0f) : (hemo >= 12.0f);
                    bool w_healthy = (illness == 0);
                    bool w_minor = (illness == 1);
                    bool w_major = (illness == 2);

                    if (!p || !q || w_major || risk) {
                        resultStatus = 0; // INELIGIBLE
                        if (!p) strcpy(reasons[reasonCount++], "- Age is outside the safe range (18-65).");
                        if (!q) strcpy(reasons[reasonCount++], "- Weight is below the 50kg threshold.");
                        if (w_major) strcpy(reasons[reasonCount++], "- Currently suffering from a major active illness.");
                        if (risk) strcpy(reasons[reasonCount++], "- High-risk behavioral/medical history flags.");
                    } 
                    else if (p && q && s && !travel && !meds && !tattoo && !risk && (r || !preg) && w_healthy) {
                        resultStatus = 1; // ELIGIBLE
                        strcpy(reasons[reasonCount++], "Congratulations! You meet all health");
                        strcpy(reasons[reasonCount++], "and safety conditions to donate blood.");
                    } 
                    else {
                        resultStatus = 2; // DEFERRED
                        if (!s) strcpy(reasons[reasonCount++], "- Hemoglobin levels are temporarily outside target.");
                        if (w_minor) strcpy(reasons[reasonCount++], "- Recovering from a minor illness.");
                        if (travel) strcpy(reasons[reasonCount++], "- Recent travel to infectious zones.");
                        if (meds) strcpy(reasons[reasonCount++], "- Active window for recent medication.");
                        if (tattoo) strcpy(reasons[reasonCount++], "- Piercing/Tattoo deferral window has not passed.");
                        if (!r && preg) strcpy(reasons[reasonCount++], "- Pregnancy/Breastfeeding requires recovery time.");
                    }

                    currentState = STATE_RESULT;
                }
            } break;

            // ----------------------------------------------------
            // STATE: RESULTS SCREEN
            // ----------------------------------------------------
            case STATE_RESULT: {
                DrawText("EVALUATION RESULTS", 250, 50, 30, DARKGRAY);

                Color statusColor = GRAY;
                char statusText[50] = "";

                // Determine display color and header based on logic outcome
                if (resultStatus == 0) {
                    statusColor = RED;
                    strcpy(statusText, "STATUS: INELIGIBLE");
                } else if (resultStatus == 1) {
                    statusColor = DARKGREEN;
                    strcpy(statusText, "STATUS: ELIGIBLE");
                } else if (resultStatus == 2) {
                    statusColor = ORANGE;
                    strcpy(statusText, "STATUS: TEMPORARILY DEFERRED");
                }

                DrawText(statusText, 50, 120, 30, statusColor);
                DrawText("Reasoning / Notes:", 50, 180, 20, DARKGRAY);
                
                // Draw all calculated reasons row-by-row
                for (int i = 0; i < reasonCount; i++) {
                    DrawText(reasons[i], 70, 220 + (i * 30), 20, BLACK);
                }

                if (GuiButton((Rectangle){ 300, 500, 200, 50 }, "Back to Main Menu")) {
                    currentState = STATE_MENU;
                }
            } break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}