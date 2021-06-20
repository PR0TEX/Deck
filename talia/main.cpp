#define _CRT_SECURE_NO_WARNINGS 0
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

enum color_t { green, blue, red, violet, yellow, white, black };


struct Card_t {
        int color;
        int value;
}card;

typedef struct userValues_t
{
        int n;
        int g;
        int gv;
        int k;
        int o;
        int active;
        int e;
}userValues;

typedef struct Player_t {
        Card_t hand[100];
        int ctCard;
        int stCard;
};

typedef struct Hand_t {
        Card_t card[7];
};

int compareMyType(const void* a, const void* b)
{
        if (*(int*)a < *(int*)b) return -1;
        if (*(int*)a == *(int*)b) return 0;
        return 1;

}

void setDeck(Card_t* deck, userValues_t userValues, int* valOfCards)
{
        int k = 0, c = 1;
        for (int i = 0;i < userValues.g;i++)
        {
                deck[i].color = 0;
                deck[i].value = userValues.gv;
        }
        for (int i = 0;i < userValues.k * userValues.o;i++)
        {
                if (k == userValues.o)
                {
                        k = 0;
                        c++;
                }

                deck[i + userValues.g].color = c;
                deck[i + userValues.g].value = valOfCards[k];
                k++;


        }
}

void printDeck(Card_t* deck, int size)
{
        const char* const colors[] = { "green","blue","red","violet","yellow","white","black" };
        FILE* file;
        file = fopen("trucizna.txt", "w");
        for (int i = 0;i < size;i++)
        {
                fprintf(file, "%d %s ", deck[i].value, colors[deck[i].color]);
        }
        fclose(file);
}

void cardsDeal(Player_t** player, Card_t* deck, userValues_t userValues)
{

        for (int i = 0;i < userValues.g + userValues.k * userValues.o;i++)
        {
                if (deck != NULL)
                {
                        player[i % userValues.n]->hand[i / userValues.n].color = deck[i].color;
                        player[i % userValues.n]->hand[i / userValues.n].value = deck[i].value;
                }
        }



}
void printPlayerBasicHand(Player_t** player, userValues_t userValues)
{
        const char* const colors[] = { "green","blue","red","violet","yellow","white","black" };
        FILE* file;
        file = fopen("trucizna.txt", "w");
        for (int i = 0;i < userValues.n;i++)
        {
                if (i == 0)
                {
                        fprintf(file, "%s\n", "active player = 1");
                        fprintf(file, "%s %d\n", "players number =", userValues.n);
                }
                fprintf(file, "%d %s", i + 1, "player hand cards: ");
                for (int j = 0;j < userValues.g + userValues.k * userValues.o;j++)
                {

                        if (player[i]->hand[j].color >= 0 && player[i]->hand[j].color <= 6)
                        {

                                fprintf(file, " %d %s", player[i]->hand[j].value, colors[player[i]->hand[j].color]);
                        }
                }
                fprintf(file, "\n%d %s \n", i + 1, "player deck cards:");
        }
        for (int i = 0;i < userValues.k; i++)
        {
                fprintf(file, "%d %s\n", i + 1, "pile cards:");
        }
        fclose(file);
}

void printPlayerHand(Player_t** player, Player_t** playerDeck, Player_t** pileCards, userValues_t userValues)
{
        const char* const colors[] = { "green","blue","red","violet","yellow","white","black" };
        FILE* file;
        file = fopen("trucizna.txt", "w");
        for (int i = 0;i < userValues.n;i++)
        {
                if (i == 0)
                {
                        fprintf(file, "%s%d\n", "active player = ", userValues.active + 1);
                        fprintf(file, "%s%d\n", "players number = ", userValues.n);
                        fprintf(file, "%s%d", "explosion threshold = ", userValues.e);
                }
                fprintf(file, "\n%d %s", i + 1, "player hand cards: ");
                for (int j = 0;j < player[i]->ctCard;j++)
                {
                        fprintf(file, "%d %s ", player[i]->hand[j].value, colors[player[i]->hand[j].color]);
                }
                fprintf(file, "\n%d %s", i + 1, "player deck cards: ");
                for (int j = 0;j < playerDeck[i]->ctCard;j++)
                {
                        fprintf(file, "%d %s ", playerDeck[i]->hand[j].value, colors[playerDeck[i]->hand[j].color]);
                }
        }
        for (int i = 0;i < userValues.k; i++)
        {
                fprintf(file, "\n%d %s", i + 1, "pile cards: ");
                for (int j = 0;j < pileCards[i]->ctCard;j++)
                {
                        fprintf(file, "%d %s ", pileCards[i]->hand[j].value, colors[pileCards[i]->hand[j].color]);
                }
        }
        fclose(file);
}

void setPlayerCard(Player_t* player, char* tab)
{
        int suma = 0, counter = 0;
        player->ctCard = 0;
        const char* const colors[] = { "green","blue","red","violet","yellow","white","black" };
        char* pch;

        pch = strtok(tab, " ");
        bool isDoubleDot = false;
        while (pch != NULL)
        {
                if (strstr(pch, "cards:"))
                {
                        isDoubleDot = true;
                }

                else if (isDoubleDot)
                {
                        for (int i = 0;i < strlen(pch);i++)
                        {
                                suma = suma * 10 + (int)pch[i] - '0';

                        }
                        player->hand[counter].value = suma;
                        suma = 0;
                        pch = strtok(NULL, " ");
                        if (pch == NULL)
                        {
                                break;
                        }
                        for (int i = 0;i < 7;i++)
                        {

                                if (strstr(pch, colors[i]))
                                {
                                        player->hand[counter].color = i;
                                        break;
                                }
                        }
                        counter++;

                }

                pch = strtok(NULL, " ");

        }
        player->ctCard = counter;
        player->stCard = counter;
}

void printPlayerBasicAmounts(Player_t** player, int n, Player_t** playerDeck)
{
        for (int i = 0;i < n;i++)
        {
                cout << i + 1 << " player has " << player[i]->ctCard << " cards on hand " << endl;
                cout << i + 1 << " player has " << playerDeck[i]->ctCard << " cards in front of him " << endl;
        }
}

void printPlayerAmounts(Player_t** player, int n, Player_t** playerDeck, Player_t** pileCards, int k)
{
        for (int i = 0;i < n;i++)
        {
                cout << i + 1 << " player has " << player[i]->ctCard << " cards on hand " << endl;
                cout << i + 1 << " player has " << playerDeck[i]->ctCard << " cards in front of him " << endl;
        }
        for (int i = 0;i < k;i++)
        {
                cout << "there are " << pileCards[i]->ctCard << " cards on " << i + 1 << " pile" << endl;
        }
}

int countColors(Player_t** player, int n)
{
        int count = 0;
        char pColor[] = { 0,0,0,0,0,0,0 };
        for (int i = 0;i < n;i++) {
                for (int j = 0;j < player[i]->ctCard;j++)
                {
                        if (pColor[player[i]->hand[j].color] == 0)
                        {
                                pColor[player[i]->hand[j].color]++;
                                count++;
                        }
                }
        }

        return count - 1;
}

void countGreen(Player_t** player, Player_t** pileCards, int n, int k)
{
        int count = 0;
        int greenValues[9];
        for (int i = 0;i < n;i++)
        {
                for (int j = 0;j < player[0]->ctCard;j++)
                {
                        if (player[i]->hand[j].color == green)
                        {
                                greenValues[count] = player[i]->hand[j].value;
                                count++;

                        }
                }
        }
        for (int i = 0;i < k;i++)
        {
                for (int j = 0;j < pileCards[0]->ctCard;j++)
                {
                        if (pileCards[i]->hand[j].color == green)
                        {
                                greenValues[count] = pileCards[i]->hand[j].value;
                                count++;

                        }
                }
        }
        bool same = true;
        for (int i = 0;i < 8;i++)
        {
                if (greenValues[i] > 0 && greenValues[i + 1] > 0)
                {
                        if (greenValues[i] != greenValues[i + 1])
                        {
                                same = false;
                                break;
                        }
                }
        }

        if (count == 0)
        {
                cout << "Green cards does not exist" << endl;
        }
        else if (same)
        {
                cout << "Found " << count << " green cards, all with " << greenValues[0] << " value" << endl;
        }
        else
        {
                cout << "Different green cards values occurred" << endl;
        }

}
//sprawdza czy ilosc kolorow jest taka sama
void countCards(Player_t** player, Player_t** pileCards, Player_t** playerDeck, int n, int k)
{
        const char* const colors[] = { "green","blue","red","violet","yellow","white","black" };
        int cardAmount[7] = { 0,0,0,0,0,0,0 };
        for (int i = 0;i < n;i++)
        {
                for (int j = 0;j < player[i]->ctCard;j++)
                {
                        if (player[i]->hand[j].color >= 0 && player[i]->hand[j].color < 8)
                        {
                                cardAmount[player[i]->hand[j].color]++;
                        }
                }
        }
        for (int i = 0;i < k;i++)
        {
                for (int j = 0;j < pileCards[i]->ctCard;j++)
                {
                        if (pileCards[i]->hand[j].color >= 0 && pileCards[i]->hand[j].color < 8)
                        {
                                cardAmount[pileCards[i]->hand[j].color]++;
                        }
                }
        }
        for (int i = 0;i < n;i++)
        {
                for (int j = 0;j < playerDeck[i]->ctCard;j++)
                {
                        if (playerDeck[i]->hand[j].color >= 0 && playerDeck[i]->hand[j].color < 8)
                        {
                                cardAmount[playerDeck[i]->hand[j].color]++;
                        }
                }
        }
        bool same = true;
        for (int i = 1;i < sizeof(cardAmount) / sizeof(*cardAmount) - 1;i++)
        {
                if (cardAmount[i] != cardAmount[i + 1] && cardAmount[i] != 0 && cardAmount[i + 1] != 0)
                {
                        same = false;
                }
        }
        if (same)
        {
                cout << "The number cards of all colors is equal: " << cardAmount[blue] << endl;
        }
        else
        {
                cout << "At least two colors with a different number of cards were found: " << endl;
                for (int i = 1;i < sizeof(cardAmount) / sizeof(*cardAmount);i++)
                {
                        cout << colors[i] << " cards are " << cardAmount[i] << endl;
                }

        }
}
//sprawdza czy wartosci kart sa takie same
void valuesOfCards(Player_t** player, Player_t** playerDeck, Player_t** pileCards, int n, int k)
{
        const char* const colors[] = { "green","blue","red","violet","yellow","white","black" };
        int valuesOfColors[7][21];
        for (int i = 0;i < 7;i++)
        {
                for (int j = 0;j < 21;j++)
                {
                        valuesOfColors[i][j] = 0;
                }

        }
        for (int i = 0;i < n;i++)
        {
                for (int j = 0;j < player[i]->ctCard;j++)
                {
                        if (player[i]->hand[j].color >= 0 && player[i]->hand[j].color < 8)
                        {
                                valuesOfColors[player[i]->hand[j].color][valuesOfColors[player[i]->hand[j].color][0] + 1] = player[i]->hand[j].value;
                                valuesOfColors[player[i]->hand[j].color][0]++;
                        }
                }
        }

        for (int i = 0;i < k;i++)
        {
                for (int j = 0;j < pileCards[i]->ctCard;j++)
                {
                        if (pileCards[i]->hand[j].color >= 0 && pileCards[i]->hand[j].color < 8)
                        {
                                valuesOfColors[pileCards[i]->hand[j].color][valuesOfColors[pileCards[i]->hand[j].color][0] + 1] = pileCards[i]->hand[j].value;
                                valuesOfColors[pileCards[i]->hand[j].color][0]++;
                        }
                }
        }

        for (int i = 0;i < n;i++)
        {
                for (int j = 0;j < playerDeck[i]->ctCard;j++)
                {
                        if (playerDeck[i]->hand[j].color >= 0 && playerDeck[i]->hand[j].color < 8)
                        {
                                valuesOfColors[playerDeck[i]->hand[j].color][valuesOfColors[playerDeck[i]->hand[j].color][0] + 1] = playerDeck[i]->hand[j].value;
                                valuesOfColors[playerDeck[i]->hand[j].color][0]++;
                        }
                }
        }

        for (int i = 0;i < 7;i++)
        {
                valuesOfColors[i][0] = 0;
                qsort((void*)valuesOfColors[i], (sizeof valuesOfColors[i]) / (sizeof valuesOfColors[i][0]), sizeof(valuesOfColors[i][0]), compareMyType);
        }
        bool same = true;
        for (int i = 1;i < k;i++)

        {
                for (int j = 0;j < (sizeof valuesOfColors[1]) / (sizeof valuesOfColors[0][0]);j++)
                {

                        if (valuesOfColors[i][j] != valuesOfColors[i + 1][j] && valuesOfColors[i][j] > 0 && valuesOfColors[i + 1][j] > 0)
                        {
                                same = false;
                                break;
                        }
                }
                if (same == false)
                {
                        break;
                }
        }
        if (same)
        {
                cout << "The values of cards of all colors are identical: " << endl;
                for (int i = 0;i < (sizeof valuesOfColors[1]) / (sizeof valuesOfColors[0][0]);i++)
                {
                        if (valuesOfColors[1][i] > 0)
                        {
                                cout << valuesOfColors[1][i] << " ";
                        }

                }
        }
        else
        {
                cout << "The values of cards of all colors are not identical: " << endl;
                for (int i = 1;i < k + 1;i++)
                {
                        cout << colors[i] << " cards values: ";
                        for (int j = 0;j < (sizeof valuesOfColors[i]) / (sizeof valuesOfColors[i][0]);j++)
                        {
                                if (valuesOfColors[i][j] > 0)
                                {
                                        cout << valuesOfColors[i][j] << " ";
                                }

                        }
                        cout << endl;
                }
        }



}
//liczy ilosc kolorow w kociolku
int countPileColors(Player_t* pileCards)
{

        int count = 0;
        char pColor[] = { 0,0,0,0,0,0,0 };
        for (int j = 0;j < pileCards->ctCard;j++)
        {

                if (pColor[pileCards->hand[j].color] == 0)
                {
                        pColor[pileCards->hand[j].color]++;
                        if (pileCards->hand[j].color != green)
                        {
                                count++;
                        }

                }
        }


        return count;

}
//sprawdza czy kociolki odpowiednia ilosc kolorow
bool isPileRight(Player_t** pileCards, int k)
{
        bool isOk = true;
        for (int i = 0;i < k;i++)
        {
                if (!(countPileColors(pileCards[i]) == 1 || countPileColors(pileCards[i]) == 0))
                {
                        cout << "Two different colors were found on the " << i + 1 << " pile" << endl;
                        isOk = false;
                }

        }
        return isOk;
}
// sprawdza czy ilosc kart w grze sie zgadza
bool isAmountOfCardsRight(Player_t** players, Player_t** pileCards, int n, int k)
{
        bool isOk = true;
        int deckSize = 0;
        int amountOfPileCards = 0;
        for (int i = 0;i < k;i++)
        {
                amountOfPileCards += pileCards[i]->ctCard;
        }
        int place = 0;
        do
        {
                if (place == n)
                {
                        place = 0;
                }
                players[place]->stCard += 1;
                amountOfPileCards--;
                place++;
        } while (amountOfPileCards > 0);
        int primarySizeOfHand[6] = { 0,0,0,0,0,0 };

        for (int i = 0;i < n;i++)
        {
                deckSize += players[i]->stCard;
        }
        int basicPlayerHand = deckSize / n;
        for (int i = 0;i < n;i++)
        {
                primarySizeOfHand[i] = basicPlayerHand;
        }
        if (deckSize - basicPlayerHand != 0)
        {
                int sub = deckSize - basicPlayerHand * n;
                int place2 = 0;
                do
                {
                        if (place2 == n)
                        {
                                place2 = 0;
                        }
                        primarySizeOfHand[place2] += 1;
                        sub--;
                        place2++;
                } while (sub > 0);
        }
        bool sameAmount = true;
        for (int i = 0;i < n;i++)
        {
                if (primarySizeOfHand[i] != 0)
                {
                        if (players[i]->stCard != primarySizeOfHand[i])
                        {
                                sameAmount = false;
                                break;
                        }
                }
        }
        if (!sameAmount)
        {
                cout << "The number of players cards on hand is wrong" << endl;
                isOk = false;
        }
        return isOk;
}
bool isSizeOfPileRight(Player_t** pileCards, int e, int k)
{
        bool isOk = true;
        for (int i = 0;i < k;i++)
        {
                int currentSizeOfPile = 0;
                for (int j = 0;j < pileCards[i]->ctCard;j++)
                {
                        currentSizeOfPile += pileCards[i]->hand[j].value;
                }
                if (currentSizeOfPile > e)
                {
                        cout << "Pile number " << i + 1 << " should explode earlier" << endl;
                        isOk = false;
                }
        }
        return isOk;
}
void addCard(Card_t card, Player_t* pileCards)
{
        pileCards->hand[pileCards->ctCard] = card;
        pileCards->ctCard++;
}
void removeCard(Player_t* player)
{
        for (int i = 0;i < player->ctCard - 1;i++)
        {
                player->hand[i] = player->hand[i + 1];
        }
        player->ctCard--;
}
//sprawdza czy kociolek jest przepelniony
bool sizeOfPile(Player_t* pileCards, int e)
{
        int currentSize = 0;
        for (int i = 0;i < pileCards->ctCard;i++)
        {
                currentSize += pileCards->hand[i].value;
        }
        if (currentSize > e)
        {
                return false;
        }
        return true;
}
void pileExplosion(Player_t* pileCards, Player_t* playerDeck)
{
        int breakPoint = pileCards->ctCard;
        for (int i = 0;i < breakPoint;i++)
        {
                playerDeck->hand[playerDeck->ctCard] = pileCards->hand[0];
                playerDeck->ctCard++;
                removeCard(pileCards);

        }
}
void playerMove(Player_t* player, Player_t** pileCards, int k, int& activePlayer)
{
        if (player->hand[0].color == green)
        {
                addCard(player->hand[0], pileCards[0]);

        }
        else
        {
                for (int i = 0;i < k;i++)
                {
                        if (pileCards[i]->hand[pileCards[i]->ctCard - 1].color == player->hand[0].color || pileCards[i]->hand[pileCards[i]->ctCard - 1].color == green)
                        {
                                addCard(player->hand[0], pileCards[i]);
                        }

                }
        }
        removeCard(player);
        activePlayer++;
}
void playerMoveExplosion(Player_t* player, Player_t* playerDeck, Player_t** pileCards, int k, int& activePlayer, int e)
{
        if (player->hand[0].color == green)
        {
                addCard(player->hand[0], pileCards[0]);
                if (!sizeOfPile(pileCards[0], e))
                {
                        pileExplosion(pileCards[0], playerDeck);
                }


        }
        else
        {
                for (int i = 0;i < k;i++)
                {
                        if (pileCards[i]->hand[pileCards[i]->ctCard - 1].color == player->hand[0].color || pileCards[i]->hand[pileCards[i]->ctCard - 1].color == green)
                        {
                                addCard(player->hand[0], pileCards[i]);
                                if (!sizeOfPile(pileCards[i], e))
                                {
                                        pileExplosion(pileCards[i], playerDeck);
                                }
                                break;
                        }

                }
        }
        removeCard(player);
        activePlayer++;
}
//wspolne korzystanie z pliku dla pkt 3b-5
void basicMove(char* tab, userValues_t& userValues, char x)
{
        FILE* file;
        file = fopen("trucizna.txt", "r");
        fgets(tab, 1000, file);
        fgets(tab, 1000, file);
        char* pch = strtok(tab, " ");
        while (pch != NULL)
        {
                if (pch[0] > '0' && pch[0] <= '9')
                {
                        userValues.n = atoi(pch);
                        break;
                }

                pch = strtok(NULL, " ");
        }
        Player_t** players = (Player_t**)malloc(sizeof(Player_t*) * userValues.n);
        for (int i = 0;i < userValues.n;i++)
        {
                players[i] = (Player_t*)malloc(100 * sizeof(Player_t));
        }
        Player_t** playersDeck = (Player_t**)malloc(sizeof(Player_t*) * userValues.n);
        for (int i = 0;i < userValues.n;i++)
        {
                playersDeck[i] = (Player_t*)malloc(100 * sizeof(Player_t));
        }
        for (int i = 0;i < userValues.n;i++)
        {
                fgets(tab, 1000, file);
                setPlayerCard(players[i], tab);
                fgets(tab, 1000, file);
                setPlayerCard(playersDeck[i], tab);
        }
        userValues.k = countColors(players, userValues.n);
        Player_t** pileCards = (Player_t**)malloc(sizeof(Player_t*) * userValues.k);
        for (int i = 0;i < userValues.k;i++)
        {
                pileCards[i] = (Player_t*)malloc(100 * sizeof(Player_t));
        }
        for (int i = 0;i < userValues.k;i++)
        {
                fgets(tab, 1000, file);
                setPlayerCard(pileCards[i], tab);
        }
        switch (x)
        {
        case '3':
        {
                printPlayerAmounts(players, userValues.n, playersDeck, pileCards, userValues.k);
                break;
        }
        case '4':
        {
                countGreen(players, pileCards, userValues.n, userValues.k);
                break;
        }
        case'5':
        {
                countCards(players, pileCards, playersDeck, userValues.n, userValues.k);
                break;
        }
        case '6':
        {
                valuesOfCards(players, playersDeck, pileCards, userValues.n, userValues.k);
                break;
        }
        }
        fclose(file);
        free(pileCards);
        free(players);
        free(playersDeck);
}
//wspolne korzystanie z pliku dla pkt 6-7b
void connectMove(char* tab, userValues_t* userValues, char x)
{
        FILE* file = fopen("trucizna.txt", "r");
        fgets(tab, 1000, file);
        char* pch;
        pch = strtok(tab, " ");

        while (pch != NULL)
        {
                if (pch[0] > '0' && pch[0] <= '9')
                {
                        userValues->active = atoi(pch) - 1;
                        break;
                }

                pch = strtok(NULL, " ");
        }
        fgets(tab, 1000, file);
        pch = strtok(tab, " ");
        while (pch != NULL)
        {
                if (pch[0] > '0' && pch[0] <= '9')
                {
                        userValues->n = atoi(pch);
                        break;
                }

                pch = strtok(NULL, " ");
        }
        fgets(tab, 1000, file);
        pch = strtok(tab, " ");
        while (pch != NULL)
        {
                if (pch[0] > '0' && pch[0] <= '9')
                {
                        userValues->e = atoi(pch);
                        break;
                }

                pch = strtok(NULL, " ");
        }
        Player_t** players = (Player_t**)malloc(sizeof(Player_t*) * userValues->n);
        for (int i = 0;i < userValues->n;i++)
        {
                players[i] = (Player_t*)malloc(100 * sizeof(Player_t));
        }
        Player_t** playersDeck = (Player_t**)malloc(sizeof(Player_t*) * userValues->n);
        for (int i = 0;i < userValues->n;i++)
        {
                playersDeck[i] = (Player_t*)malloc(100 * sizeof(Player_t));
        }
        for (int i = 0;i < userValues->n;i++)
        {
                fgets(tab, 1000, file);
                setPlayerCard(players[i], tab);
                fgets(tab, 1000, file);
                setPlayerCard(playersDeck[i], tab);
        }
        userValues->k = countColors(players, userValues->n);
        Player_t** pileCards = (Player_t**)malloc(sizeof(Player_t*) * userValues->k);
        for (int i = 0;i < userValues->k;i++)
        {
                pileCards[i] = (Player_t*)malloc(100 * sizeof(Player_t));
        }
        for (int i = 0;i < userValues->k;i++)
        {
                fgets(tab, 1000, file);
                setPlayerCard(pileCards[i], tab);
        }
        Hand_t** hand = (Hand_t**)malloc(userValues->n * sizeof(Hand_t));
        for (int i = 0;i < userValues->n;i++)
        {
                hand[i] = (Hand_t*)malloc(20 * sizeof(Hand_t));
        }
        switch (x)
        {
        case '7':
        {
                bool test1 = isAmountOfCardsRight(players, pileCards, userValues->n, userValues->k);
                bool test2 = isPileRight(pileCards, userValues->k);
                bool test3 = isSizeOfPileRight(pileCards, userValues->e, userValues->k);
                if (test1 && test2 && test3) {
                        cout << "Current state of the game is ok" << endl;
                }
                break;
        }
        case '8':
        {
                playerMove(players[userValues->active], pileCards, userValues->k, userValues->active);
                userValues->active = userValues->active % userValues->n;
                printPlayerHand(players, playersDeck, pileCards, *userValues);
                break;
        }
        case'9':
        {
                playerMoveExplosion(players[userValues->active], playersDeck[userValues->active], pileCards, userValues->k, userValues->active, userValues->e);
                userValues->active = userValues->active % userValues->n;
                printPlayerHand(players, playersDeck, pileCards, *userValues);
                break;
        }
        }
        fclose(file);
        free(hand);
        free(pileCards);
        free(players);
        free(playersDeck);
}





int main()
{
        userValues_t userValues;
        userValues.active = 0;
        userValues.e = 0;
        userValues.g = 0;
        userValues.gv = 0;
        userValues.k = 0;
        userValues.n = 0;
        userValues.o = 0;
        int* valOfCards = NULL;
        char input = '0';
        bool END = false;
        char tab[1000];

        do
        {
                cout << "Input your move: " << endl;
                cout << "Instruction :" << endl;
                cout << "Press 0 - insert values and generate deck" << endl;
                cout << "Press 1 - deal cards" << endl;
                cout << "Press 2 - load game without pile" << endl;
                cout << "Press 3 - load game with pile" << endl;
                cout << "Press 4 - check green cards" << endl;
                cout << "Press 5 - check cards numbers" << endl;
                cout << "Press 6 - check cards values" << endl;
                cout << "Press 7 - check state" << endl;
                cout << "Press 8 - easy move" << endl;
                cout << "Press 9 - easy move with cauldron explosion" << endl;
                cout << "Insert end - END GAME" << endl;
                cin >> input;
                switch (input)
                {
                case '0':
                {
                        cin >> userValues.k >> userValues.g >> userValues.gv >> userValues.o;
                        valOfCards = (int*)malloc(userValues.o * sizeof(int));
                        if (valOfCards == NULL)
                        {
                                exit(1);
                        }
                        Card_t* deck = (Card_t*)malloc((userValues.g + userValues.k * userValues.o) * sizeof(Card_t));
                        for (int i = 0;i < userValues.o;i++)
                        {
                                cin >> valOfCards[i];
                        }
                        setDeck(deck, userValues, valOfCards);
                        printDeck(deck, userValues.g + userValues.k * userValues.o);
                        free(deck);
                        free(valOfCards);
                        break;
                }
                case '1':
                {
                        cin >> userValues.n >> userValues.k >> userValues.g >> userValues.gv >> userValues.o;
                        valOfCards = (int*)malloc(userValues.o * sizeof(int));
                        if (valOfCards == NULL)
                        {
                                exit(1);
                        }
                        for (int i = 0;i < userValues.o;i++)
                        {
                                cin >> valOfCards[i];
                        }
                        Card_t* deck = (Card_t*)malloc((userValues.g + userValues.k * userValues.o) * sizeof(Card_t));
                        setDeck(deck, userValues, valOfCards);
                        Player_t** players = (Player_t**)malloc(userValues.n * sizeof(Player_t*));
                        for (int i = 0;i < userValues.n;i++)
                        {
                                players[i] = (Player_t*)malloc((userValues.g + userValues.k * userValues.o) / userValues.n * sizeof(Player_t));
                        }
                        cardsDeal(players, deck, userValues);
                        printPlayerBasicHand(players, userValues);
                        free(players);
                        free(deck);
                        free(valOfCards);
                        break;
                }
                case '2':
                {

                        FILE* file;
                        file = fopen("trucizna.txt", "r");
                        fgets(tab, 1000, file);
                        fgets(tab, 1000, file);
                        char* pch = strtok(tab, " ");
                        while (pch != NULL)
                        {
                                if (pch[0] > '0' && pch[0] <= '9')
                                {
                                        userValues.n = atoi(pch);
                                        break;
                                }

                                pch = strtok(NULL, " ");
                        }
                        Player_t** players = (Player_t**)malloc(sizeof(Player_t*) * userValues.n);
                        for (int i = 0;i < userValues.n;i++)
                        {
                                players[i] = (Player_t*)malloc(100 * sizeof(Player_t));
                        }
                        Player_t** playersDeck = (Player_t**)malloc(sizeof(Player_t*) * userValues.n);
                        for (int i = 0;i < userValues.n;i++)
                        {
                                playersDeck[i] = (Player_t*)malloc(100 * sizeof(Player_t));
                        }
                        for (int i = 0;i < userValues.n;i++)
                        {
                                fgets(tab, 1000, file);
                                setPlayerCard(players[i], tab);
                                fgets(tab, 1000, file);
                                setPlayerCard(playersDeck[i], tab);
                        }
                        printPlayerBasicAmounts(players, userValues.n, playersDeck);
                        fclose(file);
                        free(players);
                        free(playersDeck);
                        break;
                }
                case '3':
                {
                        basicMove(tab, userValues, '3');
                        break;

                }
                case '4':
                {
                        basicMove(tab, userValues, '4');
                        break;
                }
                case '5':
                {
                        basicMove(tab, userValues, '5');
                        break;

                }
                case '6':
                {
                        basicMove(tab, userValues, '6');
                        Hand_t** hand = (Hand_t**)malloc(userValues.n * sizeof(Hand_t));
                        for (int i = 0;i < userValues.n;i++)
                        {
                                hand[i] = (Hand_t*)malloc(20 * sizeof(Hand_t));
                        }
                        free(hand);
                        break;
                }
                case '7':
                {
                        connectMove(tab, &userValues, '7');
                        break;
                }
                case '8':
                {
                        connectMove(tab, &userValues, '8');
                        break;
                }
                case '9':
                {
                        connectMove(tab, &userValues, '9');
                        break;
                }
                default:
                {
                        END = true;
                        break;
                }
                }
        } while (!END);
        return 0;
}
