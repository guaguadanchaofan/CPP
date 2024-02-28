#pragma once
#include<assert.h>
#include<algorithm>

namespace guagua
{
	template<class T>
	struct list_node
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _date;
		list_node(const T& x)
			:_next(nullptr)
			,_prev(nullptr)
			,_date(x)
		{}
	};

	//同一个类模板实例化出两个类型
	//typedef iterator_list< T , T& , T* >iterator;
	//typedef iterator_list<const T ,const  T& ,const  T* >const_iterator;
	template<class T,class Ref,class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> node;
		typedef __list_iterator<T, T&, T*> Self;
		node* _pnode;

		__list_iterator(node* p)
			:_pnode(p)
		{}

		//it->
		Ptr operator->()
		{
			return &_pnode->_date;
		}
		//it*
		Ref operator*()
		{
			return _pnode->_date;
		}
		//++it
		Self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}
		//it++
		Self operator++(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_next;
			return tmp;
		}
		//--it
		Self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}
		//it--
		Self operator--(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_prev;
			return tmp;
		}

		bool operator!=(const Self& it)const
		{
			return _pnode != it._pnode;
		}

		bool operator==(const Self& it)const
		{
			return _pnode == it._pnode;
		}
	};

	template<class T>
	class list
	{
		typedef list_node<T> node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end()const
		{
			return const_iterator(_head);
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		void empty_initialize()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;

			_size = 0;
		}

		list()
		{
			empty_initialize();
		}


		//遍历迭代器
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();
			while(first!=last)
			{
				push_back(*first);
				++first;
			}
		}


		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		//list<T> it1(it2)
		list(const list<T>& it)
		{
			empty_initialize();
			list<T> tmp(it.begin(), it.end());
			swap(tmp);
		}

		void push_back(const T& x)
		{
			node* newnode = new node(x);
			node* tail = _head->_prev;
			// _head         tail   newnode
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}
	private:
		node* _head;
		size_t _size;

	};
}