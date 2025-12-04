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

void NHD_EVE::doorbell(uint8_t trig, uint8_t echo, uint8_t motion)
{

    if (_screen == 2)
    {
        int bg_color = map(_temperature, 68, 65478, 0, 255);

        byte R = bg_color;
        byte G = 0xBE;
        byte B = 255 - bg_color;

        uint32_t final_bg = R;

        final_bg <<= 8;
        final_bg += G;
        final_bg <<= 8;
        final_bg += B;

        GD.ClearColorRGB(final_bg);
    }
    else
    {
        GD.ClearColorRGB(0x00);
    }

    GD.Clear();

    GD.Begin(RECTS);

    GD.ColorRGB(0x00);
    GD.Vertex2ii(0, _vsize - 80);
    GD.Vertex2ii(_hsize, _vsize);

    GD.ColorRGB(0x0d5e0d);
    GD.Vertex2ii(0, 0);
    GD.Vertex2ii(80, 480);

    GD.ColorRGB(0xffffffff);
    GD.cmd_fgcolor(0x218521);
    GD.Tag(1);
    GD.cmd_button(0, 0, 80, _vsize / 2, 30, OPT_FLAT | OPT_CENTER, "");

    GD.cmd_fgcolor(0x0d5e0d);
    GD.Tag(2);
    GD.cmd_button(0, _vsize / 2, 80, _vsize / 2, 30, OPT_FLAT | OPT_CENTER, "");

    house_icon(25, 110);
    settings_icon(25, 340);

    GD.get_inputs();

    if (GD.inputs.tag == 1)
    {
        _screen = 0;
    }
    else if (GD.inputs.tag == 2)
    {
        _screen = 1;
    }

    if (_screen == 0)
    {
        if (_person_present)
        {
            GD.ColorRGB(0xffffffff);
            GD.cmd_text((_hsize / 2) + 45, 280, 31, OPT_CENTER, "Motion Detected");
            GD.cmd_text((_hsize / 2) + 45, 320, 31, OPT_CENTER, "Near Front Door");

            GD.Begin(BITMAPS);
            GD.Vertex2ii(170, 10, 2);

            GD.ColorRGB(0xffffffff);
        }
        else
        {
            GD.cmd_text((_hsize / 2) + 45, _vsize - 160, 31, OPT_CENTER, "TUESDAY");
            GD.cmd_text((_hsize / 2) + 45, _vsize - 120, 29, OPT_CENTER, "12/2/2025");

            GD.cmd_scale(F16(0.3), F16(0.3));
            GD.cmd_setmatrix();
            GD.Begin(BITMAPS);
            GD.Vertex2ii(180, _vsize - 75, 1);

            GD.cmd_scale(F16(2.7), F16(2.8));
            GD.cmd_setmatrix();
            GD.ColorMask(1, 1, 1, 0);
            GD.Begin(BITMAPS);
            GD.Vertex2ii(88, 0, 0);

            GD.ColorMask(0, 0, 0, 1);
            GD.BlendFunc(ONE, ONE_MINUS_SRC_ALPHA);

            GD.ColorRGB(0xffffffff);
            GD.cmd_bgcolor(0x00);
            GD.cmd_clock((_hsize / 2) + 45, (_vsize / 2) - 80, 120, OPT_FLAT | OPT_NOBACK, hours, minutes, seconds, 0);

            GD.ColorRGB(0xffffffff);
        }
    }
    else if (_screen == 1)
    {
        GD.Tag(3);
        GD.cmd_button((_hsize / 2) - 80, (_vsize / 2) - 190, 250, 80, 28, OPT_CENTER, "Temperature Settings");
        GD.Tag(4);
        GD.cmd_button((_hsize / 2) - 80, (_vsize / 2) - 90, 250, 80, 28, OPT_CENTER, "Display Settings");
        GD.Tag(7);
        GD.cmd_button((_hsize / 2) - 80, (_vsize / 2) + 10, 250, 80, 28, OPT_CENTER, "Sensor Calibration");

        GD.get_inputs();

        if (GD.inputs.tag == 3)
        {
            _screen = 2;
        }
        else if (GD.inputs.tag == 4)
        {
            _screen = 3;
        }
        else if (GD.inputs.tag == 7)
        {
            _screen = 4;
        }

        GD.ColorRGB(0xffffffff);
    }
    else if (_screen == 2)
    {

        if ((GD.inputs.track_tag & 0xff) == 5 && GD.inputs.track_val > 0)
            _temperature = GD.inputs.track_val;

        _temperature < 10000 ? _temperature = 10000 : _temperature = _temperature;
        _temperature > (65478 - 10000) ? _temperature = (65478 - 10000) : _temperature = _temperature;

        GD.Tag(5);
        GD.cmd_dial((_hsize / 2) + 45, (_vsize / 2) - 10, 100, OPT_FLAT, _temperature);
        GD.cmd_track((_hsize / 2) + 45, (_vsize / 2) - 10, 1, 1, 5);

        int converted_temp = map(_temperature, 68, 65478, 58, 83);
        GD.ColorRGB(0xffffffff);
        GD.cmd_number((_hsize / 2) + 45, 80, 31, OPT_CENTER, converted_temp);

        GD.cmd_text((_hsize / 2) + 75, 50, 31, OPT_CENTER, ".");

        GD.ColorRGB(0xffffffff);
    }
    else if (_screen == 3)
    {

        int converted_brightness = map(_brightness, 68, 65478, 0, 128);

        if ((GD.inputs.track_tag & 0xff) == 6 && GD.inputs.track_val > 0)
        {
            _brightness = GD.inputs.track_val;
            GD.wr(REG_PWM_DUTY, converted_brightness);
        }

        GD.Tag(6);

        GD.cmd_slider((_hsize / 2) - 85, 120, 230, 22, 0, converted_brightness, 128);
        GD.cmd_track((_hsize / 2) - 85, 120, 230, 22, 6);

        GD.cmd_text((_hsize / 2) + 45, 70, 31, OPT_CENTER, "Brightness");
        GD.cmd_text((_hsize / 2) + 45, 230, 31, OPT_CENTER, "Wallpaper");

        GD.Tag(8);
        GD.cmd_button((_hsize / 2) - 135, 280, 50, 50, 31, OPT_FLAT, "<");
        GD.Tag(9);
        GD.cmd_button((_hsize / 2) + 165, 280, 50, 50, 31, OPT_FLAT, ">");

        switch (_wallpaper)
        {
        case 0:
            GD.cmd_text((_hsize / 2) + 45, 305, 31, OPT_CENTER, "Forrest");
            break;
        case 1:
            GD.cmd_text((_hsize / 2) + 45, 305, 31, OPT_CENTER, "Blocks");
            break;
        case 2:
            GD.cmd_text((_hsize / 2) + 45, 305, 31, OPT_CENTER, "Windows");
            break;
        case 3:
            GD.cmd_text((_hsize / 2) + 45, 305, 31, OPT_CENTER, "Orient");
            break;
        case 4:
            GD.cmd_text((_hsize / 2) + 45, 305, 31, OPT_CENTER, "Space");
            break;

        default:
            break;
        }

        GD.get_inputs();

        if (GD.inputs.tag == 8)
        {
            GD.cmd_loadimage(0, 0);

            _wallpaper == 4 ? _wallpaper = 0 : _wallpaper += 1;

            switch (_wallpaper)
            {
            case 0:
                GD.load("bg1.jpg");
                break;
            case 1:
                GD.load("bg2.jpg");
                break;
            case 2:
                GD.load("bg3.jpg");
                break;
            case 3:
                GD.load("bg4.jpg");
                break;
            case 4:
                GD.load("bg5.jpg");
                break;

            default:
                break;
            }
        }
        else if (GD.inputs.tag == 9)
        {

            GD.cmd_loadimage(0, 0);

            _wallpaper == 0 ? _wallpaper = 4 : _wallpaper -= 1;

            switch (_wallpaper)
            {
            case 0:
                GD.load("bg1.jpg");
                break;
            case 1:
                GD.load("bg2.jpg");
                break;
            case 2:
                GD.load("bg3.jpg");
                break;
            case 3:
                GD.load("bg4.jpg");
                break;
            case 4:
                GD.load("bg5.jpg");
                break;

            default:
                break;
            }
        }

        GD.ColorRGB(0xffffffff);
    }
    else if (_screen == 4)
    {

        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);

        int duration = pulseIn(echo, HIGH);
        int _check = (duration * .0343) / 2;

        GD.cmd_number((_hsize / 2) + 15, (_vsize / 2) - 50, 31, OPT_CENTER, _check);
        GD.cmd_text((_hsize / 2) + 85, (_vsize / 2) - 50, 31, OPT_CENTER, "mm");
        GD.cmd_text((_hsize / 2) + 45, (_vsize / 2) + 20, 31, OPT_CENTER, (digitalRead(motion) ? "Motion Detected" : "No Motion Detected"));

        GD.ColorRGB(0xffffffff);
    }

    if (_person_present)
    {
        if (_prox_check_timer == 400)
        {
            _person_present = _check_person(trig, echo, motion);
            _prox_check_timer = 0;
        }

        _prox_check_timer++;
    }
    else
    {
        _person_present = _check_person(trig, echo, motion);
    }

    if (_screen != 0 || _person_present)
    {
        GD.cmd_scale(F16(0.3), F16(0.3));
        GD.cmd_setmatrix();
        GD.Begin(BITMAPS);
        GD.Vertex2ii(180, _vsize - 75, 1);
    }

    if (_screen == 0 && !_person_present)
    {
        GD.ColorMask(1, 1, 1, 0);
        GD.BlendFunc(DST_ALPHA, ONE);
        GD.ColorRGB(0xffffffff);

        GD.Begin(RECTS); // Visit every pixel on the screen
        GD.Vertex2ii(88, 0);
        GD.Vertex2ii(_hsize, _vsize - 88);
    }
    clock();
    GD.swap();
}

void NHD_EVE::clock()
{
    // Capture the current time provided by the Arduino since boot
    unsigned long currentMillis = millis();

    // Check if 1000 milliseconds have passed since the last time we updated
    if (currentMillis - previousMillis >= interval)
    {
        // Save the time we last updated the clock
        previousMillis = currentMillis;

        // Increment the seconds counter
        seconds++;

        // Check if seconds reached 60
        if (seconds >= 60)
        {
            seconds = 0;
            minutes++;

            // Check if minutes reached 60
            if (minutes >= 60)
            {
                minutes = 0;
                hours++;

                // Check if hours reached 24 (handle 24-hour cycle)
                if (hours >= 24)
                {
                    hours = 0;
                }
            }
        }
    }
}

bool NHD_EVE::_check_person(uint8_t trig, uint8_t echo, uint8_t motion)
{
    bool isPerson = false;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    int duration = pulseIn(echo, HIGH);
    _distance_check = (duration * .0343) / 2;

    digitalRead(motion) ? _motion_detect = true : _motion_detect = false;
    _distance_check > 0 &&_distance_check < 20 ? _proximity_detect = true : _proximity_detect = false;

    _motion_detect || _proximity_detect ? isPerson = true : isPerson = false;

    return isPerson;
}

void NHD_EVE::house_icon(uint16_t x, uint16_t y)
{
    GD.Begin(RECTS);
    GD.ColorRGB(0xffffffff);
    GD.Vertex2ii(x, y);
    GD.Vertex2ii(x + 30, y + 30);

    GD.ColorRGB(0x218521);
    GD.Vertex2ii(x + 10, y + 15);
    GD.Vertex2ii(x + 20, y + 31);

    GD.Begin(LINES);

    GD.ColorRGB(0xffffffff);
    GD.LineWidth(16 * 5);
    GD.Vertex2ii(x + 15, y - 5);
    GD.Vertex2ii(x - 5, y + 5);
    GD.Vertex2ii(x + 15, y - 5);
    GD.Vertex2ii(x + 35, y + 5);
}

void NHD_EVE::settings_icon(uint16_t x, uint16_t y)
{
    GD.PointSize(16 * 22);
    GD.Begin(POINTS);
    GD.ColorRGB(0xffffffff);
    GD.Vertex2ii(x + 15, y + 15);

    GD.Begin(RECTS);

    GD.ColorRGB(0x0d5e0d);
    GD.Vertex2ii(x + 10, y - 10);
    GD.Vertex2ii(x + 20, y + 10);

    GD.ColorRGB(0xffffffff);

    GD.Vertex2ii(x + 10, y + 30);
    GD.Vertex2ii(x + 20, y + 40);
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

    pinMode(RST, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(DC, OUTPUT);
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);

    digitalWrite(RST, HIGH);
    digitalWrite(CS, HIGH);
    digitalWrite(DC, HIGH);
    digitalWrite(SCL, HIGH);
    digitalWrite(SDA, HIGH);

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
    case 5:
        init_480X480();
        break;
    default:
        break;
    }

    GD.BitmapHandle(0);
    GD.cmd_loadimage(0, 0);
    
    GD.load("bg2.jpg");

    GD.BitmapHandle(1);
    GD.cmd_loadimage(-4, 0);
    GD.load("logo.jpg");

    GD.BitmapHandle(2);
    GD.cmd_loadimage(-5, 0);
    GD.load("warning.jpg");

    // GD.BitmapHandle(3);
    // GD.cmd_loadimage(-3, 0);
    // GD.load("bg1.jpg");

    // GD.BitmapHandle(4);
    // GD.cmd_loadimage(-4, 0);
    // GD.load("bg3.jpg");

    // GD.BitmapHandle(5);
    // GD.cmd_loadimage(-5, 0);
    // GD.load("bg4.jpg");

    // GD.BitmapHandle(6);
    // GD.cmd_loadimage(-6, 0);
    // GD.load("bg5.jpg");

    GD.Clear();
    GD.swap();
}

void NHD_EVE::proximityDisplay(int distance)
{

    // Buffer for smoother transitions for the gauge widget

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

    GD.cmd_number(_hsize / 2, 130, 31, OPT_CENTER, (distance > 1000 ? 0 : distance));
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
    // Setup image for slideshow
    if (!_loadSlideShow)
    {
        _loadSlideShow = true;
        GD.BitmapHandle(0);
        GD.cmd_loadimage(0, 0);
        GD.load("image2.jpg");
    }

    // Cycle through images
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
    // Display stationary object
    GD.BitmapHandle(from);
    GD.ColorRGB(colorFrom);
    GD.Vertex2f(_hsize * 16, 0);

    // Display animated object transition to stationary state
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

void NHD_EVE::init_480X480()
{
    _hsize = 480;
    _vsize = 480;

    digitalWrite(RST, LOW);
    Serial.println("RESET 1");
    delay(20);

    digitalWrite(RST, HIGH);
    Serial.println("RESET 2");
    delay(100);

    _lcd_init();

    // Horizontal timing (pixels)
    GD.wr16(REG_HSIZE, 480);   // Active pixels
    GD.wr16(REG_HCYCLE, 790);  // 10 + 150 + 480 + 150
    GD.wr16(REG_HSYNC0, 0);    // HSYNC start
    GD.wr16(REG_HSYNC1, 10);   // HSYNC end (width = 10)
    GD.wr16(REG_HOFFSET, 160); // HSYNC(10) + HBP(150)

    // Vertical timing (lines)
    GD.wr16(REG_VSIZE, 480);  // Active lines
    GD.wr16(REG_VCYCLE, 530); // 10 + 20 + 480 + 20
    GD.wr16(REG_VSYNC0, 0);   // VSYNC start
    GD.wr16(REG_VSYNC1, 10);  // VSYNC end (width = 10)
    GD.wr16(REG_VOFFSET, 30); // VSYNC(10) + VBP(20)

    // Pixel clock and signal polarity
    GD.wr16(REG_PCLK, 2);
    GD.wr16(REG_SWIZZLE, 0);
    GD.wr16(REG_PCLK_POL, 0);
    GD.wr16(REG_CSPREAD, 0);
    GD.wr16(REG_DITHER, 1);
    GD.wr16(REG_ROTATE, 0);

    GD.wr16(REG_PWM_HZ, 5000);
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

void NHD_EVE::_lcd_com(unsigned char c)
{
    digitalWrite(CS, LOW);
    digitalWrite(DC, LOW);
    for (int i = 0; i < 8; i++)
    {
        if ((c & 0x80) == 0x80)
        {
            digitalWrite(SDA, HIGH);
        }
        else
        {
            digitalWrite(SDA, LOW);
        }
        c = (c << 1); // Shift byte
        digitalWrite(SCL, HIGH);
        digitalWrite(SCL, LOW);
        digitalWrite(SCL, HIGH);
    }
    digitalWrite(CS, HIGH);
}

void NHD_EVE::_lcd_dat(unsigned char d)
{
    digitalWrite(CS, LOW);
    digitalWrite(DC, HIGH);
    for (int i = 0; i < 8; i++)
    {
        if ((d & 0x80) == 0x80)
        {
            digitalWrite(SDA, HIGH);
        }
        else
        {
            digitalWrite(SDA, LOW);
        }
        d = (d << 1); // Shift byte
        digitalWrite(SCL, HIGH);
        digitalWrite(SCL, LOW);
        digitalWrite(SCL, HIGH);
    }
    digitalWrite(CS, HIGH);
}

void NHD_EVE::_lcd_init()
{
    _lcd_com(0xFF);
    _lcd_dat(0x77);
    _lcd_dat(0x01);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x13);

    _lcd_com(0xEF);
    _lcd_dat(0x08);

    _lcd_com(0xFF);
    _lcd_dat(0x77);
    _lcd_dat(0x01);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x10);

    _lcd_com(0xC0);
    _lcd_dat(0x3B);
    _lcd_dat(0x00);

    _lcd_com(0xC1);
    _lcd_dat(0x0D);
    _lcd_dat(0x02);

    _lcd_com(0xC2);
    _lcd_dat(0x21);
    _lcd_dat(0x08);

    _lcd_com(0xC7);
    _lcd_dat(0x00);

    _lcd_com(0xCC);
    _lcd_dat(0x18);

    _lcd_com(0xB0);
    _lcd_dat(0x00);
    _lcd_dat(0x13);
    _lcd_dat(0x1E);
    _lcd_dat(0x0E);
    _lcd_dat(0x11);
    _lcd_dat(0x05);
    _lcd_dat(0x09);
    _lcd_dat(0x07);
    _lcd_dat(0x07);
    _lcd_dat(0x23);
    _lcd_dat(0x04);
    _lcd_dat(0x12);
    _lcd_dat(0x0F);
    _lcd_dat(0xA7);
    _lcd_dat(0x2C);
    _lcd_dat(0x18);

    _lcd_com(0xB1);
    _lcd_dat(0x00);
    _lcd_dat(0x14);
    _lcd_dat(0x1B);
    _lcd_dat(0x0E);
    _lcd_dat(0x11);
    _lcd_dat(0x06);
    _lcd_dat(0x06);
    _lcd_dat(0x08);
    _lcd_dat(0x07);
    _lcd_dat(0x20);
    _lcd_dat(0x04);
    _lcd_dat(0x12);
    _lcd_dat(0x11);
    _lcd_dat(0xA5);
    _lcd_dat(0x2F);
    _lcd_dat(0x18);

    _lcd_com(0xFF);
    _lcd_dat(0x77);
    _lcd_dat(0x01);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x11);

    _lcd_com(0xB0);
    _lcd_dat(0x60);

    _lcd_com(0xB1);
    _lcd_dat(0x31);

    _lcd_com(0xB2);
    _lcd_dat(0x8A);

    _lcd_com(0xB3);
    _lcd_dat(0x80);

    _lcd_com(0xB5);
    _lcd_dat(0x4B);

    _lcd_com(0xB7);
    _lcd_dat(0x85);

    _lcd_com(0xB8);
    _lcd_dat(0x21);

    _lcd_com(0xC0);
    _lcd_dat(0x07);

    _lcd_com(0xC1);
    _lcd_dat(0x78);

    _lcd_com(0xC2);
    _lcd_dat(0x78);

    _lcd_com(0xE0);
    _lcd_dat(0x00);
    _lcd_dat(0x1B);
    _lcd_dat(0x02);

    _lcd_com(0xE1);
    _lcd_dat(0x08);
    _lcd_dat(0xA0);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x07);
    _lcd_dat(0xA0);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x44);
    _lcd_dat(0x44);

    _lcd_com(0xE2);
    _lcd_dat(0x11);
    _lcd_dat(0x11);
    _lcd_dat(0x44);
    _lcd_dat(0x44);
    _lcd_dat(0xED);
    _lcd_dat(0xA0);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0xEC);
    _lcd_dat(0xA0);
    _lcd_dat(0x00);
    _lcd_dat(0x00);

    _lcd_com(0xE3);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x11);
    _lcd_dat(0x11);

    _lcd_com(0xE4);
    _lcd_dat(0x44);
    _lcd_dat(0x44);

    _lcd_com(0xE5);
    _lcd_dat(0x0A);
    _lcd_dat(0xE9);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);
    _lcd_dat(0x0C);
    _lcd_dat(0xEB);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);
    _lcd_dat(0x0E);
    _lcd_dat(0xED);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);
    _lcd_dat(0x10);
    _lcd_dat(0xEF);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);

    _lcd_com(0xE6);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x11);
    _lcd_dat(0x11);

    _lcd_com(0xE7);
    _lcd_dat(0x44);
    _lcd_dat(0x44);

    _lcd_com(0xE8);
    _lcd_dat(0x09);
    _lcd_dat(0xE8);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);
    _lcd_dat(0x0B);
    _lcd_dat(0xEA);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);
    _lcd_dat(0x0D);
    _lcd_dat(0xEC);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);
    _lcd_dat(0x0F);
    _lcd_dat(0xEE);
    _lcd_dat(0xD8);
    _lcd_dat(0xA0);

    _lcd_com(0xEB);
    _lcd_dat(0x02);
    _lcd_dat(0x00);
    _lcd_dat(0xE4);
    _lcd_dat(0xE4);
    _lcd_dat(0x88);
    _lcd_dat(0x00);
    _lcd_dat(0x40);

    _lcd_com(0xEC);
    _lcd_dat(0x3C);
    _lcd_dat(0x00);

    _lcd_com(0xED);
    _lcd_dat(0xAB);
    _lcd_dat(0x89);
    _lcd_dat(0x76);
    _lcd_dat(0x54);
    _lcd_dat(0x02);
    _lcd_dat(0xFF);
    _lcd_dat(0xFF);
    _lcd_dat(0xFF);
    _lcd_dat(0xFF);
    _lcd_dat(0xFF);
    _lcd_dat(0xFF);
    _lcd_dat(0x20);
    _lcd_dat(0x45);
    _lcd_dat(0x67);
    _lcd_dat(0x98);
    _lcd_dat(0xBA);

    _lcd_com(0xEF);
    _lcd_dat(0x08);
    _lcd_dat(0x08);
    _lcd_dat(0x08);
    _lcd_dat(0x45);
    _lcd_dat(0x3F);
    _lcd_dat(0x54);

    _lcd_com(0xFF);
    _lcd_dat(0x77);
    _lcd_dat(0x01);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x13);

    _lcd_com(0xE8);
    _lcd_dat(0x00);
    _lcd_dat(0x0E);

    _lcd_com(0xFF);
    _lcd_dat(0x77);
    _lcd_dat(0x01);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x00);

    _lcd_com(0x11);
    delay(120);

    _lcd_com(0xFF);
    _lcd_dat(0x77);
    _lcd_dat(0x01);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x13);

    _lcd_com(0xE8);
    _lcd_dat(0x00);
    _lcd_dat(0x0C);
    delay(10);

    _lcd_com(0xE8);
    _lcd_dat(0x00);
    _lcd_dat(0x00);

    _lcd_com(0xFF);
    _lcd_dat(0x77);
    _lcd_dat(0x01);
    _lcd_dat(0x00);
    _lcd_dat(0x00);
    _lcd_dat(0x00);

    _lcd_com(0x3A); // 565RGB   55  16bit，666RGB   66  18bit，24bit  77
    _lcd_dat(0x77);

    _lcd_com(0x29);
    _lcd_com(0x36);
    _lcd_dat(0x00);
}