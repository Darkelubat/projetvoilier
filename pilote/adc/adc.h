#ifndef ADC_C
#define ADC_C
#include "stm32f10x.h" // Clic droit sur stm32f10X.h et faire "open document"  pour ouvrir le fichier

//Configure l'ADC en mode regular sur un channel
/*
Utilisation:
Init_Regular(ADC1, 1);
=> Initialise le channel 1 de l'ADC1.
*/
void Init_Regular(ADC_TypeDef * adc, int nChannel);

//Renvoie le flag EOC
/*
Utilisation:
while(Read_EOC(ADC1) == 0);
=> On reste bloqué tant que le flag n'est pas levé.
*/
int Read_EOC(ADC_TypeDef * adc);

//Lit la donnée de l'ADC
/*
Utilisation:
data = Read_Data_Reg(ADC1);
=> On stocke la donnée lu dans la variable "data".
=> Cette lecture remet automatiquement le EOC à 0.
*/
int Read_Data_Reg(ADC_TypeDef * adc);

//Demarre l'ADC pour une nouvelle mesure unique
/*
Utilisation:
Start_ADC(ADC1);
=> Lancement de l'ADC1 qui a été configuré au préalable.
*/
void Start_ADC(ADC_TypeDef * adc);

#endif
