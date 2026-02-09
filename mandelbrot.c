
#include "raylib.h"
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

int mandelbrot(double cx, double cy, int maxIter) {
  double x = 0.0;
  double y = 0.0;
  int i = 0;
  while (x * x + y * y <= 4.0 && i < maxIter) {
    double xt = x * x - y * y + cx;
    y = 2.0 * x * y + cy;
    x = xt;
    i++;
  }
  return i;
}

int main(void) {
  InitWindow(WIDTH, HEIGHT, "mandelbrot");
  SetTargetFPS(60);

  double baseCenterX = -0.743643135;
  double baseCenterY = 0.131825963;

  double centerX = baseCenterX;
  double centerY = baseCenterY;

  double scale = 4.0 / WIDTH;
  double zoom = 0.985;

  Image img = GenImageColor(WIDTH, HEIGHT, BLACK);
  Texture2D tex = LoadTextureFromImage(img);

  while (!WindowShouldClose()) {
    scale *= pow(zoom, GetFrameTime() * 60.0);

    if (scale < 1e-12) {
      scale = 4.0 / WIDTH;
    }

    double t = GetTime() * 0.15;
    centerX = baseCenterX + cos(t) * scale * 200.0;
    centerY = baseCenterY + sin(t) * scale * 200.0;

    int maxIter = 120 + (int)(-log10(scale) * 25.0);

    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        double cx = (x - WIDTH / 2.0) * scale + centerX;
        double cy = (y - HEIGHT / 2.0) * scale + centerY;

        int iter = mandelbrot(cx, cy, maxIter);

        Color c;
        if (iter == maxIter) {
          c = (Color){10, 10, 20, 255};
        } else {
          double v = (double)iter / maxIter;
          c = (Color){(unsigned char)(sin(6.0 * v) * 127 + 128),
                      (unsigned char)(sin(6.0 * v + 2.0) * 127 + 128),
                      (unsigned char)(sin(6.0 * v + 4.0) * 127 + 128), 255};
        }

        ImageDrawPixel(&img, x, y, c);
      }
    }

    UpdateTexture(tex, img.data);

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(tex, 0, 0, WHITE);
    EndDrawing();
  }

  UnloadTexture(tex);
  UnloadImage(img);
  CloseWindow();
  return 0;
}
