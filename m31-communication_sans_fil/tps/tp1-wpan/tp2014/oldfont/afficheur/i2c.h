
extern result_t i2cWrite ( uint8_t slaveAddress, uint8_t* data, uint16_t len );

extern result_t i2cRead ( uint8_t slaveAddress, uint8_t* data, uint16_t len );

extern void i2cInit ( void );
