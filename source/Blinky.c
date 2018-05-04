/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 * Note(s): __USE_LCD   - enable Output on LCD, uncomment #define in code to use
 *  				for demo (NOT for analysis purposes)
 *----------------------------------------------------------------------------
 * Copyright (c) 2008-2011 Keil - An ARM Company.
 * Name: Jad Viv
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.H"                       
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"
#include "usbdmain.h"
#include "type.h"

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */

/* Define picture variables */
extern unsigned char BlueBird[];
extern unsigned char RedBird[];
extern unsigned char FlappyBird[];
extern unsigned char TubesLarge[];
extern unsigned char TubesMed[];
extern unsigned char TubesSmall[];
extern unsigned char upTubesLarge[];
extern unsigned char upTubesMed[];
extern unsigned char upTubesSmall[];

/* Initialize x and y position value of pictures */
int birdPos_x = 5;
int birdPos_y = 120;
int TubesLarge_x = 320;
int TubesLarge_y = 0;
int TubesMed_x = 400;
int TubesMed_y = 0;
int TubesSmall_x = 480;
int TubesSmall_y = 0;
int upTubesLarge_x = 480;
int upTubesLarge_y = 140;
int upTubesMed_x = 440;
int upTubesMed_y = 165;
int upTubesSmall_x = 360;
int upTubesSmall_y = 190;
int startDelay = 0;
char score[10];
int scoreNum = 0;


//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}

void gameover(){
	int buttonover;
			#ifdef __USE_LCD
				GLCD_Clear(Yellow);                         /* Clear graphical LCD display   */
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(0, 0, __FI, "    ");
				GLCD_DisplayString(1, 0, __FI, " 		");
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(2, 0, __FI, "  Score:  ");
				sprintf(score, "%d", scoreNum);
				GLCD_DisplayString(2,12, __FI,  (unsigned char*)score);
				GLCD_DisplayString(3, 0, __FI, "  Game Over          ");
				GLCD_DisplayString(4, 0, __FI, "  Press LEFT         ");
				GLCD_DisplayString(5, 0, __FI, "  To Return to Menu  ");
			#endif
	while(1){
		buttonover = get_button();
		if (buttonover == KBD_LEFT){
			return;
			}
		}
}


/* Reset function to reset all variables to initial values */
void reset(){
	scoreNum = 0;
	birdPos_x = 5;
	birdPos_y = 120;
	TubesLarge_x = 320;
	TubesLarge_y = 0;
	TubesMed_x = 400;
	TubesMed_y = 0;
	TubesSmall_x = 480;
	TubesSmall_y = 0;
	upTubesLarge_x = 480;
	upTubesLarge_y = 140;
	upTubesMed_x = 440;
	upTubesMed_y = 165;
	upTubesSmall_x = 360;
	upTubesSmall_y = 190;
}


/* Game function to initialize and play Flappy Bird game */
void game(){
			int gamebutton;
			#ifdef __USE_LCD
				GLCD_Clear(Cyan);                         /* Clear graphical LCD display   */
				GLCD_SetBackColor(Cyan);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(0, 0, __FI, "  Game Selected    ");
				GLCD_DisplayString(1, 0, __FI, " Goal: Stay Alive		");
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(2, 0, __FI, "  Select - Play Game     ");
				GLCD_DisplayString(3, 0, __FI, "  Controls:  ");
				GLCD_DisplayString(4, 0, __FI, "  Up - Bird Flaps  ");
				GLCD_DisplayString(5, 0, __FI, "  Left - Quit to Main Menu  ");
			#endif
			
	
			while(1){ //game inside while loop
						
						gamebutton = get_button();
						if (gamebutton == KBD_SELECT){ //check if Select option picked
						for (startDelay = 0; startDelay < 1; startDelay++){ //for loop to clear screen once
							GLCD_Clear(Cyan); 
						}
							gamebutton = get_button();
						
							
							while(gamebutton != KBD_LEFT){ //entire game held inside while loop waiting for left to be pressed to exit game
									
									/* Reset x and y values of tubes once reached end of screen */
									if (TubesLarge_x < -30){
										TubesLarge_x = 320;
									}
									
									if (TubesMed_x < -30){
										TubesMed_x = 400;
									}
									
									if (TubesSmall_x < -30){
										TubesSmall_x = 480;
									}			

									if (upTubesLarge_x < -30){
										upTubesLarge_x = 480;
									}

									if (upTubesMed_x < -30){
										upTubesMed_x = 440;
									}

									if (upTubesSmall_x < -30){
										upTubesSmall_x = 360;
									}

						
									/* Placing pictures on LCD panel */
									GLCD_Bitmap (birdPos_x, birdPos_y, 30, 30, FlappyBird);
								
									GLCD_Bitmap (TubesLarge_x, TubesLarge_y, 30, 100, TubesLarge);
									GLCD_Bitmap (TubesMed_x, TubesMed_y, 30, 75, TubesMed);
									GLCD_Bitmap (TubesSmall_x, TubesSmall_y, 30, 50, TubesSmall);
								
									GLCD_Bitmap (upTubesLarge_x, upTubesLarge_y, 30, 100, upTubesLarge);
									GLCD_Bitmap (upTubesMed_x, upTubesMed_y, 30, 75, upTubesMed);
									GLCD_Bitmap (upTubesSmall_x, upTubesSmall_y, 30, 50, upTubesSmall);
	
									
									/* Incrementing/Decrementing values of tubes and bird */
									gamebutton = get_button();
									birdPos_y = birdPos_y + 1;
								
									TubesLarge_x = TubesLarge_x - 1;
									TubesMed_x = TubesMed_x - 1;
									TubesSmall_x = TubesSmall_x - 1;
								
									upTubesLarge_x = upTubesLarge_x - 1;
									upTubesMed_x = upTubesMed_x - 1;
									upTubesSmall_x = upTubesSmall_x - 1;

									if (gamebutton == KBD_SELECT){ //select moves bird up 2 pixels
										birdPos_y = birdPos_y - 2;
									}

									/* Tube and Bird collision detection */
									if (TubesLarge_x <= 35 && TubesLarge_x >= 30 && birdPos_y >= 0 && birdPos_y <= 70){
										gameover(); //gameover function thrown
										reset();	//reset function thrown
										return;
									}

									else if (TubesMed_x <= 35 && TubesMed_x >= 30 && birdPos_y <= 45){
										gameover();
										reset();
										return;
									}									
									
									else if (TubesSmall_x <= 35 && TubesSmall_x >= 30 && birdPos_y <= 20){
										gameover();
										reset();
										return;
									}		
									
									else if (upTubesLarge_x <= 35 && upTubesLarge_x >= 30 && birdPos_y >= 140){
										gameover();
										reset();
										return;
									}									

									else if (upTubesMed_x <= 35 && upTubesMed_x >= 30 && birdPos_y >= 165){
										gameover();
										reset();
										return;
									}									
									
									else if (upTubesSmall_x <= 35 && upTubesSmall_x >= 30 && birdPos_y >= 190){
										gameover();
										reset();
										return;
									}									
									
									/* Tube and Bird collision for top and bottom of bird */
									else if (TubesLarge_x < 35 && TubesLarge_x > 5 && birdPos_y <= 70){
										gameover();
										reset();
										return;
									}

									else if (TubesMed_x < 35 && TubesMed_x > 5 && birdPos_y <= 45){
										gameover();
										reset();
										return;
									}									
									
									else if (TubesSmall_x < 35 && TubesSmall_x > 5 && birdPos_y <= 20){
										gameover();
										reset();
										return;
									}		
									
									else if (upTubesLarge_x < 35 && upTubesLarge_x > 5 && birdPos_y >= 140){
										gameover();
										reset();
										return;
									}									

									else if (upTubesMed_x < 35 && upTubesMed_x > 5 && birdPos_y >= 165){
										gameover();
										reset();
										return;
									}									
									
									else if (upTubesSmall_x < 35 && upTubesSmall_x > 5 && birdPos_y >= 190){
										gameover();
										reset();
										return;
									}			

									else{ //incrementing score
										scoreNum++;
									}
									
									/* Bird collison detection on top and bottom of screen */
									if (birdPos_y > 210 || birdPos_y < 0){
										gameover();
										reset();
										return;
									}

							}
							GLCD_Clear(Yellow);
							return;						
						}
						
						
						if (gamebutton == KBD_LEFT){ //able to exit game at any time
						GLCD_Clear(Yellow);
							return;
						}
		}
}


/* Photo gallery function */
void photo_gallery(){
	int button;
	int time_length = 0;
	#ifdef __USE_LCD
				GLCD_Clear(Yellow);                         /* Clear graphical LCD display   */
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(0, 0, __FI, "  Gallery Selected    ");
				GLCD_DisplayString(1, 0, __FI, " 4 Options Available		");
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(3, 0, __FI, "  Up - Red Bird      ");
				GLCD_DisplayString(4, 0, __FI, "  Right - Blue Bird  ");
				GLCD_DisplayString(5, 0, __FI, "  Down - Black Bird  ");
				GLCD_DisplayString(6, 0, __FI, "  Left- Return Menu  ");
			#endif
						
						/* Selection of bird in photo gallery */
						while(1){
							button = get_button();
									if (button == KBD_RIGHT){
										GLCD_Clear  (White);
										GLCD_Bitmap (0, 0, 320, 240, BlueBird);
									}
									if (button == KBD_UP){
										GLCD_Clear  (White);
										GLCD_Bitmap (0, 0, 320,  240, RedBird);
									}
									if (button == KBD_DOWN){
										GLCD_Clear  (White);
										GLCD_Bitmap (0, 0, 320,  240, BlueBird);
									}
									if (button == KBD_LEFT){ 
										GLCD_Clear(Yellow);
										return;
							}
						}
					}		

					
/* Menu function of program */
 void menu (){
	int button;
	int selection = 1;

	/* Selection menu incrementing/decrementing */
	while(1){
		button = get_button();
		if(button == KBD_DOWN){
			if(selection == 3){
				selection = 0;
			}
			else {
				selection++;
			}
		}
		else if(button == KBD_UP){
			if(selection == 1){
				selection = 3;
			}
			else {
				selection--;
			}
		}

			if (selection == 1){
			#ifdef __USE_LCD
				//GLCD_Clear(White);                         /* Clear graphical LCD display   */
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(0, 0, __FI, "    COE718 Major  ");
				GLCD_DisplayString(1, 0, __FI, "     Jad Viv  ");
				GLCD_DisplayString(2, 0, __FI, " ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(Yellow);
				GLCD_DisplayString(4, 0, __FI, "1) Gallery");
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(5, 0, __FI, "2) MP3 Player      ");
				GLCD_DisplayString(6, 0, __FI, "3) Game");
			#endif
				if(button == KBD_SELECT){
					photo_gallery();
			}
		}
			else if (selection == 2){	
			#ifdef __USE_LCD
				//GLCD_Clear(White);                         /* Clear graphical LCD display   */
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(0, 0, __FI, "    COE718 Major  ");
				GLCD_DisplayString(1, 0, __FI, "     Jad Viv  ");
				GLCD_DisplayString(2, 0, __FI, " ");
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(4, 0, __FI, "1) Gallery");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(Yellow);
				GLCD_DisplayString(5, 0, __FI, "2) MP3 Player      ");
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(6, 0, __FI, "3) Game");
			#endif
				if(button == KBD_SELECT){	
						GLCD_Clear(Yellow);
						GLCD_DisplayString(5, 1, __FI, "MP3 Player Selected");
						music_player();
					}
		}
			else if (selection == 3){
			#ifdef __USE_LCD
				//GLCD_Clear(White);                         /* Clear graphical LCD display   */
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Red);
				GLCD_DisplayString(0, 0, __FI, "    COE718 Major  ");
				GLCD_DisplayString(1, 0, __FI, "     Jad Viv  ");
				GLCD_DisplayString(2, 0, __FI, " ");
				GLCD_SetBackColor(Yellow);
				GLCD_SetTextColor(Blue);
				GLCD_DisplayString(4, 0, __FI, "1) Gallery");
				GLCD_DisplayString(5, 0, __FI, "2) MP3 Player      ");
				GLCD_SetBackColor(Blue);
				GLCD_SetTextColor(Yellow);
				GLCD_DisplayString(6, 0, __FI, "3) Game");
			#endif 
					if(button == KBD_SELECT){
						game();
					}
				}
			}
		}
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void){
  LED_Init();                                /* LED Initialization            */
  GLCD_Init();                               /* Initialize graphical LCD (if enabled */
	KBD_Init();
	
	#ifdef __USE_LCD
				GLCD_Clear(Yellow);                         /* Clear graphical LCD display   */
	#endif
		menu();
	}