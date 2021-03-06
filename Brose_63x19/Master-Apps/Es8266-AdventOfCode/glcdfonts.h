#ifndef _GLCDFONTS_h
#define _GLCDFONTS_h


//GLCD FontName : Digits8x16
//GLCD FontSize : 8 x 16

const unsigned short Digits8x16[] = {
        0x08, 0x00, 0x00, 0xF8, 0x07, 0xFE, 0x1F, 0x07, 0x38, 0x03, 0x30, 0x07, 0x38, 0xFE, 0x1F, 0xF8, 0x07,  // Code for char 0
        0x06, 0x00, 0x00, 0x30, 0x00, 0x18, 0x00, 0x0C, 0x00, 0xFF, 0x3F, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00,  // Code for char 1
        0x08, 0x0C, 0x30, 0x0E, 0x3C, 0x07, 0x3E, 0x03, 0x3F, 0x83, 0x33, 0xC3, 0x31, 0xFE, 0x30, 0x3C, 0x30,  // Code for char 2
        0x08, 0x00, 0x00, 0x0C, 0x0C, 0x0E, 0x1C, 0x07, 0x38, 0x63, 0x30, 0x63, 0x38, 0xFE, 0x1F, 0x9C, 0x0F,  // Code for char 3
        0x08, 0x00, 0x07, 0xC0, 0x07, 0xE0, 0x06, 0x78, 0x06, 0x1E, 0x06, 0xFF, 0x3F, 0xFF, 0x3F, 0x00, 0x06,  // Code for char 4
        0x08, 0x00, 0x00, 0x78, 0x0C, 0x7F, 0x1C, 0x2F, 0x38, 0x33, 0x30, 0x73, 0x38, 0xE3, 0x1F, 0xC0, 0x0F,  // Code for char 5
        0x08, 0x00, 0x00, 0xF8, 0x07, 0xFE, 0x1F, 0x67, 0x38, 0x63, 0x30, 0xE3, 0x30, 0xCE, 0x1F, 0x8C, 0x0F,  // Code for char 6
        0x08, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x3E, 0xE3, 0x3F, 0xFB, 0x01, 0x1F, 0x00, 0x07, 0x00,  // Code for char 7
        0x08, 0x00, 0x00, 0x9E, 0x0F, 0xFF, 0x1F, 0xE3, 0x38, 0x63, 0x30, 0xE3, 0x38, 0xFF, 0x1F, 0x9E, 0x0F,  // Code for char 8
        0x08, 0x00, 0x00, 0x7C, 0x0C, 0xFE, 0x1C, 0xC3, 0x31, 0x83, 0x31, 0xC7, 0x39, 0xFE, 0x1F, 0xF8, 0x07   // Code for char 9
        };

const unsigned short Digits8x12[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char !
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char "  
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char #
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char $
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char %
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char &
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char '
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char (
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char )
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char *
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char +
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char ,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char - 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char .
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char /  
        0x06, 0xF8, 0x03, 0xFE, 0x0F, 0x06, 0x0C, 0x06, 0x0C, 0xFE, 0x0F, 0xF8, 0x03, 0x00, 0x00, 0x00, 0x00,  // Code for char 0
        0x05, 0x00, 0x00, 0x10, 0x00, 0x18, 0x00, 0xFE, 0x0F, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 1
        0x06, 0x0C, 0x0C, 0x0E, 0x0F, 0x86, 0x0F, 0xC6, 0x0D, 0xFE, 0x0C, 0x3C, 0x0C, 0x00, 0x00, 0x00, 0x00,  // Code for char 2
        0x06, 0x0C, 0x06, 0x0E, 0x0E, 0x66, 0x0C, 0x66, 0x0C, 0xFE, 0x0F, 0x9C, 0x07, 0x00, 0x00, 0x00, 0x00,  // Code for char 3
        0x06, 0xC0, 0x03, 0x70, 0x03, 0x1C, 0x03, 0xFE, 0x0F, 0xFE, 0x0F, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,  // Code for char 4
        0x06, 0x7E, 0x06, 0x7E, 0x0E, 0x36, 0x0C, 0x36, 0x0C, 0xF6, 0x0F, 0xE6, 0x07, 0x00, 0x00, 0x00, 0x00,  // Code for char 5
        0x06, 0xFC, 0x07, 0xFE, 0x0F, 0x66, 0x0C, 0x66, 0x0C, 0xE6, 0x0F, 0xCC, 0x07, 0x00, 0x00, 0x00, 0x00,  // Code for char 6
        0x06, 0x06, 0x00, 0x06, 0x0E, 0x86, 0x0F, 0xE6, 0x01, 0x7E, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 7
        0x06, 0x9C, 0x07, 0xFE, 0x0F, 0x66, 0x0C, 0x66, 0x0C, 0xFE, 0x0F, 0x9C, 0x07, 0x00, 0x00, 0x00, 0x00,  // Code for char 8
        0x06, 0x7C, 0x06, 0xFE, 0x0E, 0xC6, 0x0C, 0xC6, 0x0C, 0xFE, 0x0F, 0xFC, 0x07, 0x00, 0x00, 0x00, 0x00   // Code for char 9
        };        

const unsigned short Small4x5[] = {
        0x03, 0x00, 0x00, 0x00, 0x00,            // Code for char  
        0x02, 0x00, 0x17, 0x00, 0x00,            // Code for char !
        0x02, 0x01, 0x01, 0x00, 0x00,            // Code for char "
        0x03, 0x0A, 0x1F, 0x0A, 0x00,            // Code for char #
        0x01, 0x00, 0x00, 0x00, 0x00,            // Code for char $
        0x03, 0x19, 0x04, 0x13, 0x00,            // Code for char %
        0x03, 0x18, 0x16, 0x1E, 0x00,            // Code for char &
        0x01, 0x01, 0x00, 0x00, 0x00,            // Code for char '
        0x02, 0x0E, 0x11, 0x00, 0x00,            // Code for char (
        0x03, 0x00, 0x11, 0x0E, 0x00,            // Code for char )
        0x03, 0x0A, 0x04, 0x0A, 0x00,            // Code for char *
        0x03, 0x04, 0x0E, 0x04, 0x00,            // Code for char +
        0x02, 0x00, 0x18, 0x00, 0x00,            // Code for char ,
        0x03, 0x04, 0x04, 0x04, 0x00,            // Code for char -
        0x02, 0x00, 0x10, 0x00, 0x00,            // Code for char .
        0x03, 0x18, 0x04, 0x03, 0x00,            // Code for char /
        0x03, 0x1F, 0x11, 0x1F, 0x00,            // Code for char 0
        0x02, 0x02, 0x1F, 0x00, 0x00,            // Code for char 1
        0x03, 0x1D, 0x15, 0x17, 0x00,            // Code for char 2
        0x03, 0x11, 0x15, 0x1F, 0x00,            // Code for char 3
        0x03, 0x07, 0x04, 0x1F, 0x00,            // Code for char 4
        0x03, 0x17, 0x15, 0x1D, 0x00,            // Code for char 5
        0x03, 0x1F, 0x15, 0x1D, 0x00,            // Code for char 6
        0x03, 0x01, 0x1D, 0x03, 0x00,            // Code for char 7
        0x03, 0x1F, 0x15, 0x1F, 0x00,            // Code for char 8
        0x03, 0x17, 0x15, 0x1F, 0x00             // Code for char 9
        };


const unsigned short DaysOfWeek24x5[] = {
        0x18, 0x1F, 0x01, 0x01, 0x1F, 0x00, 0x0E, 0x11, 0x0E, 0x00, 0x1F, 0x04, 0x1F, 0x00, 0x1F, 0x15, 0x11, 0x00, 0x18, 0x0F, 0x09, 0x0F, 0x18, 0x00, 0x10,  // Code for char  
        0x17, 0x1F, 0x15, 0x15, 0x0A, 0x00, 0x01, 0x1F, 0x01, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x1F, 0x05, 0x07, 0x00, 0x1F, 0x04, 0x1F, 0x00, 0x10, 0x00,  // Code for char !
        0x17, 0x0E, 0x11, 0x11, 0x0A, 0x00, 0x1F, 0x09, 0x09, 0x06, 0x00, 0x1F, 0x15, 0x11, 0x00, 0x18, 0x0F, 0x09, 0x0F, 0x18, 0x00, 0x1E, 0x09, 0x1F, 0x00,  // Code for char "
        0x12, 0x07, 0x04, 0x1F, 0x00, 0x1F, 0x15, 0x11, 0x00, 0x01, 0x1F, 0x01, 0x00, 0x1F, 0x15, 0x15, 0x0A, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char #
        0x12, 0x1F, 0x01, 0x01, 0x1F, 0x00, 0x17, 0x0D, 0x1F, 0x00, 0x01, 0x1F, 0x01, 0x00, 0x1F, 0x04, 0x1F, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char $
        0x15, 0x0E, 0x11, 0x11, 0x0A, 0x00, 0x11, 0x0A, 0x04, 0x03, 0x00, 0x1F, 0x15, 0x15, 0x08, 0x00, 0x1F, 0x15, 0x15, 0x08, 0x00, 0x10, 0x00, 0x00, 0x00,  // Code for char %
        0x18, 0x1F, 0x15, 0x15, 0x0A, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x0E, 0x11, 0x11, 0x0A, 0x00, 0x1F, 0x04, 0x0A, 0x11, 0x00, 0x1F, 0x05, 0x07, 0x10   // Code for char &
        };        

const unsigned short WochenTage10x5[] = {
        0x0A, 0x1F, 0x02, 0x04, 0x02, 0x1F, 0x00, 0x0E, 0x11, 0x11, 0x0E,  // Code for char  
        0x09, 0x1F, 0x11, 0x11, 0x0E, 0x00, 0x00, 0x11, 0x1F, 0x11, 0x00,  // Code for char !
        0x09, 0x1F, 0x02, 0x04, 0x02, 0x1F, 0x00, 0x11, 0x1F, 0x11, 0x00,  // Code for char "
        0x09, 0x1F, 0x11, 0x11, 0x0E, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00,  // Code for char #
        0x09, 0x1F, 0x05, 0x05, 0x01, 0x00, 0x1F, 0x05, 0x0D, 0x12, 0x00,  // Code for char $
        0x09, 0x12, 0x15, 0x15, 0x09, 0x00, 0x1E, 0x09, 0x09, 0x1E, 0x00,  // Code for char %
        0x09, 0x12, 0x15, 0x15, 0x09, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00   // Code for char &
        };

const unsigned short DaysOfWeeksRu10x5[] = {
        0x09, 0x1F, 0x01, 0x01, 0x1F, 0x00, 0x1F, 0x04, 0x04, 0x1F, 0x00,  // Code for char  
        0x0A, 0x1F, 0x15, 0x15, 0x0A, 0x00, 0x01, 0x01, 0x1F, 0x01, 0x01,  // Code for char !
        0x09, 0x0E, 0x11, 0x11, 0x0A, 0x00, 0x1F, 0x09, 0x09, 0x06, 0x00,  // Code for char "
        0x0A, 0x07, 0x04, 0x04, 0x1F, 0x00, 0x01, 0x01, 0x1F, 0x01, 0x01,  // Code for char #
        0x0A, 0x1F, 0x01, 0x01, 0x1F, 0x00, 0x01, 0x01, 0x1F, 0x01, 0x01,  // Code for char $
        0x09, 0x0E, 0x11, 0x11, 0x0A, 0x00, 0x1F, 0x15, 0x15, 0x19, 0x00,  // Code for char %
        0x09, 0x1F, 0x15, 0x15, 0x0A, 0x00, 0x0E, 0x11, 0x11, 0x0A, 0x00   // Code for char &
        };        

const unsigned short Weather24x12[] = {
        0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0xC2, 0x06, 0xE2, 0x06, 0x3E, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char  
        0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x02, 0x11, 0x01, 0x82, 0x00, 0x38, 0x00, 0x7C, 0x00, 0x7D, 0x0F, 0x7C, 0x00, 0x38, 0x00, 0x82, 0x00, 0x11, 0x01, 0x10, 0x02, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char !
        0x18, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x08, 0x21, 0x04, 0x22, 0x02, 0x04, 0x01, 0x70, 0x00, 0xF8, 0x00, 0xFB, 0x0E, 0x78, 0x01, 0x30, 0x01, 0x14, 0x01, 0x12, 0x03, 0x11, 0x05, 0x20, 0x09, 0x10, 0x01, 0x08, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x08, 0x01, 0x90, 0x00, 0x60, 0x00,  // Code for char "
        0x18, 0x10, 0x04, 0x08, 0x04, 0x08, 0x04, 0x10, 0x04, 0x10, 0x02, 0x20, 0x01, 0xC1, 0x04, 0x02, 0x02, 0x04, 0x01, 0x70, 0x00, 0xF8, 0x00, 0xBB, 0x0E, 0x18, 0x01, 0x10, 0x02, 0x08, 0x02, 0x04, 0x02, 0x04, 0x02, 0x04, 0x02, 0x18, 0x02, 0x08, 0x02, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01,  // Code for char #
        0x18, 0x82, 0x00, 0x84, 0x00, 0x88, 0x00, 0x84, 0x00, 0x84, 0x00, 0x84, 0x00, 0x48, 0x00, 0x30, 0x03, 0x80, 0x04, 0x40, 0x04, 0x40, 0x04, 0x80, 0x04, 0x40, 0x04, 0x20, 0x04, 0x10, 0x04, 0x08, 0x04, 0x08, 0x04, 0x08, 0x04, 0x10, 0x04, 0x20, 0x04, 0x40, 0x04, 0x20, 0x04, 0x10, 0x04, 0x10, 0x04,  // Code for char $
        0x17, 0x00, 0x00, 0x00, 0x01, 0x30, 0x01, 0x48, 0x00, 0x48, 0x01, 0x14, 0x05, 0x14, 0x05, 0x52, 0x05, 0x52, 0x05, 0x42, 0x04, 0x4C, 0x05, 0x04, 0x05, 0x42, 0x05, 0x51, 0x01, 0x51, 0x00, 0x51, 0x05, 0x51, 0x05, 0x02, 0x05, 0x04, 0x05, 0x48, 0x01, 0x70, 0x05, 0x40, 0x05, 0x00, 0x01, 0x00, 0x00,  // Code for char %
        0x15, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x0C, 0x44, 0x03, 0x44, 0x00, 0x42, 0x0C, 0x42, 0x03, 0x42, 0x00, 0x4C, 0x0C, 0x44, 0x03, 0x42, 0x00, 0x41, 0x0C, 0x41, 0x03, 0x41, 0x00, 0x41, 0x0C, 0x42, 0x03, 0x44, 0x00, 0x48, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char &
        0x15, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x02, 0x44, 0x07, 0x44, 0x02, 0x42, 0x00, 0x42, 0x00, 0x42, 0x0A, 0x4C, 0x04, 0x44, 0x0A, 0x42, 0x00, 0x41, 0x02, 0x41, 0x07, 0x41, 0x02, 0x41, 0x00, 0x42, 0x00, 0x44, 0x05, 0x48, 0x02, 0x30, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char '
        0x18, 0x84, 0x00, 0x88, 0x00, 0x88, 0x00, 0x88, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x7C, 0x0E, 0xFE, 0x07, 0xE3, 0x01, 0x60, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x20, 0x01, 0x10, 0x01, 0x10, 0x01, 0x20, 0x01, 0x10, 0x01, 0x08, 0x01, 0x04, 0x01, 0x04, 0x01, 0x08, 0x01, 0x10, 0x01,  // Code for char (
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // Code for char )
        };        

const unsigned short Monate15x5[] = {
        0x0E, 0x08, 0x10, 0x10, 0x0F, 0x00, 0x1E, 0x09, 0x09, 0x1E, 0x00, 0x1F, 0x06, 0x0C, 0x1F, 0x00,  // Code for char  
        0x0E, 0x1F, 0x05, 0x05, 0x01, 0x00, 0x1F, 0x15, 0x15, 0x11, 0x00, 0x1F, 0x15, 0x15, 0x0A, 0x00,  // Code for char !
        0x0F, 0x1F, 0x02, 0x04, 0x02, 0x1F, 0x00, 0x1F, 0x05, 0x0D, 0x16, 0x00, 0x19, 0x15, 0x15, 0x13,  // Code for char "
        0x0E, 0x1E, 0x09, 0x09, 0x1E, 0x00, 0x1F, 0x05, 0x05, 0x02, 0x00, 0x1F, 0x05, 0x0D, 0x16, 0x00,  // Code for char #
        0x0E, 0x1F, 0x02, 0x04, 0x02, 0x1F, 0x00, 0x1E, 0x09, 0x09, 0x1E, 0x00, 0x11, 0x1F, 0x11, 0x00,  // Code for char $
        0x0E, 0x08, 0x10, 0x10, 0x0F, 0x00, 0x0F, 0x10, 0x10, 0x0F, 0x00, 0x1F, 0x06, 0x0C, 0x1F, 0x00,  // Code for char %
        0x0E, 0x08, 0x10, 0x10, 0x0F, 0x00, 0x0F, 0x10, 0x10, 0x0F, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x00,  // Code for char &
        0x0E, 0x1E, 0x09, 0x09, 0x1E, 0x00, 0x0F, 0x10, 0x10, 0x0F, 0x00, 0x0E, 0x11, 0x19, 0x1A, 0x00,  // Code for char '
        0x0E, 0x12, 0x15, 0x15, 0x09, 0x00, 0x1F, 0x15, 0x15, 0x11, 0x00, 0x1F, 0x05, 0x05, 0x02, 0x00,  // Code for char (
        0x0F, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x1F, 0x04, 0x0A, 0x11, 0x00, 0x01, 0x01, 0x1F, 0x01, 0x01,  // Code for char )
        0x0F, 0x1F, 0x06, 0x0C, 0x1F, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x03, 0x0C, 0x10, 0x0C, 0x03,  // Code for char *
        0x0E, 0x1F, 0x11, 0x11, 0x0E, 0x00, 0x1F, 0x15, 0x15, 0x11, 0x00, 0x19, 0x15, 0x15, 0x13, 0x00   // Code for char +
        };

const unsigned short MonthsRu15x5[] = {
        0x0E, 0x16, 0x09, 0x09, 0x1F, 0x00, 0x1F, 0x04, 0x04, 0x1F, 0x00, 0x1F, 0x15, 0x15, 0x0A, 0x00,  // Code for char  
        0x0F, 0x07, 0x05, 0x1F, 0x05, 0x07, 0x00, 0x1F, 0x15, 0x15, 0x11, 0x00, 0x1F, 0x15, 0x15, 0x0A,  // Code for char !
        0x0E, 0x1F, 0x02, 0x04, 0x02, 0x1F, 0x00, 0x1F, 0x05, 0x05, 0x02, 0x00, 0x01, 0x1F, 0x01, 0x00,  // Code for char "
        0x0E, 0x1E, 0x09, 0x09, 0x1E, 0x00, 0x1F, 0x01, 0x01, 0x1F, 0x00, 0x1F, 0x05, 0x05, 0x02, 0x00,  // Code for char #
        0x0F, 0x1F, 0x02, 0x04, 0x02, 0x1F, 0x00, 0x1E, 0x09, 0x09, 0x1E, 0x00, 0x12, 0x0D, 0x05, 0x1F,  // Code for char $
        0x0E, 0x1F, 0x0C, 0x06, 0x1F, 0x00, 0x1F, 0x04, 0x0E, 0x11, 0x0E, 0x00, 0x1F, 0x04, 0x1F, 0x00,  // Code for char %
        0x0F, 0x1F, 0x0C, 0x06, 0x1F, 0x00, 0x1F, 0x04, 0x0E, 0x11, 0x0E, 0x00, 0x18, 0x06, 0x01, 0x1F,  // Code for char &
        0x0E, 0x1E, 0x09, 0x09, 0x1E, 0x00, 0x1F, 0x15, 0x15, 0x0A, 0x00, 0x1F, 0x01, 0x01, 0x03, 0x00,  // Code for char '
        0x0E, 0x0E, 0x11, 0x11, 0x0A, 0x00, 0x1F, 0x15, 0x15, 0x11, 0x00, 0x1F, 0x04, 0x04, 0x1F, 0x00,  // Code for char (
        0x0F, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x1F, 0x04, 0x0A, 0x11, 0x00, 0x01, 0x01, 0x1F, 0x01, 0x01,  // Code for char )
        0x0E, 0x1F, 0x04, 0x04, 0x1F, 0x00, 0x0E, 0x11, 0x11, 0x0E, 0x00, 0x16, 0x09, 0x09, 0x1F, 0x00,  // Code for char *
        0x0F, 0x18, 0x0F, 0x09, 0x0F, 0x18, 0x00, 0x1F, 0x15, 0x15, 0x11, 0x00, 0x1F, 0x04, 0x0A, 0x11   // Code for char +
        };        

#endif

