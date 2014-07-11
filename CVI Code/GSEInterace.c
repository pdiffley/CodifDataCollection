#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "NiFpga.h"
#include "GSEInterace.h"
#include "NiFpga_SimpleDataCollection.h"
#include <stdbool.h>

static int panelHandle;
bool running = true;
NiFpga_Status status;
NiFpga_Session session;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "GSEInterace.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK aquireCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			status = NiFpga_Initialize();
			uint32_t r, timeout = 10000/* 10 seconds */;
			int32_t numSamples;
			int16_t *data = NULL;
				
			
			//while (running)
			//{
				if (NiFpga_IsNotError(status))
				{
				 	NiFpga_MergeStatus(&status, NiFpga_Open(NiFpga_SimpleDataCollection_Bitfile, NiFpga_SimpleDataCollection_Signature,"RIO0", NiFpga_OpenAttribute_NoRun, &session));

			
					//Run the FPGA, then FIFO read *numSamples* of it, which should be set to all of it
				 
				 	NiFpga_MergeStatus(&status, NiFpga_WriteI32(session, control, &numSamples)); 
				 	NiFpga_MergeStatus(&status, NiFpga_Run(session, 0));
				 	//NiFpga_MergeStatus(&status, NiFpga_ReadFifoI16 (session, NiFpga_FPGA_TargetToHostFifoI32_FIFO, data, numSamples, timeout,&r));
					int16_t[2] test = [0,0];
				 
					if(data != NULL)
				 	{
						PlotY(panelHandle, TABPANEL_GRAPH, (unsigned int*) test, numSamples,VAL_UNSIGNED_SHORT_INTEGER, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
					}
    	         	//SetCtrlAttribute(panelHandle, TABPANEL_PANEL_ACQUIRE, ATTR_DIMMED, 1);
  		         	ProcessDrawEvents();
				}
				 /* check if anything went wrong */
             	if (NiFpga_IsError(status))
            	 {
             	    char error[32];
             	    sprintf(error, "Error %d!", status);
                 	MessagePopup("Error", error);
            	 }
			//};
			
			

			 
			 
					 
			break;
	}
	/* enable the acquire button */
    //SetCtrlAttribute(panelHandle, TABPANEL_PANEL_ACQUIRE, ATTR_DIMMED, 0);
    //ProcessDrawEvents();
	
	

	return 0;
}

int CVICALLBACK stopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			running = false;
			
			NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));

            /* must be called after all other calls */
            NiFpga_MergeStatus(&status, NiFpga_Finalize());
			break;
	}
	return 0;
}
