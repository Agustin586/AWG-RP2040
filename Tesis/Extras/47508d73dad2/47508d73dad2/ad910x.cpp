/******************************************************************************
    @file:  ad910x.cpp
 
    @brief: Implements device-specific SPI and pattern generation functions,
            and printing of data from SPI read to text-based user interface
-------------------------------------------------------------------------------
    Copyright (c) 2021 Analog Devices, Inc.
    All rights reserved.
 
    This software is proprietary to Analog Devices, Inc. and its licensors.
    By using this software you agree to the terms of the associated
    Analog Devices Software License Agreement.
    
    20210120-LWSC-CTSLA
******************************************************************************/

#include "mbed.h"
#include "ad910x.h"

extern UnbufferedSerial pc;

AD910x::AD910x(PinName CSB,
               PinName MOSI,
               PinName MISO,
               PinName SCK,
               PinName RESETB,
               PinName TRIGGERB) :
    spi(MOSI, MISO, SCK), csb(CSB), resetb(RESETB), triggerb(TRIGGERB)
{
}

/*
 * @brief Reset AD910x SPI registers to default values
 * @param none
 * @return none
 */
void AD910x::AD910x_reg_reset()
{
    resetb = 0;
    wait_us( 10 );
    resetb = 1;
}


/*
 * @brief Print register address and data in hexadecimal format
 * @param addr - SPI/SRAM register address
 * @param data - 16-bit data
 * @return none
 */
void AD910x::print_data( uint16_t addr, uint16_t data )
{
    printf( "0x%04X, 0x%04X\n", addr, data );
}

/*
 * @brief Write data to SRAM
 * @param data[] - array of data to be written to SRAM
 * @return none
 */
void AD910x::AD910x_update_sram( int16_t data[] )
{ 
    spi_write( 0x001E, 0x0004 );
    
    int16_t data_shifted = 0;
    
    uint16_t sram_add = 0x6000;
    
    for ( int i=0; i<4096; i++ ){
        data_shifted = data[i] << 2;
        spi_write( sram_add+i, data_shifted );
    }
    
    spi_write( 0x001E, 0x0010 );   
}

/*
 * @brief Read from SRAM and print data
 * @param n - number of SRAM addresses to be read from
 * @return none
 */
void AD910x::AD910x_print_sram( uint16_t n )
{
    spi_write( 0x001E, 0x000C );
    
    int16_t data_shifted = 0;
    
    uint16_t sram_add = 0x6000;
    
    for ( int i=0; i<n; i++ ){
        data_shifted = spi_read( sram_add+i ) >> 2;
        print_data( sram_add+i, data_shifted );
    }
    
    spi_write( 0x001E, 0x0010 );
}

/*
 * @brief Write to SPI registers, and read and print new register values
 * @param data[] - array of data to written to SPI registers
 * @return none
 */
void AD910x::AD910x_update_regs( uint16_t data[] ){
       
    uint16_t data_display = 0;
     
    for ( int i=0; i<66; i++ ){
        spi_write( reg_add[i], data[i] );
        data_display = spi_read( reg_add[i] );
        print_data( reg_add[i], data_display );
    } 
}

/*
 * @brief Start pattern generation by setting AD910x trigger pin to 0
 * @param none
 * @return none
 */
void AD910x::AD910x_start_pattern()
{
    triggerb = 0;
}

/*
 * @brief Stop pattern generation by setting AD910x trigger pin to 1
 * @param none
 * @return none
 */
void AD910x::AD910x_stop_pattern()
{
    triggerb = 1;
}

/*********************************************************/
// SPI FUNCTIONS 
/*********************************************************/

/*
 * @brief Set AD910x SPI word length, mode, frequency
 * @param reg_len - SPI word length
 * @param mode - SPI clock polarity, clock and data phase
 * @param hz - SPI bus frequency in hz
 * @return none
 */
void AD910x::spi_init(uint8_t reg_len, uint8_t mode, uint32_t hz)
{
    spi.format( reg_len, mode );
    spi.frequency( hz );
}

/*
 * @brief Write 16-bit data to AD910x SPI/SRAM register
 * @param addr - SPI/SRAM address
 * @param data - data to be written to register address
 * @return none
 */
void AD910x::spi_write( uint16_t addr, int16_t data )
{
    csb = 0;
    
    spi.write( addr );
    spi.write( data );
    
    csb = 1;
    wait_us( 1 );
}

/*
 * @brief Read 16-bit data from AD910x SPI/SRAM register
 * @param addr - SPI/SRAM address
 * @return reg_data - data returned by AD910x
 */
int16_t AD910x::spi_read( uint16_t addr )
{
    csb = 0;
    
    uint16_t read_addr;
    int16_t reg_data;
    
    read_addr = 0x8000+addr;
    spi.write( read_addr );
    reg_data = spi.write( 0 );
    
    csb = 1;
    wait_us( 1 );
    
    return reg_data;
}