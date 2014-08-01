/** @file

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __AM335XTIMER_H__
#define __AM335XTIMER_H__

#define DMTIMER0_BASE   (0x44E05000)
/*
#define GPTIMER2_BASE   (0x49032000)
#define GPTIMER3_BASE   (0x49034000)
#define GPTIMER4_BASE   (0x49036000)
#define GPTIMER5_BASE   (0x49038000)
#define GPTIMER6_BASE   (0x4903A000)
#define GPTIMER7_BASE   (0x4903C000)
#define GPTIMER8_BASE   (0x4903E000)
#define GPTIMER9_BASE   (0x49040000)
#define GPTIMER10_BASE  (0x48086000)
#define GPTIMER11_BASE  (0x48088000)
#define GPTIMER12_BASE  (0x48304000)
*/
#define WDTIMER2_BASE   (0x44E35000)

#define DMTIMER_TIOCP_CFG (0x0010)
//#define DMTIMER_TISTAT    (0x0014)
//#define DMTIMER_TISR      (0x0018)
//#define DMTIMER_TIER      (0x001C)
//#define DMTIMER_TWER      (0x0020)
#define DMTIMER_TCLR      (0x0038)
#define DMTIMER_TCRR      (0x003C)
#define DMTIMER_TLDR      (0x0040)
#define DMTIMER_TTGR      (0x0044)
#define DMTIMER_TWPS      (0x0048)
#define DMTIMER_TMAR      (0x004C)
#define DMTIMER_TCAR1     (0x0050)
#define DMTIMER_TSICR     (0x0054)
#define DMTIMER_TCAR2     (0x0058)
/*#define DMTIMER_TPIR      (0x0048)
#define DMTIMER_TNIR      (0x004C)
#define DMTIMER_TCVR      (0x0050)
#define DMTIMER_TOCR      (0x0054)
#define DMTIMER_TOWR      (0x0058)
*/
//#define WSPR              (0x048)

#define TISR_TCAR_IT_FLAG_MASK  BIT2
#define TISR_OVF_IT_FLAG_MASK   BIT1
#define TISR_MAT_IT_FLAG_MASK   BIT0
#define TISR_ALL_INTERRUPT_MASK (TISR_TCAR_IT_FLAG_MASK | TISR_OVF_IT_FLAG_MASK | TISR_MAT_IT_FLAG_MASK)

#define TISR_TCAR_IT_FLAG_NOT_PENDING   (0UL << 2)
#define TISR_OVF_IT_FLAG_NOT_PENDING    (0UL << 1)
#define TISR_MAT_IT_FLAG_NOT_PENDING    (0UL << 0)
#define TISR_NO_INTERRUPTS_PENDING      (TISR_TCAR_IT_FLAG_NOT_PENDING | TISR_OVF_IT_FLAG_NOT_PENDING | TISR_MAT_IT_FLAG_NOT_PENDING)

#define TISR_TCAR_IT_FLAG_CLEAR BIT2
#define TISR_OVF_IT_FLAG_CLEAR  BIT1
#define TISR_MAT_IT_FLAG_CLEAR  BIT0
#define TISR_CLEAR_ALL          (TISR_TCAR_IT_FLAG_CLEAR | TISR_OVF_IT_FLAG_CLEAR | TISR_MAT_IT_FLAG_CLEAR)

#define TCLR_AR_AUTORELOAD      BIT1
#define TCLR_AR_ONESHOT         (0UL << 1)
#define TCLR_ST_ON              BIT0
#define TCLR_ST_OFF             (0UL << 0)

#define TIER_TCAR_IT_ENABLE     (BIT2
#define TIER_TCAR_IT_DISABLE    (0UL << 2)
#define TIER_OVF_IT_ENABLE      BIT1
#define TIER_OVF_IT_DISABLE     (0UL << 1)
#define TIER_MAT_IT_ENABLE      BIT0
#define TIER_MAT_IT_DISABLE     (0UL << 0)

#endif // __AM335XTIMER_H__

