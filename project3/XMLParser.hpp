#ifndef _XMLPARSER_HPP
#define _XMLPARSER_HPP

#include <string>
#include <vector>

#include "Bag.hpp"
#include "Stack.hpp"

/** enum definition for possible string token types. */
enum StringTokenType {START_TAG=1, END_TAG, EMPTY_TAG, CONTENT, DECLARATION};

/** TokenStruct definition. Used to store tokens and their corresponding types. */
struct TokenStruct 
{
	StringTokenType tokenType;
	std::string tokenString;
};

class XMLParser
{
private:
	/** Bag to store the XML element names. Uses the book's Bag implementation. */
	Bag<std::string> elementNameBag;
	/** Stack to store XML tag names while parsing. Uses your stack implementation. */
	Stack<std::string> parseStack;
	/** Vector to store the tokenized input string (token types and names) */
	std::vector<TokenStruct> tokenizedInputVector;
  
  // You can add or change the private fields.

public:
	/** The class constructor.
	 * @post Creates an instance of the class that can be used to tokenize and parse an input string . */
	XMLParser();

	// no custom destructor or copy, should not need dynamic memory

	/** Tokenizes the input string into XML markup and content. 
	 * Valid markup (tokens) are the characters included in a '<' '>' character delimiter pair.
	 * The delimiter pairs may not be nested, and tag names must not contain invalid characters 
	 * as outlined in the project description.
	 * @param inputString input string to be tokenized.
	 * @return  true if tokenization was successful (all valid tokens), or false if any invalid tokens or badly nested delimiters were found. 
	 * @post if successful, the input string is tokenized, the tokens are stored internally.  
	 * @post if unsuccessful (returns false), clears all internal data structures.*/
	bool tokenizeInputString(const std::string &inputString);

	/** Parses a valid tokenized string (stored internally after a successful call to tokenizeInputString)
	 * Valid XML satisfies the BPG discussed in the project description, where an opening brace is replaced with a start tag, 
	 * and the closing brace is replaced by the corresponding end tag. Must also follow rules for valid XML
	 * as outlined in the project description.
	 * @pre a successfully tokenized input string is stored internally.
	 * @return true if the tokenized string is valid XML, or false if any invalid XML formatting is found or tokenized string is empty. */
	bool parseTokenizedInput();

	/** Returns a vector containing the tokenized input string. 
	 * If no valid input has been tokenized, returns an empty vector. 
	 * The token strings corresponding to markup do not include the '<', '>', "<?", "?>", "</", and "/>" delimiters.
	 * @return A vector containing all the tokenized input as a vector of type "TokenStruct". */
	std::vector<TokenStruct> returnTokenizedInput() const;

	/** Determines if an element name is contained in the tokenized input string.
	 * Assumes both the tokenizeInputString() and parseTokenizedInput() methods have returned true; 
	 * throws a logic_error otherwise.
	 * @pre a valid XML input string has been tokenized and parsed 
	 * @param inputString the element name of interest (case sensitive!)
	 * @return true if the element name is in the valid XML, or false if not
	 * @throws std::logic_error if input has not been both tokenized and parsed */
	bool containsElementName(const std::string &inputString) const;

	/** Returns the number of times an element name is contained in the tokenized input string.
	 * Assumes both the tokenizeInputString() and parseTokenizedInput() methods have returned true; 
	 * throws a logic_error otherwise.
	 * @pre a valid XML input string has been tokenized and parsed 
	 * @param inputString the element name of interest (case sensitive!)
	 * @return an int representing the frequency of the element name in the valid XML string
	 * @throws std::logic_error if input has not been both tokenized and parsed */
	int frequencyElementName(const std::string &inputString) const;

	/** Clears the internal data structures for a instance of the class.
	 * @post All internal class data structures are empty */
	void clear();
};

#endif
