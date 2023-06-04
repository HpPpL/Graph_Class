#pragma once
#include "Graph.h"

namespace graph {
	///// ���������� ��� ����: /////
	// ����������� �����������:
	template<class key_type, class value_type, class weight_type>
	Graph<key_type, value_type, weight_type>::Node::Node(const Node& node) noexcept {
		m_value = node.m_value;
		if (!node.empty()) {
			m_edges = node.m_edges;
		}
	}

	// ����������� �����������:
	template<class key_type, class value_type, class weight_type>
	Graph<key_type, value_type, weight_type>::Node::Node(Node&& node) noexcept {
		swap(node);
	}

	// ��������� ���� swap:
	template <class key_type, class value_type, class weight_type>
	void Graph<key_type, value_type, weight_type>::Node::swap(Node& node) noexcept {
		std::swap(m_value, node.m_value);
		std::swap(m_edges, node.m_edges);
	}

////////////////////////////////////////////////////////////////
	//// ���������� ��� �����: ////
	// ����������� �����������:
	template<class key_type, class value_type, class weight_type>
	Graph<key_type, value_type, weight_type>::Graph(const Graph& graph) noexcept{
		if (graph.empty()) {
			return;
		}
		m_map = graph.m_map;
	}

	// ����������� �����������:
	template<class key_type, class value_type, class weight_type>
	Graph<key_type, value_type, weight_type>::Graph(Graph&& graph) noexcept{
		swap(graph);
	}

	// ��������� ���� swap:
	template<class key_type, class value_type, class weight_type>
	void Graph<key_type, value_type, weight_type>::Graph::swap(Graph& graph) noexcept {
		std::swap(m_map, graph.m_map);
	}

	// �������� []:
	template<class key_type, class value_type, class weight_type>
	value_type& Graph<key_type, value_type, weight_type>::operator[](const key_type& key) {
		return m_map[key].value();
	}

	// ������� at:
	template<class key_type, class value_type, class weight_type>
	value_type& Graph<key_type, value_type, weight_type>::at(const key_type& key) {
		if (m_map.find(key) != m_map.end()) {
			return m_map.value();
		}
		else {
			throw NoKeyException();
		}
	}

	// ������� at (const):
	template<class key_type, class value_type, class weight_type>
	value_type Graph<key_type, value_type, weight_type>::at(const key_type& key) const {
		if (m_map.find(key) != m_map.end()) {
			return m_map.at(_key_).value();
		}
		else {
			throw NoKeyException();
		}
	}

	// ������� degree_in:
	template <class key_type, class value_type, class weight_type>
	size_t Graph<key_type, value_type, weight_type>::degree_in(const key_type& key) const {
		if (m_map.find(key) != m_map.end()) {
			throw NoKeyException();
		}
		size_t res = 0;
		for (const auto& [m_key, node] : m_map) {
			for (const auto& [n_key, val] : node) {
				if (key == n_key) {
					++res;
					break;
				}
			}
		}
		return res;
	}

	// ������� degree_out:
	template <class key_type, class value_type, class weight_type>
	size_t Graph<key_type, value_type, weight_type>::degree_out(const key_type& key) const {
		if (m_map.find(key) != m_map.end()) {
			throw NoKeyException();
		}
		return m_map.find(key)->second.size();
	}

	// ������� loop:
	template <class key_type, class value_type, class weight_type>
	bool Graph<key_type, value_type, weight_type>::loop(const key_type& key) const {
		if (!degree_out(key)) {
			return false;
		}
		// ������� end => find ���������� � second => ����� key �� key => �����.
		return (m_map.find(key)->second.find(key) != m_map.find(key)->second.end());
	}

	// ������� insert:
	template <class key_type, class value_type, class weight_type>
	std::pair<typename Graph<key_type, value_type, weight_type>::iterator, bool> Graph<key_type, value_type, weight_type>::insert_node(const key_type& key, const value_type& val) {
		return m_map.insert(std::pair<const key_type, Node>{key, Node{val}});
	}

	// ������� insert_or_assign:
	template <class key_type, class value_type, class weight_type>
	std::pair<typename Graph<key_type, value_type, weight_type>::iterator, bool> Graph<key_type, value_type, weight_type>::insert_or_assign_node(const key_type& key, const value_type& val) {
		return m_map.insert_or_assign(key, Node{val});
	}

	// ������� insert_edge:
	template <class key_type, class value_type, class weight_type>
	std::pair<typename Graph<key_type, value_type, weight_type>::Node::iterator, bool> Graph<key_type, value_type, weight_type>::insert_edge(const std::pair<const key_type, const key_type>& from_key_to, const weight_type& weight) {
		m_map[from_key_to.first], m_map[from_key_to.second];
		return m_map[from_key_to.first].insert_edge(from_key_to.second, weight);
	}

	// ������� insert_or_assign_edge:
	template <class key_type, class value_type, class weight_type>
	std::pair<typename Graph<key_type, value_type, weight_type>::Node::iterator, bool> Graph<key_type, value_type, weight_type>::insert_or_assign_edge(const std::pair<const key_type, const key_type>& from_key_to, const weight_type& weight) {
		m_map[from_key_to.first], m_map[from_key_to.second];
		return m_map[from_key_to.first].insert_or_assign_edge(from_key_to.second, weight);
	}
}