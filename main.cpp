#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <raymath.h>

/////////////////////////////// COLORS
const Color transparent_lightgray = {50, 50, 50, 200};
///////////////////////////////

void mouse_circle(Vector2 mouse_pos ){

}
int main(int argc, char* argv[]){
    int width = 960; int height = 540; std::string window_name = "AntKnight";
    SetExitKey(KEY_F2);
    InitWindow(width, height, window_name.c_str());

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    //////////////////////////////MAIN LOOP//////////////////////////////////
    while(!WindowShouldClose()){
        ////////////////////////// Repeating variables
        Vector2 mouse_pos = GetMousePosition();
        float ft = GetFrameTime();
        //////////////////////////
        BeginDrawing();
        //////////////////////////
        ClearBackground(BLACK);

        DrawCircle(mouse_pos.x, mouse_pos.y, 15, transparent_lightgray);
        //////////////////////////
        EndDrawing();
    }
    //////////////////////////////End Of Loop////////////////////////////////
    CloseWindow();
}