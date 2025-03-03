#include "LMP91000.h"

LMP91000::LMP91000() {
}

uint8_t LMP91000::write(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(LMP91000_I2C_ADDRESS);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission(true);
    return read(reg);
}

uint8_t LMP91000::read(uint8_t reg){
    uint8_t chr = 0;
    Wire.beginTransmission(LMP91000_I2C_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(LMP91000_I2C_ADDRESS, 1, true);
    if(Wire.available()){
        chr = Wire.read();
    }
    return chr;
}

uint8_t LMP91000::status(void) {
    return read(LMP91000_STATUS_REG);
}

uint8_t LMP91000::lock(){
    return write(LMP91000_LOCK_REG, LMP91000_WRITE_LOCK);
}

uint8_t LMP91000::unlock(){ 
    return write(LMP91000_LOCK_REG, LMP91000_WRITE_UNLOCK);
}

uint8_t LMP91000::configure(uint8_t _tiacn, uint8_t _refcn, uint8_t _modecn){
    if(status() == LMP91000_READY){
        unlock();
        write(LMP91000_TIACN_REG, _tiacn);
        write(LMP91000_REFCN_REG, _refcn);
        write(LMP91000_MODECN_REG, _modecn);
        lock();
        return 1;
    }
    return 0;
}
