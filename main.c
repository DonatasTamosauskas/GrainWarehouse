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

struct Storage {
    StackType *grainAmountStack, *grainPriceStack;
    tQueue *grainAmountQueue, *grainPriceQueue;
    int totalGrain;
    int totalPrice;
    int leftoverGrainAmount;
    int leftoverGrainPrice;
};

void setupRandomSeed(int seed);

void createQueues(struct Storage **stock);

void createStacks(struct Storage **stock);

int getRandomNumber(int range);

void worldLoop(int days, struct Storage **stock);

void buyGrains(int *tonnesOfGrain, int *pricePerTonne);

int storeGrains(int tonnesOfGrain, int pricePerTonne, struct Storage **stock);

void sellGrains(int *profitFifo, int *profitLifo, struct Storage **stock);

void sellFifo(int *profit, int amountToSell, struct Storage **stock);

void sellLeftoverGrainFifo(int *profit, int *amountToSell, struct Storage **stock);

void sellLifo(int *profit, int amountToSell, struct Storage **stock);

int calculateAverageGrainPrice(int ration, int price, struct Storage **stock);

void printResults(int profitFifo, int profitLifo);

int main() {

    int input, simulateDays;
    struct Storage *stock = (struct Storage *) malloc(sizeof(struct Storage));

    setupRandomSeed(randomSeed);
    createQueues(&stock);
    createStacks(&stock);

    printf("1. How many days should the simulation run.\n");
    scanf("%d", &simulateDays);

    worldLoop(simulateDays, &stock);

}

void createQueues(struct Storage **stock) {
    int error = 0;

    (*stock)->grainAmountQueue = createQueue(&error);
    (*stock)->grainPriceQueue = createQueue(&error);
}

void createStacks(struct Storage **stock) {
    stack_create(&((*stock)->grainAmountStack));
    stack_create(&((*stock)->grainPriceStack));
}

void setupRandomSeed(int seed) {
    srand((unsigned int) seed);
}

int getRandomNumber(int range) {
    return rand() % (range + 1);
}


/* buy (daily grain norm +- deviation, at daily cost +- deviation)
 * store (the amount that was bought)
 * sell (0-100% of the whole stock randomly)
 */
void worldLoop(int days, struct Storage **stock) {
    int tonnesOfGrain;
    int pricePerTonne;
    int profitFifo = 0;
    int profitLifo = 0;

    (*stock)->totalGrain = 0;
    (*stock)->totalPrice = 0;
    (*stock)->leftoverGrainAmount = 0;
    (*stock)->leftoverGrainPrice = 0;

    for (int i = 0; i < days; i++) {
        buyGrains(&tonnesOfGrain, &pricePerTonne);
        storeGrains(tonnesOfGrain, pricePerTonne, stock);
        sellGrains(&profitFifo, &profitLifo, stock);
    }

    printResults(profitFifo, profitLifo);
}

void buyGrains(int *tonnesOfGrain, int *pricePerTonne) {

    int grainAmountDeviation =
            DAILY_GRAIN_NORM * (MAX_DEVIATION_GRAIN_AMOUNT - getRandomNumber(MAX_DEVIATION_GRAIN_AMOUNT * 2)) / 100;
    int grainPriceDeviation =
            PRICE_FOR_TONNE * (MAX_DEVIATION_GRAIN_PRICE - getRandomNumber(MAX_DEVIATION_GRAIN_PRICE * 2)) / 100;

    (*tonnesOfGrain) = DAILY_GRAIN_NORM + grainAmountDeviation;
    (*pricePerTonne) = PRICE_FOR_TONNE + grainPriceDeviation;
}

int storeGrains(int tonnesOfGrain, int pricePerTonne, struct Storage **stock) {

    int errorCodeForQueue = 0;

    enQueue((*stock)->grainAmountQueue, tonnesOfGrain, &errorCodeForQueue);
    enQueue((*stock)->grainPriceQueue, pricePerTonne, &errorCodeForQueue);

    stack_push((*stock)->grainAmountStack, tonnesOfGrain);
    stack_push((*stock)->grainPriceStack, pricePerTonne);

    (*stock)->totalGrain += tonnesOfGrain;
    (*stock)->totalPrice += tonnesOfGrain * pricePerTonne;


    return errorCodeForQueue;
}

void sellGrains(int *profitFifo, int *profitLifo, struct Storage **stock) {
    int amountToSell = getRandomNumber((*stock)->totalGrain);
//    printf("Sold: %d. ", amountToSell);

    sellFifo(profitFifo, amountToSell, stock);
    sellLifo(profitLifo, amountToSell, stock);

//    (*stock)->totalGrain -= amountToSell;
}

void sellFifo(int *profit, int amountToSell, struct Storage **stock) {
    int errorCodeAmount = 0;
    int errorCodePrice = 0;

    sellLeftoverGrainFifo(profit, &amountToSell, stock);

    while (amountToSell > 0) {
        int ration = getData((*stock)->grainAmountQueue, &errorCodeAmount);
        int price = getData((*stock)->grainPriceQueue, &errorCodePrice);

        if (ration <= amountToSell) {
            amountToSell -= ration;
            (*profit) += ration * price;

            deQueue((*stock)->grainAmountQueue, &errorCodeAmount);
            deQueue((*stock)->grainPriceQueue, &errorCodePrice);

        } else {
            (*profit) += amountToSell * price;
            (*stock)->leftoverGrainAmount = ration - amountToSell;
            (*stock)->leftoverGrainPrice = price;
            amountToSell = 0;

            deQueue((*stock)->grainAmountQueue, &errorCodeAmount);
            deQueue((*stock)->grainPriceQueue, &errorCodePrice);
        }
    }
}

void sellLeftoverGrainFifo(int *profit, int *amountToSell, struct Storage **stock) {
    int leftoverAmount = (*stock)->leftoverGrainAmount;
    int leftoverPrice = (*stock)->leftoverGrainPrice;

    if (leftoverAmount != 0) {
        if ((*amountToSell) >= leftoverAmount) {

            (*amountToSell) -= leftoverAmount;
            (*profit) += leftoverAmount * leftoverPrice;
            (*stock)->leftoverGrainAmount = 0;

        } else {

            (*profit) += (*amountToSell) * leftoverPrice;
            (*stock)->leftoverGrainAmount = leftoverAmount - (*amountToSell);
            (*amountToSell) = 0;
        }
    }
}

void sellLifo(int *profit, int amountToSell, struct Storage **stock) {
    int ration;
    int price;
    int averagePrice;

    while (amountToSell > 0) {
        stack_pop((*stock)->grainAmountStack, &ration);
        stack_pop((*stock)->grainPriceStack, &price);
        averagePrice = calculateAverageGrainPrice(ration, price, stock);

        if (ration <= amountToSell) {
            amountToSell -= ration;
            (*profit) += ration * averagePrice;

        } else {
            (*profit) += amountToSell * averagePrice;
            int leftoverGrainAmount = ration - amountToSell;
            int leftoverGrainPrice = price;
            amountToSell = 0;

            stack_push((*stock)->grainAmountStack, leftoverGrainAmount);
            stack_push((*stock)->grainPriceStack, leftoverGrainPrice);

            (*stock)->totalGrain += leftoverGrainAmount;
            (*stock)->totalPrice += leftoverGrainAmount * leftoverGrainPrice;
        }
    }

}

int calculateAverageGrainPrice(int ration, int price, struct Storage **stock) {
    int averagePrice = (*stock)->totalPrice / (*stock)->totalGrain;

    (*stock)->totalPrice -= ration * price;
    (*stock)->totalGrain -= ration;

    return averagePrice;
}

void printResults(int profitFifo, int profitLifo) {
    printf("Total profit of FIFO: %d.\n", (profitFifo * MARKUP) / 100);
    printf("Total profit of LIFO: %d.\n", (profitLifo * MARKUP) / 100);
}


/*
 * 1) FIFO supirkimo:
    pirmiausia parduodami seniausiai įsigyti grūdai, apskaitinė grūdų kaina lygi supirkimo kainai;
 2) LIFO svertinių vidurkių:
    pirmiausia parduodami šviežiausi grūdai; apskaitinė gautų grūdų kaina nustatoma kaip tuo metu
    sandėlyje turimų grūdų kainų svertinis vidurkis (pvz., jei sandėlyje turėjome 200 t grūdų, kurių
    apskaitinė kaina 95 LT/t ir įsigijome dar 100 t po 110 LT/t, tai įsigytų grūdų apskaitinė kaina yra 100
    LT/t = (200 * 95 + 100 * 110) / (200 + 100)).
 */