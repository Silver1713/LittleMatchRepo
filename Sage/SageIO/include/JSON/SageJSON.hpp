#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <variant>
#ifndef SAGE_JSON_HPP

namespace SageJSON
{

	class SageJSONCout
	{
	public:
		template <typename T>
		std::ostream& operator<<(const T& t)
		{
			std::cout << "SageJSON: " << t;
			return std::cout;
		}
		
	};


	 class SageJSONCerr
	{
	public:
		template <typename T>
		std::ostream& operator<<(const T& t)
		{
			std::cerr << "SageJSON: " << t;
			return std::cerr;
		}
	};


	inline SageJSONCout& operator<< (SageJSONCout& out, std::ostream& (*pf)(std::ostream&))
	{
		std::cout << pf;
		return out;
	}
	inline SageJSONCerr& operator<< (SageJSONCerr& out, std::ostream& (*pf)(std::ostream&))
	{
		std::cerr << pf;
		return out;
	}

	
	static SageJSONCout SageJSONCout{};
	static SageJSONCerr SageJSONCerr{};


	namespace Lexer
	{
		enum class LEXER_STATE
		{
			START,
			BEGIN_STRING,
			END_STRING,
			BEGIN_NUMBER,
			END_NUMBER,
			BEGIN_BOOL,
			END_BOOL,
			BEGIN_NULL,
			END_NULL,
			SYMBOL,
			MOVE_NEXT,
			END


		};
		struct Token
		{
			enum class Type
			{
				STRING,
				NUMBER,
				BOOLEAN,
				NULL_,
				ARRAY,
				OBJECT,
				COMMA,
				COLON,
				SYMBOL,
				END,
				UNKNOWN
			};

			Type type;
			std::string value;

			Token(Type type, std::string value) : type(type), value(value) {}
			Token() : type(Type::UNKNOWN), value("") {}

			void print();

			std::string toString();


		};

	}



	namespace AST
	{
		
		class Node
		{
		protected:
			Node* parent;
		public:
			using JSONType = std::variant<double, std::reference_wrapper<double>, nullptr_t, std::string,std::reference_wrapper<std::string>,
			char, std::vector<Node>, std::reference_wrapper<std::vector<Node>>, std::reference_wrapper<std::vector<Node*>>, std::vector<Node*>, bool, std::reference_wrapper<bool>>;
			enum class AST_Type
			{
				STRING,
				NUMBER,
				BOOLEAN,
				NULL_,
				ARRAY,
				OBJECT
			};

			
			virtual ~Node() = default;
			virtual void print() = 0;
			virtual std::string toString() = 0;
			virtual AST_Type getType() = 0;
			virtual std::string getName() = 0;
			virtual JSONType getKey() = 0;
			virtual JSONType const getKey() const = 0;
		};


		class StringNode : public Node
		{
			std::string key;
			std::string value;
		public:
			StringNode(std::string key, std::string value);
			void print() override;
			std::string toString() override;
			AST_Type getType() override;
			std::string getName() override;
			JSONType getKey() override;
			JSONType const getKey() const override;

		};


		class NumberValueNode : public Node
		{
			std::string key;
			double value;
		public:
			NumberValueNode(std::string key, double value);
			void print() override;
			std::string toString() override;
			std::string getName() override;
			AST_Type getType() override;
			JSONType getKey() override;
			JSONType const getKey() const override;
		};

		class BooleanValueNode : public Node
		{
			std::string key;
			bool value;
		public:
			BooleanValueNode(std::string key, bool value);
			void print() override;
			std::string toString() override;
			std::string getName() override;
			AST_Type getType() override;
			JSONType getKey() override;
			JSONType const getKey() const override;
		};

		class NullValueNode : public Node
		{
			std::string key;
			nullptr_t value;
		public:
			NullValueNode(std::string key, nullptr_t value);
			void print() override;
			std::string toString() override;
			std::string getName() override;
			AST_Type getType() override;
			JSONType getKey() override;
			JSONType const getKey() const override;
		};

		class ArrayNode : public Node
		{
			std::string key;
			std::vector<Node*> value;
		public:
			ArrayNode(std::string key, std::vector<Node*> value);
			void print() override;
			std::string toString() override;
			std::string getName() override;
			AST_Type getType() override;
			JSONType getKey() override;
			JSONType const getKey() const override;
			void appendList(Node* node);
		};

		class ObjectNode : public Node
		{
			std::string key;
			std::vector<Node*> value;

		public:
			ObjectNode(std::string key, std::vector<Node*> value={});
			void print() override;
			std::string toString() override;
			std::string getName() override;
			AST_Type getType() override;
			JSONType getKey() override;
			JSONType const getKey() const override;
			void addNode(Node* node);
		};


		// A class to represent the Abstract Syntax Tree
		class AST
		{
			Node* root;

		public:
			using JSONIterator = Node*;
			using JSONValue = std::variant<double, std::string, nullptr_t, std::vector<Node*>,Node*, bool>;
			AST() : root(nullptr) {}
			AST(Node* root) : root(root) {}

			void setRoot(Node* root);
			Node* getRoot();
			const Node* getRoot() const;

			void addChild(Node* node);
			void addChild(Node* parent, Node* node);

			JSONValue find(std::string value);

			bool cleanup(Node* root);


		};


	}


	class SageJSON
	{
		using JSONReturnValue = std::variant<AST::Node*, std::reference_wrapper<int>, std::reference_wrapper<double>, std::reference_wrapper<float>, std::reference_wrapper<std::string>, std::vector<AST::Node*>,
			int, double, float, std::string, bool, nullptr_t, std::reference_wrapper<SageJSON>
		>;
		std::vector<Lexer::Token> tokens;
		Lexer::LEXER_STATE lexer_state;
		std::string file_path;
		AST::AST ast;
		AST::AST::JSONIterator current_node{};
		std::stack<AST::Node*> node_stack;

		int lex(std::string& JSONLine);
		int construct_ast();
		void cleanup();

		size_t read_size;


	public:

		size_t size;
		using NumberValue = double;
		using StringValue = std::string;
		using BoolValue = bool;
		using NullValue = nullptr_t;

		SageJSON();
		SageJSON(std::string filepath);

		SageJSON(AST::AST ast, std::string output);

		void read(std::string json);
		void print();
		void close();

		SageJSON& operator[](std::string key);
		SageJSON& operator[](int key);

		SageJSON& operator[](std::string key) const;

		SageJSON& operator<<(std::string line);



		friend std::istream& operator>>(std::istream& is, SageJSON& json);
		friend std::ostream& operator<<(std::ostream& os, SageJSON& json);

		template <typename T>
		T as();

		template <typename T>
		SageJSON& operator=(T const& value);
		template <>
		SageJSON& operator=(SageJSON const& value);

		AST::AST& getAST();
		AST::AST const& getAST() const;
	};

	template <typename T>
	T SageJSON::as()
	{
		
		try {
			if (!current_node)
			{
				throw std::invalid_argument("No JSON object found, are you sure the key is correct?");
			}
			if (std::holds_alternative<T>(current_node->getKey()))
			{
				T val = std::get<T>(current_node->getKey());
				current_node = nullptr;
				return val;
			}
			else if (std::holds_alternative<std::reference_wrapper<T>>(current_node->getKey()))
			{
				T val = std::get<std::reference_wrapper<T>>(current_node->getKey()).get();
				current_node = nullptr;
				return val;
			}
			else
			{
				throw std::runtime_error("Type mismatch");
				
			}
		}
		catch (std::runtime_error& e)
		{
			SageJSONCerr <<"Warning: " << e.what() <<" Variable is not converted to primitive data." << std::endl;
			current_node = nullptr;
			return {};
		}
		catch (std::invalid_argument& e)
		{
			SageJSONCerr << "Warning: " << e.what() << '\n' << " Variable is not converted to primitive data." << std::endl;
			current_node = nullptr;
			return {};
		}
		catch (...)
		{
			SageJSONCerr << "Warning: " << "Unknown error" << " Variable is not converted to primitive data." << std::endl;
			current_node = nullptr;
			return {};
		}
	}

	
	
}




#endif