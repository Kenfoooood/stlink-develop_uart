#ifndef STM32FLASH_H
#define STM32FLASH_H

/* stm32f FPEC flash controller interface, pm0063 manual */
// STM32F05x is identical, based on RM0091 (DM00031936, Doc ID 018940 Rev 2, August 2012)
#define FLASH_REGS_ADDR 0x40022000
#define FLASH_REGS_SIZE 0x28

#define FLASH_ACR (FLASH_REGS_ADDR + 0x00)
#define FLASH_KEYR (FLASH_REGS_ADDR + 0x04)
#define FLASH_OPTKEYR (FLASH_REGS_ADDR + 0x08)
#define FLASH_SR (FLASH_REGS_ADDR + 0x0c)
#define FLASH_CR (FLASH_REGS_ADDR + 0x10)
#define FLASH_AR (FLASH_REGS_ADDR + 0x14)
#define FLASH_OBR (FLASH_REGS_ADDR + 0x1c)
#define FLASH_WRPR (FLASH_REGS_ADDR + 0x20)

// STM32F10x_XL has two flash memory banks with separate registers to control
// the second bank.
#define FLASH_KEYR2 (FLASH_REGS_ADDR + 0x44)
#define FLASH_SR2 (FLASH_REGS_ADDR + 0x4c)
#define FLASH_CR2 (FLASH_REGS_ADDR + 0x50)
#define FLASH_AR2 (FLASH_REGS_ADDR + 0x54)

// For STM32F05x, the RDPTR_KEY may be wrong, but as it is not used anywhere...
#define FLASH_RDPTR_KEY 0x00a5
#define FLASH_KEY1 0x45670123
#define FLASH_KEY2 0xcdef89ab

#define FLASH_L0_PRGKEY1 0x8c9daebf
#define FLASH_L0_PRGKEY2 0x13141516

#define FLASH_L0_PEKEY1 0x89abcdef
#define FLASH_L0_PEKEY2 0x02030405

#define FLASH_OPTKEY1 0x08192A3B
#define FLASH_OPTKEY2 0x4C5D6E7F

#define FLASH_F0_OPTKEY1 0x45670123
#define FLASH_F0_OPTKEY2 0xCDEF89AB

#define FLASH_L0_OPTKEY1 0xFBEAD9C8
#define FLASH_L0_OPTKEY2 0x24252627

#define FLASH_SR_BSY 0
#define FLASH_SR_PG_ERR 2
#define FLASH_SR_WRPRT_ERR 4
#define FLASH_SR_EOP 5

#define FLASH_SR_ERROR_MASK ((1 << FLASH_SR_PG_ERR) | (1 << FLASH_SR_WRPRT_ERR))

#define FLASH_CR_PG 0
#define FLASH_CR_PER 1
#define FLASH_CR_MER 2
#define FLASH_CR_OPTPG 4
#define FLASH_CR_OPTER 5
#define FLASH_CR_STRT 6
#define FLASH_CR_LOCK 7
#define FLASH_CR_OPTWRE 9
#define FLASH_CR_OBL_LAUNCH 13

#define STM32L_FLASH_REGS_ADDR ((uint32_t)0x40023c00)
#define STM32L_FLASH_ACR (STM32L_FLASH_REGS_ADDR + 0x00)
#define STM32L_FLASH_PECR (STM32L_FLASH_REGS_ADDR + 0x04)
#define STM32L_FLASH_PDKEYR (STM32L_FLASH_REGS_ADDR + 0x08)
#define STM32L_FLASH_PEKEYR (STM32L_FLASH_REGS_ADDR + 0x0c)
#define STM32L_FLASH_PRGKEYR (STM32L_FLASH_REGS_ADDR + 0x10)
#define STM32L_FLASH_OPTKEYR (STM32L_FLASH_REGS_ADDR + 0x14)
#define STM32L_FLASH_SR (STM32L_FLASH_REGS_ADDR + 0x18)
#define STM32L_FLASH_OBR (STM32L_FLASH_REGS_ADDR + 0x1c)
#define STM32L_FLASH_WRPR (STM32L_FLASH_REGS_ADDR + 0x20)
#define FLASH_L1_FPRG 10
#define FLASH_L1_PROG 3

// Flash registers common to STM32G0 and STM32G4 series.
#define STM32Gx_FLASH_REGS_ADDR ((uint32_t)0x40022000)
#define STM32Gx_FLASH_ACR (STM32Gx_FLASH_REGS_ADDR + 0x00)
#define STM32Gx_FLASH_KEYR (STM32Gx_FLASH_REGS_ADDR + 0x08)
#define STM32Gx_FLASH_OPTKEYR (STM32Gx_FLASH_REGS_ADDR + 0x0c)
#define STM32Gx_FLASH_SR (STM32Gx_FLASH_REGS_ADDR + 0x10)
#define STM32Gx_FLASH_CR (STM32Gx_FLASH_REGS_ADDR + 0x14)
#define STM32Gx_FLASH_ECCR (STM32Gx_FLASH_REGS_ADDR + 0x18)
#define STM32Gx_FLASH_OPTR (STM32Gx_FLASH_REGS_ADDR + 0x20)

// G0 (RM0444 Table 1, sec 3.7)
// Mostly the same as G4 chips, but the notation
// varies a bit after the 'OPTR' register.
#define STM32G0_FLASH_REGS_ADDR (STM32Gx_FLASH_REGS_ADDR)
#define STM32G0_FLASH_PCROP1ASR (STM32G0_FLASH_REGS_ADDR + 0x24)
#define STM32G0_FLASH_PCROP1AER (STM32G0_FLASH_REGS_ADDR + 0x28)
#define STM32G0_FLASH_WRP1AR (STM32G0_FLASH_REGS_ADDR + 0x2C)
#define STM32G0_FLASH_WRP1BR (STM32G0_FLASH_REGS_ADDR + 0x30)
#define STM32G0_FLASH_PCROP1BSR (STM32G0_FLASH_REGS_ADDR + 0x34)
#define STM32G0_FLASH_PCROP1BER (STM32G0_FLASH_REGS_ADDR + 0x38)
#define STM32G0_FLASH_SECR (STM32G0_FLASH_REGS_ADDR + 0x80)

// G4 (RM0440 Table 17, sec 3.7.19)
// Mostly the same as STM32G0 chips, but there are a few extra
// registers because 'cat 3' devices can have two Flash banks.
#define STM32G4_FLASH_REGS_ADDR (STM32Gx_FLASH_REGS_ADDR)
#define STM32G4_FLASH_PDKEYR (STM32G4_FLASH_REGS_ADDR + 0x04)
#define STM32G4_FLASH_PCROP1SR (STM32G4_FLASH_REGS_ADDR + 0x24)
#define STM32G4_FLASH_PCROP1ER (STM32G4_FLASH_REGS_ADDR + 0x28)
#define STM32G4_FLASH_WRP1AR (STM32G4_FLASH_REGS_ADDR + 0x2C)
#define STM32G4_FLASH_WRP1BR (STM32G4_FLASH_REGS_ADDR + 0x30)
#define STM32G4_FLASH_PCROP2SR (STM32G4_FLASH_REGS_ADDR + 0x44)
#define STM32G4_FLASH_PCROP2ER (STM32G4_FLASH_REGS_ADDR + 0x48)
#define STM32G4_FLASH_WRP2AR (STM32G4_FLASH_REGS_ADDR + 0x4C)
#define STM32G4_FLASH_WRP2BR (STM32G4_FLASH_REGS_ADDR + 0x50)
#define STM32G4_FLASH_SEC1R (STM32G4_FLASH_REGS_ADDR + 0x70)
#define STM32G4_FLASH_SEC2R (STM32G4_FLASH_REGS_ADDR + 0x74)

// G0/G4 FLASH control register
#define STM32Gx_FLASH_CR_PG (0)      /* Program */
#define STM32Gx_FLASH_CR_PER (1)     /* Page erase */
#define STM32Gx_FLASH_CR_MER1 (2)    /* Mass erase */
#define STM32Gx_FLASH_CR_PNB (3)     /* Page number */
#define STM32G0_FLASH_CR_PNG_LEN (5) /* STM32G0: 5 page number bits */
#define STM32G4_FLASH_CR_PNG_LEN (7) /* STM32G4: 7 page number bits */
#define STM32Gx_FLASH_CR_MER2 (15)   /* Mass erase (2nd bank)*/
#define STM32Gx_FLASH_CR_STRT (16)   /* Start */
#define STM32Gx_FLASH_CR_OPTSTRT                                               \
  (17)                              /* Start of modification of option bytes */
#define STM32Gx_FLASH_CR_FSTPG (18) /* Fast programming */
#define STM32Gx_FLASH_CR_EOPIE (24) /* End of operation interrupt enable */
#define STM32Gx_FLASH_CR_ERRIE (25) /* Error interrupt enable */
#define STM32Gx_FLASH_CR_OBL_LAUNCH (27) /* Forces the option byte loading */
#define STM32Gx_FLASH_CR_OPTLOCK (30)    /* Options Lock */
#define STM32Gx_FLASH_CR_LOCK (31)       /* FLASH_CR Lock */

// G0/G4 FLASH status register
#define STM32Gx_FLASH_SR_ERROR_MASK (0x3fa)
#define STM32Gx_FLASH_SR_PROGERR (3)
#define STM32Gx_FLASH_SR_WRPERR (4)
#define STM32Gx_FLASH_SR_PGAERR (5)
#define STM32Gx_FLASH_SR_BSY (16) /* FLASH_SR Busy */
#define STM32Gx_FLASH_SR_EOP (0)  /* FLASH_EOP End of Operation */

// G4 FLASH option register
#define STM32G4_FLASH_OPTR_DBANK (22) /* FLASH_OPTR Dual Bank Mode */

// WB (RM0434)
#define STM32WB_FLASH_REGS_ADDR ((uint32_t)0x58004000)
#define STM32WB_FLASH_ACR (STM32WB_FLASH_REGS_ADDR + 0x00)
#define STM32WB_FLASH_KEYR (STM32WB_FLASH_REGS_ADDR + 0x08)
#define STM32WB_FLASH_OPT_KEYR (STM32WB_FLASH_REGS_ADDR + 0x0C)
#define STM32WB_FLASH_SR (STM32WB_FLASH_REGS_ADDR + 0x10)
#define STM32WB_FLASH_CR (STM32WB_FLASH_REGS_ADDR + 0x14)
#define STM32WB_FLASH_ECCR (STM32WB_FLASH_REGS_ADDR + 0x18)
#define STM32WB_FLASH_OPTR (STM32WB_FLASH_REGS_ADDR + 0x20)
#define STM32WB_FLASH_PCROP1ASR (STM32WB_FLASH_REGS_ADDR + 0x24)
#define STM32WB_FLASH_PCROP1AER (STM32WB_FLASH_REGS_ADDR + 0x28)
#define STM32WB_FLASH_WRP1AR (STM32WB_FLASH_REGS_ADDR + 0x2C)
#define STM32WB_FLASH_WRP1BR (STM32WB_FLASH_REGS_ADDR + 0x30)
#define STM32WB_FLASH_PCROP1BSR (STM32WB_FLASH_REGS_ADDR + 0x34)
#define STM32WB_FLASH_PCROP1BER (STM32WB_FLASH_REGS_ADDR + 0x38)
#define STM32WB_FLASH_IPCCBR (STM32WB_FLASH_REGS_ADDR + 0x3C)
#define STM32WB_FLASH_C2ACR (STM32WB_FLASH_REGS_ADDR + 0x5C)
#define STM32WB_FLASH_C2SR (STM32WB_FLASH_REGS_ADDR + 0x60)
#define STM32WB_FLASH_C2CR (STM32WB_FLASH_REGS_ADDR + 0x64)
#define STM32WB_FLASH_SFR (STM32WB_FLASH_REGS_ADDR + 0x80)
#define STM32WB_FLASH_SRRVR (STM32WB_FLASH_REGS_ADDR + 0x84)

// WB Flash control register.
#define STM32WB_FLASH_CR_STRT (16)       /* Start */
#define STM32WB_FLASH_CR_OPTSTRT (17)    /* Start writing option bytes */
#define STM32WB_FLASH_CR_OBL_LAUNCH (27) /* Forces the option byte loading */
#define STM32WB_FLASH_CR_OPTLOCK (30)    /* Option Lock */
#define STM32WB_FLASH_CR_LOCK (31)       /* Lock */
// WB Flash status register.
#define STM32WB_FLASH_SR_ERROR_MASK (0x3f8) /* SR [9:3] */
#define STM32WB_FLASH_SR_PROGERR (3)        /* Programming alignment error */
#define STM32WB_FLASH_SR_WRPERR (4)         /* Write protection error */
#define STM32WB_FLASH_SR_PGAERR (5)         /* Programming error */
#define STM32WB_FLASH_SR_BSY (16)           /* Busy */

// 32L4 register base is at FLASH_REGS_ADDR (0x40022000)
#define STM32L4_FLASH_KEYR (FLASH_REGS_ADDR + 0x08)
#define STM32L4_FLASH_OPTKEYR (FLASH_REGS_ADDR + 0x0C)
#define STM32L4_FLASH_SR (FLASH_REGS_ADDR + 0x10)
#define STM32L4_FLASH_CR (FLASH_REGS_ADDR + 0x14)
#define STM32L4_FLASH_OPTR (FLASH_REGS_ADDR + 0x20)

#define STM32L4_FLASH_SR_ERROR_MASK 0x3f8 /* SR [9:3] */
#define STM32L4_FLASH_SR_PROGERR 3
#define STM32L4_FLASH_SR_WRPERR 4
#define STM32L4_FLASH_SR_PGAERR 5
#define STM32L4_FLASH_SR_BSY 16

#define STM32L4_FLASH_CR_LOCK 31       /* Lock control register */
#define STM32L4_FLASH_CR_OPTLOCK 30    /* Lock option bytes */
#define STM32L4_FLASH_CR_PG 0          /* Program */
#define STM32L4_FLASH_CR_PER 1         /* Page erase */
#define STM32L4_FLASH_CR_MER1 2        /* Bank 1 erase */
#define STM32L4_FLASH_CR_MER2 15       /* Bank 2 erase */
#define STM32L4_FLASH_CR_STRT 16       /* Start command */
#define STM32L4_FLASH_CR_OPTSTRT 17    /* Start writing option bytes */
#define STM32L4_FLASH_CR_BKER 11       /* Bank select for page erase */
#define STM32L4_FLASH_CR_PNB 3         /* Page number (8 bits) */
#define STM32L4_FLASH_CR_OBL_LAUNCH 27 /* Option bytes reload */
// Bits requesting flash operations (useful when we want to clear them)
#define STM32L4_FLASH_CR_OPBITS                                                \
  (uint32_t)((1lu << STM32L4_FLASH_CR_PG) | (1lu << STM32L4_FLASH_CR_PER) |    \
             (1lu << STM32L4_FLASH_CR_MER1) | (1lu << STM32L4_FLASH_CR_MER1))
// Page is fully specified by BKER and PNB
#define STM32L4_FLASH_CR_PAGEMASK (uint32_t)(0x1fflu << STM32L4_FLASH_CR_PNB)

#define STM32L4_FLASH_OPTR_DUALBANK 21

// STM32L0x flash register base and offsets RM0090 - DM00031020.pdf
#define STM32L0_FLASH_REGS_ADDR ((uint32_t)0x40022000)

#define STM32L0_FLASH_PELOCK (0)
#define STM32L0_FLASH_OPTLOCK (2)
#define STM32L0_FLASH_OBL_LAUNCH (18)

#define STM32L0_FLASH_SR_ERROR_MASK 0x00013F00
#define STM32L0_FLASH_SR_WRPERR 8
#define STM32L0_FLASH_SR_PGAERR 9
#define STM32L0_FLASH_SR_NOTZEROERR 16

#define FLASH_ACR_OFF ((uint32_t)0x00)
#define FLASH_PECR_OFF ((uint32_t)0x04)
#define FLASH_PDKEYR_OFF ((uint32_t)0x08)
#define FLASH_PEKEYR_OFF ((uint32_t)0x0c)
#define FLASH_PRGKEYR_OFF ((uint32_t)0x10)
#define FLASH_OPTKEYR_OFF ((uint32_t)0x14)
#define FLASH_SR_OFF ((uint32_t)0x18)
#define FLASH_OBR_OFF ((uint32_t)0x1c)
#define FLASH_WRPR_OFF ((uint32_t)0x20)

// STM32F7
#define FLASH_F7_REGS_ADDR ((uint32_t)0x40023c00)
#define FLASH_F7_KEYR (FLASH_F7_REGS_ADDR + 0x04)
#define FLASH_F7_OPT_KEYR (FLASH_F7_REGS_ADDR + 0x08)
#define FLASH_F7_SR (FLASH_F7_REGS_ADDR + 0x0c)
#define FLASH_F7_CR (FLASH_F7_REGS_ADDR + 0x10)
#define FLASH_F7_OPTCR (FLASH_F7_REGS_ADDR + 0x14)
#define FLASH_F7_OPTCR1 (FLASH_F7_REGS_ADDR + 0x18)
#define FLASH_F7_OPTCR_LOCK 0
#define FLASH_F7_OPTCR_START 1
#define FLASH_F7_CR_STRT 16
#define FLASH_F7_CR_LOCK 31
#define FLASH_F7_CR_SER 1
#define FLASH_F7_CR_SNB 3
#define FLASH_F7_CR_SNB_MASK 0xf8
#define FLASH_F7_SR_BSY 16
#define FLASH_F7_SR_ERS_ERR 7 /* Erase Sequence Error */
#define FLASH_F7_SR_PGP_ERR 6 /* Programming parallelism error */
#define FLASH_F7_SR_PGA_ERR 5 /* Programming alignment error */
#define FLASH_F7_SR_WRP_ERR 4 /* Write protection error */
#define FLASH_F7_SR_OP_ERR 1  /* Operation error */
#define FLASH_F7_SR_EOP 0     /* End of operation */
#define FLASH_F7_OPTCR1_BOOT_ADD0 0
#define FLASH_F7_OPTCR1_BOOT_ADD1 16

#define FLASH_F7_SR_ERROR_MASK                                                 \
  ((1 << FLASH_F7_SR_ERS_ERR) | (1 << FLASH_F7_SR_PGP_ERR) |                   \
   (1 << FLASH_F7_SR_PGA_ERR) | (1 << FLASH_F7_SR_WRP_ERR) |                   \
   (1 << FLASH_F7_SR_OP_ERR))

// STM32F4
#define FLASH_F4_REGS_ADDR ((uint32_t)0x40023c00)
#define FLASH_F4_KEYR (FLASH_F4_REGS_ADDR + 0x04)
#define FLASH_F4_OPT_KEYR (FLASH_F4_REGS_ADDR + 0x08)
#define FLASH_F4_SR (FLASH_F4_REGS_ADDR + 0x0c)
#define FLASH_F4_CR (FLASH_F4_REGS_ADDR + 0x10)
#define FLASH_F4_OPTCR (FLASH_F4_REGS_ADDR + 0x14)
#define FLASH_F4_OPTCR_LOCK 0
#define FLASH_F4_OPTCR_START 1
#define FLASH_F4_CR_STRT 16
#define FLASH_F4_CR_LOCK 31
#define FLASH_F4_CR_SER 1
#define FLASH_F4_CR_SNB 3
#define FLASH_F4_CR_SNB_MASK 0xf8
#define FLASH_F4_SR_ERROR_MASK 0x000000F0
#define FLASH_F4_SR_PGAERR 5
#define FLASH_F4_SR_WRPERR 4
#define FLASH_F4_SR_BSY 16

// STM32F2
#define FLASH_F2_REGS_ADDR ((uint32_t)0x40023c00)
#define FLASH_F2_KEYR (FLASH_F2_REGS_ADDR + 0x04)
#define FLASH_F2_OPT_KEYR (FLASH_F2_REGS_ADDR + 0x08)
#define FLASH_F2_SR (FLASH_F2_REGS_ADDR + 0x0c)
#define FLASH_F2_CR (FLASH_F2_REGS_ADDR + 0x10)
#define FLASH_F2_OPT_CR (FLASH_F2_REGS_ADDR + 0x14)
#define FLASH_F2_OPT_LOCK_BIT (1u << 0)
#define FLASH_F2_CR_STRT 16
#define FLASH_F2_CR_LOCK 31

#define FLASH_F2_CR_SER 1
#define FLASH_F2_CR_SNB 3
#define FLASH_F2_CR_SNB_MASK 0x78
#define FLASH_F2_SR_BSY 16

// STM32H7xx
#define FLASH_H7_CR_LOCK 0
#define FLASH_H7_CR_PG 1
#define FLASH_H7_CR_SER 2
#define FLASH_H7_CR_BER 3
#define FLASH_H7_CR_PSIZE 4
#define FLASH_H7_CR_START(chipid) (chipid == STM32_CHIPID_H7Ax ? 5 : 7)
#define FLASH_H7_CR_SNB 8
#define FLASH_H7_CR_SNB_MASK 0x700

#define FLASH_H7_SR_QW 2
#define FLASH_H7_SR_WRPERR 17
#define FLASH_H7_SR_PGSERR 18
#define FLASH_H7_SR_STRBERR 19
#define FLASH_H7_SR_ERROR_MASK                                                 \
  ((1 << FLASH_H7_SR_PGSERR) | (1 << FLASH_H7_SR_STRBERR) |                    \
   (1 << FLASH_H7_SR_WRPERR))

#define FLASH_H7_OPTCR_OPTLOCK 0
#define FLASH_H7_OPTCR_OPTSTART 1
#define FLASH_H7_OPTCR_MER 4

#define FLASH_H7_OPTSR_OPT_BUSY 0
#define FLASH_H7_OPTSR_OPTCHANGEERR 30

#define FLASH_H7_OPTCCR_CLR_OPTCHANGEERR 30

#define FLASH_H7_REGS_ADDR ((uint32_t)0x52002000)
#define FLASH_H7_KEYR1 (FLASH_H7_REGS_ADDR + 0x04)
#define FLASH_H7_KEYR2 (FLASH_H7_REGS_ADDR + 0x104)
#define FLASH_H7_OPT_KEYR (FLASH_H7_REGS_ADDR + 0x08)
#define FLASH_H7_OPT_KEYR2 (FLASH_H7_REGS_ADDR + 0x108)
#define FLASH_H7_CR1 (FLASH_H7_REGS_ADDR + 0x0c)
#define FLASH_H7_CR2 (FLASH_H7_REGS_ADDR + 0x10c)
#define FLASH_H7_SR1 (FLASH_H7_REGS_ADDR + 0x10)
#define FLASH_H7_SR2 (FLASH_H7_REGS_ADDR + 0x110)
#define FLASH_H7_CCR1 (FLASH_H7_REGS_ADDR + 0x14)
#define FLASH_H7_CCR2 (FLASH_H7_REGS_ADDR + 0x114)
#define FLASH_H7_OPTCR (FLASH_H7_REGS_ADDR + 0x18)
#define FLASH_H7_OPTCR2 (FLASH_H7_REGS_ADDR + 0x118)
#define FLASH_H7_OPTSR_CUR (FLASH_H7_REGS_ADDR + 0x1c)
#define FLASH_H7_OPTCCR (FLASH_H7_REGS_ADDR + 0x24)

#endif // STM32FLASH_H
