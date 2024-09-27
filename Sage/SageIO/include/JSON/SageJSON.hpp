#include <string>
#include <vector>
#include <iostream>
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
		SageJSONCerr& operator<<(const T& t)
		{
			std::cerr << "SageJSON: " << t;
			return *this;
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
			char, std::vector<Node>, std::reference_wrapper<std::vector<Node>>, std::vector<Node*>, bool>;
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

		std::vector<Lexer::Token> tokens;
		Lexer::LEXER_STATE lexer_state;
		std::string file_path;
		AST::AST ast;

		int lex(std::string& JSONLine);
		int construct_ast();
		void cleanup();
	public:
		SageJSON(std::string filepath);
		void print();
		void close();


	};


}



#endif