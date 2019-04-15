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
				* \brief Fronta implementovan� pomoc� spojov�ch struktur s vyu�it�m %OOP.
				*
				* @author	Ji�� Dvorsk� <jiri.dvorsky@vsb.cz>
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
					* Vlo�en� prvku na konec fronty.
					*
					* @param X Vkl�dan� prvek
					*/
					void Enqueue(const U & X);

					/**
					* Odebr�n� prvku z �ela fronty.
					*
					* @return Prvek z �ela fronty
					*/
					const U Dequeue();

					/**
					* Prvek na �ele fronty.
					* Prvek nen� z �ela fronty odstran�n, jedn� se o nedestruktivn� variantu metody #Dequeue
					*
					* @return Prvek z �ela fronty
					*/
					const U Peek() const;

					/**
					* Test, je-li fronta pr�zdn�.
					*
					* @return Funkce vrac� true pokud je fronta pr�zdn�, jinak false.
					*/
					bool IsEmpty() const;

					/**
					* Smaz�n� cel�ho obsahu fronty.
					*
					*/
					void Clear();

				private:
					/**
					* \brief Struktura reprezentuj�c� polo�ku ve front�.
					*/
					struct QueueItem
					{
						/**
						* Hodnota obsa�en� v polo�ce.
						*/
						U Value;
						/**
						* Ukazatel na p�edchoz� polo�ku. Pokud takov� polo�ka neexistuje ukazatel m� hodnotu nullptr.
						*/
						QueueItem* Prev = nullptr;
					};

					/**
					* Hlava fronty. Hlava fronty ukazuje na prvn� prvek fronty.
					* Prvn� prvek fronty naz�v�me tak� �elo fronty.
					*/
					QueueItem* Head = nullptr;

					/**
					* Ocas fronty. Tento ukazatel b�n� ukazuje na posledn� prvek ve front�.
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
