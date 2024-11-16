#ifndef Cdd_I2C_2024_03_06_H
  #define Cdd_I2C_2024_03_06_H

  #include "stddef.h"
  #include "stdint.h"

  void CddI2c_Init(void);
  void CddI2c_StartTransmission(const uint8_t DeviceAddress, const size_t DataSize, const uint8_t WriteReadMode);
  void CddI2c_TransferMultipleBytes(const uint8_t* Data, const size_t DataSize);
  void CddI2c_TransferSingleByte(const uint8_t Data);
  void CddI2c_Stop(void);

#endif /* Cdd_I2C_2024_03_06_H */
