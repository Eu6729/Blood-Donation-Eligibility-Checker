#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 720

struct MedHistory {
    bool meds_anti;
    bool meds_pros;
    bool pros_fin;
    bool pros_dut;
    bool meds_acne;
    bool acne_iso;
    bool acne_aci;
    bool meds_blood;
    bool blood_coag;
    bool meds_HIV;
    bool HIV_oral;
    bool HIV_inject;
    bool meds_art;
    bool art_upa;
    bool art_myco;
    bool art_lef;
};

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blood Donation Eligibility Checker");
    SetTargetFPS(60);

    // Center window to screen
    int monitorWidth = GetMonitorWidth(0);
    int monitorHeight = GetMonitorHeight(0);
    SetWindowPosition((monitorWidth - WINDOW_WIDTH) / 2, (monitorHeight - WINDOW_HEIGHT) / 2);

    // Font Config
    Font customFont = LoadFontEx("resources/Roboto-Regular.ttf", 20, NULL, 0);
    if (IsFontValid(customFont)) {
        GuiSetFont(customFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    } else {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 16); // Fallback size
    }

    // --- GUI State Variables ---
    float actual_age = 18.0f;
    float actual_weight = 50.0f;
    bool actual_sex_male = true; // true = MALE, false = FEMALE
    float actual_hemo = 13.5f;

    bool actual_travel = false;
    bool actual_meds = false;
    struct MedHistory user_meds = { 0 };

    bool actual_tattoo = false;
    bool actual_risk = false;
    bool actual_illness = false;
    bool illness_severity_major = false; // true = Major, false = Minor
    bool actual_preg = false;

    while (!WindowShouldClose())
    {
        // --- 1. LOGIC PROCESSING BLOCK ---
        bool p = (actual_age >= 18.0f && actual_age <= 65.0f);
        bool q = (actual_weight >= 50.0f);
        bool r = actual_sex_male; 
        
        bool s = r ? (actual_hemo >= 13.0f) : (actual_hemo >= 12.0f);
        bool t = actual_travel;
        bool u = actual_meds && (
                    user_meds.meds_anti || user_meds.pros_fin || user_meds.pros_dut || 
                    user_meds.acne_iso || user_meds.acne_aci || user_meds.blood_coag || 
                    user_meds.HIV_oral || user_meds.HIV_inject || user_meds.art_lef || 
                    user_meds.art_myco || user_meds.art_upa);
        bool v = actual_tattoo;
        bool x = actual_risk;
        bool y = (!r && actual_preg);
        
        bool w_healthy = !actual_illness;
        bool w_minor   = actual_illness && !illness_severity_major;
        bool w_major   = actual_illness && illness_severity_major;

        // --- 2. RENDER LAYER ---
        BeginDrawing();
            ClearBackground(WHITE);

            // Column 1: Basic Profiles & History
            GuiGroupBox((Rectangle){ 20, 20, 400, 320 }, "STEP 1: Basic Profiles");
            
            GuiSlider((Rectangle){ 140, 50, 200, 24 }, "Age:", TextFormat("%.0f yrs", actual_age), &actual_age, 0.0f, 100.0f);
            GuiSlider((Rectangle){ 140, 95, 200, 24 }, "Weight:", TextFormat("%.0f kg", actual_weight), &actual_weight, 0.0f, 150.0f);
            
            GuiToggle((Rectangle){ 140, 140, 200, 30 }, actual_sex_male ? "SEX: MALE" : "SEX: FEMALE", &actual_sex_male);
            GuiSlider((Rectangle){ 140, 190, 200, 24 }, "Hemoglobin:", TextFormat("%.1f g/dL", actual_hemo), &actual_hemo, 0.0f, 25.0f);
            
            GuiCheckBox((Rectangle){ 30, 240, 24, 24 }, "Travelled to Malaria/Zika zones (Last 12mo)", &actual_travel);
            GuiCheckBox((Rectangle){ 30, 275, 24, 24 }, "High-risk behavior/medical history flags", &actual_risk);

            GuiGroupBox((Rectangle){ 20, 360, 400, 160 }, "STEP 3: General Health Status");
            GuiCheckBox((Rectangle){ 30, 390, 24, 24 }, "Currently experiencing symptoms/illness", &actual_illness);
            if (actual_illness) {
                GuiToggle((Rectangle){ 60, 425, 200, 30 }, illness_severity_major ? "Severity: MAJOR" : "Severity: MINOR", &illness_severity_major);
            }
            if (!actual_sex_male) {
                GuiCheckBox((Rectangle){ 30, 475, 24, 24 }, "Currently pregnant or breastfeeding", &actual_preg);
            }

            GuiCheckBox((Rectangle){ 30, 535, 24, 24 }, "Had a tattoo or piercing in last 12mo", &actual_tattoo);

            // Column 2: Medication Framework
            GuiGroupBox((Rectangle){ 440, 20, 390, 500 }, "STEP 2: Medications & Screenings");
            GuiCheckBox((Rectangle){ 450, 45, 24, 24 }, "Has taken medications recently", &actual_meds);

            if (actual_meds) {
                GuiCheckBox((Rectangle){ 470, 85, 20, 20 }, "Antibiotics (last 48 hours)", &user_meds.meds_anti);
                
                GuiCheckBox((Rectangle){ 470, 120, 20, 20 }, "Hair loss / Prostate meds", &user_meds.meds_pros);
                if (user_meds.meds_pros) {
                    GuiCheckBox((Rectangle){ 500, 150, 16, 16 }, "Finasteride (last 1 month)", &user_meds.pros_fin);
                    GuiCheckBox((Rectangle){ 500, 175, 16, 16 }, "Dutasteride (last 6 months)", &user_meds.pros_dut);
                }

                GuiCheckBox((Rectangle){ 470, 210, 20, 20 }, "Acne Treatments", &user_meds.meds_acne);
                if (user_meds.meds_acne) {
                    GuiCheckBox((Rectangle){ 500, 240, 16, 16 }, "Isotretinoin (last 1 month)", &user_meds.acne_iso);
                    GuiCheckBox((Rectangle){ 500, 265, 16, 16 }, "Acitretin (last 3 years)", &user_meds.acne_aci);
                }

                GuiCheckBox((Rectangle){ 470, 300, 20, 20 }, "Blood Thinners / Antiplatelet", &user_meds.meds_blood);
                if (user_meds.meds_blood) {
                    GuiCheckBox((Rectangle){ 500, 330, 16, 16 }, "Anticoagulants active (last 7 days)", &user_meds.blood_coag);
                }

                GuiCheckBox((Rectangle){ 470, 365, 20, 20 }, "HIV Prevention (PrEP / PEP)", &user_meds.meds_HIV);
                if (user_meds.meds_HIV) {
                    GuiCheckBox((Rectangle){ 500, 395, 16, 16 }, "Oral PrEP/PEP (last 3 months)", &user_meds.HIV_oral);
                    GuiCheckBox((Rectangle){ 500, 420, 16, 16 }, "Injectable PrEP (last 2 years)", &user_meds.HIV_inject);
                }

                GuiCheckBox((Rectangle){ 470, 455, 20, 20 }, "Arthritis Meds / Immunosuppressants", &user_meds.meds_art);
                if (user_meds.meds_art) {
                    GuiCheckBox((Rectangle){ 500, 485, 14, 14 }, "Upadacitinib / Mycophenolate / Leflunomide", &user_meds.art_upa);
                    // Simplify mapping nested values to flag sub-conditions uniformly
                    user_meds.art_myco = user_meds.art_upa;
                    user_meds.art_lef = user_meds.art_upa;
                }
            }

            // Results Panel Block
            GuiLine((Rectangle){ 20, 570, 810, 20 }, NULL);
            GuiGroupBox((Rectangle){ 20, 595, 810, 110 }, "DIAGNOSTIC STATUS OUTPUT");

            int textY = 620;
            float spacing = 2.0f; // Standard letter spacing

            if (!p || !q || w_major || x) {
                DrawTextEx(customFont, "STATUS: INELIGIBLE", (Vector2){ 40, textY }, 22, spacing, RED);
                
                if (!p) DrawTextEx(customFont, "- Age is outside the safe range (18-65).", (Vector2){ 320, textY }, 16, spacing, DARKGRAY);
                if (!q) DrawTextEx(customFont, "- Weight is below the 50kg threshold.", (Vector2){ 320, textY + 20 }, 16, spacing, DARKGRAY);
                if (w_major) DrawTextEx(customFont, "- Suffers from major active illness symptoms.", (Vector2){ 320, textY + 40 }, 16, spacing, DARKGRAY);
                if (x) DrawTextEx(customFont, "- High-risk history flags triggered.", (Vector2){ 320, textY + 60 }, 16, spacing, DARKGRAY);
            } 
            else if (p && q && s && !t && !u && !v && !x && (r || !y) && w_healthy) {
                DrawTextEx(customFont, "STATUS: ELIGIBLE", (Vector2){ 40, textY }, 22, spacing, GREEN);
                DrawTextEx(customFont, "Congratulations! You meet all guidelines to donate blood.", (Vector2){ 320, textY }, 18, spacing, DARKGRAY);
            } 
            else {
                DrawTextEx(customFont, "STATUS: DEFERRED", (Vector2){ 40, textY }, 22, spacing, ORANGE);
                int offset = 0;
                
                if (!s) { DrawTextEx(customFont, "- Hemoglobin levels are outside safe boundaries.", (Vector2){ 320, textY + offset }, 16, spacing, DARKGRAY); offset += 20; }
                if (w_minor) { DrawTextEx(customFont, "- Recovering from minor illness symptoms.", (Vector2){ 320, textY + offset }, 16, spacing, DARKGRAY); offset += 20; }
                if (t) { DrawTextEx(customFont, "- Infectious zone travel window active.", (Vector2){ 320, textY + offset }, 16, spacing, DARKGRAY); offset += 20; }
                if (u) { DrawTextEx(customFont, "- Dynamic medication processing holding period.", (Vector2){ 320, textY + offset }, 16, spacing, DARKGRAY); offset += 20; }
                if (v) { DrawTextEx(customFont, "- Body art piercing or tattoo deferral active.", (Vector2){ 320, textY + offset }, 16, spacing, DARKGRAY); offset += 20; }
                if (y) { DrawTextEx(customFont, "- Pregnancy recovery structural hold active.", (Vector2){ 320, textY + offset }, 16, spacing, DARKGRAY); offset += 20; }
            }

        EndDrawing();
    }

    if (IsFontValid(customFont)) UnloadFont(customFont);
    CloseWindow();
    return 0;
}