#pragma once
#include "Exceptions.hpp"

namespace NSD
{
	template<class T> struct BDList
	{
		struct Node
		{
			T data_;
			Node *pNext_, *pPrev_;
			explicit Node(const T& data) : data_(data), pNext_(0), pPrev_(0) {}
		};
		struct iterator
		{
			typedef T ElementT;
			Node *pCurrent_;
			BDList *pContainer_;
			iterator(Node *pCurrent, BDList *pContainer) : pCurrent_(pCurrent), pContainer_(pContainer) {}
			operator bool () const
			{
				return pContainer_ != 0 && pCurrent_ != 0;
			}
			T& operator*()
			{
				if(pCurrent_) return pCurrent_->data_;
				else throw EInvalidIterator();
			}
			T* operator->()
			{
				if(pCurrent_) return &pCurrent_->data_;
				else throw EInvalidIterator();
			}
			const T& operator*() const
			{
				if(pCurrent_) return pCurrent_->data_;
				else throw EInvalidIterator();
			}
			iterator& operator ++()
			{
				if(pCurrent_ ) pCurrent_ = pCurrent_->pNext_;
				else throw EInvalidIterator();
				return *this;
			}
			iterator& operator --()
			{
				if(pCurrent_ ) pCurrent_ = pCurrent_->pPrev_;
				else throw EInvalidIterator();
				return *this;
			}
			iterator operator ++(int)
			{
				iterator old = *this;
				if(pCurrent_ ) pCurrent_ = pCurrent_->pNext_;
				else throw EInvalidIterator();
				return old;
			}
			iterator operator --(int)
			{
				iterator old = *this;
				if(pCurrent_ ) pCurrent_ = pCurrent_->pPrev_;
				else throw EInvalidIterator();
				return old;
			}

			bool operator ==(const iterator& arg)
			{
				return (pContainer_ == arg.pContainer_) && (pCurrent_ == arg.pCurrent_);
			}
			bool operator !=(const iterator& arg)
			{
				return !(*this == arg);
			}
			void insertBefore(const T& data);
			/*{
				Node *pn = new Node(data);
				if(pCurrent_)
				{
					pn->pPrev_ = pCurrent_->pPrev_;
					pn->pNext_ = pCurrent_;
					pCurrent_->pPrev_ = pn;
					if(pn->pPrev_ == 0) pContainer_->pFirst_ = pn;
				}
				else
				{
					pContainer_->pFirst_ = pn;
					pContainer_->pLast_ = pn;
					pCurrent_ = pn;
				}
			}*/
			void insertAfter(const T& data);
			/*{
				Node *pn = new Node(data);
				if( pCurrent_)
				{
				  pn->pNext_ = pCurrent_->pNext_ ;
				  pn->pPrev_ = pCurrent_;
				  pCurrent_->pNext_ = pn;
				  if(pn->pNext_ == 0) pContainer_->pLast_ = pn;
				}
					else
					{
				  pContainer_->pFirst_ = pn;
				  pContainer_->pLast_ = pn;
				  pCurrent_ = pn;
				}
			}*/
			void remove();
			/*{
				if(pCurrent_ )
				{
					Node* pn = pCurrent_;
					if (pn->pPrev_ ) pn->pPrev_->pNext_ = pn->pNext_;
					else pContainer_->pFirst_ = pn->pNext_;

					if(pn->pNext_) pn->pNext_->pPrev_ = pn->pPrev_;
					else pContainer_->pLast_ = pn->pPrev_;

					pCurrent_ = 0;
					delete pn;
				} else throw "Can't delete node which does not exist.";
			}*/
		};
		Node *pFirst_, *pLast_;
		BDList() : pFirst_(0), pLast_(0) {}
		iterator getFirst()
		{
			return iterator(pFirst_, this);
		}
		iterator getLast()
		{
			return iterator(pLast_, this);
		}
		unsigned size()
		{
			unsigned count = 0;
			Node *pn = pFirst_;
			while(pn) 
			{
				++count;
				pn = pn->pNext_;
			}
			return count;
		}

		~BDList()
		{
			while(pFirst_)
			{
				Node *pn = pFirst_;
				pFirst_ = pFirst_->pNext_;
				delete pn;
			}
		}
	};
	template<class T> void BDList<T>::iterator::insertBefore(const T& data)
	{
		Node *pn = new Node(data);
		if(pCurrent_)
		{
			pn->pPrev_ = pCurrent_->pPrev_;
			pn->pNext_ = pCurrent_;
			if(pCurrent_->pPrev_) pCurrent_->pPrev_->pNext_ = pn;
			pCurrent_->pPrev_ = pn;
			if(pn->pPrev_ == 0) pContainer_->pFirst_ = pn;
		}
		else
		{
			pContainer_->pFirst_ = pn;
			pContainer_->pLast_ = pn;
			pCurrent_ = pn;
		}
	}
	template<class T> void BDList<T>::iterator::insertAfter(const T& data)
	{
		Node *pn = new Node(data);
		if( pCurrent_)
		{
		  pn->pNext_ = pCurrent_->pNext_ ;
		  pn->pPrev_ = pCurrent_;
		  if(pCurrent_->pNext_) pCurrent_->pNext_->pPrev_ = pn;
		  pCurrent_->pNext_ = pn;
		  if(pn->pNext_ == 0) pContainer_->pLast_ = pn;
		}
			else
		{
		  pContainer_->pFirst_ = pn;
		  pContainer_->pLast_ = pn;
		  pCurrent_ = pn;
		}
	}
	template<class T> void BDList<T>::iterator::remove()
	{
		if(pCurrent_ )
		{
			Node* pn = pCurrent_;
			if (pn->pPrev_ ) pn->pPrev_->pNext_ = pn->pNext_;
			else pContainer_->pFirst_ = pn->pNext_;

			if(pn->pNext_) pn->pNext_->pPrev_ = pn->pPrev_;
			else pContainer_->pLast_ = pn->pPrev_;

			pCurrent_ = 0;
			delete pn;
		} else throw "Can't delete node which does not exist.";
	}

}
