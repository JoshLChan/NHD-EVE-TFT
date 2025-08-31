#include <NHD-EVE.h>
#include <Arduino.h>

NHD_EVE::NHD_EVE(uint8_t index)
{
    _index = index;
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
        break;
    default:
        break;
    }
}

void NHD_EVE::helloWorld(char* text)
{
    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.cmd_text(_hsize / 2, _vsize / 2, 31, OPT_CENTER, text);
    GD.swap();
}

void NHD_EVE::threerats()
{
    GD.Clear();
    GD.swap();
    GD.cmd_loadimage(0, 0);
    GD.load("image1.jpg");
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.cmd_scale(F16(2), F16(2.2));
    GD.cmd_setmatrix();
    GD.BitmapSize(NEAREST, BORDER, BORDER, _hsize, _vsize);
    GD.Vertex2ii(0, 0);
    GD.swap();
}

void NHD_EVE::coolbear()
{
    GD.Clear();
    GD.swap();
    GD.cmd_loadimage(0, 0);
    GD.load("image2.jpg");
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.cmd_scale(F16(1), F16(1.2));
    GD.cmd_setmatrix();
    GD.BitmapSize(NEAREST, BORDER, BORDER, _hsize, _vsize);
    GD.Vertex2ii(0, 0);
    GD.swap();
}

void NHD_EVE::logo()
{
    GD.Clear();
    GD.swap();
    GD.ClearColorRGB(0xFFFFFF);
    GD.cmd_loadimage(0, 0);
    GD.load("image3.jpg");
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.cmd_scale(F16(0.7), F16(0.7));
    GD.cmd_setmatrix();
    GD.BitmapSize(NEAREST, BORDER, BORDER, _hsize, _vsize);
    GD.Vertex2ii(0, _vsize / 2.5);
    GD.swap();
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