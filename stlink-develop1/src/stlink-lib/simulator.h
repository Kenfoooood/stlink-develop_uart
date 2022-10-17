#include <stlink.h>

#define MB_BUFFER_SIZE 256

typedef struct {
	uint8_t rxBuf[MB_BUFFER_SIZE];
	uint8_t txBuf[MB_BUFFER_SIZE];
	uint16_t rxSize;
	uint16_t txSize;
}MB_modbus_t;

int32_t send_recv1(MB_modbus_t *const modbus, uint8_t *txBuf, uint16_t txSize, uint8_t *rxBuf)
int stlink_uart_write_debug32(stlink_t *sl, uint32_t addr, uint32_t data);
void MB_SendMsg(MB_modbus_t *const modbus);
int32_t MB_msgHandler(MB_modbus_t *const modbus);
int32_t MEM_writeMem(uint32_t addr, const uint8_t *data, uint16_t size);
int32_t MB_write32(MB_modbus *const modbus);
int32_t MEM_readMem(uint32_t addr, uint8_t *data, uint16_t size);
int32_t MB_read32(MB_modbus_t *const modbus);

