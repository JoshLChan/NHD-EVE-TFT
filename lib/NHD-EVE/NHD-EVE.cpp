#include <NHD-EVE.h>
#include <Arduino.h>

NHD_EVE::NHD_EVE(uint8_t index)
{
    _index = index;
}

uint8_t NHD_EVE::mainMenu()
{
    if (!_loadmainmenu)
    {
        GD.BitmapHandle(0);
        GD.cmd_loadimage(0, 0);
        GD.load("image3.jpg");
    }

    GD.ClearColorRGB(0xffffffff);
    GD.Clear();

    GD.VertexTranslateY((-_vsize / 2) * 16);
    GD.Begin(BITMAPS);
    GD.BitmapHandle(0);
    GD.cmd_scale(F16(0.7), F16(0.7));
    GD.cmd_setmatrix();
    GD.Vertex2f((_hsize / 2) * 12, 120 * 16);

    GD.ColorRGB(0x000000);
    GD.cmd_text(_hsize / 2, _vsize - 40, 31, OPT_CENTER, "TECH DEMO");

    GD.ColorRGB(0xffffffff);
    GD.cmd_bgcolor(_buttonclr);
    GD.TagMask(1);
    GD.cmd_button(((_hsize / 2) - 100), _vsize + 30, 200, 80, 30, OPT_FLAT | OPT_CENTER, "Prox. Sensor");
    GD.ColorRGB(0xffffffff);
    GD.cmd_bgcolor(_buttonclr);
    GD.TagMask(2);
    GD.cmd_button(((_hsize / 2) - 100) + 250, _vsize + 30, 200, 80, 30, OPT_FLAT | OPT_CENTER, "Slideshow");
    GD.ColorRGB(0xffffffff);
    GD.cmd_bgcolor(_buttonclr);
    GD.TagMask(3);
    GD.cmd_button(((_hsize / 2) - 100) - 250, _vsize + 30, 200, 80, 30, OPT_FLAT | OPT_CENTER, "Hello World!");

    GD.get_inputs();
    // Serial.println("X: " + (String)GD.inputs.x + " | Y: " + (String)GD.inputs.y);

    GD.swap();

    return 1;
}

void NHD_EVE::reset()
{
    GD.Clear();
    GD.swap();
    _loadmainmenu = false;
    _loadSlideShow = false;
}
void NHD_EVE::begin()
{

    GD.begin(0, 10, 5);
    GD.Clear();

    switch (_index)
    {
    case 0:
        init_320X240();
        break;
    case 1:
        init_480X272();
        break;
    case 2:
        init_800X480_4_3();
        break;
    case 3:
        init_800X480_5_0();
        break;
    case 4:
        init_800X480_7_0();
        Serial.print("7");
        break;
    default:
        break;
    }

    GD.Clear();
    GD.swap();

    // GD.cmd_calibrate();

    // GD.BitmapHandle(0);
    // GD.cmd_loadimage(0, 0);
    // GD.load("image3.jpg");

    // GD.BitmapHandle(1);
    // GD.cmd_loadimage(-1, 0);
    // GD.load("image2.jpg");

    // GD.BitmapHandle(1);
    // GD.cmd_loadimage(-1, 0);
    // GD.load("image3.jpg");

    // GD.BitmapHandle(2);
    // GD.cmd_loadimage(-1, 0);
    // GD.load("image4.jpg");
    // delay(10);
}

void NHD_EVE::proximityDisplay(int distance)
{

    // distance > _distance ? _distance += 5 : _distance -= 5;

    if (distance > _distance + 7 && _distance < 150)
        _distance += 5;
    if (distance < _distance - 7 && _distance > 0)
        _distance -= 5;
    GD.ClearColorRGB(_proximitybg);

    GD.Clear();

    GD.Begin(POINTS);
    GD.PointSize(16 * 200);
    GD.Vertex2ii(_hsize / 2, _vsize - 100);
    GD.PointSize(16 * 190);
    GD.ColorRGB(_proximitybg);
    GD.Vertex2ii(_hsize / 2, _vsize - 100);

    GD.ColorRGB(0xffffffff);
    GD.cmd_bgcolor(_proximitybg);

    GD.cmd_gauge(
        _hsize / 2,
        _vsize - 100,
        180,
        OPT_FLAT,
        5,
        4,
        150 - _distance,
        150);

    int gapWidth = 30;
    if (distance > 10)
        gapWidth = 40;
    if (distance > 100)
        gapWidth = 50;

    uint32_t caution = 0xffffffff;
    if (distance < 20 && distance > 10)
        caution = 0xfff740;
    if (distance < 10)
        caution = 0xba0000;

    GD.cmd_number(_hsize / 2, 130, 31, OPT_CENTER, distance);
    GD.cmd_text((_hsize / 2) + gapWidth + 20, 130, 28, OPT_CENTER, "CM");

    GD.Begin(RECTS);
    GD.ColorRGB(_proximitybg);
    GD.LineWidth(10 * 70); // corner radius 10.0 pixels
    GD.Vertex2ii((_hsize / 2) + 100, (_vsize / 2) - 50);
    GD.Vertex2ii((_hsize / 2) - 100, (_vsize / 2) - 50);

    GD.ColorRGB(caution);
    GD.LineWidth(10 * 35); // corner radius 10.0 pixels
    GD.Vertex2ii((_hsize / 2) + 100, (_vsize / 2) - 50);
    GD.Vertex2ii((_hsize / 2) - 100, (_vsize / 2) - 50);

    GD.ColorRGB(_proximitybg);
    GD.LineWidth(7 * 30); // corner radius 10.0 pixels
    GD.Vertex2ii((_hsize / 2) + gapWidth, (_vsize / 2) - 75);
    GD.Vertex2ii((_hsize / 2) - gapWidth, (_vsize / 2) - 75);

    GD.swap();
    GD.finish();
}

void NHD_EVE::helloWorld(char *text)
{
    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.cmd_text(_hsize / 2, _vsize / 2, 31, OPT_CENTER, text);
    GD.swap();
}

void NHD_EVE::slideshow()
{
    if (!_loadSlideShow)
    {
        _loadSlideShow = true;
        GD.BitmapHandle(0);
        GD.cmd_loadimage(0, 0);
        GD.load("image2.jpg");
    }
    if (_slideshowx > _hsize)
    {
        delay(5000);
        _slideshowx = 0;
        _slideshowindex >= 3 ? _slideshowindex = 1 : _slideshowindex++;
    }
    else
    {
        _slideshowx++;
    }

    GD.Clear();
    GD.Begin(BITMAPS);
    GD.VertexTranslateX(-_hsize * 16);

    switch (_slideshowindex)
    {
    case 1:
        ChangeSlide(0, 0, 0xffffff, 0x43b08f);
        break;
    case 2:
        ChangeSlide(0, 0, 0x43b08f, 0xf08989);
        break;
    case 3:
        ChangeSlide(0, 0, 0xf08989, 0xffffff);
        break;

    default:
        break;
    }

    GD.swap();

    Serial.println("x: " + (String)_slideshowx);
}

void NHD_EVE::ChangeSlide(uint8_t from, uint8_t to, uint32_t colorFrom, uint32_t colorTo)
{
    GD.BitmapHandle(from);
    GD.ColorRGB(colorFrom);
    GD.Vertex2f(_hsize * 16, 0);

    GD.BitmapHandle(to);
    GD.ColorRGB(colorTo);
    GD.Vertex2f(_slideshowx * 16, 0);
}

void NHD_EVE::init_320X240()
{
    _hsize = 320;
    _vsize = 240;
    GD.wr16(REG_HSIZE, 320);
    GD.wr16(REG_HCYCLE, 408);
    GD.wr16(REG_HOFFSET, 70);
    GD.wr16(REG_HSYNC0, 0);
    GD.wr16(REG_HSYNC1, 10);
    GD.wr16(REG_VSIZE, 240);
    GD.wr16(REG_VCYCLE, 263);
    GD.wr16(REG_VOFFSET, 13);
    GD.wr16(REG_VSYNC0, 0);
    GD.wr16(REG_VSYNC1, 2);
    GD.wr16(REG_PCLK, 8);
    GD.wr16(REG_SWIZZLE, 0);
    GD.wr16(REG_PCLK_POL, 0);
    GD.wr16(REG_CSPREAD, 1);
    GD.wr16(REG_DITHER, 1);
    GD.wr16(REG_ROTATE, 0);
    GD.swap();
}

void NHD_EVE::init_480X272()
{
    _hsize = 480;
    _vsize = 272;
    GD.wr16(REG_HSIZE, 480);
    GD.wr16(REG_HCYCLE, 548);
    GD.wr16(REG_HOFFSET, 43);
    GD.wr16(REG_HSYNC0, 0);
    GD.wr16(REG_HSYNC1, 41);
    GD.wr16(REG_VSIZE, 272);
    GD.wr16(REG_VCYCLE, 292);
    GD.wr16(REG_VOFFSET, 12);
    GD.wr16(REG_VSYNC0, 0);
    GD.wr16(REG_VSYNC1, 10);
    GD.wr16(REG_PCLK, 5);
    GD.wr16(REG_SWIZZLE, 0);
    GD.wr16(REG_PCLK_POL, 1);
    GD.wr16(REG_CSPREAD, 1);
    GD.wr16(REG_DITHER, 1);
    GD.wr16(REG_ROTATE, 0);
    GD.swap();
}

void NHD_EVE::init_800X480_4_3()
{
    _hsize = 800;
    _vsize = 480;
    GD.wr16(REG_HSIZE, 800);
    GD.wr16(REG_HCYCLE, 928);
    GD.wr16(REG_HOFFSET, 88);
    GD.wr16(REG_HSYNC0, 0);
    GD.wr16(REG_HSYNC1, 48);
    GD.wr16(REG_VSIZE, 480);
    GD.wr16(REG_VCYCLE, 525);
    GD.wr16(REG_VOFFSET, 32);
    GD.wr16(REG_VSYNC0, 0);
    GD.wr16(REG_VSYNC1, 3);
    GD.wr16(REG_PCLK, 2);
    GD.wr16(REG_SWIZZLE, 0);
    GD.wr16(REG_PCLK_POL, 1);
    GD.wr16(REG_CSPREAD, 0);
    GD.wr16(REG_DITHER, 1);
    GD.wr16(REG_ROTATE, 0);
    GD.swap();
}

void NHD_EVE::init_800X480_5_0()
{
    _hsize = 800;
    _vsize = 480;
    GD.wr16(REG_HSIZE, 800);
    GD.wr16(REG_HCYCLE, 928);
    GD.wr16(REG_HOFFSET, 88);
    GD.wr16(REG_HSYNC0, 0);
    GD.wr16(REG_HSYNC1, 48);
    GD.wr16(REG_VSIZE, 480);
    GD.wr16(REG_VCYCLE, 525);
    GD.wr16(REG_VOFFSET, 32);
    GD.wr16(REG_VSYNC0, 0);
    GD.wr16(REG_VSYNC1, 3);
    GD.wr16(REG_PCLK, 2);
    GD.wr16(REG_SWIZZLE, 0);
    GD.wr16(REG_PCLK_POL, 0);
    GD.wr16(REG_CSPREAD, 0);
    GD.wr16(REG_DITHER, 1);
    GD.wr16(REG_ROTATE, 0);
    GD.swap();
}

void NHD_EVE::init_800X480_7_0()
{
    _hsize = 800;
    _vsize = 480;
    GD.wr16(REG_HSIZE, 800);
    GD.wr16(REG_HCYCLE, 928);
    GD.wr16(REG_HOFFSET, 88);
    GD.wr16(REG_HSYNC0, 0);
    GD.wr16(REG_HSYNC1, 48);
    GD.wr16(REG_VSIZE, 480);
    GD.wr16(REG_VCYCLE, 525);
    GD.wr16(REG_VOFFSET, 32);
    GD.wr16(REG_VSYNC0, 0);
    GD.wr16(REG_VSYNC1, 3);
    GD.wr16(REG_PCLK, 2);
    GD.wr16(REG_SWIZZLE, 0);
    GD.wr16(REG_PCLK_POL, 1);
    GD.wr16(REG_CSPREAD, 0);
    GD.wr16(REG_DITHER, 1);
    GD.wr16(REG_ROTATE, 0);
    GD.swap();
}