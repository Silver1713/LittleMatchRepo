#include "SageJSON.hpp"
#include <fstream>
#include<string>
#include <crtdbg.h>
#include <stack>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
namespace SageJSON::Lexer
{
	void Token::print()
	{
		std::cout << "Token: " << value << std::endl;
	}

	std::string Token::toString()
	{
		return "Token: " + value;
	}


}

namespace SageJSON::AST
{
	// String
	StringNode::StringNode(std::string key, std::string value)
	{
		this->key = key;
		this->value = value;
	}

	std::string StringNode::getName()
	{
		return key;
	}

	Node::JSONType StringNode::getKey()
	{
		return value;
	}

	Node::AST_Type StringNode::getType()
	{
		return AST_Type::STRING;
	}

	void StringNode::print()
	{
		SageJSONCout << toString() << std::endl;

	}

	std::string StringNode::toString()
	{
		if (key.empty())
			return "\"" + value + "\"";
		else
			return  "\"" + key + "\"" + " : " + "\""+ value + "\"";

	}

	Node::JSONType const StringNode::getKey() const
	{
		return value;
	}


	// Bool
	BooleanValueNode::BooleanValueNode(std::string key, bool value)
	{
		this->key = key;
		this->value = value;
	}

	Node::JSONType BooleanValueNode::getKey()
	{
		return value;
	}

	Node::JSONType const BooleanValueNode::getKey() const
	{
		return  value;
	}


	std::string BooleanValueNode::getName()
	{
		return key;
	}

	Node::AST_Type BooleanValueNode::getType()
	{
		return AST_Type::BOOLEAN;
	}

	void BooleanValueNode::print()
	{
		SageJSONCout << toString() << std::endl;
	}
	std::string BooleanValueNode::toString()
	{
		if (key.empty())
			return std::to_string(value);
		else
			return "\"" + key + "\"" + " : " + std::to_string(value);
	}


	NumberValueNode::NumberValueNode(std::string key, double value)
	{
		this->key = key;
		this->value = value;
	}




	Node::JSONType NumberValueNode::getKey()
	{
		return value;
	}

	std::string NumberValueNode::getName()
	{
		return key;
	}

	Node::AST_Type NumberValueNode::getType()
	{
		return AST_Type::NUMBER;
	}

	void NumberValueNode::print()
	{
		SageJSONCout << toString() << std::endl;
	}


	bool isInt(double value)
	{
		if (value == static_cast<int>(value))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	std::string NumberValueNode::toString()
	{
		if (key.empty())
			return std::to_string(isInt(value) ? static_cast<int>(value) : value);
		else
			return "\"" + key + "\"" + " : " + std::to_string(isInt(value) ? static_cast<int>(value) : value);
	}



	Node::JSONType const NumberValueNode::getKey() const
	{
		return value;
	}

	//Null
	NullValueNode::NullValueNode(std::string key, nullptr_t value)
	{
		this->key = key;
		this->value = value;
	}

	Node::JSONType NullValueNode::getKey()
	{
		return value;
	}

	Node::JSONType const NullValueNode::getKey() const
	{
		return value;
	}

	std::string NullValueNode::getName()
	{
		return key;
	}

	Node::AST_Type NullValueNode::getType()
	{
		return AST_Type::NULL_;
	}

	void NullValueNode::print()
	{
		SageJSONCout << toString() << std::endl;
	}

	std::string NullValueNode::toString()
	{
		if (key.empty())
			return "null";
		else
			return "\"" + key + "\"" + " : " + "null";
	}

	// Array

	ArrayNode::ArrayNode(std::string key, std::vector<Node*> value)
	{
		this->key = key;
		this->value = value;
	}

	Node::JSONType ArrayNode::getKey()
	{
		return value;
	}

	Node::JSONType const ArrayNode::getKey() const
	{
		return value;
	}

	std::string ArrayNode::getName()
	{
		return key;
	}
	Node::AST_Type ArrayNode::getType()
	{
		return AST_Type::ARRAY;
	}
	void ArrayNode::print()
	{
		SageJSONCout << toString() << std::endl;
	}

	std::string ArrayNode::toString()
	{
		

		std::string str;
		if (key.empty())
			str = "[ ";
		else str = "\"" + key + "\"" + " : [ ";
		for (auto i : value)
		{
			if (value.back() == i)
			{
				str += i->toString();
				break;
			}
			str += i->toString() + ", ";
		}
		str += " ]";
		return str;
	}
	void ArrayNode::appendList(Node* node)
	{
		value.push_back(node);
	}

	// Object

	ObjectNode::ObjectNode(std::string key, std::vector<Node*> value)
	{
		this->key = key;
		this->value = value;
	}

	void ObjectNode::addNode(Node* node)
	{
		value.push_back(node);
	}

	Node::JSONType ObjectNode::getKey()
	{
		return value;
	}

	Node::JSONType const ObjectNode::getKey() const
	{
		return value;
	}
	std::string ObjectNode::getName()
	{
		return key;
	}

	Node::AST_Type ObjectNode::getType()
	{
		return AST_Type::OBJECT;
	}

	void ObjectNode::print()
	{
		SageJSONCout << toString() << std::endl;
	}

	std::string ObjectNode::toString()
	{
		std::string str;
		if (key.empty())
			str = "{ ";
		else str = "\"" + key + "\"" + " : { ";
		for (auto i : value)
		{
			if (value.back() == i)
			{
				str += i->toString();
				break;
			}
			str += i->toString() + ", ";
		}
		str += " }";
		return str;
	}

	void AST::addChild(Node* node)
	{
		if (!root)
		{
			root = node;
			return;
		}

		if (node->getType() == Node::AST_Type::OBJECT)
		{
			ObjectNode* ast_node = dynamic_cast<ObjectNode*>(node);
			ObjectNode* root_obj = dynamic_cast<ObjectNode*>(root);
			root_obj->addNode(ast_node);
		}
		else if (node->getType() == Node::AST_Type::ARRAY)
		{
			ArrayNode* arr = dynamic_cast<ArrayNode*>(node);
			ObjectNode* root_arr = dynamic_cast<ObjectNode*>(root);
			root_arr->addNode(arr);

		}
		else
		{
			Node* nde = node;
			ObjectNode* rootn = dynamic_cast<ObjectNode*>(root);
			rootn->addNode(nde);
		}
	}

	void AST::addChild(Node* parent, Node* node)
	{
		if (!root)
		{
			root = node;
			return;
		}

		if (parent->getType() == Node::AST_Type::OBJECT)
		{
			Node* n = node;
			ObjectNode* root_obj = dynamic_cast<ObjectNode*>(parent);
			root_obj->addNode(n);
		}
		else if (parent->getType() == Node::AST_Type::ARRAY)
		{
			Node* n = node;
			ArrayNode* root_arr = dynamic_cast<ArrayNode*>(parent);
			root_arr->appendList(node);

		}
	}


	Node* AST::getRoot()
	{
		return root;

	}

	const Node* AST::getRoot() const
	{
		return root;

	}
	// set root is unsafe, it is better to use addChild
	void AST::setRoot(Node* node)
	{
		this->root = node;

	}



	bool AST::cleanup(Node* root)
	{

		if (root->getType() == Node::AST_Type::OBJECT)
		{
			ObjectNode* obj = dynamic_cast<ObjectNode*>(root);
			Node::JSONType val = obj->getKey();
			if (std::holds_alternative<std::vector<Node*>>(val))
			{
				std::vector<Node*> vec = std::get<std::vector<Node*>>(val);
				for (auto& i : vec)
				{
					cleanup(i);
				}

				delete root;
			}
		}
		else if (root->getType() == Node::AST_Type::ARRAY)
		{
			ArrayNode* arr = dynamic_cast<ArrayNode*>(root);
			Node::JSONType val = arr->getKey();
			if (std::holds_alternative<std::vector<Node*>>(val))
			{
				std::vector<Node*> vec = std::get<std::vector<Node*>>(val);
				for (auto& i : vec)
				{
					cleanup(i);
				}
				delete root;
			}
		}
		else {
			delete root;
		}
		return true;



	}



}



namespace SageJSON
{
	SageJSON::SageJSON(std::string filepath) : lexer_state(Lexer::LEXER_STATE::START), file_path{ filepath }, tokens{}
	{

		std::string line;
		std::ifstream json_file{ file_path };
		int i{};
		SageJSONCout << "Loaded Data: " << file_path << '\n';
		while (std::getline(json_file, line))
		{

			int s = lex(line);

			if (!s)
			{
				SageJSONCout << "Scanned Line: " << i++ << '\n';
			}
		}



		construct_ast();

		ast.getRoot()->print();


		json_file.close();





	}



	int SageJSON::lex(std::string& JSONLine) //lexical analysis line by line.
	{
		std::string::iterator begin = JSONLine.begin();
		static std::string container = {};
		static double number = 0;
		int decimal_count{};


		while (lexer_state != Lexer::LEXER_STATE::END && begin < JSONLine.end())
		{
			char const& symbol = *begin;




			if (symbol == '\"') {

				if (lexer_state != Lexer::LEXER_STATE::BEGIN_STRING) {
					lexer_state = Lexer::LEXER_STATE::BEGIN_STRING;
					begin++;
					continue;
				}

				lexer_state = Lexer::LEXER_STATE::END_STRING;
			}
			else if (std::isdigit(symbol) && lexer_state != Lexer::LEXER_STATE::BEGIN_STRING)
			{
				lexer_state = Lexer::LEXER_STATE::BEGIN_NUMBER;
			}
			else if ((symbol == 't' || symbol == 'f') && lexer_state != Lexer::LEXER_STATE::BEGIN_STRING)
			{
				lexer_state = Lexer::LEXER_STATE::BEGIN_BOOL;
			}
			else if (lexer_state != Lexer::LEXER_STATE::BEGIN_STRING && lexer_state != Lexer::LEXER_STATE::BEGIN_NUMBER)
			{
				lexer_state = Lexer::LEXER_STATE::SYMBOL;
			}
			else if (lexer_state == Lexer::LEXER_STATE::BEGIN_NUMBER && (!std::isdigit(symbol)))
			{
				if (symbol == '.' && !decimal_count)
					decimal_count++;
				else lexer_state = Lexer::LEXER_STATE::END_NUMBER;
			}


			if (lexer_state == Lexer::LEXER_STATE::SYMBOL)
			{
				if (symbol == ',')
				{
					Lexer::Token token{ Lexer::Token::Type::COMMA, std::string{symbol} };
					tokens.emplace_back(token);
				}
				else if (symbol == ':')
				{
					Lexer::Token token{ Lexer::Token::Type::COLON, std::string{symbol} };
					tokens.emplace_back(token);
				}
				else if (symbol == '{')
				{
					Lexer::Token token{ Lexer::Token::Type::OBJECT, std::string{symbol} };
					tokens.emplace_back(token);
				}
				else if (symbol == '}')
				{
					Lexer::Token token{ Lexer::Token::Type::OBJECT, std::string{symbol} };
					tokens.emplace_back(token);
				}
				else if (symbol == '[')
				{
					Lexer::Token token{ Lexer::Token::Type::ARRAY, std::string{symbol} };
					tokens.emplace_back(token);
				}
				else if (symbol == ']')
				{
					Lexer::Token token{ Lexer::Token::Type::ARRAY, std::string{symbol} };
					tokens.emplace_back(token);
				}
			}
			else if (lexer_state == Lexer::LEXER_STATE::BEGIN_STRING)
			{
				container += symbol;
			}
			else if (lexer_state == Lexer::LEXER_STATE::END_STRING)
			{
				Lexer::Token token{ Lexer::Token::Type::STRING, container };
				tokens.emplace_back(token);
				container.clear();
			}
			else if (lexer_state == Lexer::LEXER_STATE::BEGIN_NUMBER)
			{
				container += *begin;
			}
			else if (lexer_state == Lexer::LEXER_STATE::END_NUMBER)
			{

				Lexer::Token token(Lexer::Token::Type::NUMBER, container);
				tokens.emplace_back(token);
				container.clear();
				if (begin < JSONLine.end() - 1 && begin > JSONLine.begin())
					begin--;
				decimal_count = 0;
			}

			begin++;
		}


		return 0;
	}


	int SageJSON::construct_ast()
	{
		std::stack<AST::Node*> tmp_stack;
		std::string current{};
		bool inArray{ false };
		for (Lexer::Token& token : tokens)
		{
			if (current.empty() && token.type == Lexer::Token::Type::STRING && !inArray)
			{
				current = token.value;
				continue;
			}

			if (token.type == Lexer::Token::Type::OBJECT)
			{
				if (token.value == "{")
				{
					// create object

					AST::ObjectNode* obj = new AST::ObjectNode(current, {});
					current.clear();

					if (tmp_stack.empty())
					{
						tmp_stack.push(obj);
						ast.addChild(obj);
					}
					else
					{
						AST::Node* parent = tmp_stack.top();
						ast.addChild(parent, obj);
						tmp_stack.push(obj);
					}

				}
				else if (token.value == "}")
				{
					// pop object
					tmp_stack.pop();
				}

			}

			if (token.type == Lexer::Token::Type::ARRAY)
			{
				if (token.value == "[")
				{
					// create array
					AST::ArrayNode* arr = new AST::ArrayNode(current, {});
					current.clear();

					if (tmp_stack.empty())
					{
						tmp_stack.push(arr);
						ast.addChild(arr);
					}
					else
					{
						AST::Node* parent = tmp_stack.top();
						ast.addChild(parent, arr);
						tmp_stack.push(arr);
					}
					inArray = true;
				}
				else if (token.value == "]")
				{
					// pop array
					tmp_stack.pop();
					inArray = false;
				}
			}

			if (token.type == Lexer::Token::Type::STRING)
			{
				AST::Node* c_obj = tmp_stack.top();
				AST::StringNode* str = new AST::StringNode(current, token.value);
				current.clear();
				ast.addChild(c_obj, str);
			}
			else if (token.type == Lexer::Token::Type::NUMBER)
			{
				AST::Node* c_obj = tmp_stack.top();
				AST::NumberValueNode* num = new AST::NumberValueNode(current, std::stod(token.value));
				current.clear();
				ast.addChild(c_obj, num);
			}

		}
		return 0;
	}


	void SageJSON::cleanup()
	{
		if (ast.getRoot())
		{
			ast.cleanup(ast.getRoot());
		}
	}


	void SageJSON::close()
	{
		cleanup();
	}

}