/*
 ============================================================================
 Name        : Project.c
 Author      : Nardeen Mahfouz
 Diploma no. : 69
 Description : C Mini Project
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

#define WITH_ENGINE_TEMP_CONTROLLER 1

void Start();
void SensorsSetMenu();
void DisplayControllers();
void SetSenors();
void setTrafficlights();
void SetRoomTemperature();
void SetEngineTemperature();

unsigned char choose_state=0;
unsigned char Vehicle_speed=0;
unsigned char Engine_State=0;
unsigned char AcController=0;
float roomTemperature=35;
float Enginetemperature=90;
unsigned char TemperatureController=0;

enum Boolean{
	false=0, true=1
};

enum Activation{
	OFF=0,
	ON=1
};

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	unsigned char program= ON;

	Start();

	scanf(" %c",&choose_state);

	while(program)
	{
		switch(choose_state) {

		case 'a' : {
			printf("The vehicle engine is turned ON\n\n");
			Engine_State=ON;
			SensorsSetMenu();
			SetSenors();

		}

		break;


		case 'b': {
			printf("The vehicle engine is turned OFF\n\n");
			Start();
			scanf(" %c",&choose_state);


		}
		break;

		case 'c':  {
		printf("\nQuit the system\n\n");
		Engine_State=OFF;
		program=OFF;
		}
		break;
		}
	}
}
void Start() {
	printf("Enter your choice:\n\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
}


void SensorsSetMenu() {
	printf("Enter your choice:\n\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature \n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature \n");
#endif
}


void DisplayControllers() {
	if(Vehicle_speed==30)
	{	if(AcController==OFF) {
				AcController=ON;
			}
			roomTemperature= roomTemperature *((float)5/4) + 1;
#if WITH_ENGINE_TEMP_CONTROLLER
			if(TemperatureController==OFF) {
				TemperatureController=ON;
					}
			Enginetemperature= Enginetemperature*((float)5/4) + 1;
#endif
		}

	if(Engine_State==OFF)
		printf("Engine state is OFF\n");
	else if(Engine_State==ON) {
		printf("Engine state is ON\n");
	}
	if(AcController==OFF)
		printf("AC is OFF\n");
	else if(AcController==ON) {
		printf("AC is ON\n");
	}
	printf("Vehicle Speed : %d Km/Hr\n",Vehicle_speed);
	printf("Room Temperature : %0.2f °C\n", roomTemperature);

#if WITH_ENGINE_TEMP_CONTROLLER
	if(TemperatureController==OFF)
		printf("Engine Temperature Controller is OFF\n");
	else if(TemperatureController==ON) {
		printf("Engine Temperature Controller is ON\n");
	}

	printf("Engine Temperature: %0.2f °C\n\n",Enginetemperature);
#endif
}

void SetSenors(){
	unsigned char choose_Sensors;
	scanf(" %c",&choose_Sensors);
	if(choose_Sensors=='a') {
		choose_state='b';
	}

	else if(choose_Sensors=='b') {
		printf("\nEnter the required color\n");
		setTrafficlights();
		DisplayControllers();
		SensorsSetMenu();
		SetSenors();
	}
	else if(choose_Sensors=='c') {
		printf("\nEnter the required Room Temperature\n");
		SetRoomTemperature();
		DisplayControllers();
		SensorsSetMenu();
		SetSenors ();

	}

	#if WITH_ENGINE_TEMP_CONTROLLER
	else if(choose_Sensors=='d') {
		printf("\nEnter the required Engine Temperature\n");
		SetEngineTemperature();
		DisplayControllers();
		SensorsSetMenu();
		SetSenors();
	}
	#endif

}
void setTrafficlights(){

    unsigned char choose_color;
	scanf(" %c",&choose_color);

	if(choose_color=='G' || choose_color=='g' ) {
		Vehicle_speed=100;
	  }
	else if(choose_color=='O' || choose_color=='o') {
		Vehicle_speed=30;
	}
	else if(choose_color=='R'|| choose_color=='r') {
		Vehicle_speed=0;

	}

}
void SetRoomTemperature() {

	scanf("%f",&roomTemperature);
	if ( roomTemperature < 10)
	{ AcController=ON;
	 roomTemperature= 20; }
	else if ( roomTemperature > 30)
	{
		AcController=ON;
		roomTemperature= 20; }

	else AcController=OFF;
}
#if WITH_ENGINE_TEMP_CONTROLLER
void SetEngineTemperature() {

	scanf("%f",&Enginetemperature);

	if(Enginetemperature < 100 )
	{	Enginetemperature=125;
	TemperatureController=ON;
	}
	else if (Enginetemperature > 150 ) {
		Enginetemperature=125;
		TemperatureController=ON;

	}
	else TemperatureController=OFF;
}
#endif
