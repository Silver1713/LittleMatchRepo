/* Start Header ************************************************************************/
/*!
\file		SageJSON.hpp
\title		Memory's Flame
\author		Yeo Jia Hao, jiahao.yeo, 2301325 (100%)
\par		jiahao.yeo@digipen.edu
\date		02 October 2024

\brief		This file contain the declaration for a generic JSON parser that can both parse and
			write JSON files. As this interface utilize templates, templated functions are
			defined in this header files.

			This header comprises of different namespaces that each
			represent a component that are crucial to serializing and deserializing JSON
			files format. The namespace are as follows:

			1. SageJSON: Main namespace containing the JSON parser class that contain the
			function to parse and write JSON files. It also accept stream of input files.

			2. Lexer: Namespace containing classes for purpose of conducting lexical analysis.
			This tokenizes the raw sstring into JSON tokens which allow for a Abstract Syntax
			Tree (AST) to be more easily constructed.

			3. AST: Namespace containing classes that are crucial for a JSON AST. This namespace
			contain the Base class Node that is inherited by other classes such as StringNode,
			NumberNode and etc. This node classes represent the element in the AST and it use
			to preserve the structure of the JSON file. The AST class is also crucial for
			serialization of C++ objects into the JSON format. It also contain function to
			build a AST from C++ data, allowing custom data to be serialized into JSON format.

			These namespaces represent the simplified version of how a compiler works. Thus
			the JSON parser will first pass the data to the Lexer to tokenize the data and
			then pass the tokenized data to the AST to construct the tree structure of the JSON
			data.

			\note As of now, the JSON can be used to deserialize JSON data into C++ objects.

			All content © 2024 DigiPen Institute of Technology Singapore. All rights reserved.
*/
/* End Header **************************************************************************/
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <variant>
#ifndef SAGE_JSON_HPP


/*!*****************************************************************************
\brief
	Main namespace containing the JSON parser class that contain the
	function to parse and write JSON files. It also accept stream of input files.
*******************************************************************************/
namespace SageJSON
{
	/*!*****************************************************************************
	\brief
		This class allow messages from the JSON parser to be displayed in the console.
		It add a prefix to the message to indicate that the output originated from
		the custom JSON parser.
	*******************************************************************************/
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

	/*!*****************************************************************************
	\brief
		This class allow error from the JSON parser to be displayed in the console.
		It add a prefix to the message to indicate that the output originated from
		the custom JSON parser.
	*******************************************************************************/
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

	 /*!*****************************************************************************
	 \brief
		 Overloaded operator (`<<`) to allow the SageJSONCout class to be used in
		 the output stream with the `std::cout` object.
	 *******************************************************************************/
	inline SageJSONCout& operator<< (SageJSONCout& out, std::ostream& (*pf)(std::ostream&))
	{
		std::cout << pf;
		return out;
	}
	/*!*****************************************************************************
	\brief
		Overloaded operator (`<<`) to allow the SageJSONCout class to be used in
		the error stream with the `std::cerr` object.
	*******************************************************************************/
	inline SageJSONCerr& operator<< (SageJSONCerr& out, std::ostream& (*pf)(std::ostream&))
	{
		std::cerr << pf;
		return out;
	}

	
	static SageJSONCout SageJSONCout{}; //!< Object of SageJSONCout class
	static SageJSONCerr SageJSONCerr{}; //!< Object of SageJSONCerr class

	/*!*****************************************************************************
	\brief
		Namespace containing classes for purpose of conducting lexical analysis.
		This tokenizes the raw sstring into JSON tokens which allow for an
		Abstract Syntax Tree (AST) to be more easily constructed.

		
	*******************************************************************************/
	namespace Lexer
	{
	/*!*****************************************************************************
	\brief
		The different state that the lexer can be in. This enum represent the
		current state of the lexer and it is used to determine the next action
		of the lexer. The lexer is implemented as a finite state machine.
	*******************************************************************************/
		enum class LEXER_STATE 
		{
			START, //!< The start state of the lexer
			BEGIN_STRING, //!< In a string
			END_STRING, //!< Out of a string
			BEGIN_NUMBER, //!< In a number
			END_NUMBER, //!< Out of a number
			BEGIN_BOOL, //!< In a boolean
			END_BOOL, //!< Out of a boolean
			BEGIN_NULL, //!< In a null
			END_NULL, //!< Out of a null
			SYMBOL, //!< Is a symbol
			MOVE_NEXT, //!< Move to the next token
			END //!< End of the lexer
		};
		/*!*****************************************************************************
		\brief
			This structure represent a token that is generated by the lexer. The token
			class contain the type of the token and the value of the token in string.
			This token will then be converted into their appropriate type in the AST.
		*******************************************************************************/
		struct Token
		{
			enum class Type
			{
				STRING, //!< The token is a string
				NUMBER, //!< The token is a number
				BOOLEAN, //!< The token is a boolean
				NULL_, //!< The token is a null
				ARRAY, //!< The token is an array
				OBJECT, //!< The token is an object
				COMMA, //!< The token is a comma
				COLON, //!< The token is a colon
				SYMBOL, //!< The token is a symbol
				END, //!< The token is the end of the file
				UNKNOWN //! < The token is unknown
			};

			Type type;
			std::string value;
			/*!*****************************************************************************
			\brief
				Construtor for the Token class. It take in an type and a value.
			\param type
				The type of the token
			\param value
				The value of the token
			*******************************************************************************/
			Token(Type type, std::string value) : type(type), value(value) {}
			Token() : type(Type::UNKNOWN), value("") {}
			/*!*****************************************************************************
			\brief
				Print out the token value.
			*******************************************************************************/
			void print();
			/*!*****************************************************************************
			\brief
				Get the token as raw string.
			\return
				The token as a string
			*******************************************************************************/
			std::string toString();
		};

	}


	/*!*****************************************************************************
	\brief
		Namespace containing classes that are crucial for a JSON AST. This namespace
		contain the Base class Node that is inherited by other classes such as StringNode,
		NumberNode and etc. This node classes represent the element in the AST and it use
		to preserve the structure of the JSON file. The AST class is also crucial for
		serialization of C++ objects into the JSON format. It also contain function to
		build a AST from C++ data, allowing custom data to be serialized into JSON format.
	*******************************************************************************/
	namespace AST
	{
		/*!*****************************************************************************
		\brief
			Represent a Node in the Abstract Syntax Tree (AST). This base class is inherited
			by other classes such as StringNode, NumberNode and etc. This node classes
			represent the generic element in the AST and it use to preserve the format
			and structure of the JSON file. It contains function to retrieve the type of the
			data, the name of the data and the value of the data.
		*******************************************************************************/
		class Node
		{
		protected:
			Node* parent; //!< The parent node of the current node
		public:
			/// Variant type to store the JSON data
			using JSONType = std::variant<double, std::reference_wrapper<double>, nullptr_t, std::string,std::reference_wrapper<std::string>,
			char, std::vector<Node>, std::reference_wrapper<std::vector<Node>>, std::reference_wrapper<std::vector<Node*>>, std::vector<Node*>, bool, std::reference_wrapper<bool>>;
			enum class AST_Type //!< The type of the AST node
			{
				STRING, //!< String
				NUMBER, //!< Number
				BOOLEAN, //!< Boolean
				NULL_, //!< Null
				ARRAY, //!< Array
				OBJECT //!< Object
			};

			/*!*****************************************************************************
			\brief
				Virtual destructor for the Node class
			*******************************************************************************/
			virtual ~Node() = default;
			/*!*****************************************************************************
			\brief
				Print out the node in JSON format to the console
			*******************************************************************************/
			virtual void print() = 0;
			/*!*****************************************************************************
			\brief
				Convert the Node to a JSON string
			*******************************************************************************/
			virtual std::string toString() = 0;
			/*!*****************************************************************************
			\brief
				Get the type of the Node
			*******************************************************************************/
			virtual AST_Type getType() = 0;
			/*!*****************************************************************************
			\brief
				Get the name of the Node
			*******************************************************************************/
			virtual std::string getName() = 0;
			/*!*****************************************************************************
			\brief
				Get the value of the Node
			*******************************************************************************/
			virtual JSONType getKey() = 0;
			/*!*****************************************************************************
			\brief
				Get the value of the Node
			*******************************************************************************/
			virtual JSONType const getKey() const = 0;
		};

		/*!*****************************************************************************
		\brief
			Represent a Node in the Abstract Syntax Tree (AST) that contain a string
			value. This class is inherited from the Node class and contain overriden function
			to handle the string value.
		*******************************************************************************/
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

		/*!*****************************************************************************
		\brief
			Represent a Node in the Abstract Syntax Tree (AST) that contain a number
			value. This class is inherited from the Node class and contain overriden function
			to handle the number value. Number are store using double precision type
		*******************************************************************************/
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
		/*!*****************************************************************************
		\brief
			Represent a Node in the Abstract Syntax Tree (AST) that contain a bool
			value. This class is inherited from the Node class and contain overriden function
			to handle the bool value. 
		*******************************************************************************/
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
		/*!*****************************************************************************
		\brief
			Represent a Null in the Abstract Syntax Tree (AST) that contain a null
			value. This class is inherited from the Node class and contain overriden function
			to handle the null value.
		*******************************************************************************/
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
		/*!*****************************************************************************
		\brief
			Represent a Array in the Abstract Syntax Tree (AST) that contain a array.
			This class is inherited from the Node class and contain overriden function
			to handle the array such as adding or removing node from the array.
		*******************************************************************************/
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
			size_t size() const;
		};
		/*!*****************************************************************************
		\brief
			Represent an Object in the Abstract Syntax Tree (AST) that contain an object.
			This class is inherited from the Node class and contain overriden function
			to handle the object such as adding or removing node from the object.
		*******************************************************************************/
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
			size_t size() const;
		};


		/*!****************************************************************************
		\brief
			This class represents an Abstract Syntax Tree (AST) which are used for organizing
			and manipulating a hierarchical structures of nodes,  found in
			parsers and interpreters.
		*******************************************************************************/
		class AST
		{
			Node* root; //!< The root node of the tree.

		public:
			using JSONIterator = Node*; //!< Iterator for the JSON tree
			using JSONValue = std::variant<double, std::string, nullptr_t, std::vector<Node*>, Node*, bool>; //!< A variant type to store the JSON data

			/*!****************************************************************************
			\brief Default constructor that create an empty AST.
			******************************************************************************/
			AST() : root(nullptr) {}
			/*!****************************************************************************
			\brief Overloaded constructor that create an AST with a root node.

			\param root
				The root node of the AST.
			******************************************************************************/
			AST(Node* root) : root(root) {}
			/*!****************************************************************************
			\brief Set the root node of the AST.

			\param root
				The root node of the AST.
			\note This function is unsafe as setting a root to its children will cause
			cleanup to be incomplete as the cleanup function will use the root to
			traverse the tree.
			******************************************************************************/
			void setRoot(Node* root);
			/*!****************************************************************************
			\brief Get the root node of the AST.
			******************************************************************************/
			Node* getRoot();
			/*!****************************************************************************
			\brief Get the root node of the AST.
			******************************************************************************/
			const Node* getRoot() const;
			/*!****************************************************************************
			\brief Add a child to the root node of the AST.
			\param node
				The node to be added to the root node.
			******************************************************************************/
			void addChild(Node* node);
			/*!****************************************************************************
			\brief Add a child to a node in the AST.
			\param parent
				The parent node to add the child to.
			\param node
				The node to be added to the parent node.
			******************************************************************************/
			void addChild(Node* parent, Node* node);

			//JSONValue find(std::string value);
			/*!****************************************************************************
			\brief Traverse the tree and free memory allocated for the nodes to the
			free store. The function will take the root as the starting point.
			******************************************************************************/
			bool cleanup(Node* _root);


		};


	}

	/*!****************************************************************************
	\brief The JSON parser class that contain the function to parse and write JSON files.
	This class encapsulate the AST and the lexer to allow for JSON files to be
	serialized into a AST and vice versa. The class also contain function to
	stream input files into the parser. Parsing JSON format into AST allows for
	generic data to be serialized into JSON format.
	*******************************************************************************/
	class SageJSON
	{
		using JSONReturnValue = std::variant<AST::Node*, std::reference_wrapper<int>, std::reference_wrapper<double>, std::reference_wrapper<float>, std::reference_wrapper<std::string>, std::vector<AST::Node*>,
			int, double, float, std::string, bool, nullptr_t, std::reference_wrapper<SageJSON> //!< Variant type to store the JSON data
		>;
		std::vector<Lexer::Token> tokens; //!< Vector to store the tokenized JSON data
		Lexer::LEXER_STATE lexer_state; //!< The current state of the lexer
		std::string file_path; //!< The file path of the JSON file
		AST::AST ast; //!< The Abstract Syntax Tree (AST) of the JSON file
		AST::AST::JSONIterator current_node{}; //!< The current node that the parser is at
		std::stack<AST::Node*> node_stack; //!< Stack to store the node of the AST
		/*!****************************************************************************
		\brief
			Utilize the lexical analysis to tokenize the JSON data. The function will
			tokenize the JSON data line by line and store the token in the tokens vector.
			This enable files to be streamed into the parser.
		\param JSONLine
			The line of JSON data to be tokenized.
		*******************************************************************************/
		int lex(std::string& JSONLine);
		/*!****************************************************************************
		\brief
			Using data in the tokens list, construct a AST structure. This structure is
			persistant and can be used to incrementally build the JSON data. This allow
			streaming of JSON data into the parser.
		*******************************************************************************/
		int construct_ast();
		/*!****************************************************************************
		\brief
			Cleanup the memory allocated for the nodes in the AST. This function is called
			in the destructor to ensure that the memory allocated for the nodes are freed.
		*******************************************************************************/
		void cleanup();

		size_t read_size; //!< The read size of the JSON file when streaming


	public:

		class SageJSONArrayProxy
		{
			SageJSON& parent;
			AST::AST::JSONIterator current_node;
			AST::ArrayNode* array_node;

			SageJSONArrayProxy& operator[](size_t index);

			size_t size() const;


			template <typename T>
			T as();

			SageJSONArrayProxy(SageJSON& mainClass, AST::AST::JSONIterator current);
		};

		

		class SageJSONObjectProxy
		{
			SageJSON& parent;
			AST::AST::JSONIterator current_node;
			AST::ObjectNode* object_node;

			SageJSONObjectProxy& operator[](std::string key);
			size_t size() const;
			template <typename T>
			T as();

			SageJSONObjectProxy(SageJSON& mainClass, AST::AST::JSONIterator current);
		};

		

		size_t size; //!< The size of the JSON file
		using NumberValue = double; //!< The number value of the JSON data
		using StringValue = std::string; //!< The string value of the JSON data
		using BoolValue = bool; //!< The boolean value of the JSON data
		using NullValue = nullptr_t; //!< The null value of the JSON data
		using JSONList = std::vector<AST::Node*>; //!< JSON object and arrays.
		/*!****************************************************************************
		 \brief Default constructor that create an empty JSON parser. Allows for streaming
		 of data from the input stream
		*******************************************************************************/
		SageJSON();
		/*!****************************************************************************
		 \brief Overloaded constructor that accepts the path to a JSON file and
		 serialize the JSON file into a AST. The AST can then be modified.
		*******************************************************************************/
		SageJSON(std::string filepath);

		//SageJSON(AST::AST ast, std::string output);

		//void read(std::string json);
		/*!****************************************************************************
		 \brief Convert the AST into a JSON string and print it to the console.
		*******************************************************************************/
		void print();
		/*!****************************************************************************
		 \brief Close the JSON parser and cleanup the memory allocated for the nodes in
		 the AST.
		*******************************************************************************/
		void close();
		/*!****************************************************************************
		 \brief Subscript operator to access the JSON data. This function allow for the
		 data to be accessed in a similar manner to a map. The function will return the
		 value of the key in the JSON data.
		 \param key
			The key to access the JSON data
		*******************************************************************************/
		SageJSON& operator[](std::string key);
		/*!****************************************************************************
		 \brief Subscript operator to access the JSON array. This function allow for the
		 data to be accessed in a similar manner to a map. The function will return the
		 value of the key in the JSON data.
		 \param key
			The index to access the JSON data
		*******************************************************************************/
		SageJSON& operator[](int key);

		SageJSON& operator[](std::string key) const;
		/*!****************************************************************************
		 \brief Allow streaming of string objects into the parser.

		 \param line
			The line of JSON data to be streamed into the parser.
		*******************************************************************************/
		SageJSON& operator<<(std::string line);


		/*!****************************************************************************
		 \brief Allow streaming of the input stream into the parser.
		 \param is
			The input stream to be streamed into the parser.
		*******************************************************************************/
		friend std::istream& operator>>(std::istream& is, SageJSON& json);
		/*!****************************************************************************
		 \brief Allow conversion of the data in AST into a JSON format and stream it out
		 to the output stream.
		 \param os
			The output stream.
		*******************************************************************************/
		friend std::ostream& operator<<(std::ostream& os, SageJSON& json);
		/*!****************************************************************************
		 \brief A function to check if the key exists
		*******************************************************************************/
		template <typename T>
		bool key_exists();
		/*!****************************************************************************
		 \brief A function to convert the JSON data into a primitive data type. This
		 allow it to be read naturally by the C++ program.
		 \tparam T the type of the data to be converted to.
		*******************************************************************************/
		template <typename T>
		T as();
		template <typename T>
		/*!****************************************************************************
		 \brief Set the AST node found to a value given by the user.
		 \tparam T the type of the data to be converted to.
		 \param value the value to be set to the AST node.
		*******************************************************************************/
		SageJSON& operator=(T const value);
		/*!****************************************************************************
		 \brief Get the AST of the JSON data.
		*******************************************************************************/
		AST::AST& getAST();
		/*!****************************************************************************
		 \brief Get the AST of the JSON data.
		*******************************************************************************/
		AST::AST const& getAST() const;

		size_t len();
		
	};
	template <typename T>
	bool SageJSON::key_exists()
	{
		try
		{
			if (!current_node)
			{
				throw std::invalid_argument("");
			}
			if (std::holds_alternative<T>(current_node->getKey()))
			{
				current_node = nullptr;
				return true;
			}
			else if (std::holds_alternative<std::reference_wrapper<T>>(current_node->getKey()))
			{
				current_node = nullptr;
				return true;
			}
			else
			{
				throw std::runtime_error("");
				current_node = nullptr;
				return false;
			}
		}
		catch (...)
		{
			current_node = nullptr;
			return false;
		}
	}

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

	template <typename T>
	SageJSON& SageJSON::operator=(T const value)
	{
		try
		{
			if (std::holds_alternative<T>(current_node->getKey()))
			{
				current_node->getKey() = value;
				current_node = nullptr;
			}
			else if (std::holds_alternative<std::reference_wrapper<T>>(current_node->getKey()))
			{
				std::get<std::reference_wrapper<T>>(current_node->getKey()).get() = value;
				current_node = nullptr;
			}
			else
			{
				throw std::runtime_error("Type mismatch");
			}
			return *this;
		}
		catch (std::runtime_error& e)
		{
			SageJSONCerr << "Warning: " << e.what() << '\n'  << " Variable is not converted to primitive data." << std::endl;
			current_node = nullptr;
			return *this;
		}
	}


	template <typename T>
	T SageJSON::SageJSONArrayProxy::as()
	{
		try {
			if (!current_node)
			{
				throw std::invalid_argument("No JSON Array found, are you sure the key is correct?");
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
			SageJSONCerr << "Warning: " << e.what() << " Variable is not converted to primitive data." << std::endl;
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


	template <typename T>
	T SageJSON::SageJSONObjectProxy::as()
	{
		try {
			if (!current_node)
			{
				throw std::invalid_argument("No JSON Array found, are you sure the key is correct?");
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
			SageJSONCerr << "Warning: " << e.what() << " Variable is not converted to primitive data." << std::endl;
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