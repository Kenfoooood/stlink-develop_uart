#define FLASH_MEM 288*1024
#define RAM_MEM 8*1024

uint8_t flash_memory[FLASH_MEM];
uint8_t ram[RAM_MEM];

MB_modbus_t MB_host;
MB_modbus_t MB_device;


/*int stlink_uart_write_debug32(stlink_t *sl, uint32_t addr, uint32_t data) {
	
	MB_modbus_t *const modbus = &MB_host; // sl->backend_data
	
	unsigned char *const rdata = sl->q_buf;
	unsigned char *const cmd = sl->c_buf;
	
	int i = 0;
	cmd[i++] = SRLINK_DEBUG_APIV2_WRITEDEBUGREG;
	write_uint32(&cmd[i], addr);
	write_uint32(&cmd[i + 4], data);
	
	return send_recv(modbus, cmd, i, rdata);
}*/

/*int stlink_uart_read_debug32(stlink_t *sl, uint32_t addr, uint32_t *data) {
	
    MB_modbus_t *const modbus = &MB_host;
    unsigned char *const rdata = sl->q_buf;
    unsigned char *const cmd = sl->c_buf;
    
    int i = 0;
    cmd[i++] = STLINK_DEBUG_APIV2_READDEBUGREG;
    write_uint32(&cmd[i], addr);
    size = send_recv(modbus, cmd, i, rdata);

    if (size < 0) {
        return(-1);
    }

    *data = read_uint32(rdata, 4);

    return(0);
}*/

/*int32_t send_recv(MB_modbus_t *const modbus, uint8_t *txBuf, uint16_t txSize, uint8_t *rxBuf) {
    
    //-- skip modbus header
	uint8_t *payload = &modbus->txBuf[2];
	memcpy(payload, txBuf, txSize);
	
	//-- send message to device/simulator
	MB_sendMsg(modbus);
	
	/* Answer will be received at modbus->rxBuf*/
	
	//uint16_t rxSize = modbus->rxBuf[2];
	
	//check error
	/*if(!rxSize) {
		return -1;
	}
	
	//-- skip modbus header and size
	payload = &modbus->rxBuf[3];
	memcpy(rxBuf, payload, rxSize);
	
	return 0;
}*/

//--- Device/Simulator side code ---//


//-- Emulate send data to UART
void MB_SendMsg(MB_modbus_t *const modbus) {
	
	MB_modbus_t *const dest = (modbus == MB_host) ? &MB_device : &MB_host;
	
	/* Node: calc crc16 and set modbus header (txSize + 4)*/
	dest->rxSize = modbus->txSize + 4;
	memcpy(dest->rxBuf, modbus->txBuf, dest->rxSize);
	
	//-- Emulate receive and handle data on remote device/simulator
	if (dest == &MB_device) {
		MB_msgHandler(dest);
	}
}

int32_t MB_msgHandler(MB_modbus_t *const modbus) {
	//-- skip modbus header
	uint8_t *payload = &modbus->rxBuf[2];
	uint8_t cmd = payload[0];
	int32_t res = 0;
	
	switch(cmd) {
		case STLINK_DEBUG_APIV2_READDEBUGREG:
			res = MB_read32(modbus);
			break;
		case STLINK_DEBUG_APIV2_WRITEDEBUGREG:
			res = MB_write32(modbus);
			break;
		case STLINK_DEBUG_APIV2_READREG:
			res = ;
			break;
		case STLINK_DEBUG_APIV2_READALLREGS:
			res = ;
			break;
		case STLINK_DEBUG_READMEM_32BIT:
			res = MB_read32(modbus);
			break;
		case STLINK_DEBUG_WRITEMEM_32BIT:
			res = MB_write32(modbus);
			break;
		
			
		
		
		default:
			return -1;
			break;
	}
	
	//check error code
	if(res) {
		//-- set cmd(error) (for AMP protocol)
		modbus->txBuf[2] = 0;
	}
	
	MB_sendMsg(modbus);
	
	return 0;
	
}
int32_t MEM_writeMem(uint32_t addr, const uint8_t *data, uint16_t size) {
	//-- check addr
	if (addr > 0x8000000 && addr < 0x20000000) {
		//-- write flash
	}
	else if (addr >= 0x20000000) {
		//-- write ram
	}
	else {
		// error
		return -1;
	}
	
	return 0;
}

int32_t MB_write32(MB_modbus *const modbus) {
	//-- skip modbus header and cmd
	uint8_t *payload = &modbus->rxBuf[3];
	
	uint32_t addr = *(uint32_t *)payload;
	payload += 4;
	
	uint32_t value = *(uint32_t *)payload;
	payload += 4;
	
	//-- save cmd(ok) (for AMP protocol)
	modbus->txBuf[2] = 1;
	
	return MEM_writeMem(addr, &value, 4);
}

int32_t MEM_readMem(uint32_t addr, uint8_t *data, uint16_t size) {
	//-- check addr
	if(addr > 0x8000000 && addr < 0x20000000) {
		//-- read flash
		
	}
	else if (addr >= 0x20000000) {
		//-- read ram
	}
	else {
		// error
		return -1;
	}
	return 0;
}

int32_t MB_read32(MB_modbus_t *const modbus) {
	//-- skip modbus header and cmd
	uint8_t *payload = &modbus->rxBuf[3];
	
	uint32_t addr = *(uint32_t *)payload;
	payload += 4;
	
	//-- save size (for AMP protocol)
	modbuss->txBuf[2] = 4;
	
	//-- skip modbus header and size
	uint8_t *recData = &modbus->txBuf[3];
	
	//-- Note: recData as sl->q_buf
	return MEM_readMem(addr, recData, 4);
}

struct stlink_reg init_regs {
	{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150},
	{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150,
	0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150},
	0x01000000,
	0x20000c80,
	0x00000000,
	0x00000000,
	0x00000000,
	0,0,0,0,0
}

int32_t MB_ReadAllRegs(MB_modbus_t *const modbus) {
	memcpy(modbus->txBuf[i], init_regs, sizeof(init_regs));
}


