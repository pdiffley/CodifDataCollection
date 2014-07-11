/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2014. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_PANEL_ACQUIRE              2       /* control type: command, callback function: aquireCallback */
#define  PANEL_STOP                       3       /* control type: command, callback function: stopCallback */
#define  PANEL_SETVOLTAGE                 4       /* control type: command, callback function: SetVoltage */
#define  PANEL_COMMANDBUTTON_4            5       /* control type: command, callback function: (none) */
#define  PANEL_PAC_READER                 6       /* control type: scale, callback function: (none) */
#define  PANEL_MCP_READER                 7       /* control type: scale, callback function: (none) */
#define  PANEL_GRAPH                      8       /* control type: graph, callback function: (none) */
#define  PANEL_TIMER                      9       /* control type: timer, callback function: pollData */
#define  PANEL_MCP                        10      /* control type: numeric, callback function: (none) */
#define  PANEL_PAC                        11      /* control type: numeric, callback function: (none) */
#define  PANEL_LED                        12      /* control type: LED, callback function: (none) */
#define  PANEL_TEST                       13      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK aquireCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pollData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetVoltage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
