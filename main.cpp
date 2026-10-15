#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <raymath.h>
/////////////////////////////// Textures
Texture2D bg_sp_sheet;
Texture2D play_button;
/////////////////////////////// COLORS
const Color TRANSPARENT_WHITE = {1, 1, 1, 25};
///////////////////////////////
Rectangle next_frame(Texture2D sheet, int frames){
    return {(float)sheet.width / frames, 0, sheet.width / frames, sheet.height};
}
Rectangle anim(Texture2D sheet, int frames, float anim_speed){
    static int currentframe = 0;
    static float elapsed = 0;
    static Texture2D frame = sheet;
    float ft = GetFrameTime();
    static float frame_width = (float)sheet.width / frames;
    elapsed += ft;
    if(elapsed >= anim_speed) {
        currentframe++;
        if (currentframe > frames - 1) currentframe = 0;
        
        elapsed = 0;
    }
    return {currentframe * frame_width  , 0.0f, frame_width, sheet.height};
}

int main(int argc, char* argv[]){
    ////////////////////////////VARIABLES////////////////////////////////////
    int width = 960; int height = 540; std::string window_name = "AntKnight";
    SetExitKey(KEY_F2);
    InitWindow(width, height, window_name.c_str());

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    bg_sp_sheet = LoadTexture("Assets/Texture/gui/bg_texture.png");
    //////////////////////////////MAIN LOOP//////////////////////////////////
    while(!WindowShouldClose()){
        ////////////////////////// Repeating variables
        Vector2 mouse_pos = GetMousePosition();
        float ft = GetFrameTime();
        //////////////////////////
        BeginDrawing();
        //////////////////////////
        ClearBackground(BLACK);
        DrawTexturePro(bg_sp_sheet, anim(bg_sp_sheet, 2, 0.6), {0, 0, width, height}, {0, 0}, 0, WHITE);
        DrawTexturePro()
        
        if(IsCursorOnScreen())DrawCircle(mouse_pos.x, mouse_pos.y, 30, TRANSPARENT_WHITE);
        //////////////////////////
        EndDrawing();
    }
    //////////////////////////////End Of Loop////////////////////////////////
    CloseWindow();
}