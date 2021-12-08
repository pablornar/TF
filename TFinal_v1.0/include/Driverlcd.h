/*
 *
 */

#ifndef DRIVERLCD_H_
#define DRIVERLCD_H_

// ----------------------------------------------------------------------------

//variables
struct D{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
struct C{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
struct E{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
struct B{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
struct C D0={ GPIO_PIN_7, GPIOC};
struct C D1={ GPIO_PIN_8, GPIOC};
struct D D2={ GPIO_PIN_15, GPIOD};
struct C D3={ GPIO_PIN_6, GPIOC};
struct D D4={ GPIO_PIN_13, GPIOD};
struct D D5={ GPIO_PIN_14, GPIOD};
struct D D6={ GPIO_PIN_11, GPIOD};
struct D D7={ GPIO_PIN_12, GPIOD};
struct D D8={ GPIO_PIN_9, GPIOD};
struct D D9={ GPIO_PIN_10, GPIOD};
struct B D10={ GPIO_PIN_15, GPIOB};
struct D D11={ GPIO_PIN_8, GPIOD};
struct B D12={ GPIO_PIN_13, GPIOB};
struct B D13={ GPIO_PIN_14, GPIOB};
struct B D14={ GPIO_PIN_12, GPIOB};
struct B D15={ GPIO_PIN_11, GPIOB};
struct B RS={ GPIO_PIN_10, GPIOB};
struct E WR={ GPIO_PIN_15, GPIOE};
struct E CS={ GPIO_PIN_14, GPIOE};
struct E REST={ GPIO_PIN_13, GPIOE};

//Funciones


// ----------------------------------------------------------------------------

#endif // DRIVERLCD_H_
