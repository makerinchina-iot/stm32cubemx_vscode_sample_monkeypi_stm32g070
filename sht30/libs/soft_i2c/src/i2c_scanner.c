/********************************************************************************
 * @author: MonkeyPi
 * @website: makerinchina.cn
 * @date: 2022/8/21 12:04
 * @version: 0.1
 * @description:
 ********************************************************************************/

#include "soft_i2c.h"

/**
 * @brief  scan i2c bus, address type: 7bit
 * @param  from_addr : scan start address
 * @param  to_addr   : scan end address
 * @param  callback  : scan result callback func, result == true if address found
 */
void scan_i2c_bus(uint8_t from_addr, uint8_t to_addr,
                  void (*callback)(uint8_t address, bool result))
{
    bool rc;
    for (uint8_t addr = from_addr; addr <= to_addr; addr++)
    {
        rc = soft_i2c_transfer(addr, 0, 0, 0, 0);

        callback(addr, rc);
    }
}
