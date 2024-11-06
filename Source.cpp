#include "raylib.h"
#include <cmath>
#include <ctime>

#pragma warning(disable : 4996)

void DrawLineBresenham(int x0, int y0, int x1, int y1, Color color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void DrawClock(float centerX, float centerY, float radius) {
    
    time_t now = time(0);
    tm* ltm = localtime(&now);

    float seconds = ltm->tm_sec;
    float minutes = ltm->tm_min + seconds / 60.0;
    float hours = ltm->tm_hour % 12 + minutes / 60.0;

    float hourAngle = (hours / 12.0) * 2 * PI - PI / 2;
    float minuteAngle = (minutes / 60.0) * 2 * PI - PI / 2;
    float secondAngle = (seconds / 60.0) * 2 * PI - PI / 2;

    DrawLineBresenham(centerX, centerY, centerX + radius * 0.5 * cos(hourAngle),centerY + radius * 0.5 * sin(hourAngle), DARKGRAY);

    DrawLineBresenham(centerX, centerY, centerX + radius * 0.7 * cos(minuteAngle), centerY + radius * 0.7 * sin(minuteAngle), GRAY);

    DrawLineBresenham(centerX, centerY, centerX + radius * 0.9 * cos(secondAngle), centerY + radius * 0.9 * sin(secondAngle), RED);

    DrawCircleLines(centerX, centerY, radius, BLACK);
}

int main() {
    InitWindow(800, 600, "Analog Clock with Bresenham");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float centerX = GetScreenWidth() / 2;
        float centerY = GetScreenHeight() / 2;
        float radius = 200;

        DrawClock(centerX, centerY, radius);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
