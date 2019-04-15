#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

namespace ADSLibrary
{
	namespace DataStructures
	{
		namespace LinkedStructures
		{
			namespace OOP
			{
				/**
				* \brief Fronta implementovaná pomocí spojových struktur s využitím %OOP.
				*
				* @author	Jiøí Dvorský <jiri.dvorsky@vsb.cz>
				* @date	2010 - 2017
				*/
				template<typename U>
				class Queue
				{
				public:

					/**
					* Destuktor
					*/
					~Queue();

					/**
					* Vložení prvku na konec fronty.
					*
					* @param X Vkládaný prvek
					*/
					void Enqueue(const U & X);

					/**
					* Odebrání prvku z èela fronty.
					*
					* @return Prvek z èela fronty
					*/
					const U Dequeue();

					/**
					* Prvek na èele fronty.
					* Prvek není z èela fronty odstranìn, jedná se o nedestruktivní variantu metody #Dequeue
					*
					* @return Prvek z èela fronty
					*/
					const U Peek() const;

					/**
					* Test, je-li fronta prázdná.
					*
					* @return Funkce vrací true pokud je fronta prázdná, jinak false.
					*/
					bool IsEmpty() const;

					/**
					* Smazání celého obsahu fronty.
					*
					*/
					void Clear();

				private:
					/**
					* \brief Struktura reprezentující položku ve frontì.
					*/
					struct QueueItem
					{
						/**
						* Hodnota obsažená v položce.
						*/
						U Value;
						/**
						* Ukazatel na pøedchozí položku. Pokud taková položka neexistuje ukazatel má hodnotu nullptr.
						*/
						QueueItem* Prev = nullptr;
					};

					/**
					* Hlava fronty. Hlava fronty ukazuje na první prvek fronty.
					* První prvek fronty nazýváme také èelo fronty.
					*/
					QueueItem* Head = nullptr;

					/**
					* Ocas fronty. Tento ukazatel bìžnì ukazuje na poslední prvek ve frontì.
					*/
					QueueItem* Tail = nullptr;
				};

				template<typename U>
				Queue<U>::~Queue()
				{
					this->Clear();
				}

				template<typename U>
				void Queue<U>::Enqueue(const U & X)
				{
					QueueItem* n = new QueueItem;
					n->Value = X;
					n->Prev = nullptr;
					if (this->IsEmpty())
					{
						this->Head = n;
					}
					else
					{
						this->Tail->Prev = n;
					}
					this->Tail = n;
				}

				template<typename U>
				const U Queue<U>::Dequeue()
				{
					QueueItem* d = this->Head;
					const U result = d->Value;
					this->Head = this->Head->Prev;
					if (this->IsEmpty())
					{
						this->Tail = nullptr;
					}
					delete d;
					return result;
				}

				template<typename U>
				const U Queue<U>::Peek() const
				{
					return this->Head->Value;
				}



				template<typename U>
				bool Queue<U>::IsEmpty() const
				{
					return this->Head == nullptr;
				}

				template<typename U>
				void Queue<U>::Clear()
				{
					while (!this->IsEmpty())
					{
						this->Dequeue();
					}
				}

			}
		}
	}
}
