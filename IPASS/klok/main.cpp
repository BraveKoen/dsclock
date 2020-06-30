
//          Copyright Koen Brave 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "ledscreen.hpp"
#include "lednumber.hpp"
#include "dsClock.hpp"
#include "i2c_bus.cpp"

int main(){
    namespace target = hwlib::target;
    //to display the day
    const char *days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saterday"};
    
    //connection to the oled
    auto scl     = target::pin_oc( target::pins::scl );
    auto sda     = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 

    auto font    = hwlib::font_default_16x16(); //big fond for the numbers
    auto display = hwlib::terminal_from( oled, font );
    
    //connection to the ds1307 chip
    auto bus = r2d2::i2c::i2c_bus_c(r2d2::i2c::i2c_bus_c::interface::interface_0, 50000);
    auto clock = dsClock(bus, 40 ,59, 23, 3 , 30, 6, 20);

    
    int minut_old = -1; //to prefent updating every time
    int hour_old = -1;

    int minut_first = 0;    
    int minut_second = 0;

    int hour_first = 0;
    int hour_second = 0;

    while(true){    //infinty loop for updating time every 0.5 sec
        int minutes = clock.get_minutes();
 
        int hour = clock.get_hour();
        //lib::cout << clock.get_day();
      
        //you do not want to update if it minutes are still the same
        if(minutes != minut_old){
        
            minut_old = minutes;

            if(minutes < 10){
                minut_first = 0;
                minut_second = minutes;
            }else{
                minut_first = minutes / 10 % 10;
                minut_second = minutes %10;
                //number_three.draw_number(minut_first); //hwlib::cout << " Eerste getet moet 3 zijn: " << minut_first << "\n";
                //number_four.draw_number(minut_second); //hwlib::cout << minut_second;
            }
            //update the display if the minutes are changing 
            display << "\f" << hour_first << hour_second << " : " << minut_first << minut_second << "\n" << clock.get_date() <<
            "/" << clock.get_month() << "/" << clock.get_year() << "\n" << days[clock.get_day()-1]<<hwlib::flush;

        }
        //Update if hour is not the same as before
        if(hour != hour_old){
            //hwlib::cout << hour_old << "  " << hour;
            hour_old = hour;
            if(hour < 10){
                hour_first = 0;
                hour_second = hour;
            }else{
                hour_first = hour / 10 % 10;
                hour_second = hour %10;
                //number_three.draw_number(hour_first); hwlib::cout << hour_first << "\n";
                //number_four.draw_number(hour_second); hwlib::cout << hour_second << "\n";
            }  
            //update the display if the hour is updated
            display << "\f" << hour_first << hour_second << " : " << minut_first << minut_second << "\n" << clock.get_date() <<
            "/" << clock.get_month() << "/" << clock.get_year() << "\n" << days[clock.get_day()-1]<<hwlib::flush;
        }

        
      
      
      
   hwlib::wait_ms(500);



   }

}
