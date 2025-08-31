#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

void setup()
{
  GD.begin();
}

void loop()
{
  int i;

  GD.VertexFormat(2);   // 2 bits of subpixel precision

  GD.VertexTranslateX(PIXELS(GD.w / 2));
  GD.VertexTranslateY(PIXELS(GD.h / 2));
  GD.Clear();

  int R = GD.h / 2 - 1;     // outside radius

  // Draw radial rings
  GD.Begin(POINTS);
  for (i = 0; i < 10; i++) {
    int r = map(i, 0, 9, PIXELS(R), PIXELS(30));

    GD.ColorRGB(255, 255, 255);
    GD.PointSize(r);
    GD.Vertex2f(0, 0);

    GD.ColorRGB(0, 0, 0);
    GD.PointSize(r - PIXELS(1));
    GD.Vertex2f(0, 0);
  }

  // Draw rays
  GD.ColorRGB(255, 255, 255);
  GD.Begin(LINES);
  for (i = 0; i < 8; i++) {
    int x, y;
    int theta = map(i, 0, 8, 0, 65536L);    // angle in Furmans

    GD.polar(x, y, 4 * R, theta);
    GD.Vertex2f(0, 0);
    GD.Vertex2f(x, y);
  }
  GD.swap();
}
