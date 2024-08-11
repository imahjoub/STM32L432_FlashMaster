#ifndef Cdd_I2C_2024_03_06_H
  #define Cdd_I2C_2024_03_06_H

  #include "stddef.h"
  #include "stdint.h"

  void CddI2c_Init(void);
  void CddI2c_StartTransmission(uint8_t DeviceAddress, size_t DataSize, uint8_t WriteReadMode);
  void CddI2c_TransferMultipleByte(uint8_t* Data, size_t DataSize);
  void CddI2c_TransferSingleByte(uint8_t Data);
  void CddI2c_Stop(void);

#endif /* Cdd_I2C_2024_03_06_H */
