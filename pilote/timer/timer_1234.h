#ifndef TIMER_1234_C
#define TIMER_1234_C
#include "stm32f10x.h"

//Configure et lance en timer en décompteur avec "optimisation" des registres.
/*
Utilisation:
if(Timer_1234_Init(TIM2, 500000) > 505000)
{
	exit;//Message d'erreur au besoin.
}
=> Configuration du timer à 500000 micro secondes.
=> La fonction renvoie la valeur réelle calculée : 
=> Message d'erreur si la precision n'est pas suffisante.
*/
float Timer_1234_Init(TIM_TypeDef * Timer, float Duree_us);

//Configure et lance l'IT timer en definissant sa priorité ainsi que sa fonction.
/*
Utilisation:
Timer_Active_IT(TIM2,2,fonction_IT);
=> Configuration du timer 2 en IT.
=> La priorité et de niveau 2 (le niveau le plus prioritaire étant le 0 et le moins prioritaire étant le 15)
=> On passe la fonction que l'on va lancer dans notre IT en paramétre.
*/
void Timer_Active_IT(TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void));

//Configure un timer en PWM avec choix du channel de sortie
/*
Utilisation:
*/
unsigned int PWM_Init(TIM_TypeDef *Timer, char Channel, float Frequence_PWM_Khz);

//Lance la PWM avec choix du channel de sortie et le rapport cyclique.
/*
Utilisation:
*/
void Lance_PWM(TIM_TypeDef *Timer, char Channel, unsigned int resolution, float rapportCyclique);
#endif
