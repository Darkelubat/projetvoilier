#ifndef GPIO_C
#define GPIO_C
#include "stm32f10x.h" // Clic droit sur stm32f10X.h et faire "open document"  pour ouvrir le fichier

//Configure une broche d'un port en output PP.
/*
Utilisation:
while(Port_IO_Init_Output(GPIOB,8) == 1);
=> Initialisation la clock du GPIOB et met la pin PB.8 en mode output PP.
=> Reste bloqué tant que la fonction retourne une erreur.
*/
char Port_IO_Init_Output(GPIO_TypeDef * Port,u8 Broche);

//Configure une broche d'un port en input floating.
/*
Utilisation:
while(Port_IO_Init_Input(GPIOB,8) == 1);
=> Initialisation la clock du GPIOB et met la pin PB.8 en mode input floating.
=> Reste bloqué tant que la fonction retourne une erreur.
*/
char Port_IO_Init_Input(GPIO_TypeDef * Port,u8 Broche);

//Mettre à 1 une broche d'un port.
/*
Utilisation:
Port_IO_IO_Set(GPIOB,9);
=> Met la pin PB.9 sur l'état '1'.
*/
void Port_IO_IO_Set(GPIO_TypeDef * Port,u8 Broche);

//Mettre à 0 une broche d'un port.
/*
Utilisation:
Port_IO_IO_Reset(GPIOB,9);
=> Met la pin PB.9 sur l'état '0'.
*/
void Port_IO_IO_Reset(GPIO_TypeDef * Port,u8 Broche);

//Inverse l'état d'une broche.
/*
Utilisation:
Port_IO_Blink(GPIOB,9);
=> Met la pin PB.9 sur l'état complémentaire de son état actuel.
*/
void Port_IO_Blink(GPIO_TypeDef * Port,u8 Broche);

//Lire l'état d'une broche d'un port.
/*
Utilisation:
if(Port_IO_Read(GPIOB,9) == 1)
{
	//Action
}
else if(Port_IO_Read(GPIOB,9) == 0)
{
	//Action2
}
else
{
	exit;//Message d'erreur si possible.
}
=> Donne la valeur de la pin "Broche" sur le GPIO "port".
=> La fonction renvoi 2 s'il y a un probléme.
*/
unsigned int Port_IO_Read(GPIO_TypeDef * Port,u8 Broche);

//Passe un port en mode analog input (pour l'ADC)
/*
Utilisation:
Port_IO_Init_AI(GPIOB,8);
=> Initialisation la clock du GPIOB et met la pin PB.8 en mode AI.
*/
void Port_IO_Init_AI(GPIO_TypeDef * Port,u8 Broche);

//Passe un port en mode alternate output push pull (pour la PWM)
/*
Utilisation:
*/
void Port_IO_Init_AltO_PP(GPIO_TypeDef * Port,u8 Broche);

#endif
