/*
 * ct_app.h
 *
 * Logic of the tester. The device works on its own: it keeps the cables in its
 * flash, tests them by the button of the display and shows the errors there.
 * USB is needed only to upload the cables from the PC.
 *
 * The display keeps the interface of the existing HMI project (page0):
 *   cableName  ComboBox   the list of the stored cables, the MCU fills .path,
 *                         .val is the choice of the user
 *   cablePic   ExPicture  the picture of the cable, the MCU sets .path
 *                         ("sd0/c<slot>.jpg" instead of the built in .pic)
 *   errorList  ComboBox   the list of the errors, the MCU fills .path and .txt
 *                         and sets .bco (green when the cable is good)
 *   errPic1    Picture    the lightning at the first pin of the error
 *   errPic2    Picture    the lightning at the second pin
 *   errFlash   Timer      blinks the lightnings by their .aph, the MCU only
 *                         switches .en
 *
 * What the display must send (printh, see ct_nextion.h):
 *   #T             the test button
 *   #E <val>       errorList.val, the error is selected
 *   #C <val>       cableName.val, the cable is selected
 *   #R             page0 postinitialize, the MCU sends the state again
 */

#ifndef CT_APP_H_
#define CT_APP_H_

#include "ct_test.h"

/* Offset of the picture on the page and the size of the lightning icon */
#define CT_APP_IMAGE_X      0
#define CT_APP_IMAGE_Y      0
#define CT_APP_ICON_CX      26
#define CT_APP_ICON_CY      26

/* Colors of errorList: 565 format, as the HMI project uses */
#define CT_APP_COLOR_GOOD   1024    /* green */
#define CT_APP_COLOR_ERROR  63488   /* red */

#define CT_APP_DISPLAY_BAUD 250000  /* as baud= in Program.s of the HMI project */

#define CT_APP_NO_SLOT      0xFF
#define CT_APP_MAX_LIST     12      /* errors in the list of the display */
#define CT_APP_LINE_SIZE    96      /* one line of the error list */
#define CT_APP_LIST_LABEL   14      /* pin label in the list is cut to this */
#define CT_APP_NAME_LABEL   20      /* cable name in the list is cut to this */

/* Before MX_USB_DEVICE_Init(), while USB is disconnected: the flash work stalls
   the CPU and would break the enumeration */
void CtApp_EarlyInit(void);

/* After the peripherals are initialized */
void CtApp_Init(void);

/* Call it in the main loop */
void CtApp_Poll(void);

/* Shows the cable of the slot, returns 0 when the slot is empty */
int CtApp_SelectSlot(uint8_t slot);

/* Erases the cable, the next ones move one slot down with their pictures,
   so the slots 0..N-1 stay without gaps */
void CtApp_EraseSlot(uint8_t slot);

uint8_t CtApp_GetSlot(void);

/* The package of the selected cable or NULL */
const CtPkgHeader* CtApp_GetPackage(void);

const CtTestResult* CtApp_GetResult(void);

/* Tests the selected cable and shows the result */
uint8_t CtApp_RunTest(void);

/* Shows the error by its index, 0xFF hides the lightnings */
void CtApp_ShowError(uint8_t index);

/* Sends the whole state to the display */
void CtApp_Refresh(void);

/* Refills the list of the cables, call it after a change in the storage */
void CtApp_RefreshCableList(void);

#endif /* CT_APP_H_ */
