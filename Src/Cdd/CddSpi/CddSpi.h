#ifndef CDD_SPI_2023_08_22_H
  #define CDD_SPI_2023_08_22_H

  #include <stdbool.h>
  #include <stdint.h>

  #include <Mcal/Mcu.h>


 /* SPI_transmission_fifo_status_level SPI Transmission FIFO Status Level */
  #define CDD_SPI_FTLVL_EMPTY                 (0x00000000UL)
  #define CDD_SPI_FTLVL_QUARTER_FULL          (0x00000800UL)
  #define CDD_SPI_FTLVL_HALF_FULL             (0x00001000UL)
  #define CDD_SPI_FTLVL_FULL                  (0x00001800UL)

  /* SPI_reception_fifo_status_level SPI Reception FIFO Status Level */
  #define CDD_SPI_FRLVL_EMPTY                 (0x00000000UL)
  #define CDD_SPI_FRLVL_QUARTER_FULL          (0x00000200UL)
  #define CDD_SPI_FRLVL_HALF_FULL             (0x00000400UL)
  #define CDD_SPI_FRLVL_FULL                  (0x00000600UL)

  #define CDD_SPI_FLAG_FTLVL                  (0x3UL << 11U)  /* SPI fifo transmission level  */

  #define CDD_SPI_SR_FRLVL                    (0x3UL << 9U)   /*!< FIFO Reception Level */

  #define CDD_SPI_SR_TXE_POS                  (1U)

  /* functions prototypes */
  void CddSpi_Init(void);
  void CddSpi_CsEnable(void);
  void CddSpi_CsDisable(void);

  void SPI_Receive        (      uint8_t *pRxBuffer, uint32_t DataSize);
  void SPI_Transmit       (const uint8_t* pTxBuffer, uint32_t DataSize);
  void SPI_TransmitReceive(      uint8_t *pRxBuffer, uint32_t DataSize);


#endif // CDD_SPI_2023_08_22_H
