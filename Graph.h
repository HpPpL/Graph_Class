#pragma once

#include <unordered_map>
#include <stdexcept>

namespace graph {

	template <class key_type = int, class value_type = int, class weight_type = double> 
	class Graph {
	public:
		class Node;
		using iterator = typename std::unordered_map<key_type, Node>::iterator;
		using const_iterator = typename std::unordered_map<key_type, Node>::const_iterator;
		
		iterator begin() { return m_map.begin(); }
		iterator end() { return m_map.end(); }
		const_iterator begin() const { return m_map.begin(); }
		const_iterator cbegin() const { return m_map.cbegin(); }
		const_iterator end() const { return m_map.end(); }
		const_iterator cend() const { return m_map.cend(); }

		Graph() noexcept = default;
		~Graph() noexcept = default;
		Graph(const Graph& graph) noexcept;
		Graph(Graph&& graph) noexcept;

		void swap(Graph& graph) noexcept;
		bool empty() const noexcept { return m_map.empty(); }
		size_t size() const noexcept { return m_map.size(); }
		void clear() noexcept { m_map.clear(); }
		size_t degree_in(const key_type& key) const;
		size_t degree_out(const key_type& key) const;
		bool loop(const key_type& key) const;

		std::pair<iterator, bool> insert_node(const key_type& key, const value_type& val);
		std::pair<iterator, bool> insert_or_assign_node(const key_type& key, const value_type& val);

		// Передаем две вершины и вес. //
		std::pair<typename Node::iterator, bool> insert_edge(const std::pair<const key_type, const key_type>& from_key_to, const weight_type& weight);
		std::pair<typename Node::iterator, bool> insert_or_assign_edge(const std::pair<const key_type, const key_type>& from_key_to, const weight_type& weight);

		value_type& operator[](const key_type& key);
		value_type& at(const key_type& key);
		value_type at(const key_type& key) const;

	private:
		std::unordered_map<key_type, Node> m_map;
	};

	template <class key_type, class value_type, class weight_type>
	class Graph<key_type, value_type, weight_type>::Node {
	public:
		using iterator = typename std::unordered_map<key_type, weight_type>::iterator;
		using const_iterator = typename std::unordered_map<key_type, weight_type>::const_iterator;

		iterator begin() { return m_edges.begin(); }
		iterator end() { return m_edges.end(); }
		const_iterator begin() const { return m_edges.begin(); }
		const_iterator cbegin() const { return m_edges.cbegin(); }
		const_iterator end() const { return m_edges.end(); }
		const_iterator cend() const { return m_edges.cend(); }

		Node() noexcept = default;
		~Node() noexcept = default;
		Node(const Node& node) noexcept;
		Node(Node&& node) noexcept;

		void swap(Node& node) noexcept;
		bool empty() const noexcept { return m_edges.empty(); }
		size_t size() const noexcept { return m_edges.size(); }
		value_type value() const { return m_value; }
		value_type& value() { return m_value; }
		void clear() noexcept { m_edges.clear(); }

	private:
		value_type m_value = value_type();
		std::unordered_map<key_type, weight_type> m_edges;
	};
	struct GraphException : public std::exception {
		GraphException(const char* str) : std::exception(str) {}
	};
	struct NoKeyException : public GraphException {
		NoKeyException() : GraphException("The key is not in the graph!") {}
	};

}
