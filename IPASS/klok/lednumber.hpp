#ifndef LEDNUMBER_HPP
#define LEDNUMBER_HPP
#include "hwlib.hpp"
#include "ledscreen.hpp"
namespace ledscreen{
    class lednumber{
    private:
        ledscreen::ledwindow_base & window; 
        int led_start;
        hwlib::color colour = hwlib::color(0,100,0);
        hwlib::line zero_line = hwlib::line(hwlib::xy(led_start,0), hwlib::xy(led_start + 4,0), colour);
        hwlib::line one_line = hwlib::line(hwlib::xy(led_start + 4 ,0), hwlib::xy(led_start + 8,0), colour);
        hwlib::line two_line = hwlib::line(hwlib::xy(led_start+ 8,0), hwlib::xy(led_start + 12,0), colour);
        hwlib::line three_line = hwlib::line(hwlib::xy(led_start + 12 ,0), hwlib::xy(led_start + 16, 0) , colour);
        hwlib::line four_line = hwlib::line(hwlib::xy(led_start + 16 ,0), hwlib::xy(led_start + 20,0), colour);
        hwlib::line five_line = hwlib::line(hwlib::xy(led_start + 20 ,0), hwlib::xy(led_start + 24,0), colour);
        hwlib::line six_line = hwlib::line(hwlib::xy(led_start + 24 ,0), hwlib::xy(led_start + 28,0), colour);

    public:

    lednumber(ledscreen::ledwindow_base & window, int led_start, hwlib::color color):
        window(window),
        led_start(led_start),
        colour(color)
        {}

    void change_color(int lijst[3]){
        colour = hwlib::color(lijst[0],lijst[1],lijst[2]);
    }

    void draw_number(int number){
        window.clear();
        window.flush();
        if(number == 0){
            one_line.draw(window);
            two_line.draw(window);
            three_line.draw(window);
            four_line.draw(window);
            five_line.draw(window);
            six_line.draw(window);
        }else if(number == 1){
            one_line.draw(window);
            six_line.draw(window);
        }else if(number == 2){
            zero_line.draw(window);
            one_line.draw(window);
            two_line.draw(window);
            four_line.draw(window);
            five_line.draw(window);
        }else if(number == 3){
            two_line.draw(window);
            one_line.draw(window);
            zero_line.draw(window);
            six_line.draw(window);
            five_line.draw(window);
        }else if(number == 4){
            three_line.draw(window);
            one_line.draw(window);
            zero_line.draw(window);
            six_line.draw(window);
        }else if(number == 5){
            two_line.draw(window);
            three_line.draw(window);
            zero_line.draw(window);
            six_line.draw(window);
            five_line.draw(window);
        }else if(number == 6){
            two_line.draw(window);
            three_line.draw(window);
            zero_line.draw(window);
            four_line.draw(window);
            five_line.draw(window);
            six_line.draw(window);
        }else if(number == 7){
            two_line.draw(window);
            one_line.draw(window);
            six_line.draw(window);
        }else if(number == 8){
            zero_line.draw(window);
            one_line.draw(window);
            two_line.draw(window);
            three_line.draw(window);
            four_line.draw(window);
            five_line.draw(window);
            six_line.draw(window);
        }else if(number == 9){
            two_line.draw(window);
            one_line.draw(window);
            three_line.draw(window);
            zero_line.draw(window);
            six_line.draw(window);
            five_line.draw(window);
        }
        window.flush();

    }
    void draw_line(){
        six_line.draw(window);
        window.clear();
    }


    };
};


#endif
