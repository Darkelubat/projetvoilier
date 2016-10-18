#include "stm32f10x.h"
#include "timer_1234.h"
#include "clock.h"

//On crée un pointeur par fonction, on ne sait pas combien d'IT on va lancer.
void (*ptrfctTIM2_IT) (void);
void (*ptrfctTIM3_IT) (void);
void (*ptrfctTIM4_IT) (void);

//Handler du timer 2
void TIM2_IRQHandler(void)
{
	//Flag a 0
	TIM2->SR &= ~(0x01);
	//Lancement de la fonction
	ptrfctTIM2_IT();
}

//Initialisation de l'it du timer 2,3 ou 4.
void Timer_Active_IT(TIM_TypeDef *Timer, u8 Priority, void (*IT_function) (void))
{	
	if(Timer == TIM2)
	{
		ptrfctTIM2_IT = IT_function;	
		//Autorisation des interruptions pour le flag UI
		Timer->DIER = 0x01;
		
		//Définition des priorités
		NVIC->IP[28] = Priority << 4;
		
		//Activation au niveau du NVIC
		NVIC->ISER[0] = 0x1 << 28;
	}
	
	if(Timer == TIM3)
	{
		ptrfctTIM3_IT = IT_function;	
		//Autorisation des interruptions pour le flag UI
		Timer->DIER = 0x01;
		
		//Définition des priorités
		NVIC->IP[29] = Priority << 4;
		
		//Activation au niveau du NVIC
		NVIC->ISER[0] = 0x1 << 29;
	}
	
	if(Timer == TIM4)
	{
		ptrfctTIM4_IT = IT_function;	
		//Autorisation des interruptions pour le flag UI
		Timer->DIER = 0x01;
		
		//Définition des priorités
		NVIC->IP[30] = Priority << 4;
		
		//Activation au niveau du NVIC
		NVIC->ISER[0] = 0x1 << 30;
	}
}

//Initialisation timer
float Timer_1234_Init(TIM_TypeDef * Timer, float Duree_us)
{
	float RapportTemp;
	float FrequenceCompteur;
	float TempsReel;
	float freq;

	//Activation de la clock liee au timer selectionne
	if (Timer == TIM1)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN;
	}
	if (Timer == TIM2)
	{
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN;
	}
	if (Timer == TIM3)
	{
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM3EN;
	}
	if (Timer == TIM4)
	{
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM4EN;
	}
	
	//On prend la fréquence du timer X et on le met en MHz.
	freq = CLOCK_GetTIMCLK(Timer)/1000000;
	
	//Calcul du rapport temporel
	RapportTemp = Duree_us/(1./freq);
	
	//Si celui-ci depasse la valeur maximal du compteur on utilise le prescaler
	//La variable FrequenceCompteur correspond à celle que l'on souhaite obtenir à la fin :
	//c'est à dire la fréquence des underflows
	if(RapportTemp > 0xFFFF)
	{
		Timer->ARR = 0xFFFF;
		
		FrequenceCompteur = ((float) 0xFFFF)/Duree_us;
						
		Timer->PSC = (freq - FrequenceCompteur)/FrequenceCompteur;
	}
	else
	{
		Timer->ARR = RapportTemp - 1;
		
		Timer->PSC = 0x00;
	}
	
	TempsReel = Timer->ARR * Timer-> PSC * (1./freq);
	
	//On active le compteur (en decompteur) et on active les Update sur overflow.
	Timer->CR1 |= 0x0015;
	
	return TempsReel;
}

//Configure un timer en PWM avec choix du channel de sortie
unsigned int PWM_Init(TIM_TypeDef * Timer, char Channel, float Frequence_PWM_Khz)
{
	float RapportTemp;
	float FrequenceCompteur;
	unsigned int Resolution;
	float freq;
	float Duree_us;

	//Activation de la clock liee au timer selectionne
	if (Timer == TIM1)
	{
		(RCC->APB2ENR)|= RCC_APB2ENR_TIM1EN;
		Timer->BDTR |= TIM_BDTR_MOE;
	}
	if (Timer == TIM2)
	{
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM2EN;
	}
	if (Timer == TIM3)
	{
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM3EN;
	}
	if (Timer == TIM4)
	{
		(RCC->APB1ENR)|= RCC_APB1ENR_TIM4EN;
	}
	
	//On prend la fréquence du timer X et on le met en MHz.
	freq = CLOCK_GetTIMCLK(Timer)/1000000;
	
	//Calcul du rapport temporel
	Duree_us  = (1./Frequence_PWM_Khz) * 1000;
	RapportTemp = Duree_us/(1./freq);
	
	//Si celui-ci depasse la valeur maximal du compteur on utilise le prescaler
	//La variable FrequenceCompteur correspond à celle que l'on souhaite obtenir à la fin :
	//c'est à dire la fréquence des underflows
	if(RapportTemp > 0xFFFF)
	{
		Timer->ARR = 0xFFFF;
		
		FrequenceCompteur = ((float) 0xFFFF)/Duree_us;
						
		Timer->PSC = (freq - FrequenceCompteur)/FrequenceCompteur;
	}
	else
	{
		Timer->ARR = RapportTemp - 1;
		
		Timer->PSC = 0x00;
	}
		
	Resolution = Timer->ARR;
	
	//selection du channel
	switch(Channel)
	{
		case 1:
					//Configuration en mode 1 PWM
					Timer->CCMR1 &= ~(TIM_CCMR1_OC1M);
					Timer->CCMR1 |= (TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1);
					//Configure en polarité inverse car on decompte.
					Timer->CCER &= ~(TIM_CCER_CC1P);
					break;
		case 2:
					//Configuration en mode 1 PWM
					Timer->CCMR1 &= ~(TIM_CCMR1_OC2M);
					Timer->CCMR1 |= (TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1);
					//Configure en polarité inverse car on decompte.
					Timer->CCER &= ~(TIM_CCER_CC2P);
					break;
		case 3:
					//Configuration en mode 1 PWM
					Timer->CCMR2 &= ~(TIM_CCMR2_OC3M);
					Timer->CCMR2 |= (TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1);
					//Configure en polarité inverse car on decompte.
					Timer->CCER &= ~(TIM_CCER_CC3P);
					break;
		case 4:
					//Configuration en mode 1 PWM
					Timer->CCMR2 &= ~(TIM_CCMR2_OC4M);
					Timer->CCMR2 |= (TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1);
					//Configure en polarité inverse car on decompte.
					Timer->CCER &= ~(TIM_CCER_CC4P);
					break;
		default: 
					break;
	}
	
	//On active le compteur (en decompteur) et on active les Update sur overflow.
	Timer->CR1 |= 0x0015;
	
	return Resolution;
}

//Lance la PWM avec choix du channel de sortie et le rapport cyclique.
void Lance_PWM(TIM_TypeDef *Timer, char Channel, unsigned int resolution, float rapportCyclique)
{
		float compare;
	
		compare = resolution * rapportCyclique;
	
		//selection du channel
		switch(Channel)
		{
			case 1:
						Timer->CCR1 = (unsigned int)compare;
						Timer->CCER |= TIM_CCER_CC1E;
						break;
			case 2:
						Timer->CCR2 = (unsigned int)compare;
						Timer->CCER |= TIM_CCER_CC2E;
						break;
			case 3:
						Timer->CCR3 = (unsigned int)compare;
						Timer->CCER |= TIM_CCER_CC3E;
						break;
			case 4:
						Timer->CCR4 = (unsigned int)compare;
						Timer->CCER |= TIM_CCER_CC4E;
						break;
			default: 
						break;
		}
}