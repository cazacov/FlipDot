#include "CommandProcessor.h"

void CommandProcessor::processByte(uint8_t next_byte) {
    if (is_receiving_) {
        if (next_byte & COMMAND_FLAG) {

            Serial.print("ERR 1 ");  // Awaiting info byte, got command  
            Serial.print(awaiting_bytes);
            Serial.print(" ");
            Serial.println(next_byte, HEX);
            got_new_command(next_byte);
        }
        buffer[offset++] = next_byte;
        awaiting_bytes--;
        if (awaiting_bytes == 0) {
            if (command_ == GfxCommand::kBitmap && offset == 4) {   // Variable length command, calculate remaining buffer length
                uint8_t w = buffer[2];
                uint8_t h = buffer[3];
                uint8_t row = (w + 7) >> 3;
                awaiting_bytes = row * h;
                is_receiving_ = awaiting_bytes;
            }
            else {
                is_receiving_ = false;
                executeCommand();
            }
        }
    } else {
        if (!(next_byte & COMMAND_FLAG)) {
            Serial.println("ERR 2");  // Awaiting command, got info byte       
        } else {   
            got_new_command(next_byte);
        }
    }
}

void CommandProcessor::got_new_command(uint8_t next_byte) {
     is_receiving_ = decodeCommand(next_byte);
     if (!is_receiving_) {   // Self-contained command
        executeCommand();
    }
}

bool CommandProcessor::decodeCommand(uint8_t data) {
    offset = 0;
    switch (data) {
        case (int)GfxCommand::kClear:
            command_ = GfxCommand::kClear;
            awaiting_bytes = 0;
            return false;
            break;
        case (int)GfxCommand::kSetDelays:
            command_ = GfxCommand::kSetDelays;
            awaiting_bytes = 1;
            return true;
            break;
        case (int)GfxCommand::kFill:
            command_ = GfxCommand::kFill;
            awaiting_bytes = 0;
            return false;
            break;
        case (int)GfxCommand::kDotSet:
            command_ = GfxCommand::kDotSet;
            awaiting_bytes = 2;
            return true;
            break;
        case (int)GfxCommand::kDotReset:
            command_ = GfxCommand::kDotReset;
            awaiting_bytes = 2;
            return true;
            break;
        case (int)GfxCommand::kSetColor:
            command_ = GfxCommand::kSetColor;
            awaiting_bytes = 1;
            return true;
            break;
        case (int)GfxCommand::kLine:
            command_ = GfxCommand::kLine;
            awaiting_bytes = 4;
            return true;
            break;         
        case (int)GfxCommand::kRect:
            command_ = GfxCommand::kRect;
            awaiting_bytes = 4;
            return true;
            break;               
        case (int)GfxCommand::kFillRect:
            command_ = GfxCommand::kFillRect;
            awaiting_bytes = 4;
            return true;
            break;          
        case (int)GfxCommand::kBitmap:
            command_ = GfxCommand::kBitmap;
            awaiting_bytes = 4;
            return true;
            break;               
        default:
            command_ = GfxCommand::kNop;
            awaiting_bytes = 0;
            return false;
    }
    return true;
}

void CommandProcessor::executeCommand() {
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t h;
    uint8_t factor;
    switch (command_) {
        case GfxCommand::kClear:
            for (int16_t y = 0; y < display_->height(); y++) {
                display_->writeFastHLine(0, y, display_->width(), 0);
            }
            break;
        case GfxCommand::kSetDelays:
            factor = buffer[0];
            if (factor < 10) {
                factor = 10;
            }
            pulse_microseconds = PULSE_MICROSECONDS * factor / 100;
            delay_microseconds = DELAY_MICROSECONDS * factor / 100;
            break;
        case GfxCommand::kFill:
            for (int16_t y = 0; y < display_->height(); y++) {
                display_->writeFastHLine(0, y, display_->width(), 1);
            }
            break;
        case GfxCommand::kDotSet:
            display_->writePixel(buffer[0], buffer[1], 1);
            break;
        case GfxCommand::kDotReset:
            display_->writePixel(buffer[0], buffer[1], 0);
            break;       
        case GfxCommand::kSetColor:
            color = buffer[0];
            break;
        case GfxCommand::kLine:
            display_->writeLine(buffer[0], buffer[1], buffer[2], buffer[3], color);
            break;    
        case GfxCommand::kRect:
            x = buffer[0];
            y = buffer[1];
            w = buffer[2];
            h = buffer[3];
            display_->writeFastHLine(x, y, w, color);
            display_->writeFastHLine(x, y + h - 1, w, color);
            display_->writeFastVLine(x, y, h, color);
            display_->writeFastVLine(x + w - 1, y, h, color);
            break;         
        case GfxCommand::kFillRect:
            x = buffer[0];
            y = buffer[1];
            w = buffer[2];
            h = buffer[3];
            for (int16_t i = x; i < x + w; i++) {
                 display_->writeFastVLine(i, y, h, color);
            }
            break;   
        case GfxCommand::kBitmap:
            x = buffer[0];
            y = buffer[1];
            w = buffer[2];
            h = buffer[3];
//            Serial.println("Copy bitmap");
            copyBitmap(x, y, w, h, buffer + 4);
            break;            
        default:
            // Do nothing;
            break;
    }   
}

void CommandProcessor::copyBitmap(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t *bytes) {
    display_->setBitmap(bytes, display_->frameBufferSize);
    return;
// TODO: allow partial screen updating    
    uint8_t mask = 0x80;
    uint8_t yy = y0;
    for (int i = 0; i < w; i++) {
        uint8_t xx = x0;
        for (int j = 0; j < w; j++) {
            display_->drawPixel(xx, yy, ((*bytes) & mask) ? 1 : 0);
            xx++;
            mask >>= 1;
            if (mask == 0) {
                mask = 0x80;
                bytes++;
            }
        }
        if (mask != 0x80) {
            mask = 0x80;
            bytes++;
        }
        yy++;
    }
}

 void CommandProcessor::simulateCommand(GfxCommand command, int byte_count, ...) {
    
    va_list valist;
    va_start(valist, byte_count);
    for (int i = 0; i < byte_count; i++) {
      buffer[i] = va_arg(valist, int);
    }
    va_end(valist);
    command_ = command;
    executeCommand();
 }