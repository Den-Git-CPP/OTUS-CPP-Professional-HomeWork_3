#pragma once

#include <cstddef>
#include <memory>
#include <utility>

template <typename T, typename Allocator = std::allocator<T>>
class ForwardList {
private:
	struct Node {
		Node(T value, Node* next) :
			value(std::move(value)), next(next) {}

		T value;
		Node* next;
	};

public:
	ForwardList() = default;
	~ForwardList() {
		while (m_first != nullptr) {
			Node* ptr = m_first;
			m_first = m_first->next;
			m_allocator.destroy(ptr);
			m_allocator.deallocate(ptr, 1);
		}
	}

	class Iterator {
	private:
		friend class ForwardList<T, Allocator>;

		Iterator(Node* node, const ForwardList<T, Allocator>* instance) :
			m_node(node), m_instance(instance) {}

	public:
		Iterator& operator++() {
			m_node = m_node->next;
			return *this;
		}

		const T& operator*() const {
			return m_node->value;
		}

		bool operator!=(const Iterator& other) {
			return m_node != other.m_node;
		}

	private:
		Node* m_node;
		const ForwardList<T, Allocator>* m_instance;
	};

	Iterator begin() const {
		return Iterator{ m_first, this };
	}

	Iterator end() const {
		return Iterator{ nullptr, this };
	}

	Iterator insert_after(Iterator pos, T value) {
		Node* inserted = m_allocator.allocate(1);
		if (m_size == 0) {
			m_allocator.construct(inserted, std::move(value), nullptr);
			m_first = inserted;
		}
		else {
			m_allocator.construct(inserted, std::move(value), pos.m_node->next);
			pos.m_node->next = inserted;
		}
		Iterator it(inserted, this);
		++m_size;
		return it;
	}

	void push_front(T value) {
		Node* inserted = m_allocator.allocate(1);
		m_allocator.construct(inserted, std::move(value), m_first);
		m_first = inserted;
		++m_size;
	}

	std::size_t size() const {
		return m_size;
	}
	
private:
	using NodeAllocator = typename std::allocator_traits<Allocator>:: template rebind_alloc<Node>;
	Node* m_first = nullptr;
	NodeAllocator m_allocator;
	std::size_t m_size = 0;
};
