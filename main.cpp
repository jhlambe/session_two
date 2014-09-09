/*
*  space_one_rework.h
*  AIE Basic Framework For Xcode
*
*  Created by MAXXIE on 9/3/14.
*  Copyright 2014 AIE. All rights reserved.
*
*/

#include "AIE.h"
#include <iostream>

//Screen
const int iScreenWidth = 755; // screen size
const int iScreenHeight = 780; // screen size

//Marquee
int marqueeWidth = 672; //location on screen
int marqueeHeight = 780; //location on screen
unsigned int iArcadeMarquee = 0;  

//font
const char* pInVadersFont = "./fonts/invaders.fnt";

char pkScore1[10] = "00000";
char pkHighScore[10] = "00000";
char pkScore2[10] = "00000";
char pkCredit[10] = "0";
char pkInsertCoins[10] = "99";


//player
const int iPlayerCannonWidth = 64; //plaper icon size
const int iPlayerCannonHeight = 32; // player icon size
unsigned int iPlayerCannon;
float fPlayerX = iScreenWidth * 0.5f;
float fPlayerY = 80.f;

///////////////////////////////////////////////////////////

enum GAMESTATES
{
	eMAIN_MENU,
	eGAMEPLAY,
	eEND,
};


GAMESTATES eCurrentState = GAMESTATES::eMAIN_MENU; //current switch state

//////////////////////////////////////////////////////////

int main(int argc, char* argv[]) // main
{
	Initialise(iScreenWidth, iScreenHeight, false, "Space Invaders"); // open screen???
	
	iPlayerCannon = CreateSprite("./images/cannon.png", iPlayerCannonWidth, iPlayerCannonHeight, true);
	iArcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", iScreenWidth, iScreenHeight, true);
	MoveSprite(iArcadeMarquee, iScreenWidth *0.5f, iScreenHeight * 0.5f);


	do
	{

		ClearScreen(); // clear screen
		
		switch (eCurrentState) //switch
		{

		case GAMESTATES::eMAIN_MENU:
		
			DrawSprite(iArcadeMarquee);
			SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF)); // set background to blk
			AddFont(pInVadersFont); //these calls not found in Xcode AIEFramework tried to add from Other file but didn't work
			SetFont(pInVadersFont); //lost a few hours on these.. thx guys
			//DrawString(pkInsertCoins, iScreenWidth * 0.5f, iScreenHeight * 0.75f); //add int for pkInsertcoin
			DrawString( pkCredit, iScreenWidth * 0.6f, iScreenHeight *0.45f);
			DrawString("CREDITS", iScreenWidth * 0.4, iScreenHeight *0.45f);
			DrawString("Press Enter to Play", iScreenWidth * 0.35, iScreenHeight *0.5f);


			//if key is down goto eGAMEPLAY
			if (IsKeyDown(GLFW_KEY_ENTER))
			{
				eCurrentState = eGAMEPLAY;
			}
			break;


			//GAME LOOP


		case GAMESTATES::eGAMEPLAY:

			//Screen setup
		
			SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF)); // set background to blk
		

			//txt score etc.
			AddFont(pInVadersFont); //these calls not found in Xcode AIEFramework tried to add from Other file but didn't work
			SetFont(pInVadersFont); //lost a few hours on these.. thx guys
			DrawString("SCORE1 <1>", iScreenWidth * 0.020f, iScreenHeight - 2);
			DrawString("HIGH SCORE <1>", iScreenWidth * 0.35f, iScreenHeight - 2);
			DrawString("SCORE2 <1>", iScreenWidth * 0.73f, iScreenHeight - 2);
			DrawString("CREDITS <1>", iScreenWidth * 0.72f, iScreenHeight - 750);
			
			DrawLine(0, 40, iScreenWidth, 40, SColour(0x00, 0xFC, 0x00, 0xFF));

			DrawSprite(iPlayerCannon);
			 MoveSprite(iPlayerCannon, iScreenWidth * 0.5f, 40); //place icon
			

			//fPlayerX = iScreenWidth * 0.5f;
			//fPlayerY = 80.f;
			MoveSprite(iPlayerCannon, fPlayerX, fPlayerY);
		

			if (IsKeyDown('A')) // if you press a move left
			{
				fPlayerX -= 2.f; //move player by 2

				if (fPlayerX < iPlayerCannonWidth / 2) //screen starts at 0,0 so just need the player sprite /2 their code was 32.f sprite is 64
				{
					fPlayerX = iPlayerCannonWidth / 2;
				}
			}

			if (IsKeyDown('D')) // if you press d move right
			{

				fPlayerX += 2.f;

				if (fPlayerX > iScreenWidth - iPlayerCannonWidth / 2) //width of screen - player / 2
				{
					fPlayerX = iScreenWidth - iPlayerCannonWidth / 2; //width of screen - player width /2
				}
			}

			break;


			// end game go back to main menu

		case GAMESTATES::eEND:


			eCurrentState = eMAIN_MENU;

			break;


		default:
			std::cout << "Default Case";
			break;
			
			}

		///////////////////////////////////////////////////

		} while

			(FrameworkUpdate() == false);

		DestroySprite(iPlayerCannon);
		DestroySprite(iArcadeMarquee);
		Shutdown();

		return 0;


	}