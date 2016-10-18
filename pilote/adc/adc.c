#include "stm32f10x.h" // Clic droit sur stm32f10X.h et faire "open document"  pour ouvrir le fichier
#include "adc.h"

//Configure l'ADC en mode regular sur un channel
void Init_Regular(ADC_TypeDef * adc, int nChannel)
{
	//Activation de la clock
	if (adc == ADC1)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_ADC1EN;
	}
	else if (adc == ADC2)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_ADC2EN;
	}
		
	//Mode single conversion
	adc->CR2 &= ~(ADC_CR2_CONT);
	
	//Mise en place de la séquence
	adc->SQR1 &= ~(ADC_SQR1_L);
	adc->SQR3 &= ~(ADC_SQR3_SQ1);
	adc->SQR3 |= nChannel;
	
	//Demarrage de la conversion des channels regular
	adc->CR2 |= ADC_CR2_ADON;
	
	//Calibration de l'ADC
	adc->CR2 |= ADC_CR2_CAL;
	while((adc->CR2 & ADC_CR2_CAL) == ADC_CR2_CAL);
	
	adc->CR2 |= ADC_CR2_ADON;
}

//Renvoie le flag EOC
int Read_EOC(ADC_TypeDef * adc)
{
	int flag;
	
	//On decale de 1 car le flag est en réalité égal à 2 lorsqu'EOC est levé.
	flag = (adc->SR & ADC_SR_EOC)>>1;
	
	return flag;
}

//Lit la donnée de l'ADC
int Read_Data_Reg(ADC_TypeDef * adc)
{
	return adc->DR; //le flag EOC se reset automatiquement
}

//Demarre l'ADC pour une nouvelle mesure unique
void Start_ADC(ADC_TypeDef * adc)
{
	adc->CR2 |= ADC_CR2_ADON; //On lance l'ADC içi.
}