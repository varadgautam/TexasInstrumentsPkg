/** @file
*  Main file supporting the SEC Phase on ARM Platforms
*
*  Copyright (c) 2011-2012, ARM Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/
#include <Library/DebugLib.h>
#include <Library/PeCoffGetEntryPointLib.h>
#include <Library/ArmTrustedMonitorLib.h>
#include <Library/DebugAgentLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SerialPortLib.h>
#include <Library/ArmGicLib.h>
#include <Ppi/GuidedSectionExtraction.h>
#include <Guid/LzmaDecompress.h>
#include <Library/PrePiLib.h>
#include "SecInternal.h"
#include "LzmaDecompress.h"

#define SerialPrint(txt)  SerialPortWrite ((UINT8*)txt, AsciiStrLen(txt)+1);

EFI_STATUS
EFIAPI
ExtractGuidedSectionLibConstructor (
  VOID
  );

EFI_STATUS
EFIAPI
LzmaDecompressLibConstructor (
  VOID
  );

UINTN mGlobalVariableBase = 0;

VOID
CEntryPoint (
  IN  VOID  *MemoryBase,
  IN  UINTN MemorySize,
  IN  VOID  *StackBase,
  IN  UINTN StackSize
  )
{
  VOID *HobBase;
  CHAR8 Q[4] = "4let";
  SerialPortWrite ((UINT8 *) Q, 4);

  CHAR8 R[5] = "5lets";
  SerialPortWrite ((UINT8 *) R, 4);
  SerialPortWrite ((UINT8 *) R, 5);

  //DEBUG((EFI_D_ERROR, "UART ON\n"));
  *((volatile unsigned int *) 0x44E09000) = 'A';

  DebugPrint(EFI_D_ERROR, "UART");
  *((volatile unsigned int *) 0x44E09000) = 'B';
  // Build a basic HOB list
  HobBase = (VOID *)(UINTN)(FixedPcdGet32(PcdEmbeddedFdBaseAddress) + FixedPcdGet32(PcdEmbeddedFdSize));
  CreateHobList (MemoryBase, MemorySize, HobBase, StackBase);

  // CPU specific settings
  ArmEnableBranchPrediction ();

  // Add memory allocation hob for relocated FD
  BuildMemoryAllocationHob (FixedPcdGet32(PcdEmbeddedFdBaseAddress), FixedPcdGet32(PcdEmbeddedFdSize), EfiBootServicesData);

  // Add the FVs to the hob list
  BuildFvHob (PcdGet32(PcdFlashFvMainBase), PcdGet32(PcdFlashFvMainSize));

  SerialPortInitialize ();

  InitializeDebugAgent (DEBUG_AGENT_INIT_PREMEM_SEC, NULL, NULL);
  SaveAndSetDebugTimerInterrupt (TRUE);

  DEBUG ((EFI_D_ERROR, "UART ready\n"));

  // BuildGuidDataHob
  ExtractGuidedSectionLibConstructor ();

  // Build HOBs manually, since no PrePeiMain execution
  BuildPeCoffLoaderHob ();
  BuildExtractSectionHob (
    &gLzmaCustomDecompressGuid,
    LzmaGuidedSectionGetInfo,
    LzmaGuidedSectionExtraction
    );

  // Assume the FV that contains the SEC (our code) also contains a compressed FV.
  DecompressFirstFv ();

  // Load the DXE Core and transfer control to it
  LoadDxeCoreFromFv (NULL, 0);

  // DXE Core should always load and never return

  ASSERT (0); // never return
}

/*
VOID
TrustedWorldInitialization (
  IN  UINTN                     MpId,
  IN  UINTN                     SecBootMode
  )
{
  //UINTN   JumpAddress;

  //-------------------- Monitor Mode ---------------------

  // Set up Monitor World (Vector Table, etc)
  ArmSecureMonitorWorldInitialize ();

  // Transfer the interrupt to Non-secure World
  ArmGicSetupNonSecure (MpId, PcdGet32(PcdGicDistributorBase), PcdGet32(PcdGicInterruptInterfaceBase));

  // Initialize platform specific security policy
  ArmPlatformSecTrustzoneInit (MpId);

  // Setup the Trustzone Chipsets
  if (SecBootMode == ARM_SEC_COLD_BOOT) {
    if (ArmPlatformIsPrimaryCore (MpId)) {
      if (ArmIsMpCore()) {
        // Signal the secondary core the Security settings is done (event: EVENT_SECURE_INIT)
        ArmCallSEV ();
      }
    } else {
      // The secondary cores need to wait until the Trustzone chipsets configuration is done
      // before switching to Non Secure World

      // Wait for the Primary Core to finish the initialization of the Secure World (event: EVENT_SECURE_INIT)
      ArmCallWFE ();
    }
  }

  // Call the Platform specific function to execute additional actions if required
  //JumpAddress = PcdGet32 (PcdFvBaseAddress);
  //ArmPlatformSecExtraAction (MpId, &JumpAddress);

  // Initialize architecture specific security policy
  ArmSecArchTrustzoneInit ();

  // CP15 Secure Configuration Register
  ArmWriteScr (PcdGet32 (PcdArmScr));

  //NonTrustedWorldTransition (MpId, JumpAddress);
}

VOID
NonTrustedWorldTransition (
  IN  UINTN                     MpId,
  IN  UINTN                     JumpAddress
  )
{
  // If PcdArmNonSecModeTransition is defined then set this specific mode to CPSR before the transition
  // By not set, the mode for Non Secure World is SVC
  if (PcdGet32 (PcdArmNonSecModeTransition) != 0) {
    set_non_secure_mode ((ARM_PROCESSOR_MODE)PcdGet32 (PcdArmNonSecModeTransition));
  }

  return_from_exception (JumpAddress);
  //-------------------- Non Secure Mode ---------------------

  // PEI Core should always load and never return
  ASSERT (FALSE);
}

*/