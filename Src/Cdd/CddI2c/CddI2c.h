#ifndef Cdd_I2C_2024_03_06_H
  #define Cdd_I2C_2024_03_06_H

  #include "stdint.h"

  void CddI2c_Init(void);
  void CddI2c_StartTransmission(uint8_t address, uint8_t direction);
  void CddI2c_TransferSingleByte(uint8_t data);
  void CddI2c_Stop(void);

  uint8_t CddI2c_ReadAck(void);
  uint8_t CddI2c_ReadNack(void);

#endif /* Cdd_I2C_2024_03_06_H */
