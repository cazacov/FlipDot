#pragma once

// Supports Russian characters in win1251 encoding and German cp850 with ß moved to 191 to avoid collision

String utf8ascii(String source)
{
    String result = "";
    char buffer[2] = {'0', '\0'};

    int len = source.length();
    int i = 0;
    
    while (i < len) {
        unsigned char ch = source[i++];

        if (ch >= 0xC0) {
            // German Umlauts
            if (ch == 0xC3) {
                ch = source[i++];
                switch (ch) 
                {
                    case 0x84:  // Ä
                        ch = 0x8E;
                        break;
                    case 0xA4:  // ä
                        ch = 0x84;
                        break;
                    case 0x96:  // Ö
                        ch = 0x99;
                        break;
                    case 0xB6:  // ö
                        ch = 0x94;
                        break;
                    case 0x9C:  // Ü
                        ch = 0x9A;
                        break;
                    case 0xbc:  // ü
                        ch = 0x81;
                        break;
                    case 0x9F:  // ß
                        ch = 0xE1;
                        break;
                    default:
                        ch = 0x5F; // "_"
                        break;
                }                    
            }
            // Russian characters
            else if (ch == 0xD0) {
                ch = source[i++]; 
                if (ch == 0x81) { 
                    ch = 0xA8; 
                } else if (ch >= 0x90 && ch <= 0xBF) {
                    ch = ch + 0x30;
                }
            }
            else if (ch == 0xD1) {
                ch = source[i++];
                if (ch == 0x91) { 
                    ch = 0xB8; 
                } else if (ch >= 0x80 && ch <= 0x8F) {
                    ch = ch + 0x70;
                }
            }
        }

        buffer[0] = ch; 
        result = result + String(buffer);
    }
    return result;
}
