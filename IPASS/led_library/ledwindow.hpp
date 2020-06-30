#ifndef LEDWINDOW_HPP
#define LEDWINDOW_HPP

#include "ledstrip.hpp"

/// @file

namespace ledscreen {
    /// \brief
    /// Base hwlib::window based window for the WS2812B.
    /// \details
    /// Adds base functionality of hwlib::window to the WS2812B so it can easily be used as a screen. This version only supports length x 1 as dimensions.
    class ledwindow_base : public hwlib::window, public ledscreen::WS2812B {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            WS2812B::draw(pos.x, colour.rgb());
        }
    public:
        ledwindow_base(const hwlib::xy & size, hwlib::pin_out & pin):
        window(size),
        WS2812B(pin, size.x*size.y)
        {}
        void flush()override{
            WS2812B::flush();
        }
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a horizontally-layed-out WS2812B matrix with the 0th pixel in the top left. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_horizontal_top_left : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.y % 2){ //if pos.y is uneven
                newPos = (pos.y * size.x) + (size.x - pos.x -1);
            }else{
                newPos = (pos.y * size.x) + pos.x;
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_horizontal_top_left(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a horizontally-layed-out WS2812B matrix with the 0th pixel in the top right. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_horizontal_top_right : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.y % 2){ //if pos.y is uneven
                newPos = (pos.y * size.x + pos.x);
            }else{
                newPos = (pos.y * size.x) + (size.x - pos.x - 1);
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_horizontal_top_right(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a horizontally-layed-out WS2812B matrix with the 0th pixel in the bottom left. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_horizontal_bottom_left : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.y % 2){ //if pos.y is uneven
                newPos = ((size.y - pos.y -1) * size.x) + pos.x;
            }else{
                newPos = ((size.y - pos.y -1) * size.x) + (size.x - pos.x -1);
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_horizontal_bottom_left(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a horizontally-layed-out WS2812B matrix with the 0th pixel in the bottom right. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_horizontal_bottom_right : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.y % 2){ //if pos.y is uneven
                newPos = ((size.y-pos.y-1) * size.x + (size.x - pos.x - 1));
            }else{
                newPos = ((size.y-pos.y-1) * size.x) + pos.x;
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_horizontal_bottom_right(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a vertically-layed-out WS2812B matrix with the 0th pixel in the top left. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_vertical_top_left : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.x % 2){ //if pos.x is uneven
                newPos = (pos.x * size.y + (size.y - pos.y - 1));
            }else{
                newPos = (pos.x * size.y) + pos.y;
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_vertical_top_left(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a vertically-layed-out WS2812B matrix with the 0th pixel in the top right. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_vertical_top_right : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.x % 2){ //if pos.x is uneven
                newPos = ((size.x - pos.x -1) * size.y + pos.y);
            }else{
                newPos = ((size.x - pos.x -1) * size.y) + (size.y - pos.y - 1);
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_vertical_top_right(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a vertically-layed-out WS2812B matrix with the 0th pixel in the bottom left. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_vertical_bottom_left : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.x % 2){ //if pos.x is uneven
                newPos = (pos.x * size.y + pos.y);
            }else{
                newPos = (pos.x * size.y) + (size.y - pos.y - 1);
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_vertical_bottom_left(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    /// \brief
    /// Layout expansion on ledscreen::window_base.
    /// \details
    /// Adds support for a vertically-layed-out WS2812B matrix with the 0th pixel in the bottom right. Supports any dimensions with no more than 2048 total leds.
    class ledwindow_vertical_bottom_right : public ledscreen::ledwindow_base {
    private:
        void write_implementation(hwlib::xy pos, hwlib::color colour)override{
            int newPos;
            if(pos.x % 2){ //if pos.x is uneven
                newPos = ((size.x-pos.x-1) * size.y + (size.y - pos.y - 1));
            }else{
                newPos = ((size.x-pos.x-1) * size.y) + pos.y;
            }
            WS2812B::draw(newPos, colour.rgb());
        }
    public:
        ledwindow_vertical_bottom_right(const hwlib::xy & size, hwlib::pin_out & pin):
        ledwindow_base(size, pin)
        {}
    };

    
};
#endif