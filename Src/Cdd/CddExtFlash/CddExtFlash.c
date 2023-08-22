#include <Cdd/CddExtFlash/CddExtFlash.h>


// Function to enable writing
void is25lp128f_write_enable(void)
{
  // Send Write Enable command
  spi_transfer(CMD_WRITE_ENABLE);
}

// Function to wait until the chip is not busy
void is25lp128f_wait_for_read(void)
{
  while (spi_transfer(0x05) & 0x01); // Poll Status Register until busy bit is cleared
}

// Function to write data to a sector
void is25lp128f_write_sector(uint32_t sector_address, uint8_t *data, uint32_t len)
{
  // Enable writing
  is25lp128f_write_enable();

  // Send Page Program command
  spi_transfer(CMD_PAGE_PROGRAM);

  spi_transfer((sector_address >> 16) & 0xFF);

  // Address byte 2
  spi_transfer((sector_address >> 8) & 0xFF);

  // Address byte 1
  spi_transfer(sector_address & 0xFF);

  // Address byte 0
  // Write data
  for (uint32_t i = 0; i < len; i++)
  {
    spi_transfer(data[i]);
  }

  // Wait for completion
  is25lp128f_wait_for_read();
}


