/*12. Grūdų sandėlis (ADT: stekas, eilė).
  Įmonė aktyviai prekiauja grūdais.
* Kiekvieną dieną įmonė perka ir sandėliuoja grūdus bei juos parduoda (atsitiktinai nuo 0 iki 100% sandėlyje turimų grūdų).
* Yra nustatyta per dieną superkamų grūdų norma (pvz., 100 t) ir supirkimo kaina (pvz., 200 LT/t)
 , bet natūralu, kad ne visomis dienomis vienodai sekasi, todėl ekspertiškai žinomas superkamų grūdų kiekio
maksimalus nuokrypis (pvz., 15%, tai reiškia, kad kiekvieną dieną įmonė superka 85-115 t grūdų) ir
maksimalus grūdų supirkimo kainos nuokrypis (pvz., 5%, tai reiškia, kad įmonė superka gūdus po 190-
210 LT/t).
 Parduodama grūdus įmonė ima nustatytą antkainį (pvz., 10%) nuo apskaitinės grūdų kainos.
Gali būti naudojami tokie atsargų apskaitos metodai:
 1) FIFO supirkimo:
    pirmiausia parduodami seniausiai įsigyti grūdai, apskaitinė grūdų kaina lygi supirkimo kainai;
 2) LIFO svertinių vidurkių:
    pirmiausia parduodami šviežiausi grūdai; apskaitinė gautų grūdų kaina nustatoma kaip tuo metu
    sandėlyje turimų grūdų kainų svertinis vidurkis (pvz., jei sandėlyje turėjome 200 t grūdų, kurių
    apskaitinė kaina 95 LT/t ir įsigijome dar 100 t po 110 LT/t, tai įsigytų grūdų apskaitinė kaina yra 100
    LT/t = (200 * 95 + 100 * 110) / (200 + 100)).

Tikslas: patyrinėti, kurį grūdų apskaitos metodą naudodama įmonė gauna didesnį pelną.*/

#include <stdio.h>
#include <stdlib.h>
#include "DataStorageStructures/stekas_1/stack.h"
#include "DataStorageStructures/eilė_2/queue.h"

const int DAILY_GRAIN_NORM = 100;
const int PRICE_FOR_TONNE = 200;
const int MAX_DEVIATION_GRAIN_AMOUNT = 15;
const int MAX_DEVIATION_GRAIN_PRICE = 5;
const int MARKUP = 10;
const int randomSeed = 10;

struct grainRation {
    double grainAmount;
    double grainPrice;
};

void createDataStructure(StackType **grainStack, tQueue **grainQueue);

void setupRandomSeed(int seed);

void worldLoop(int days);

int getRandomNumber(int range);

void buyGrains(int *tonnesOfGrain, int *pricePerTonne);

int main() {

    int input, simulateDays;
    StackType *grainStack;
    tQueue *grainQueue;

    setupRandomSeed(randomSeed);
    createDataStructure(&grainStack, &grainQueue);

    // queue works
//        enQueue(grainQueue, 5, NULL);
//        enQueue(grainQueue, 6, NULL);
//        enQueue(grainQueue, 7, NULL);
//        printf("%d", getData(grainQueue, NULL));

    // stack works
//    stack_push(grainStack, 5);
//    stack_push(grainStack, 6);
//    stack_push(grainStack, 7);
//    int n = 0;
//    stack_pop(grainStack, &n);
//    printf("%d", n);

    printf("1. How many days should the simulation run.\n");
    scanf("%d", &simulateDays);

    worldLoop(simulateDays);


}

void createDataStructure(StackType **grainStack, tQueue **grainQueue) {
    int error;
    stack_create(grainStack);
    (*grainQueue) = createQueue(&error);
}

void setupRandomSeed(int seed) {
    srand((unsigned int) seed);
}

int getRandomNumber(int range) {
    return rand() % range;
}

void worldLoop(int days) {
    for (int i = 0; i < days; i++) {
        /* buy (daily grain norm +- deviation, at daily cost +- deviation)
         * store (the amount that was bought)
         * sell (0-100% of the whole stock randomly)
         */


    }
}

void buyGrains(int *tonnesOfGrain, int *pricePerTonne) {
    int grainAmountDeviation =
            DAILY_GRAIN_NORM * (MAX_DEVIATION_GRAIN_AMOUNT - getRandomNumber(MAX_DEVIATION_GRAIN_AMOUNT * 2));
    int grainPriceDeviation =
            PRICE_FOR_TONNE * (MAX_DEVIATION_GRAIN_PRICE - getRandomNumber(MAX_DEVIATION_GRAIN_PRICE * 2));

    (*tonnesOfGrain) = DAILY_GRAIN_NORM + grainAmountDeviation;
    (*pricePerTonne) = PRICE_FOR_TONNE + grainPriceDeviation;
}

/*
 *  const int DAILY_GRAIN_NORM = 100;
    const int PRICE_FOR_TONNE = 200;
    const double MAX_DEVIATION_GRAIN_AMOUNT = 0.15;
    const double MAX_DEVIATION_GRAIN_PRICE = 0.05;
    const double MARKUP = 0.1;
    const int randomSeed = 10;
 */
