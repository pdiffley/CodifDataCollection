#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "NiFpga.h"
#include "GSEInterace.h"	 //Header File for the User Interface
#include "NiFpga_SimpleDataCollection.h"
#include <stdbool.h>

static int panelHandle;
bool running = false;
NiFpga_Status status;
NiFpga_Session session;

//Voltage Variables
float pacV = 0;
float mcpV = 0;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "GSEInterace.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	
	//LED colors
	SetCtrlAttribute (panelHandle, PANEL_LED,ATTR_OFF_COLOR,VAL_BLACK);
	SetCtrlAttribute (panelHandle, PANEL_LED,ATTR_ON_COLOR,VAL_GREEN);
	
	ResetTimer (panelHandle, PANEL_TIMER);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			if(running)
			{
				NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));

      	  		/* must be called after all other calls */
        		NiFpga_MergeStatus(&status, NiFpga_Finalize());
			}
			QuitUserInterface(0);
			break;
	}
	return 0;
}



int tick (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
		int32_t numSamples;
			
			
		if (NiFpga_IsNotError(status))
		{
			//Run the FPGA, then FIFO read *numSamples* of it, which should be set to all of it
		 
		 	 
			 	
		 	//NiFpga_MergeStatus(&status, NiFpga_ReadFifoI16 (session, NiFpga_FPGA_TargetToHostFifoI32_FIFO, data, numSamples, timeout,&r));
			int test [200];
			for(int i=0;i<200;i++)
			{
				test[i]=i;	
			}
					
			numSamples = 200;
				 
			//if(test != NULL)
		 	//{

				//GetPanelHandleFromTabPage(panelHandle, PANEL,0,&panelHandle);
				DeleteGraphPlot(panelHandle,PANEL_GRAPH,-1,VAL_IMMEDIATE_DRAW); 
				PlotY(panelHandle, PANEL_GRAPH, (unsigned int*) test, numSamples,VAL_UNSIGNED_SHORT_INTEGER, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
				//	RefreshGraph (panelHandle, PANEL_GRAPH);

			//}
    	   	//SetCtrlAttribute(panelHandle, TABPANEL_PANEL_ACQUIRE, ATTR_DIMMED, 1);
  		         	
		}
		 /* check if anything went wrong */
        if (NiFpga_IsError(status))
        {
            char error[32];
            sprintf(error, "Error %d!", status);
           	MessagePopup("Error", error);
        }
		
					 

    ProcessDrawEvents();
	
	

	return 0;
}

int CVICALLBACK stopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(running)
			{
				NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));

      	  		/* must be called after all other calls */
        		NiFpga_MergeStatus(&status, NiFpga_Finalize());
			}
			
			running = false; 
			/* enable the running LED */
    		SetCtrlVal(panelHandle, PANEL_LED, running);
			
			break;
	}
	return 0;
}

int CVICALLBACK pollData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_TIMER_TICK:
			if (running)
			{
				tick (panel, control, event, callbackData, eventData1, eventData2);
			}
			//SetCtrlVal (panelHandle, PANEL_PAC_READER, pacV);
			//SetCtrlVal (panelHandle, PANEL_MCP_READER, mcpV);
			break;
	}
	return 0;
}

int CVICALLBACK aquireCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			uint32_t r, timeout = 10000/* 10 seconds */;
			int16_t *data = NULL;
			
			if(!running)
			{
				status = NiFpga_Initialize();
				//open a session
				NiFpga_MergeStatus(&status, NiFpga_Open(NiFpga_SimpleDataCollection_Bitfile, NiFpga_SimpleDataCollection_Signature,"RIO0", NiFpga_OpenAttribute_NoRun, &session));
			
				//Run it outside the timer loop
				NiFpga_MergeStatus(&status, NiFpga_Run(session, 0));
			}
			
			running = true;
			/* enable the running LED */
    		SetCtrlVal(panelHandle, PANEL_LED, running);

			break;
		case EVENT_TIMER_TICK:

			break;
	}
	return 0;
}

int CVICALLBACK SetVoltage (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_PAC, &pacV);
			GetCtrlVal (panelHandle, PANEL_MCP, &mcpV);
			
			
			
			if(!running)
			{
				status = NiFpga_Initialize();
				uint32_t r, timeout = 10000/* 10 seconds */;
				int16_t *data = NULL;
				//open a session
				NiFpga_MergeStatus(&status, NiFpga_Open(NiFpga_SimpleDataCollection_Bitfile, NiFpga_SimpleDataCollection_Signature,"RIO0", NiFpga_OpenAttribute_NoRun, &session));
			
	
			}
			
			NiFpga_MergeStatus(&status, NiFpga_WriteI16(session, NiFpga_SimpleDataCollection_ControlI16_PAC, pacV));
			NiFpga_MergeStatus(&status, NiFpga_WriteI16(session, NiFpga_SimpleDataCollection_ControlI16_MCP, mcpV));
			
			NiFpga_MergeStatus(&status, NiFpga_ReadI16(session, NiFpga_SimpleDataCollection_ControlI16_PAC, &pacV)); 
			//SetCtrlVal(panelHandle, PANEL_TEST, pacV);
			
			break;
			
		case EVENT_TIMER_TICK:

			break;
	}
	return 0;
}
