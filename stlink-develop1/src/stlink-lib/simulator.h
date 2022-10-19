#define MB_BUFFER_SIZE 256

typedef struct {
	uint8_t rxBuf[MB_BUFFER_SIZE];
	uint8_t txBuf[MB_BUFFER_SIZE];
	uint16_t rxSize;
	uint16_t txSize;
}MB_modbus_t;

void MB_sendMsg(MB_modbus_t *const modbus);
int32_t MB_msgHandler(MB_modbus_t *const modbus);
int32_t MEM_writeMem(uint32_t addr, const uint8_t *data, uint16_t size);
int32_t MB_write32(MB_modbus_t *const modbus);
int32_t MEM_readMem(uint32_t addr, uint8_t *data, uint16_t size);
int32_t MB_read32(MB_modbus_t *const modbus);

