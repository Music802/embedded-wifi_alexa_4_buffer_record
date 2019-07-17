/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008 - 2013 Code Red Technologies Ltd, 
 * Copyright 2015, 2018 NXP
 * (c) NXP Semiconductors 2013-2019
 * Generated linker script file for MIMXRT1062xxxxA
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v10.3.1 [Build 2233] [2019-02-20] on Jul 8, 2019 2:21:17 PM
 */

MEMORY
{
  /* Define each memory region */
  BOARD_FLASH (rx) : ORIGIN = 0x60202000, LENGTH = 0x19fe000 /* 26616K bytes (alias Flash) */  
  SRAM_DTC (rwx) : ORIGIN = 0x20000000, LENGTH = 0x80000 /* 512K bytes (alias RAM) */  
  SRAM_ITC (rwx) : ORIGIN = 0x0, LENGTH = 0x0 /* 0M bytes (alias RAM2) */  
  SRAM_OC (rwx) : ORIGIN = 0x20200000, LENGTH = 0x80000 /* 512K bytes (alias RAM3) */  
}

  /* Define a symbol for the top of each memory region */
  __base_BOARD_FLASH = 0x60202000  ; /* BOARD_FLASH */  
  __base_Flash = 0x60202000 ; /* Flash */  
  __top_BOARD_FLASH = 0x60202000 + 0x19fe000 ; /* 26616K bytes */  
  __top_Flash = 0x60202000 + 0x19fe000 ; /* 26616K bytes */  
  __base_SRAM_DTC = 0x20000000  ; /* SRAM_DTC */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM_DTC = 0x20000000 + 0x80000 ; /* 512K bytes */  
  __top_RAM = 0x20000000 + 0x80000 ; /* 512K bytes */  
  __base_SRAM_ITC = 0x0  ; /* SRAM_ITC */  
  __base_RAM2 = 0x0 ; /* RAM2 */  
  __top_SRAM_ITC = 0x0 + 0x0 ; /* 0M bytes */  
  __top_RAM2 = 0x0 + 0x0 ; /* 0M bytes */  
  __base_SRAM_OC = 0x20200000  ; /* SRAM_OC */  
  __base_RAM3 = 0x20200000 ; /* RAM3 */  
  __top_SRAM_OC = 0x20200000 + 0x80000 ; /* 512K bytes */  
  __top_RAM3 = 0x20200000 + 0x80000 ; /* 512K bytes */  
