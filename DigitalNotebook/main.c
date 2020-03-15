/*----------------------------------------------------------------------------
 *			Digital Notebook by Ripak Co.LTD
 *			info@Ripak.ir	& RipakOfficial@gmail.com & RipakOfficial@yahoo.com
 *			Date:		2014/02/05
 *			Author: Mojtaba Rostami 
 *--------------------------------------------------------------------------*/
#include	"TFTLCD\GLCD.h"
#include	"TouchPanel\TouchPanel.h"
#include	"HT24LC\HT24LC.h"
#include	"DELAY\delay.h"
#include	<stdio.h>

Coordinate  point,point2;
char	str[];
Matrix matrix2;
uint8_t Save0=0,Save1=1,SaveOk;

int main(void)
{
	
	I2C0_Init ();
	
	HT24LC_PageRd(I2CDEV,HT24LC_SLVADDR,0,&matrix2.An);
	HT24LC_PageRd(I2CDEV,HT24LC_SLVADDR,1,&matrix2.Bn);
	HT24LC_PageRd(I2CDEV,HT24LC_SLVADDR,2,&matrix2.Cn);
	HT24LC_PageRd(I2CDEV,HT24LC_SLVADDR,3,&matrix2.Dn);
	HT24LC_PageRd(I2CDEV,HT24LC_SLVADDR,4,&matrix2.En);
	HT24LC_PageRd(I2CDEV,HT24LC_SLVADDR,5,&matrix2.Fn);
	HT24LC_PageRd(I2CDEV,HT24LC_SLVADDR,6,&matrix2.Divider);
	HT24LC_ByteRd(I2CDEV,HT24LC_SLVADDR,100,&SaveOk);
	
	delay_init();
	
	GLCD_Init();
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Yellow);
	
	//Touch Initialization:
	TP_Init();
	
	if(SaveOk==0)
	{
		point=*Read_Ads7846();
	
		GLCD_PutPixel(120,50);
		do{
			ScreenSample[0]=*Read_Ads7846();
		}while(ScreenSample[0].x==point.x && ScreenSample[0].y==point.y);
		delay(2000);

		GLCD_PutPixel(30, 200);
		do{
			ScreenSample[1]=*Read_Ads7846();
		}while(ScreenSample[1].x==point.x && ScreenSample[1].y==point.y);
		delay(2000);
	
		GLCD_PutPixel(290,190);
		do{
			ScreenSample[2]=*Read_Ads7846();
		}while(ScreenSample[2].x==point.x && ScreenSample[2].y==point.y);
		delay(2000);

		setCalibrationMatrix( &DisplaySample[0],&ScreenSample[0],&matrix);
		
		matrix2.An=matrix.An;
		matrix2.Bn=matrix.Bn;
		matrix2.Cn=matrix.Cn;
		matrix2.Dn=matrix.Dn;
		matrix2.En=matrix.En;
		matrix2.Fn=matrix.Fn;
		matrix2.Divider=matrix.Divider;
	}

	delay(1000);
	GLCD_Clear(Black);
	GLCD_DisplayString  (0, 2, 1, "Press a location!");
	GLCD_PutPixel(290,190);
	do{
		point2=*Read_Ads7846();
	}while(point2.x==point.x && point2.y==point.y);
	getDisplayPoint(&display,&point2,&matrix2);
	
	sprintf(str,"Cab point.x is:%3d",display.x);
	GLCD_DisplayString  (1, 2, 1, str);
	sprintf(str,"Cab point.y is:%3d",display.y);
	GLCD_DisplayString  (2, 2, 1, str);
	delay(2000);

	GLCD_Clear(Black);
	point=*Read_Ads7846();
	for(;;)
	{
		do{
			point2=*Read_Ads7846();
		}while(point2.x==point.x && point2.y==point.y);
		getDisplayPoint(&display,&point2,&matrix2);

		if(point2.x<320)
			{		
				if(point2.y>460 && point2.y<834)
					{
						GLCD_Clear(Black);
					}
				else if (point2.y>1170 && point2.y<1500)
					{
						GLCD_Clear(Blue);
					}
				if (point2.y>1800 && point2.y<2160)
					{
						GLCD_Clear(Green);								
						HT24LC_PageWr(I2CDEV,HT24LC_SLVADDR,0,&matrix2.An);
						HT24LC_PageWr(I2CDEV,HT24LC_SLVADDR,1,&matrix2.Bn);
						HT24LC_PageWr(I2CDEV,HT24LC_SLVADDR,2,&matrix2.Cn);
						HT24LC_PageWr(I2CDEV,HT24LC_SLVADDR,3,&matrix2.Dn);
						HT24LC_PageWr(I2CDEV,HT24LC_SLVADDR,4,&matrix2.En);
						HT24LC_PageWr(I2CDEV,HT24LC_SLVADDR,5,&matrix2.Fn);
						HT24LC_PageWr(I2CDEV,HT24LC_SLVADDR,6,&matrix2.Divider);
						HT24LC_ByteWr(I2CDEV,HT24LC_SLVADDR,100,&Save1);	
					}
				else if (point2.y>2445 && point2.y<2810)
					{
					}
				else if (point2.y>3155 && point2.y<3565)
					{
						GLCD_Clear(Red);
						HT24LC_ByteWr(I2CDEV,HT24LC_SLVADDR,100,&Save0);
					}
			}	
			else 
				{	
					GLCD_PutPixel(display.x,display.y);
				}

	}
					
}