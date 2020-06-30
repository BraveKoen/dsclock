
//          Copyright Koen Brave 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef DSCLOCK_HPP
#define DSCLOCK_HPP
#include "i2c_bus.hpp"

/// @file
/// \brief
/// library that let you communicate with the ds1307 chip 
/// \details
/// This library gives you control over setting the time and receive the time
class dsClock{
private:
    /// \brief 
    /// address of the chip
    /// \details
    /// The address of the ds1307 chip is always 0x68
    uint8_t  ds_address = 0x68; //adres from the chip
	uint8_t data_send[2]; //Buffer to send bits
	uint8_t  data_get[2];   //vector to receive data 

    /// \brief
    /// Communication bus
    /// \details
    /// A r2d2 bus is needed to communicate with the chip
    r2d2::i2c::i2c_bus_c & bus;

    /// \brief
    /// Decimal to binary-coded decimal
    /// \details
    /// This is the formula to go from decimal to BCD(binary-coded decimal)
    uint8_t dec_Bcd(uint8_t waarde){return((waarde/10*16) + (waarde%10));} //dec to bcd
    /// \brief
    /// Binary-coded decimal to decimal
    /// \details
    /// Formula to go from BCD to decimal

    uint8_t bcd_Dec(uint8_t waarde){return((waarde/16*10) + (waarde%16));} //bcd to dec
    /// \brief
    /// Function to write data to the chip
    /// \details
    /// reg_address is the register address where there will be written to
    /// Time can not be lower then 0
    void write_data(int reg_address, uint8_t time){

        if(time < 0){
            time = 0;
        }
        data_send[0] = reg_address;
        data_send[1] = dec_Bcd(time);
        bus.write(ds_address, data_send, 2);
    }
    /// \brief
    /// Gives time back in BCD
    /// \details
    /// gives the raw data out of the register.

    int get_data(int reg_address){
        bus.read(ds_address, data_get, 1, reg_address, 1);
        return data_get[0];
    }

public:
    /// \brief
    /// make a object with a r2d2 bus
    /// \details
    /// everything will be default 0
    dsClock( r2d2::i2c::i2c_bus_c & bus):
    bus(bus)
    {}
    /// \brief
    /// make a object with a r2d2 bus and with time set
    /// \details
    /// make a object with time set to time given
    /// \note year will be given in the follwing form: 2013 = 13 2090 = 90
    dsClock( r2d2::i2c::i2c_bus_c & bus, int second = 0, int minutes = 0 , int hour = 0,int day = 1, int date = 1, int month = 1, int year = 0):
    bus(bus)
    {
        set_seconds(second);
        set_minutes(minutes);
        set_hour(hour);
        set_day(day);
        set_date(date);
        set_month(month);
        set_year(year);
    }

    /// \brief
    /// set seconds
    /// \details
    /// If you set seconds higher then 60 it will be set to 59.
    /// If the second is a negative number it will be set to 0.
    void set_seconds(int sec){
        if(sec >= 60){
            sec = 59;
        }
        write_data(0, sec);
    }
    /// \brief
    /// Gives back the seconds
    /// \details
    /// seconds encoded with bcd to dec
    int get_seconds(){
        return bcd_Dec(get_data(0x00 & 0x7f));   
    }
    /// \brief
    /// set minutes
    /// \details
    /// If you set minutes higher then 60 it will be set to 59.
    /// If the second is a negative number it will be set to 0.

    void set_minutes(int min){
        if(min >= 60){
            min = 59;
        }
        write_data(1, min);
    }
    /// \brief
    /// Gives back the minutes
    /// \details
    /// minutes encoded with bcd to dec
    int get_minutes(){
        return bcd_Dec(get_data(0x01 ));
    }
    
    /// \brief
    /// set hour
    /// \details
    /// If you set hour higher then 23 it will be set to 23.
    /// If the hour is a negative number it will be set to 0.
    void set_hour(int hour){
        if(hour > 23){
            hour = 23;
        }
        write_data(2, hour);
    }

    /// \brief
    /// Gives back the hour
    /// \details
    /// hour encoded with bcd to dec
    int get_hour(){
        return bcd_Dec(get_data(0x02& 0x3f) );
    }
    /// \brief
    /// set day
    /// \details
    /// day 1 == monday, day 2 == tuesday so on
    /// If you set the day higher then 7 it will be set to 7.
    /// If the hour is a negative number it will be set to 1.
    void set_day(int day){
        if(day > 7){
            day = 7;
        } else if(day < 1){
            day = 1;
        }
        write_data(3, day);
    }
    /// \brief
    /// gives a int back 
    /// \details
    /// day 1 == monday, day 2 == tuesday so on
    int get_day(){
        return bcd_Dec(get_data(0x03));
    }

    /// \brief 
    /// set date
    /// \details
    /// If you set the date higher then 31 it will be set to 31.
    /// If the date is a negative number it will be set to 1.
    void set_date(int date){
        if(date > 31){
            date = 31;
        } else if(date < 1){
            date = 1;
        }
        write_data(4, date);
    }

    /// \brief
    /// gives the date back
    int get_date(){
        return bcd_Dec(get_data(0x04));
    }
    /// \brief 
    /// set month
    /// \details
    /// If you set the month higher then 12 it will be set to 12.
    /// If the date is a negative number it will be set to 1.


    void set_month(int month){
        if(month > 12){
            month = 12;
        }else if(month < 1){
            month = 1;
        }
        write_data(5, month);
    }
    /// \brief
    /// gives the month back

    int get_month(){
        return bcd_Dec(get_data(0x05));
    }
    /// \brief
    /// set year
    /// \details
    /// If you set the year higher then 99 it will be set to 99.
    /// If the year is a negative number it will be set to 0.

    void set_year(int year){
        if(year > 99 ){
            year = 99;
        }
        write_data(6, year);
    }
    /// \brief
    /// Gives back the year
    /// \details
    /// You will only get the last 2 numbers back.  
    int get_year(){
        return bcd_Dec(get_data(0x06));
    }

};
#endif
