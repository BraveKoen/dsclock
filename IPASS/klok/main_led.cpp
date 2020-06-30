#include "ledscreen.hpp"
#include "lednumber.hpp"
#include "dsClock.hpp"
#include "i2c_bus.cpp"
#include <vector>
int main(){
   using namespace std;
   //Data pins for the communication to the led strip
   auto pin_out_one = hwlib::target::pin_out(hwlib::target::pins::d12);
   auto pin_out_two = hwlib::target::pin_out(hwlib::target::pins::d23);
   auto pin_out_three = hwlib::target::pin_out(hwlib::target::pins::d24);
   auto pin_out_four = hwlib::target::pin_out(hwlib::target::pins::d25);

   //a window for every number
   auto window_one = ledscreen::ledwindow_base(hwlib::xy(28,1), pin_out_one);
   auto window_two = ledscreen::ledwindow_base(hwlib::xy(28,1), pin_out_two);
   auto window_three = ledscreen::ledwindow_base(hwlib::xy(28,1), pin_out_three);
   auto window_four = ledscreen::ledwindow_base(hwlib::xy(28,1), pin_out_four);
    
   auto number_one = ledscreen::lednumber(window_one, 0, hwlib::color(255,0,0));
   auto number_two = ledscreen::lednumber(window_two, 0, hwlib::color(255,0,0));
   auto number_three = ledscreen::lednumber(window_three, 0, hwlib::color(255,0,0));
   auto number_four = ledscreen::lednumber(window_four, 0, hwlib::color(255,0,0));
   hwlib::wait_ms(500);
   
   auto bus = r2d2::i2c::i2c_bus_c(r2d2::i2c::i2c_bus_c::interface::interface_1, 50000);
   auto clock = dsClock(bus, 40 ,59, 5, 30, 6, 20);

   int minut_old = -1; //to prefent updating every time
   int hour_old = -1;

   int lijst[10][3] = {{255,0,0}, {0,255,0}, {0,0,255}, {148, 0,211}, {255,255,51}, {0,0,102}, {96,96,96}, {204,0,102},{178,255, 102}, {102,0,0}};
   while(true){
      int minutes = clock.get_minutes();
      number_one.change_color(lijst[hour_old]);
      hwlib::cout << lijst[9][1];
      

      int hour = clock.get_hour();
      
      //you do not want to update if it minutes are still the same
      if(minutes != minut_old){
        
         minut_old = minutes;

         if(minutes < 10){
            number_three.draw_number(0);
            number_four.draw_number(minutes);
   
         }else{
            int minut_first = minutes / 10 % 10;
            int minut_second = minutes %10;
            number_three.draw_number(minut_first); //hwlib::cout << " Eerste getet moet 3 zijn: " << minut_first << "\n";
            number_four.draw_number(minut_second); //hwlib::cout << minut_second;
         }

      }
      //Update if hour is not the same as before
      if(hour != hour_old){
         hwlib::cout << hour_old << "  " << hour;
         hour_old = hour;
         if(hour < 10){
            number_one.draw_number(0);
            number_two.draw_number(hour);
         }else{
            int hour_first = hour / 10 % 10;
            int hour_second = hour %10;
            number_three.draw_number(hour_first); hwlib::cout << hour_first << "\n";
            number_four.draw_number(hour_second); hwlib::cout << hour_second << "\n";
         }

      }

      
      
      
   hwlib::wait_ms(500);



   }

}