#include "stm32f10x.h" // Clic droit sur stm32f10X.h et faire "open document"  pour ouvrir le fichier
#include "gpio.h" 

//Configure une broche d'un port en output PP.
//Sortie: err, vaut 1 s'il y a une erreur et 0 si la fonction a bien marché.
char Port_IO_Init_Output(GPIO_TypeDef * Port,u8 Broche)
{
	char err = 1;
	
	//Activation de la clock selon le port designé.
	if(Port == GPIOA)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPAEN;
	}
	else if(Port == GPIOB)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPBEN;
	}
	else if(Port == GPIOC)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPCEN;
	}
	
	//Initialisation de la broche sur le bon registre selon son numéro.
	if(Broche	>= 8 && Broche <= 15)
	{
		//Application de la configuration avec adaptation du decalage de bits en fonction du numero de broche
		Port->CRH &= ~(0x0F << (Broche - 8)*4);
		Port->CRH |= (0x01 << (Broche - 8)*4);
		err = 0;
	}
	else if(Broche >= 0)
	{
		Port->CRL &= ~(0x0F << Broche*4);
		Port->CRL |= (0x01 << Broche*4);
		err = 0;
	}
	
	return err;
}

//Configure une broche d'un port en input floating.
//Sortie: err, vaut 1 s'il y a une erreur et 0 si la fonction a bien marché.
char Port_IO_Init_Input(GPIO_TypeDef * Port,u8 Broche)
{
	char err = 1;

	//Activation de la clock selon le port designé.
	if(Port == GPIOA)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPAEN;
	}
	else if(Port == GPIOB)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPBEN;
	}
	else if(Port == GPIOC)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPCEN;
	}
	
	//Initialisation de la broche sur le bon registre selon son numéro.
	if(Broche	>= 8 && Broche <= 15)
	{
		//Application de la configuration avec adaptation du decalage de bits en fonction du numero de broche
		Port->CRH &= ~(0x0F << (Broche - 8)*4);
		Port->CRH |= (0x04 << (Broche - 8)*4);
		err = 0;
	}
	else if(Broche >= 0)
	{
		Port->CRL &= ~(0x0F << Broche*4);
		Port->CRL |= (0x04 << Broche*4);
		err = 0;
	}
	
	return err;
	
}
//Mettre à 1 une broche d'un port.
void Port_IO_IO_Set(GPIO_TypeDef * Port,u8 Broche)
{
	Port->ODR |= (0x01 << Broche);
}
//Mettre à 0 une broche d'un port.
void Port_IO_IO_Reset(GPIO_TypeDef * Port,u8 Broche)
{
	Port->ODR &= ~(0x01 << Broche);
}
//Inverse l'état d'une broche.
void Port_IO_Blink(GPIO_TypeDef * Port,u8 Broche)
{
	if((Port->ODR & (0x01 << Broche)) == 0) 
	{
		Port_IO_IO_Set(Port,Broche); 
	}
	else
	{
		Port_IO_IO_Reset(Port,Broche);
	}
}
//Lire l'état d'une broche d'un port.
//Sortie: etat, vaut 1 ou 0 selon l'état et 2 s'il y a un probléme.
unsigned int Port_IO_Read(GPIO_TypeDef * Port,u8 Broche)
{
	unsigned int etat = 2;
	//Si on retourne 2, il y a un probléme.
	
	if((Port->IDR & (0x01 << Broche)) == 0)
	{
		etat = 0;
	}
	else
	{
		etat = 1;
	}
	
	return etat;
}

//Passe un port en mode analog input (pour l'ADC)
void Port_IO_Init_AI(GPIO_TypeDef * Port,u8 Broche)
{
	//Activation de la clock selon le port designé.
	if(Port == GPIOA)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPAEN;
	}
	else if(Port == GPIOB)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPBEN;
	}
	else if(Port == GPIOC)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPCEN;
	}
	
	//Choix du CSH ou du CSL
	if(Broche	>= 8 && Broche <= 15)
	{
		//Application de la configuration avec adaptation du decalage de bits en fonction du numero de broche
		Port->CRH &= ~(0x0F << (Broche - 8)*4);
		Port->CRH |= (0x00 << (Broche - 8)*4);
	}
	else if(Broche >= 0)
	{
		Port->CRL &= ~(0x0F << Broche*4);
		Port->CRL |= (0x00 << Broche*4);
	}
	
}

//Passe un port en mode alternate output push pull (pour la PWM)
void Port_IO_Init_AltO_PP(GPIO_TypeDef * Port,u8 Broche)
{
	//Activation de la clock selon le port designé.
	if(Port == GPIOA)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPAEN;
	}
	else if(Port == GPIOB)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPBEN;
	}
	else if(Port == GPIOC)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_IOPCEN;
	}
	
	//Choix du CSH ou du CSL
	if(Broche	>= 8 && Broche <= 15)
	{
		//Application de la configuration avec adaptation du decalage de bits en fonction du numero de broche
		Port->CRH &= ~(0x0F << (Broche - 8)*4);
		Port->CRH |= (0x09 << (Broche - 8)*4);
	}
	else if(Broche >= 0)
	{
		Port->CRL &= ~(0x0F << Broche*4);
		Port->CRL |= (0x09 << Broche*4);
	}
}