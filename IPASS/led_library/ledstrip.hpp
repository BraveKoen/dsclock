#ifndef LEDSTRIP_HPP
#define LEDSTRIP_HPP
#include <array>
#include "hwlib.hpp"

/// @file

namespace ledscreen {
    /// \brief
    /// Base class for a WS2812B LED strip.
    /// \details
    /// Adds base functionality for writing certain colours to certain leds on the strip.
    class WS2812B {
    private:
        /// \brief
        /// Hardware gpio pin.
        /// \details
        /// The gpio pin used for the data out to the ledstrip.
        hwlib::pin_out & pin;

        /// \brief
        /// Length of the leds strip.
        /// \details
        /// Number of leds on the used ledstrip, max 2048, roughly 1024 if you want 30 fps.
        const unsigned int length;

        /// \brief
        /// Array of pixels/leds. Draw-buffer.
        /// \details
        /// Contains the colour values (in RGB hex) for every led/pixel.
        std::array<unsigned int, 2048> pixels;

        /// \brief
        /// Writes a zero to the ledstrip.
        /// \details
        /// Uses correct timings to send the '0' data to the ledstrip. N for number of 0's, defaults to 1.
        void zero(unsigned int n=1){
            for(unsigned int i=0; i < n; i++){
                pin.write(1);

                pin.write(0);
                hwlib::wait_ns(50); //Using lowest functioning delay
            }
        }

        /// \brief
        /// Writes a one to the ledstrip.
        /// \details
        /// Uses correct timings to send the '1' data to the ledstrip. N for number of 1's, defaults to 1.
        void one(unsigned int n=1){
            for(unsigned int i=0; i < n; i++){
                pin.write(1);
                hwlib::wait_ns(50); //Using lowest functioning delay

                pin.write(0);
                hwlib::wait_ns(50); //Using lowest functioning delay
            }
        }

        /// \brief
        /// Send reset/end of frame data to ledstrip.
        /// \details
        /// Uses correct timings to send the resetend of frame data to the ledstrip.
        void reset(){
            pin.write(0);
            hwlib::wait_ns(95000); //Using lowest seemingly possible delay. According to tests.
        }
    public:
        /// \brief
        /// Constructor for base WS2812B class.
        /// \details
        /// Requires correct hwlib-style gpio pin that the ledstrip is connected. As well as the number of leds/length.
        WS2812B(hwlib::pin_out & pin, const unsigned int length):
        pin(pin),
        length(length)
        {
            for(unsigned int i=0; i<length; i++){
                pixels[i] = 0;
            }
        }

        /// \brief
        /// Basic draw function for rgbHex values.
        /// \details
        /// Checks min and max values, and converts rgbHex to grbHex as used by the ledstrip. Then adds colour data to the draw-buffer. Requires a flush() call to actually render.
        void draw(unsigned int pos, int rgbHex){
            if(rgbHex > 0xFFFFFF){
                rgbHex = 0xFFFFFF;
            }else if(rgbHex < 0x0){
                rgbHex = 0x0;
            }
            if(pos > length){
                pos = length-1;
            }else if(pos < 0){
                pos = 0;
            }
            int grbHex = ((rgbHex & 0b011111111 << 8) << 8);
            grbHex |= ((rgbHex & 0b011111111 << 16) >> 8);
            grbHex |= (rgbHex & 0b011111111);
            pixels[pos] = grbHex;
        }

        /// \brief
        /// Basic draw function for RGB values.
        /// \details
        /// Checks min and max values, and converts RGB to grbHex as used by the ledstrip.Then adds colour data to the draw-buffer. Requires a flush() call to actually render.
        void draw(unsigned int pos, int R, int G, int B){
            if(R > 255){R = 255;}else if(R < 0){R = 0;}
            if(G > 255){G = 255;}else if(G < 0){G = 0;}
            if(B > 255){B = 255;}else if(B < 0){B = 0;}
            if(pos > length){
                pos = length-1;
            }else if(pos < 0){
                pos = 0;
            }
            int grbHex = G << 16;
            grbHex |= R << 8;
            grbHex |= B;
            pixels[pos] = grbHex;
        }
        /// \brief
        /// Flushes draw-buffer to ledstrip.
        /// \details
        /// Flushes the draw-buffer colour data (in grbHex) to the ledstrip using bitshifting and the one() and zero() functions, then call reset() for the reset/end of frame data.
        void flush(){
            for(unsigned int i=0; i<length; i++){
                for(unsigned int j=0; j<24; j++){
                    if(pixels[i] & (0b01 << (23-j))){
                        one();
                    }else{
                        zero();
                    }
                }
            }
            reset();
        }

        /// \brief
        /// Getter for pixel colour values. Takes pixel index. Returns RGB in hex.
        /// \details
        /// Allows you to get the colour value of a specific pixel. Useful for applications that want to use the colour data, so that they dont need to keep a copy themselves.
        virtual int get(const unsigned int & index){
            return pixels[index];
        }
    };
};

#endif