#pragma once
#include<assert.h>

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

	//ͬһ����ģ��ʵ��������������
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



	private:
		node* _head;
		size_t _size;

	};
}